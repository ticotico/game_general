/*
 紀錄按鍵的狀態 
 KeyState 和 KeyContinous 在使用前都要先 init()
 接著以 Test() 測試並記錄目前鍵盤的狀態 
 KeyState 有三種狀態
 1.現在是否壓著
 2.現在是否為壓下按鍵的瞬間
 3.現在是否為放開按鍵的瞬間 
 KeyContinius 繼承了 KeyState的所有功能(無改寫)
 與 KeyState 相同，必須不斷用 Test() 更新狀態 
 另外新增了按鍵是否連續按超過 tContinous 秒 
 */

//105/05/07 完成keystate.h
//105/05/27 加入GetMousePos
//105/06/15 移除 KeyContinuous::isContinuous(DWORD tContinous) 
//			中，壓下去瞬間也回傳true的判定 
#ifndef KEYSTATE_H
#define KEYSTATE_H
class KeyState {
private:
	int key;		//按鍵編號
	bool pre_press;	//上一次按鍵狀態
	bool cur_press;	//這一次按鍵狀態
public:
	KeyState() : key(VK_SPACE) { init(); }
	KeyState(int _key) : key(_key) { init(); }
	void init()
	{
		pre_press = FALSE;
		cur_press = FALSE;
	}
	void SetKey(int _key) { key = _key; }
	//測試並記錄按鍵目前的狀態
	void Test()
	{
		pre_press = cur_press;
		cur_press = (GetAsyncKeyState(key) < 0);
	}
	//測試時是否為按鍵壓下去的瞬間
	bool IsPressDownMoment()
	{return (pre_press == FALSE && cur_press == TRUE);}
	//測試時是否為按鍵放開的瞬間
	bool IsReleaseMoment()
	{return (pre_press == TRUE && cur_press == FALSE);}
	//測試時是否壓著按鍵
	bool IsPressNow()
	{return cur_press;}
};

class KeyContinuous : public KeyState {
private:
	DWORD prev_t;		//上一次檢查按鍵狀態的時間
	DWORD cur_t;		//這一次檢查按鍵狀態的時間
public:
	KeyContinuous() { init(); }
	KeyContinuous(int k) { init(); SetKey(k); }
	void init()
	{
		prev_t = GetTickCount();
		cur_t = prev_t;
	}
	//回傳按鍵是否連續按下的狀態超過 t (ms) 
	bool isContinuous(DWORD tContinous)
	{
		if (!IsPressNow()) return FALSE;
		cur_t = GetTickCount();

		if (cur_t - prev_t >= tContinous) {
			prev_t += tContinous;
			return TRUE;
		}
		else return FALSE;
	}


};

//取得滑鼠在視窗hWnd的座標，輸出mx和my
void GetMousePos(HWND hWnd, int& mx, int& my);
#endif
