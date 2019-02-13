// playSoundShell.cpp
// basic playSound functions included here

#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#pragma comment(lib, "winmm.lib")

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Colors, brushes and fonts used.
COLORREF AquaBlue = RGB(51,255,204), yellow = RGB(255,255,102);
HBRUSH   AquaBluebr = CreateSolidBrush(AquaBlue);

HFONT sysfont=static_cast<HFONT>(GetStockObject(SYSTEM_FONT));

// sound clips used
LPCTSTR soundA = L"AudioClips\\GameOpen.wav";
LPCTSTR soundB = L"AudioClips\\gOneShot.wav";
LPCTSTR soundC = L"AudioClips\\rocketFire.wav";
LPCTSTR soundD = L"AudioClips\\airWrench.wav";
LPCTSTR soundE = L"AudioClips\\levelBK1.wav";
LPCTSTR soundF = L"AudioClips\\levelBK2.wav";
LPCTSTR soundG = L"AudioClips\\levelBK3.wav";

HDC hdc;
static HINSTANCE hInst;

int APIENTRY WinMain(HINSTANCE hinst,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
		HWND hwnd;
	MSG  lpmsg;
	WNDCLASSEX wc = {0};
	static wchar_t szAppName[] = L"playSoundShell.app";
	
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = szAppName;
	wc.hInstance = hinst;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wc.lpszMenuName = 0;
	wc.hbrBackground =  AquaBluebr;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	if( !RegisterClassEx (&wc) )
		return 0;

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,szAppName,L"playSoundShell",
		WS_OVERLAPPEDWINDOW,200,200,640,// started at 600
		480,NULL,NULL,hinst,NULL );

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&lpmsg,NULL,0,0) )
	{
		TranslateMessage(&lpmsg);
		DispatchMessage(&lpmsg);
	}//End Message Loop.

	return(lpmsg.wParam);
 	// TODO: Place code here.
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	
	PAINTSTRUCT ps;
	
	static POINTS pt,sz={300,300};
	RECT rect;
	char ch;
	int j=0;// for looping.
	
	switch(msg)
	{
		case WM_CREATE:			
			hInst = ((LPCREATESTRUCT) lParam) -> hInstance;
			return 0 ;

		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			ValidateRect(hwnd, NULL);
			GetClientRect (hwnd, &rect) ;
			TextOut(hdc, 100, 100, L"This is a project shell with working playSound calls", 52);
			EndPaint(hwnd, &ps);			
			return 0;
			
		case WM_CHAR:// Handles keyboard events.			
			ch = wParam;
			ch = tolower(ch);

			switch( ch )
			{
				case 'a':// non-looping clips
					PlaySound((LPCTSTR) soundA, NULL, SND_FILENAME | SND_ASYNC);
					break;
				case 'b':
					PlaySound((LPCTSTR) soundB, NULL, SND_FILENAME | SND_ASYNC);
					break;
				case 'c':
					PlaySound((LPCTSTR) soundC, NULL, SND_FILENAME | SND_ASYNC);
					break;
				case 'd':
					PlaySound((LPCTSTR) soundD, NULL, SND_FILENAME | SND_ASYNC);
					break;
				case 'e':// looping clips
					PlaySound((LPCTSTR) soundE, NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
					break;
				case 'f':
					PlaySound((LPCTSTR) soundF, NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
					break;
				case 'g':
					PlaySound((LPCTSTR) soundG, NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
					break;
				case 's':
					PlaySound(NULL, 0, 0);// stops playback of clip
					break;
				case VK_ESCAPE:// terminate app.					
					PostQuitMessage(0);
					break;
				default:
					break;
			}
			return 0;		

		case WM_DESTROY:			
			PostQuitMessage(0);
			break;		
		default:
			return( DefWindowProc(hwnd, msg, wParam, lParam) );
			break;
	}//End Switch on msg.
	return(0);
}//End CALLBACK.