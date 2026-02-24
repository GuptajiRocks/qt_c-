#include "StatePanel.h"

wxBEGIN_EVENT_TABLE(StatePanel, wxPanel)
    EVT_PAINT(StatePanel::OnPaint)
wxEND_EVENT_TABLE()

StatePanel::StatePanel(wxWindow* parent)
    : wxPanel(parent)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void StatePanel::SetCurrentState(int state)
{
    currentState = state;
    Refresh(); // triggers redraw
}

void StatePanel::OnPaint(wxPaintEvent& evt)
{
    wxPaintDC dc(this);

    int radius = 30;

    for(int i = 0; i < 7; i++)
    {
        int x = 80 + i*100;
        int y = 100;

        if(i == currentState)
            dc.SetBrush(wxBrush(*wxGREEN));
        else
            dc.SetBrush(wxBrush(*wxLIGHT_GREY));

        dc.DrawCircle(x, y, radius);

        dc.DrawText(wxString::Format("%d", i), x-5, y-5);
    }
}
