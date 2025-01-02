#include "dman.h"
#include <curl/curl.h>
#include <fstream>

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

// --------------------------------------------------------
// 간단히 파일에 다운로드하기 위한 콜백
static size_t WriteDataCallback(void *ptr, size_t size, size_t nmemb,
                                void *userdata) {
  std::ofstream *outStream = static_cast<std::ofstream *>(userdata);
  size_t totalBytes = size * nmemb;
  outStream->write(static_cast<char *>(ptr), totalBytes);
  return totalBytes;
}
// --------------------------------------------------------

DMan::DMan() : m_stopFlag(false) {}

DMan::~DMan() { Cleanup(); }

bool DMan::Init() {
  // libcurl 전역 초기화(멀티스레드 환경에서 안전하게 쓰려면 필요)
  curl_global_init(CURL_GLOBAL_DEFAULT);

  return true;
}

void DMan::Cleanup() {
  // 스레드 종료 등...
  curl_global_cleanup();
}

void DMan::AddTask(const std::string &url) {
  // 기존에 스레드 큐에 넣는 로직이라면, 아래처럼
  // m_taskQueue.push(url);
  // m_cv.notify_one();
  //
  // 여기서는 데모로, 일단 스레드가 아니라 즉시 다운로드 해볼 수도 있음:
  DownloadFile(url);
}

// [예시] 스레드에서 URL을 하나씩 꺼내 다운로드
void DMan::WorkerThreadFunc() {
  // while (true) {
  //   wait for a task ...
  //   DownloadFile(taskUrl);
  // }
}

// 실제 다운로드 로직 (간단 버전)
bool DMan::DownloadFile(const std::string &url) {
  // 임시로 "downloaded_file"라는 이름으로 저장
  // 실제로는 URL에서 파일명 파싱하거나, 사용자 지정 경로 쓰면 됨
  const std::string filename = "downloaded_file";

  std::ofstream outFile(filename, std::ios::binary);
  if (!outFile) {
    std::cerr << "[DMan] Failed to open file for writing: " << filename
              << std::endl;
    return false;
  }

  // curl handle 생성
  CURL *curlHandle = curl_easy_init();
  if (!curlHandle) {
    std::cerr << "[DMan] curl_easy_init failed" << std::endl;
    return false;
  }

  curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, WriteDataCallback);
  curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &outFile);

  // HTTPS 인증서 문제 회피(시연용)
  curl_easy_setopt(curlHandle, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curlHandle, CURLOPT_SSL_VERIFYHOST, 0L);

  CURLcode res = curl_easy_perform(curlHandle);
  if (res != CURLE_OK) {
    std::cerr << "[DMan] Download error: " << curl_easy_strerror(res)
              << std::endl;
    curl_easy_cleanup(curlHandle);
    return false;
  }

  std::cout << "[DMan] Downloaded: " << url << " => " << filename << std::endl;

  // 정리
  curl_easy_cleanup(curlHandle);
  outFile.close();
  return true;
}
