#include "WinApp.h"

#include <string>

namespace {
	// SJIS -> WideChar
	std::wstring ConvertString(const std::string& str) {
		if (str.empty()) {
			return std::wstring();
		}

		auto size_needed =
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), static_cast<int>(str.size()), NULL, 0);
		if (size_needed == 0) {
			return std::wstring();
		}
		std::wstring result(size_needed, 0);
		MultiByteToWideChar(
			CP_ACP, 0, str.c_str(), static_cast<int>(str.size()), &result[0], size_needed);
		return result;
	}

	// ref: https://devblogs.microsoft.com/oldnewthing/20131017-00/?p=2903
	BOOL UnadjustWindowRectEx(LPRECT prc, DWORD dwStyle, BOOL fMenu, DWORD dwExStyle) {
		RECT rc;
		SetRectEmpty(&rc);
		BOOL fRc = AdjustWindowRectEx(&rc, dwStyle, fMenu, dwExStyle);
		if (fRc) {
			prc->left -= rc.left;
			prc->top -= rc.top;
			prc->right -= rc.right;
			prc->bottom -= rc.bottom;
		}
		return fRc;
	}
} // namespace

const wchar_t WinApp::kWindowClassName[] = L"�Ԃ��ƂуJ�[���[�X";

WinApp* WinApp::GetInstance() {
	static WinApp instance;
	return &instance;
}

// �E�B���h�E�v���V�[�W��
LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	WinApp* app = reinterpret_cast<WinApp*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	// ���b�Z�[�W�ŕ���
	switch (msg) {
	case WM_DESTROY:        // �E�B���h�E���j�����ꂽ
		PostQuitMessage(0); // OS�ɑ΂��āA�A�v���̏I����`����
		return 0;

	case WM_SIZING: {
		// �A�X�y�N�g���ς���T�C�Y�ύX�������Ȃ�
		if (app && app->GetSizeChangeMode() == WinApp::SizeChangeMode::kFixedAspect) {
			float aspectRatio = app->aspectRatio_;
			float aspectRatioRecp = 1.0f / aspectRatio;
			RECT* rect = reinterpret_cast<RECT*>(lparam);
			UnadjustWindowRectEx(
				rect, GetWindowLong(hwnd, GWL_STYLE), GetMenu(hwnd) != 0,
				GetWindowLong(hwnd, GWL_EXSTYLE));

			switch (wparam) {
			case WMSZ_LEFT:
			case WMSZ_BOTTOMLEFT:
			case WMSZ_RIGHT:
			case WMSZ_BOTTOMRIGHT:
				rect->bottom = rect->top + LONG((rect->right - rect->left) * aspectRatioRecp);
				break;
			case WMSZ_TOP:
			case WMSZ_TOPRIGHT:
			case WMSZ_BOTTOM:
				rect->right = rect->left + LONG((rect->bottom - rect->top) * aspectRatio);
				break;
			case WMSZ_TOPLEFT:
				rect->top = rect->bottom - LONG((rect->right - rect->left) * aspectRatioRecp);
				rect->left = rect->right - LONG((rect->bottom - rect->top) * aspectRatio);
				break;
			}

			AdjustWindowRectEx(
				rect, GetWindowLong(hwnd, GWL_STYLE), GetMenu(hwnd) != 0,
				GetWindowLong(hwnd, GWL_EXSTYLE));
		}
		break;
	}
	}
	return DefWindowProc(hwnd, msg, wparam, lparam); // �W���̏������s��
}

void WinApp::CreateGameWindow(
	const char* title, UINT windowStyle, int32_t clientWidth, int32_t clientHeight) {
	windowStyle_ = windowStyle;
	aspectRatio_ = float(clientWidth) / float(clientHeight);
	// �E�B���h�E�N���X�̐ݒ�
	wndClass_.cbSize = sizeof(WNDCLASSEX);
	wndClass_.lpfnWndProc = (WNDPROC)WindowProc;     // �E�B���h�E�v���V�[�W��
	wndClass_.lpszClassName = kWindowClassName;      // �E�B���h�E�N���X��
	wndClass_.hInstance = GetModuleHandle(nullptr);  // �E�B���h�E�n���h��
	wndClass_.hCursor = LoadCursor(NULL, IDC_ARROW); // �J�[�\���w��

	RegisterClassEx(&wndClass_); // �E�B���h�E�N���X��OS�ɓo�^

	// �E�B���h�E�T�C�Y{ X���W Y���W ���� �c�� }
	RECT wrc = { 0, 0, clientWidth, clientHeight };
	AdjustWindowRect(&wrc, windowStyle_, false); // �����ŃT�C�Y�␳

	// �E�B���h�E�^�C�g����wchar_t�ɕϊ�
	std::wstring titleWString = ConvertString(title);

	// �E�B���h�E�I�u�W�F�N�g�̐���
	hwnd_ = CreateWindow(
		wndClass_.lpszClassName, // �N���X��
		titleWString.c_str(),    // �^�C�g���o�[�̕���
		windowStyle_,            // �^�C�g���o�[�Ƌ��E��������E�B���h�E
		CW_USEDEFAULT,           // �\��X���W�iOS�ɔC����j
		CW_USEDEFAULT,           // �\��Y���W�iOS�ɔC����j
		wrc.right - wrc.left,    // �E�B���h�E����
		wrc.bottom - wrc.top,    // �E�B���h�E�c��
		nullptr,                 // �e�E�B���h�E�n���h��
		nullptr,                 // ���j���[�n���h��
		wndClass_.hInstance,     // �Ăяo���A�v���P�[�V�����n���h��
		nullptr);                // �I�v�V����
	SetWindowLongPtr(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	// �E�B���h�E�\��
	ShowWindow(hwnd_, SW_NORMAL);
}

void WinApp::TerminateGameWindow() {
	// �E�B���h�E�N���X��o�^����
	UnregisterClass(wndClass_.lpszClassName, wndClass_.hInstance);
}

bool WinApp::ProcessMessage() {
	MSG msg{}; // ���b�Z�[�W

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // ���b�Z�[�W������H
	{
		TranslateMessage(&msg); // �L�[���̓��b�Z�[�W�̏���
		DispatchMessage(&msg);  // �E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
	}

	if (msg.message == WM_QUIT) // �I�����b�Z�[�W�������烋�[�v�𔲂���
	{
		return true;
	}

	return false;
}

void WinApp::SetFullscreen(bool fullscreen) {

	if (isFullscreen_ != fullscreen) {
		if (fullscreen) {
			// ���̏�Ԃ��o���Ă���
			GetWindowRect(hwnd_, &windowRect_);

			// ���z�t���X�N���[����
			SetWindowLong(
				hwnd_, GWL_STYLE,
				windowStyle_ &
				~(WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME));

			RECT fullscreenRect{ 0 };
			HMONITOR monitor = MonitorFromWindow(hwnd_, MONITOR_DEFAULTTONEAREST);
			MONITORINFO info;
			info.cbSize = sizeof(info);
			GetMonitorInfo(monitor, &info);
			fullscreenRect.right = info.rcMonitor.right - info.rcMonitor.left;
			fullscreenRect.bottom = info.rcMonitor.bottom - info.rcMonitor.top;

			SetWindowPos(
				hwnd_, HWND_TOPMOST, fullscreenRect.left, fullscreenRect.top, fullscreenRect.right,
				fullscreenRect.bottom, SWP_FRAMECHANGED | SWP_NOACTIVATE);
			ShowWindow(hwnd_, SW_MAXIMIZE);

		}
		else {
			// �ʏ�E�B���h�E�ɖ߂�
			SetWindowLong(hwnd_, GWL_STYLE, windowStyle_);

			SetWindowPos(
				hwnd_, HWND_NOTOPMOST, windowRect_.left, windowRect_.top,
				windowRect_.right - windowRect_.left, windowRect_.bottom - windowRect_.top,
				SWP_FRAMECHANGED | SWP_NOACTIVATE);

			ShowWindow(hwnd_, SW_NORMAL);
		}
	}

	isFullscreen_ = fullscreen;
}

bool WinApp::IsFullscreen() const { return isFullscreen_; }

void WinApp::SetSizeChangeMode(SizeChangeMode sizeChangeMode) {

	sizeChangeMode_ = sizeChangeMode;
	if (sizeChangeMode_ == SizeChangeMode::kNone) {
		windowStyle_ &= ~WS_THICKFRAME;
	}
	else {
		// �A�X�y�N�g��ύX�s�Ȃ̂Ō��݂̃A�X�y�N�g��������Ă���
		if (sizeChangeMode_ == SizeChangeMode::kFixedAspect) {
			RECT clientRect{};
			GetClientRect(hwnd_, &clientRect);
			aspectRatio_ =
				float(clientRect.right - clientRect.left) / float(clientRect.bottom - clientRect.top);
		}
		windowStyle_ |= WS_THICKFRAME;
	}
	SetWindowLong(hwnd_, GWL_STYLE, windowStyle_);
	SetWindowPos(
		hwnd_, NULL, 0, 0, 0, 0, (SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED));
	ShowWindow(hwnd_, SW_NORMAL);
}

WinApp::SizeChangeMode WinApp::GetSizeChangeMode() const { return sizeChangeMode_; }
