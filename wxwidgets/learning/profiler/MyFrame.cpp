#include "MyFrame.h"
#include "StatePanel.h"

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Profiler MVP",
              wxDefaultPosition, wxSize(900, 400))
{
    wxPanel* root = new wxPanel(this);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // state panel
    statePanel = new StatePanel(root);
    sizer->Add(statePanel, 1, wxEXPAND | wxALL, 10);

    // buttons
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

    root->SetSizer(sizer);
}
