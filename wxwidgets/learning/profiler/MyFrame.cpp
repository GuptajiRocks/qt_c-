#include "MyFrame.h"
#include "StatePanel.h"
#include "CSVReader.h"

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Profiler MVP",
              wxDefaultPosition, wxSize(1000, 700))
    , playbackTimer(nullptr)
{
    CreateMenuBar();
    CreateControls();
}

MyFrame::~MyFrame()
{
    if(playbackTimer) {
        delete playbackTimer;
    }
}

void MyFrame::CreateControls()
{
    wxPanel* root = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // state panel
    statePanel = new StatePanel(root, &csvData);
    sizer->Add(statePanel, 1, wxEXPAND | wxALL, 10);

    // Timeline controls
    wxBoxSizer* timelineSizer = new wxBoxSizer(wxHORIZONTAL);
    
    // Play/Pause button
    playPauseBtn = new wxButton(root, wxID_ANY, "Play");
    playPauseBtn->Bind(wxEVT_BUTTON, &MyFrame::OnPlayPause, this);
    timelineSizer->Add(playPauseBtn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    
    // Timeline slider
    timelineSlider = new wxSlider(root, wxID_ANY, 0, 0, 100);
    timelineSlider->Bind(wxEVT_SLIDER, &MyFrame::OnSliderUpdate, this);
    timelineSizer->Add(timelineSlider, 1, wxEXPAND | wxALL, 5);
    
    sizer->Add(timelineSizer, 0, wxEXPAND | wxALL, 5);

    /* Commented out: State buttons
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

    for(int i=0;i<7;i++)
    {
        wxButton* btn = new wxButton(root, wxID_ANY,
            wxString::Format("State %d", i));

        btnSizer->Add(btn, 0, wxALL, 5);

        int index = i;
        btn->Bind(wxEVT_BUTTON, [this,index](wxCommandEvent&){
            statePanel->SetCurrentState(index);
        });
    }

    sizer->Add(btnSizer, 0, wxCENTER);
    */

    root->SetSizer(sizer);
}

void MyFrame::CreateMenuBar()
{
    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(wxID_OPEN, "&Load CSV\tCtrl+O", "Load state data from CSV file");
    fileMenu->Append(wxID_EXIT, "E&xit\tCtrl+Q", "Exit application");
    
    wxMenuBar* menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    
    SetMenuBar(menuBar);
    
    Bind(wxEVT_MENU, &MyFrame::OnLoadCSV, this, wxID_OPEN);
    Bind(wxEVT_MENU, [this](wxCommandEvent&) { Close(); }, wxID_EXIT);
}

void MyFrame::OnLoadCSV(wxCommandEvent& evt)
{
    wxFileDialog dlg(this, "Open CSV file", "", "",
        "CSV files (*.csv)|*.csv|All files (*.*)|*.*",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if(dlg.ShowModal() == wxID_OK) {
        // Stop playback if running
        if(playbackTimer && playbackTimer->IsRunning()) {
            playbackTimer->Stop();
            isPlaying = false;
            playPauseBtn->SetLabel("Play");
        }
        
        std::string filename = dlg.GetPath().ToStdString();
        
        if(CSVReader::read(filename, csvData)) {
            statePanel->SetCSVData(&csvData);
            
            // Setup slider range based on CSV timestamps
            if(csvData.getRecordCount() > 0) {
                long long minTime = csvData.getMinTimestamp();
                long long maxTime = csvData.getMaxTimestamp();
                long long duration = maxTime - minTime;
                
                // Convert to seconds for slider
                int maxSeconds = (duration / 1000) + 1;
                timelineSlider->SetMax(maxSeconds > 0 ? maxSeconds : 100);
                timelineSlider->SetValue(0);
            }
            
            currentTime = csvData.getMinTimestamp();
            UpdateStateFromTime();
            
            wxMessageBox("CSV loaded successfully!", "Success", wxOK | wxICON_INFORMATION);
        } else {
            wxMessageBox("Failed to load CSV file!", "Error", wxOK | wxICON_ERROR);
        }
    }
}

void MyFrame::OnPlayPause(wxCommandEvent& evt)
{
    if(!csvData.getRecordCount()) {
        wxMessageBox("Please load a CSV file first!", "No Data", wxOK | wxICON_WARNING);
        return;
    }
    
    if(!playbackTimer) {
        playbackTimer = new wxTimer(this);
        Bind(wxEVT_TIMER, &MyFrame::OnPlaybackTick, this);
    }
    
    if(!isPlaying) {
        // Start playback
        isPlaying = true;
        playPauseBtn->SetLabel("Pause");
        playbackTimer->Start(playbackSpeed); // Tick every 1 second
    } else {
        // Pause playback
        isPlaying = false;
        playPauseBtn->SetLabel("Play");
        playbackTimer->Stop();
    }
}

void MyFrame::OnPlaybackTick(wxTimerEvent& evt)
{
    if(!csvData.getRecordCount()) return;
    
    long long minTime = csvData.getMinTimestamp();
    long long maxTime = csvData.getMaxTimestamp();
    
    currentTime += 1000; // Advance by 1 second
    
    if(currentTime >= maxTime) {
        currentTime = maxTime;
        playbackTimer->Stop();
        isPlaying = false;
        playPauseBtn->SetLabel("Play");
    }
    
    // Update slider
    long long duration = maxTime - minTime;
    int sliderPos = (currentTime - minTime) / 1000; // Convert to seconds
    timelineSlider->SetValue(sliderPos);
    
    UpdateStateFromTime();
}

void MyFrame::OnSliderUpdate(wxCommandEvent& evt)
{
    if(!csvData.getRecordCount()) return;
    
    long long minTime = csvData.getMinTimestamp();
    int sliderValue = timelineSlider->GetValue();
    
    // Convert slider position back to timestamp
    currentTime = minTime + (sliderValue * 1000);
    
    UpdateStateFromTime();
}

void MyFrame::UpdateStateFromTime()
{
    if(!csvData.getRecordCount()) return;
    
    const auto& records = csvData.getRecords();
    
    // Find the state at current time
    int currentState = 0;
    long long cumulativeTime = csvData.getMinTimestamp();
    
    for(size_t i = 0; i < records.size(); i++) {
        long long stateDuration = (long long)(records[i].duration * 1000); // Convert to milliseconds
        long long stateEndTime = cumulativeTime + stateDuration;
        
        if(currentTime >= cumulativeTime && currentTime < stateEndTime) {
            currentState = records[i].state;
            break;
        }
        
        cumulativeTime = stateEndTime;
    }
    
    statePanel->SetCurrentState(currentState);
}
