#include "StatePanel.h"
#include <sstream>
#include <iomanip>

wxBEGIN_EVENT_TABLE(StatePanel, wxPanel)
    EVT_PAINT(StatePanel::OnPaint)
wxEND_EVENT_TABLE()

StatePanel::StatePanel(wxWindow* parent, CSVData* data)
    : wxPanel(parent), csvData(data)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void StatePanel::SetCurrentState(int state)
{
    currentState = state;
    Refresh(); // triggers redraw
}

void StatePanel::SetCSVData(CSVData* data)
{
    csvData = data;
    Refresh();
}

wxColor StatePanel::HexToWxColor(const std::string& hex)
{
    // Parse hex color like "#CCCCCC"
    std::string color = hex;
    if(!color.empty() && color[0] == '#') {
        color = color.substr(1);
    }
    
    if(color.length() != 6) {
        return *wxLIGHT_GREY; // fallback
    }
    
    try {
        unsigned long val = std::stoul(color, nullptr, 16);
        unsigned char r = (val >> 16) & 0xFF;
        unsigned char g = (val >> 8) & 0xFF;
        unsigned char b = val & 0xFF;
        return wxColor(r, g, b);
    } catch(...) {
        return *wxLIGHT_GREY;
    }
}

void StatePanel::OnPaint(wxPaintEvent& evt)
{
    wxPaintDC dc(this);
    dc.SetBackground(*wxWHITE);
    dc.Clear();

    int radius = 35;
    int numStates = 7;

    for(int i = 0; i < numStates; i++)
    {
        int x = 80 + i*115;
        int y = 100;

        // Get state info from CSV if available
        wxColor color = *wxLIGHT_GREY;
        wxString stateName = wxString::Format("State %d", i);

        if(csvData && i < (int)csvData->getRecords().size()) {
            const auto& records = csvData->getRecords();
            if(i < (int)records.size()) {
                color = HexToWxColor(records[i].color);
                stateName = records[i].stateName;
            }
        }

        // Highlight current state
        if(i == currentState) {
            dc.SetBrush(wxBrush(color));
            dc.SetPen(wxPen(*wxBLACK, 3)); // Bold border for current
        } else {
            // Dim non-current states
            color.Set(
                (color.Red() * 200) / 256,
                (color.Green() * 200) / 256,
                (color.Blue() * 200) / 256
            );
            dc.SetBrush(wxBrush(color));
            dc.SetPen(wxPen(wxColour(128, 128, 128), 1));
        }

        // Draw circle
        dc.DrawCircle(x, y, radius);

        // Draw state name
        dc.SetTextForeground(*wxBLACK);
        wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        dc.SetFont(font);
        
        wxSize textSize = dc.GetTextExtent(stateName);
        dc.DrawText(stateName, x - textSize.GetWidth()/2, y - textSize.GetHeight()/2 - 5);

        // Draw state index at bottom
        wxString indexStr = wxString::Format("%d", i);
        wxSize indexSize = dc.GetTextExtent(indexStr);
        dc.DrawText(indexStr, x - indexSize.GetWidth()/2, y - indexSize.GetHeight()/2 + 15);
    }
}
