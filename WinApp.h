#pragma once
#include<DirectXMath.h>
#include<Windows.h>
#include <DirectXTex.h>
#include <tchar.h>



class WinApp {

public:
	static WinApp* GetInstance();

	// �E�B���h�E�T�C�Y
	static const int window_width = 1280; // ����
	static const int window_height = 720; // �c��

	
public://�ÓI�����o�֐�
	static LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public:
	//�֐��Q
	void WinApiInitialize();

	void DebugOutputFormatString(const char* format, ...);
	bool ProcessMessage();
	void Finalize();

	//Getter�o�^
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