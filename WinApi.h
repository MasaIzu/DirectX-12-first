#pragma once
#include<DirectXMath.h>
#include<Windows.h>
#include <DirectXTex.h>
#include <tchar.h>



class WinApi {

public:
	WinApi();
	void WinApiInitialize();

	void DebugOutputFormatString(const char* format, ...);
	static LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	WNDCLASSEX W();
	HWND Hwnd();
	MSG Msg();
	int Window_width();
	int Window_height();

	void Updata();
private:
	// �E�B���h�E����
	const int window_width = 1280;
	// �E�B���h�E�c��
	const int window_height = 720;

	WNDCLASSEX w;
	RECT wrc;
	HWND hwnd;
	MSG msg;
};