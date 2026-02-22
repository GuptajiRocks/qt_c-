#include<wx/wxprec.h>

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include "three.h"

TextFrame::TextFrame(const wxChar *title, int xpos, int ypos, int width, int height) : wxFrame((wxFrame *) NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height))
{

}

TextFrame::~TextFrame() {}

