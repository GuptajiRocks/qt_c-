#pragma once
#include <wx/wx.h>

class StatePanel : public wxPanel
{
public:
    StatePanel(wxWindow* parent);

    void SetCurrentState(int state);

private:
    int currentState = 0;

    void OnPaint(wxPaintEvent& evt);

    wxDECLARE_EVENT_TABLE();
};
