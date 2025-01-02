#include "DMainFrame.h"
#include <wx/wx.h>

class DLiteApp : public wxApp {
public:
  virtual bool OnInit();
};

wxIMPLEMENT_APP(DLiteApp);

bool DLiteApp::OnInit() {
  if (!wxApp::OnInit())
    return false;

  // 메인 프레임 생성
  DMainFrame *frame = new DMainFrame("DLite Download Manager");
  frame->Show(true);

  return true;
}
