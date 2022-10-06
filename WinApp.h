#pragma once
#include<DirectXMath.h>
#include<Windows.h>
#include <DirectXTex.h>
#include <tchar.h>



class WinApp {

public:
	static WinApp* GetInstance();

	// ウィンドウサイズ
	static const int window_width = 1280; // 横幅
	static const int window_height = 720; // 縦幅

	
public://静的メンバ関数
	static LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:
	//関数群
	void WinApiInitialize();

	void DebugOutputFormatString(const char* format, ...);
	bool ProcessMessage();
	void Finalize();

	//Getter登録
	HWND GetHwnd() const { return hwnd_; }
	HINSTANCE GetHInstance() const { return w_.hInstance; }

private:
	WinApp();
	~WinApp();

private:
	

	WNDCLASSEX w_{};
	RECT wrc;
	HWND hwnd_ = nullptr;
	MSG msg;
};