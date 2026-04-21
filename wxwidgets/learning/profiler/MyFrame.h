#pragma once
#include <wx/wx.h>
#include "CSVData.h"

class StatePanel;

class MyFrame : public wxFrame
{
public:
    MyFrame();
    ~MyFrame();

private:
    StatePanel* statePanel;
    CSVData csvData;
    wxSlider* timelineSlider;
    wxButton* playPauseBtn;
    wxTimer* playbackTimer;
    bool isPlaying = false;
    long long currentTime = 0; // in milliseconds
    long long playbackSpeed = 1000; // 1 second per tick
    
    void OnLoadCSV(wxCommandEvent& evt);
    void OnPlayPause(wxCommandEvent& evt);
    void OnSliderUpdate(wxCommandEvent& evt);
    void OnPlaybackTick(wxTimerEvent& evt);
    void UpdateStateFromTime();
    void CreateMenuBar();
    void CreateControls();
};
