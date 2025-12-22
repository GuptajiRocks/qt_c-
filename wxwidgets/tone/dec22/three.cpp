#include <wx/wx.h>

class MyApp : public wxApp {
	public:
		bool OnInit() override;
};

bool MyApp::OnInit() {
	wxFrame *frame = new wxFrame(NULL, wxID_ANY, "My First GUI", wxPoint(50, 50), wxSize(450, 340));
	frame->Show(true);
	return true;
}

wxIMPLEMENT_APP(MyApp);

