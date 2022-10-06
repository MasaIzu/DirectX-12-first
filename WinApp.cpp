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
	//���b�Z�[�W�ŕ���
	switch (msg){
	case WM_DESTROY://�E�B���h�E���j�󂳂ꂽ
		PostQuitMessage(0);//OS�ɑ΂��āA�A�v���̏I����`����
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}



WinApp::WinApp() {

}

WinApp::~WinApp()
{
}

void WinApp::WinApiInitialize()
{

#pragma region WindowsAPI����������


	w_ = {};
	w_.cbSize = sizeof(WNDCLASSEX);
	w_.lpfnWndProc = (WNDPROC)WinApp::WindowProcedure;	//�E�B���h�E�v���V�[�W����ݒ�
	w_.lpszClassName = _T("DX12Sample");			//�E�B���h�E�N���X��
	w_.hInstance = GetModuleHandle(nullptr);		//�E�B���h�E�n���h��
	w_.hCursor = LoadCursor(NULL, IDC_ARROW);	//�J�[�\���w��

	//�E�B���h�E�N���X��OS�ɓo�^����
	RegisterClassEx(&w_);
	//�E�B���h�E�T�C�Y{X���W�@Y���W�@�����@�c��}
	wrc = { 0,0,window_width,window_height };
	//�֐����g���ăE�B���h�E�̃T�C�Y�������ŕ␳����
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�I�u�W�F�N�g�̐���
	hwnd_ = CreateWindow(w_.lpszClassName,//�N���X���w��
		_T("LE2B_16_�C�Y�~�__�}�T�g_AL3"),					//�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,			//�^�C�g���o�[�Ƌ��E��������E�B���h�E
		CW_USEDEFAULT,					//�\��x���W��OS�ɂ��C��
		CW_USEDEFAULT,					//�\��y���W��OS�ɂ��C��
		wrc.right - wrc.left,			//�E�B���h�E��
		wrc.bottom - wrc.top,			//�E�B���h�E��
		nullptr,						//�e�E�B���h�E�n���h��
		nullptr,						//���j���[�n���h��
		w_.hInstance,					//�Ăяo���A�v���P�[�V�����n���h��
		nullptr);						//�ǉ��p�����[�^�[(�I�v�V����)

	//�E�B���h�E�\��
	ShowWindow(hwnd_, SW_SHOW);

	

#pragma endregion

}

WinApp* WinApp::GetInstance() {
	static WinApp instance;
	return &instance;
}

bool WinApp::ProcessMessage() {
	MSG msg{};
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (msg.message == WM_QUIT) // �I�����b�Z�[�W�������烋�[�v�𔲂���
	{
		return true;
	}

	return false;

}

void WinApp::Finalize()
{

#pragma region  WindowsAPI��n��

	//�����N���X�͎g��Ȃ��̂œo�^����������
	UnregisterClass(w_.lpszClassName, w_.hInstance);

#pragma endregion

}



