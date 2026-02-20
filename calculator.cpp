#include <windows.h>
#include <cstdio>

#define ID_NUM1 101
#define ID_NUM2 102
#define ID_PLUS   201
#define ID_MINUS  202
#define ID_TIME   203
#define ID_DIVIDE 204
/* This is where all the input to the window goes to */
HWND num1, num2, textfield, plus, minus, time, divide;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
		switch(Message) {

			case WM_CREATE:

				textfield = CreateWindow("STATIC","Please input two numbers",
					WS_VISIBLE|WS_CHILD|WS_BORDER,
					20,20,200,20,
					hwnd,NULL,NULL,NULL);

				num1 = CreateWindow("EDIT","",
					WS_VISIBLE|WS_CHILD|WS_BORDER,
					30,50,180,20,
					hwnd,(HMENU)ID_NUM1,NULL,NULL);

				num2 = CreateWindow("EDIT","",
					WS_VISIBLE|WS_CHILD|WS_BORDER,
					30,80,180,20,
					hwnd,(HMENU)ID_NUM2,NULL,NULL);

				plus = CreateWindow("BUTTON","+",
					WS_VISIBLE|WS_CHILD,
					45,120,30,25,
					hwnd,(HMENU)ID_PLUS,NULL,NULL);

				minus = CreateWindow("BUTTON","-",
					WS_VISIBLE|WS_CHILD,
					85,120,30,25,
					hwnd,(HMENU)ID_MINUS,NULL,NULL);

				time = CreateWindow("BUTTON","*",
					WS_VISIBLE|WS_CHILD,
					125,120,30,25,
					hwnd,(HMENU)ID_TIME,NULL,NULL);

				divide = CreateWindow("BUTTON","/",
					WS_VISIBLE|WS_CHILD,
					165,120,30,25,
					hwnd,(HMENU)ID_DIVIDE,NULL,NULL);

				break;

			case WM_COMMAND:
			{
				if (HIWORD(wParam) == BN_CLICKED)
				{
					int id = LOWORD(wParam);

					if (id == ID_PLUS || id == ID_MINUS ||
						id == ID_TIME || id == ID_DIVIDE)
					{
						char buffer1[50], buffer2[50];
						GetDlgItemText(hwnd, ID_NUM1, buffer1, 50);
						GetDlgItemText(hwnd, ID_NUM2, buffer2, 50);

						float f1 = atof(buffer1);
						float f2 = atof(buffer2);
						float result = 0;

						switch(id)
						{
						case ID_PLUS:
							result = f1 + f2;
							break;

						case ID_MINUS:
							result = f1 - f2;
							break;

						case ID_TIME:
							result = f1 * f2;
							break;

						case ID_DIVIDE:
							if (f2 == 0)
							{
								MessageBox(hwnd, "Cannot divide by zero",
										"Error", MB_OK);
								return 0;
							}
							result = f1 / f2;
							break;
						}

							char output[100];
							sprintf(output, "%f", result);
							MessageBox(hwnd, output, "Result", MB_OK);
						}
					}
					break;
				}
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}	

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(255,0,0));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"WindowClass",
		"My Calculator",
		WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,
		NULL,
		hInstance,
		NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
