#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    bool OnInit() override
    {
        wxMessageBox(
            "Hello, wxWidgets!",
            "Welcome",
            wxOK | wxICON_INFORMATION
        );
        return false;  // exit after dialog
    }
};

wxIMPLEMENT_APP(MyApp);
