#pragma once

#include <string>
// 필요한 헤더들 (ex: <thread>, <mutex>, <queue> 등)

class DMan {
public:
  // 생성자, 소멸자
  DMan();
  ~DMan();

  // 주요 메서드
  bool Init();                          // 다운로드 환경 초기화
  void Cleanup();                       // 자원 정리
  void AddTask(const std::string &url); // 다운로드 작업 추가

private:
  // 내부에서만 쓰는 메서드
  void WorkerThreadFunc();

  // 필요한 멤버 변수들
  bool m_stopFlag; // 멈춤 플래그
  // std::queue<std::string> m_taskQueue;  // 큐, 스레드, 뮤텍스 등
  // std::mutex m_queueMutex;
  // std::condition_variable m_cv;
  // std::thread m_workerThread;
};
