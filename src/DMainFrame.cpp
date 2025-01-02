#include "DMainFrame.h"

// wxWidgets 헤더는 보통 .cpp에서 포함
#include <wx/button.h>
#include <wx/listbox.h>
#include <wx/msgdlg.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>

wxBEGIN_EVENT_TABLE(DMainFrame, wxFrame)
    // 여기서 특정 ID에 대한 이벤트를 매핑할 수 있음 (Bind로 대체 가능)
    wxEND_EVENT_TABLE()

        DMainFrame::DMainFrame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(500, 300)) {
  // 패널 생성
  m_panel = new wxPanel(this, wxID_ANY);

  // UI 요소 생성
  m_urlInput =
      new wxTextCtrl(m_panel, wxID_ANY, "", wxDefaultPosition, wxSize(300, -1));
  m_addButton = new wxButton(m_panel, wxID_ANY, "Add");
  m_taskList = new wxListBox(m_panel, wxID_ANY);

  // Sizer (레이아웃)
  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *inputSizer = new wxBoxSizer(wxHORIZONTAL);

  inputSizer->Add(m_urlInput, 1, wxALL | wxEXPAND, 5);
  inputSizer->Add(m_addButton, 0, wxALL, 5);

  topSizer->Add(inputSizer, 0, wxEXPAND);
  topSizer->Add(m_taskList, 1, wxALL | wxEXPAND, 5);

  m_panel->SetSizer(topSizer);

  // 버튼 클릭 이벤트 바인딩
  m_addButton->Bind(wxEVT_BUTTON, &DMainFrame::OnAddTask, this);

  // 예) 다운로드 매니저 초기화
  // m_dman.Init();
}

DMainFrame::~DMainFrame() {
  // 예) 다운로드 매니저 정리
  // m_dman.Cleanup();
}

void DMainFrame::OnAddTask(wxCommandEvent &event) {
  wxString url = m_urlInput->GetValue();
  if (url.IsEmpty()) {
    wxMessageBox("URL is empty!", "Error", wxOK | wxICON_ERROR);
    return;
  }

  // 리스트에 URL 추가
  m_taskList->Append(url);

  // 실제 다운로드 추가 로직
  // m_dman.AddTask(std::string(url.mb_str()));

  // 입력 칸 초기화
  m_urlInput->SetValue("");
}
