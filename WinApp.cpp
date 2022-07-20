#include"WinApp.h"


// @brief �R���\�[����ʂɃt�H�[�}�b�g�t��������̕\��
// @param format �t�H�[�}�b�g(%d�Ƃ�%f�Ƃ���)
// @param �ϒ�����
// @remarks ���̊֐��̓f�o�b�N�p�ł��B�f�o�b�O���ɂ������삵�܂���
void WinApp::DebugOutputFormatString(const char* format, ...) {
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	vprintf(format, valist);
	va_end(valist);
#endif
}

LRESULT WinApp::WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//�E�B���h�E���j�󂳂ꂽ��Ă΂��
	if (msg == WM_DESTROY) {
		PostQuitMessage(0);//OS�ɑ΂��āu���̃A�v���͂����I���v�Ɠ`����
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}


MSG WinApp::Msg()
{
	return this->msg;
}



WinApp::WinApp() {

}

void WinApp::WinApiInitialize()
{

#pragma region WindowsAPI����������


	wndClass_ = {};
	wndClass_.cbSize = sizeof(WNDCLASSEX);
	wndClass_.lpfnWndProc = (WNDPROC)WinApp::WindowProcedure;	//�E�B���h�E�v���V�[�W����ݒ�
	wndClass_.lpszClassName = _T("DX12Sample");			//�E�B���h�E�N���X��
	wndClass_.hInstance = GetModuleHandle(nullptr);		//�E�B���h�E�n���h��
	wndClass_.hCursor = LoadCursor(NULL, IDC_ARROW);	//�J�[�\���w��

	//�E�B���h�E�N���X��OS�ɓo�^����
	RegisterClassEx(&wndClass_);
	//�E�B���h�E�T�C�Y{X���W�@Y���W�@�����@�c��}
	wrc = { 0,0,kWindowWidth,kWindowHeight };
	//�֐����g���ăE�B���h�E�̃T�C�Y�������ŕ␳����
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�I�u�W�F�N�g�̐���
	hwnd_ = CreateWindow(wndClass_.lpszClassName,//�N���X���w��
		_T("LE2B_16_�C�Y�~�__�}�T�g_AL3"),					//�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,			//�^�C�g���o�[�Ƌ��E��������E�B���h�E
		CW_USEDEFAULT,					//�\��x���W��OS�ɂ��C��
		CW_USEDEFAULT,					//�\��y���W��OS�ɂ��C��
		wrc.right - wrc.left,			//�E�B���h�E��
		wrc.bottom - wrc.top,			//�E�B���h�E��
		nullptr,						//�e�E�B���h�E�n���h��
		nullptr,						//���j���[�n���h��
		wndClass_.hInstance,					//�Ăяo���A�v���P�[�V�����n���h��
		nullptr);						//�ǉ��p�����[�^�[(�I�v�V����)

	//�E�B���h�E�\��
	ShowWindow(hwnd_, SW_SHOW);

	msg = {};

#pragma endregion

}

void WinApp::Updata() {

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}

void WinApp::WinAppFinish()
{

#pragma region  WindowsAPI��n��

	//�����N���X�͎g��Ȃ��̂œo�^����������
	UnregisterClass(wndClass_.lpszClassName, wndClass_.hInstance);

#pragma endregion

}



