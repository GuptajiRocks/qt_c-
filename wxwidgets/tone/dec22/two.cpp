#include <wx/wx.h>


class MyFrame : public wxFrame {
	public:
		MyFrame();
	private:
		void OnHello(wxCommandEvent& event);
		void OnExit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
};

class MyApp : public wxApp {
	public:
		bool OnInit() override;
};

bool MyApp :: OnInit() {
	MyFrame *frame = new MyFrame();
	frame->Show(true);
	return true;
}

wxIMPLEMENT_APP(MyApp);

