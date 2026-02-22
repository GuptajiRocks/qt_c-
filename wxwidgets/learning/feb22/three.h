#ifndef _TEXTFRAME_H
#define _TEXTFRAME_H

class TextFrame : public wxFrame
{
  public:
    TextFrame(const wxChar *title, int xpos, int ypos, int width, int height);

    ~TextFrame();
};

#endif
