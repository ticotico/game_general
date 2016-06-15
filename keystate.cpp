//取得滑鼠在視窗hWnd的座標，輸出mx和my
#include <windows.h>
void GetMousePos(HWND hWnd, int& mx, int& my)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	mx = pt.x;
	my = pt.y;
}
