#pragma once
#include<DirectXMath.h>
#include<Windows.h>
#include <DirectXTex.h>
#include <tchar.h>



class WinApp {

public:
	// �E�B���h�E�T�C�Y
	static const int kWindowWidth = 1280; // ����
	static const int kWindowHeight = 720; // �c��
	// �E�B���h�E�N���X��
	static const wchar_t kWindowClassName[];

	enum class SizeChangeMode {
		kNone,        //!< �T�C�Y�ύX�s��
		kNormal,      //!< ���R�ύX
		kFixedAspect, //!< �A�X�y�N�g����
	};

public://GetterSettter�o�^
	HINSTANCE GetHInstance() const { return wndClass_.hInstance; };
	HWND GetHwnd() const { return hwnd_; };
	

public://�֐��Q
	WinApp();
	void WinApiInitialize();

	void DebugOutputFormatString(const char* format, ...);
	static LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	bool ProcessMessage();

	void WinAppFinish();

private:
	

	WNDCLASSEX wndClass_{};
	RECT wrc;
	HWND hwnd_;
	MSG msg;
};