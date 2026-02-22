class AppFrame : public wxFrame {
  wxRect DetermineFrameSize();
};

AppFrame :: AppFrame {
  SetSize (DetermineFrameSize());
}

wxRect AppFrame : DetermineFrameSize () {
}

