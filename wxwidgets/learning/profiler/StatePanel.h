#pragma once
#include <wx/wx.h>
#include "CSVData.h"

class StatePanel : public wxPanel
{
public:
    StatePanel(wxWindow* parent, CSVData* data = nullptr);

    void SetCurrentState(int state);
    void SetCSVData(CSVData* data);

private:
    int currentState = 0;
    CSVData* csvData = nullptr;

    void OnPaint(wxPaintEvent& evt);
    wxColor HexToWxColor(const std::string& hex);

    wxDECLARE_EVENT_TABLE();
};
