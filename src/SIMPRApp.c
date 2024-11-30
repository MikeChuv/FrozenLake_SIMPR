// SIMPRApp.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "SIMPRApp.h"

#include "app.h"


#include <SFML/Audio.h>
#include <SFML/Graphics.h>



#define MAX_LOADSTRING 100
#define MAX_PATH_LEN 512

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
WCHAR szCurrentDir[MAX_PATH_LEN];


tApp appInstance = {0};


// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.
    pApp app = &appInstance;

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SIMPRAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    if (!AppInit(app)) {
        return FALSE;
    }

    //GetCurrentDirectory(MAX_PATH_LEN, szCurrentDir);
    //printf("Current dir: %s\n", szCurrentDir);


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPRAPP));

    MSG msg = {0};

    sfEvent event;
    while (sfRenderWindow_isOpen(app->sfMainWindow))
    {
        // Process events
        while (sfRenderWindow_pollEvent(app->sfMainWindow, &event))
        {
            // Close window : exit
            if (event.type == sfEvtClosed) {
                PostMessage(app->winapiMainWindow, WM_QUIT, 0, 0);
                sfRenderWindow_close(app->sfMainWindow);
            }
        }

        if (GetMessage(&msg, NULL, 0, 0)) {
            printf("Got message: %u\n", msg.message);
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            AppProcessWinMessage(app, &msg);

        } else {
            printf("CLOSE\n");
        }

        if (HeroHoleReached(app->hero)) { 
            printf("HOLE REACHED\n"); 
            HeroGoToStart(app->hero);
        }
        if (HeroGoalReached(app->hero)) { 
            printf("GOAL REACHED\n"); 
            HeroGoToStart(app->hero);
        }

        AppRedraw(app);

    }


    printf("Program exited on message: %u, %d\n", msg.message, (int)msg.wParam);

    AppDestroy(app);

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    //wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SIMPRAPP));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SIMPRAPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    pApp app = &appInstance;
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    app->winapiMainWindow = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!app->winapiMainWindow)
    {
        return FALSE;
    }

    // ShowWindow(app->winapiMainWindow, nCmdShow);
    // UpdateWindow(app->winapiMainWindow);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    pApp app = &appInstance;
    switch (message)
    {
    case WM_CREATE: 
    {
        break;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_STOP:
                break;
            case ID_START:
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        if (message == app->interpreter.conditionMessage) {
            tResult res = InterpreterProcessConditionsMessage(&app->interpreter, wParam, lParam);
            return (LRESULT)res;
        } else if (message == app->interpreter.actionMessage) {
            tResult res = InterpreterProcessActionsMessage(&app->interpreter, wParam, lParam);
			AppRedraw(app);
            Sleep(ENV_ACTION_DELAY);
            return (LRESULT)res;
        }
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}





// Обработчик сообщений для окна "О программе".
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
