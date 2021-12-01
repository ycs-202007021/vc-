// WindowsProject4.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject4.h"
#include <stdlib.h>     // 랜덤 값 획득 함수 호출
#include <time.h>       // SEED 값 조절을 위해 현재 시간 값 이용

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT4));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT4));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT4);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

HWND g_hWnd;
int x = 0, y = 0;

//hMenu를 위한 ID 값 선언
#define IDM_BTN_CLICK	999
RECT g_me;
RECT g_map[1000];

// 상대의 속도를 가질 변수
int g_speed;

// 점수
int g_score;

// 타이머
int g_timer;  
// 타이머 아이디를 선언
#define TIMER_ID_1          1 
#define TIMER_ID_2          2
RECT g_small;
int i;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WCHAR mmsg[128] = { 0, };
    switch (message)
    {
        //버튼 이벤트 ID 확인 메세지
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다: 버튼 클릭시 ID 확인 가능한 위치
		
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_CREATE:
		HDC hdc;
		srand(time(NULL));
		MoveWindow(hWnd, 0, 0, 1000, 1000, true); 
		 for (int i = 0; i < 100; i++) {
			if (i == 0) {
				g_map[0].left = -600;
				g_map[0].top = -3300;
				g_map[0].right = g_map[0].left + 40;
				g_map[0].bottom = g_map[i].top + 40;
			}
			else if(i < 5){ // 4개
				g_map[i].left = g_map[i - 1].left + 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (5 < i && i < 10) { //4개
				g_map[i].left = g_map[i - 1].left - 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (10 < i && i < 15) {
				g_map[i].left = g_map[i - 1].left + 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;

			}
			else if (15< i && i < 20) {
				g_map[i].left = g_map[i - 1].left - 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (20 < i && i < 25) {
				g_map[i].left = g_map[i - 1].left - 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (25 < i && i < 30) {
				g_map[i].left = g_map[i - 1].left + 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (30 < i && i < 35) {
				g_map[i].left = g_map[i - 1].left - 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (35 < i && i < 40) {
				g_map[i].left = g_map[i - 1].left + 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (40 < i && i < 45) {
				g_map[i].left = g_map[i - 1].left + 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (45 < i && i < 50) {
				g_map[i].left = g_map[i - 1].left - 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (50 < i && i < 55) {
				g_map[i].left = g_map[i - 1].left + 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (55 < i && i < 60) {
				g_map[i].left = g_map[i - 1].left - 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (65 < i && i < 70) {
				g_map[i].left = g_map[i - 1].left - 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (70 < i && i < 75) {
				g_map[i].left = g_map[i - 1].left + 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (75 < i && i < 80) {
				g_map[i].left = g_map[i - 1].left - 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (80 < i && i < 85) {
				g_map[i].left = g_map[i - 1].left + 40;
				g_map[i].top = g_map[i - 1].top + 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			else if (85 < i && i < 90) {
			g_map[i].left = g_map[i - 1].left - 40;
			g_map[i].top = g_map[i - 1].top + 40;
			g_map[i].right = g_map[i].left + 40;
			g_map[i].bottom = g_map[i].top + 40;
			}
			else if (90 < i && i < 95) {
			g_map[i].left = g_map[i - 1].left + 40;
			g_map[i].top = g_map[i - 1].top + 40;
			g_map[i].right = g_map[i].left + 40;
			g_map[i].bottom = g_map[i].top + 40;
			}
			else {
			g_map[i].left = g_map[i - 1].left + 40;
			g_map[i].top = g_map[i - 1].top + 40;
			g_map[i].right = g_map[i].left + 40;
			g_map[i].bottom = g_map[i].top + 40;
			}

			g_me.left = g_map[i].left;
			g_me.top = g_map[i].top-40;
			g_me.right = g_me.left + 40;
			g_me.bottom = g_me.top + 40;

			g_small.left = g_me.left;
			g_small.top = g_me.top +40;
			g_small.right = g_small.left + 40;
			g_small.bottom = g_small.top + 30;
			

		}
		g_speed = 1000;
		// 타이머를 기동 --> 주기적으로 WM_TIMER를 OS가 호출해준다.
		SetTimer(hWnd, TIMER_ID_1, g_speed, NULL);

		// 게임 타이머 시간 설정. 무조건 1초에 한번씩만 불려야 함
		g_timer = 20;       // 제한 시간 30초
		SetTimer(hWnd, TIMER_ID_2, 1000, NULL);
		break;
      
     
    case WM_TIMER:
    {
        int i = 0;
        RECT dst;       // 겹침 영역의 좌표를 획득

        // WM_TIMER 메시지는 wParam에 SetTimer에서 설정한 ID 값이 넘겨져 온다!
        switch (wParam)
        {
			//교수님 보고잇다면 정답을알려주!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//case TIMER_ID_1:
		//	for (int i = 0; i < 100; i++) {
		//		if (FALSE == IntersectRect(&dst, &g_small, &g_map[i])) {  // 좌표 겹침이 없다면
		//			KillTimer(hWnd, TIMER_ID_1);
		//			KillTimer(hWnd, TIMER_ID_2);
		//			MessageBox(hWnd, L"아이고.. 떨어져부럿네... ", L"실패", MB_OK);
		//			return 0;
		//		}
		//	}
			break;
			
		case TIMER_ID_2:
			g_timer--;
			if (0 == g_timer)
			{
				KillTimer(hWnd, TIMER_ID_1);
				KillTimer(hWnd, TIMER_ID_2);
				MessageBox(hWnd, L"시간으로 종료", L"게임오버", MB_OK);
			}

			break;
		}
		// 화면 무효화
		InvalidateRect(hWnd, NULL, TRUE);
	}
	break;

    case WM_KEYDOWN:
    {
        RECT dst;

		switch (wParam)
		{
			// 좌, 상, 우, 하 키가 입력되었는지 확인
		case VK_LEFT:   // x 좌표의 이동 (left, right) -> 감소
			for (int i = 0; i < 100; i++) {
				g_map[i].left += 40;
				g_map[i].top += 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
				
			}
			g_score++;
			
			break;

		case VK_RIGHT:  // x 좌표의 이동 (left, right) -> 증가
			for (int i = 0; i < 100; i++) {
				g_map[i].left -= 40;
				g_map[i].top += 40;
				g_map[i].right = g_map[i].left + 40;
				g_map[i].bottom = g_map[i].top + 40;
			}
			g_score++;
			break;
	
		}
        InvalidateRect(hWnd, NULL, TRUE);
    }
	break;
	
    case WM_PAINT:
    {
		RECT dst;
		//MessageBox(hWnd, L"시작!", L"25초만에 끝까지 올라가보세요! :)", MB_OK);
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
		WCHAR score[64] = { 0, };
		
		for (int i = 0; i < 100; i++) {
			Rectangle(hdc, g_map[i].left, g_map[i].top, g_map[i].right, g_map[i].bottom);
		}
		
		
        Ellipse(hdc, g_me.left, g_me.top, g_me.right, g_me.bottom); 
		Rectangle(hdc, g_small.left, g_small.top, g_small.right, g_small.bottom);
		wsprintfW(score, L"계단수 : %d\t Timer: %d", g_score, g_timer);
		TextOut(hdc, 10, 500, score, lstrlenW(score));


		if (g_score==99)
		{
		KillTimer(hWnd, TIMER_ID_1);
		KillTimer(hWnd, TIMER_ID_2);
		MessageBox(hWnd, L"이기셨어요!!", L"성공", MB_OK);
		}

		
		EndPaint(hWnd, &ps);
        }
		
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


