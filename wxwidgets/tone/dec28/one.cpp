#include <wx/wx.h>

class DerivedApp : public wxApp
{
public:
    virtual bool OnInit() override;
};
 
wxIMPLEMENT_APP(DerivedApp);

enum {
	ID_MYFRAME = 1
};

class MyFrame : public wxFrame {
};


