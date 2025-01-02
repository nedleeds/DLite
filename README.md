# DLite

Download manager program based on cpp.

## Directories

DMan/
├── CMakeLists.txt
├── include/
│ └── dman.h
├── src/
│ ├── dman.cpp
│ └── main.cpp
├── test/
│ └── test_dman.cpp
├── lib/
└── README.md

- include/ : 헤더(.h) 파일들 보
- test/ : 단위 테스트 관련 코드, 스크립트
- test_dman.cpp : Google Test 등이 들어갈 예시
- lib/ : 외부 라이브러리나 내부 static 라이브러리(예: libcurl 등) 모아두는 폴더
- main.cpp : 샘플 실행 파일(테스트 겸용) 진입점
