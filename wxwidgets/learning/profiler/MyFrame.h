#pragma once
#include <wx/wx.h>

class StatePanel;

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    StatePanel* statePanel;
};
