#pragma once
#include<Windows.h>
#include <cstdint>

class WinApp
{
public:
	// �E�B���h�E�T�C�Y
	const int window_width = 1280; // ����
	const int window_height = 720; // �c��

public: // �ÓI�����o�֐�
	/// <summary>
	/// �E�B���h�E�v���V�[�W��
	/// </summary>
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public://�����o�֐�
	void MakeWindow(std::wstring title);
	bool ProcessMessage();
	void DeleteGameWindow();


public://GetterSetter

	HWND Gethwnd() { return hwnd; }

private://�����o�ϐ�

	WNDCLASSEX w{};
	HWND hwnd;

};

