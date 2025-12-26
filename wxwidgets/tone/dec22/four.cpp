#include <wx/wx.h>

class MyApp : public wxApp {
	public:
		bool OnInit() {
			wxFrame *frame = new wxFrame(NULL, wxID_ANY, "Hello GUI", wxPoint(50, 50),  wxSize(1920, 1080));
			frame->Show(true);
			return true;
		}
};

wxIMPLEMENT_APP(MyApp);
