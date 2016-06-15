/*
 fps物件: 
 在無窮迴圈中使用 counter() 做記數
 以getDur回傳最後一個和倒數第二個counter的時間差
 以getFPS回傳一秒之內一個迴圈中counter 執行了幾次 
 */
#ifndef FPS_H
#define FPS_H
#include <windows.h>
#include <stdio.h>
class FPS {
private:
	enum { ONE_SEC = 1000 }; //GetTickCount()的計算單位為毫秒，故 1000 為一秒 
	DWORD start, last, cur;	//GetTickCount() 的存放值
	int count;				//紀錄在一個迴圈中 counter()執行了幾次 
	int fps;				//迴圈每秒實際執行的次數 
public:
	//建構式
	FPS() { last = cur = start = GetTickCount(); count = 0; fps = 0; }
	//放在迴圈中，計算每秒執行了幾次這個迴圈
	void counter() {
		last = cur;
		cur = GetTickCount();
		count++;
		if (cur - start >= ONE_SEC) {
			fps = count;
			count = 0;
			start += ONE_SEC;
		}
	}
	//回傳fps
	int getFPS() const { return fps; }
	//計算執行兩次 counter 所經過的時間
	DWORD getDur() const { return cur - last; }
	//在hdc上顯示fps
	void draw(HDC& hdc, int x, int y) {
		char fps_char[12];
		sprintf(fps_char, "fps:%d", fps);
		TextOut(hdc, x, y, fps_char, strlen(fps_char));
	}
};
#endif
