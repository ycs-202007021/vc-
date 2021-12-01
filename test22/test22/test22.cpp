// test22.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "test22.h"
#include <stdlib.h>     // 랜덤 값 획득 함수 호출
#include <time.h>       // SEED 값 조절을 위해 현재 시간 값 이용
#include <Windows.h>

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
    LoadStringW(hInstance, IDC_TEST22, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST22));

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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST22));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEST22);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
RECT g_me;
RECT map[57][9] =
{ 0, };
RECT g_map[100] = { 0, };
int x=150, y=80;
int a = 120; //첫 rect left 값에 + 40한 값
int b = 760;

int g_speed;
int g_score;

// 타이머
int g_timer;

// 타이머 아이디를 선언
#define TIMER_ID_1          1 
#define TIMER_ID_2          2

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
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
		MoveWindow(hWnd, 0, 0, 1000, 1000, true);
		srand(time(NULL));
		HDC hdc;
		g_me.left = a;
		g_me.top = b;
		g_me.right = g_me.left+40;
		g_me.bottom = g_me.top+40;
		
		g_map[0].left = 160;
		g_map[0].top = 0;
		g_map[0].right = g_map[0].left + 40;
		g_map[0].bottom = g_map[0].top + 40;

		for (int i = 0; i < 100; i++) {
			g_map[i].left = g_map[i-1].left + 40;
			g_map[i].top = g_map[i-1].top + 40;
			g_map[i].right = g_map[i].left + 40;
			g_map[i].bottom = g_map[i].top + 40;
		}

		g_speed = 1000;
		// 타이머를 기동 --> 주기적으로 WM_TIMER를 OS가 호출해준다.
		SetTimer(hWnd, TIMER_ID_1, g_speed, NULL);

		// 게임 타이머 시간 설정. 무조건 1초에 한번씩만 불려야 함
		g_timer = 10;       // 제한 시간 10초
		SetTimer(hWnd, TIMER_ID_2, 1000, NULL);
		break;
		
	case WM_TIMER:
	{
		int i = 0;
		RECT dst;       // 겹침 영역의 좌표를 획득

		// WM_TIMER 메시지는 wParam에 SetTimer에서 설정한 ID 값이 넘겨져 온다!
		switch (wParam)
		{
			// 상대가 주기적으로 이동하는 타이머가 도착했다!
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
		case VK_LEFT:    // x 좌표의 이동 (left, right) -> 감소
			g_me.left -= 40;
			g_me.top -= 40;
			g_me.right -= 40;
			g_me.bottom -= 40;
			g_score += 100;
			
			break;
		case VK_RIGHT: // x 좌표의 이동 (left, right) -> 증가
			g_me.left += 40;
			g_me.top -= 40;
			g_me.right += 40;
			g_me.bottom -= 40;
			g_score += 100;
			
			break;
		
		}
		InvalidateRect(hWnd, NULL, TRUE);
	}
	break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			WCHAR score[64] = { 0, };
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
			/*for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 9; j++) {
					Rectangle(hdc, map[i][j].left, map[i][j].top, map[i][j].right, map[i][j].bottom);
				}

			}*/
			//스테이지 1 맵 
			
			//Rectangle(hdc, 160, 0, 200, 40);
			//Rectangle(hdc, 200, 40, 240, 80);
			//Rectangle(hdc, 240, 80, 280, 120);
			//Rectangle(hdc, 200, 120, 240, 160);
			//Rectangle(hdc, 160, 160, 200, 200);
			//Rectangle(hdc, 120, 200, 160, 240);
			//Rectangle(hdc, 80, 240, 120, 280);
			//Rectangle(hdc, 40, 280, 80, 320);
			//Rectangle(hdc, 80, 320, 120, 360);
			//Rectangle(hdc, 120, 360, 160, 400);
			//Rectangle(hdc, 160, 400, 200, 440);
			//Rectangle(hdc, 200, 440, 240, 480);
			//Rectangle(hdc, 240, 480, 280, 520);
			//Rectangle(hdc, 200, 520, 240, 560);
			//Rectangle(hdc, 160, 560, 200, 600);
			//Rectangle(hdc, 200, 600, 240, 640);
			//Rectangle(hdc, 160, 640, 200, 680);
			//Rectangle(hdc, 120, 680, 160, 720);
			//Rectangle(hdc, 160, 720, 200, 760);
			//Rectangle(hdc, 200, 760, 240, 800);
		
			////스테이지 2 맵 출력 원 left 값 맨 밑 rect.left 값에 +40
			//
			//Rectangle(hdc, 120, 800, 160, 840);
			//Rectangle(hdc, 160, 840, 200, 880);
			//Rectangle(hdc, 200, 880, 240, 920);
			//Rectangle(hdc, 240, 920, 280, 960);
			//Rectangle(hdc, 200, 960, 240, 1000);
			//Rectangle(hdc, 240, 1000, 280, 1040);
			//Rectangle(hdc, 200, 1040, 240, 1080);
			//Rectangle(hdc, 160, 1080, 200, 1120);
			//Rectangle(hdc, 120, 1120, 160, 1160);
			//Rectangle(hdc, 160, 1160, 200, 1200);
			//Rectangle(hdc, 200, 1200, 240, 1240);
			//Rectangle(hdc, 240, 1240, 280, 1280);
			//Rectangle(hdc, 200, 1280, 240, 1320);
			//Rectangle(hdc, 160, 1320, 200, 1360);
			//Rectangle(hdc, 120, 1360, 160, 1400);
			//Rectangle(hdc, 80, 1400, 120, 1440);
			//Rectangle(hdc, 120, 1440, 160, 1480);
			//Rectangle(hdc, 80, 1480, 120, 1520);
			//Rectangle(hdc, 120, 1520, 160, 1560);
			//Rectangle(hdc, 80, 1560, 120, 1600);
			//
		
			//Rectangle(hdc, 80,1600,120,1640);
			//Rectangle(hdc, 120,1640,160,1680);
			//Rectangle(hdc, 160,1680,200,1720);
			//Rectangle(hdc, 200,1720,240,1760);
			//Rectangle(hdc, 160,1760,200,1800);
			//Rectangle(hdc, 120,1800,160,1840);
			//Rectangle(hdc, 160,1840,200,1880);
			//Rectangle(hdc, 120,1880,160,1920);
			//Rectangle(hdc, 80,1920,120,1960);
			//Rectangle(hdc, 40,1960,80,2000);
			//Rectangle(hdc, 80,2000,120,2040);
			//Rectangle(hdc, 120,2040,160,2080);
			//Rectangle(hdc, 160,2080,200,2120);
			//Rectangle(hdc, 200,2120,240,2160);
			//Rectangle(hdc, 240,2160,280,2200);
			//Rectangle(hdc, 200,2200,240, 2240);
			//Rectangle(hdc, 160,2240,200,2280);
			//Rectangle(hdc, 200,2280,240,2320);
			//Rectangle(hdc, 240,2320,280,2360);
			//Rectangle(hdc, 280,2360,320,2400);
			
			//나 출력
			Ellipse(hdc, g_me.left, g_me.top, g_me.right, g_me.bottom);
			
			wsprintfW(score, L"Score : %d\t Timer: %d", g_score, g_timer);
			TextOut(hdc, 10, 500, score, lstrlenW(score));
			if (g_me.left == 160 && g_me.top == -40 && g_me.right == 200 && g_me.bottom == 0) {
				KillTimer(hWnd, TIMER_ID_1);
				KillTimer(hWnd, TIMER_ID_2);
				MessageBox(hWnd, L"1라운드 통과하셨습니다!", L"통과!", MB_OK);
				
				return 0;
			}
			if (g_me.left == 120 && g_me.top == -40 && g_me.right == 160 && g_me.bottom == 0) {
				KillTimer(hWnd, TIMER_ID_1);
				KillTimer(hWnd, TIMER_ID_2);
				MessageBox(hWnd, L"2라운드 통과하셨습니다!", L"통과!",  MB_OK);

				return 0;
			}
			if (g_me.left == 80 && g_me.top == -40 && g_me.right == 120 && g_me.bottom == 0) {
				KillTimer(hWnd, TIMER_ID_1);
				KillTimer(hWnd, TIMER_ID_2);
				MessageBox(hWnd, L"모든 라운드를 통과!", L"수고하셨습니다 :)", MB_OK);

				return 0;
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
