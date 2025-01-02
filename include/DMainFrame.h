#pragma once

#include <wx/frame.h>

// (선택) 다운로드 매니저 포함 필요 시
// #include "dman.h"

// 전방 선언(Forward Declarations)
// wxWidgets 클래스들을 미리 선언해두면, 헤더 내에서 불필요한 헤더 포함을 줄일
// 수 있음
class wxPanel;
class wxTextCtrl;
class wxButton;
class wxListBox;
class wxCommandEvent;

class DMainFrame : public wxFrame {
public:
  // 생성자
  DMainFrame(const wxString &title);
  // 소멸자 (필요 시)
  ~DMainFrame();

private:
  // UI 구성 요소
  wxPanel *m_panel;       // 전체를 감싸는 패널
  wxTextCtrl *m_urlInput; // URL 입력 필드
  wxButton *m_addButton;  // "Add" 버튼
  wxListBox *m_taskList;  // 등록된 다운로드 리스트 표시

  // 다운로드 매니저(멀티스레드 로직)와의 연동을 고려한다면 멤버로 둘 수도 있음
  // DMan m_dman;

private:
  // 이벤트 핸들러
  void OnAddTask(wxCommandEvent &event);

  // wxWidgets 이벤트 테이블 매크로
  wxDECLARE_EVENT_TABLE();
};
