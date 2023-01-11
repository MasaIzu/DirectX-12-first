#pragma once
#include<Windows.h>
#include <cstdint>

class WinApp
{
public:
	// ウィンドウサイズ
	const int window_width = 1280; // 横幅
	const int window_height = 720; // 縦幅

public: // 静的メンバ関数
	/// <summary>
	/// ウィンドウプロシージャ
	/// </summary>
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public://メンバ関数
	void MakeWindow(std::wstring title);
	bool ProcessMessage();
	void DeleteGameWindow();


public://GetterSetter

	HWND Gethwnd() { return hwnd; }

private://メンバ変数

	WNDCLASSEX w{};
	HWND hwnd;

};

