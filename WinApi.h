#pragma once
#include<DirectXMath.h>
#include<Windows.h>
#include <DirectXTex.h>
#include <tchar.h>



class WinApi {

public:
	WinApi();

	void DebugOutputFormatString(const char* format, ...);
	LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	// ウィンドウ横幅
	const int window_width = 1280;
	// ウィンドウ縦幅
	const int window_height = 720;


};