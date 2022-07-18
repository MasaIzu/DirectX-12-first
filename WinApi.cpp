#include"WinApi.h"


// @brief �R���\�[����ʂɃt�H�[�}�b�g�t��������̕\��
// @param format �t�H�[�}�b�g(%d�Ƃ�%f�Ƃ���)
// @param �ϒ�����
// @remarks ���̊֐��̓f�o�b�N�p�ł��B�f�o�b�O���ɂ������삵�܂���
void WinApi::DebugOutputFormatString(const char* format, ...) {
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	vprintf(format, valist);
	va_end(valist);
#endif
}

LRESULT WinApi::WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//�E�B���h�E���j�󂳂ꂽ��Ă΂��
	if (msg == WM_DESTROY) {
		PostQuitMessage(0);//OS�ɑ΂��āu���̃A�v���͂����I���v�Ɠ`����
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}


WinApi::WinApi() {

#pragma region WindowsAPI����������


	//WNDCLASSEX w = {};
	//w.cbSize = sizeof(WNDCLASSEX);
	//w.lpfnWndProc = (WNDPROC)WinApi::WindowProcedure;	//�E�B���h�E�v���V�[�W����ݒ�
	//w.lpszClassName = _T("DX12Sample");			//�E�B���h�E�N���X��
	//w.hInstance = GetModuleHandle(nullptr);		//�E�B���h�E�n���h��
	//w.hCursor = LoadCursor(NULL, IDC_ARROW);	//�J�[�\���w��

	////�E�B���h�E�N���X��OS�ɓo�^����
	//RegisterClassEx(&w);
	////�E�B���h�E�T�C�Y{X���W�@Y���W�@�����@�c��}
	//RECT wrc = { 0,0,window_width,window_height };
	////�֐����g���ăE�B���h�E�̃T�C�Y�������ŕ␳����
	//AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	////�E�B���h�E�I�u�W�F�N�g�̐���
	//HWND hwnd = CreateWindow(w.lpszClassName,//�N���X���w��
	//	_T("LE2B_16_�C�Y�~�__�}�T�g_AL3"),					//�^�C�g���o�[�̕���
	//	WS_OVERLAPPEDWINDOW,			//�^�C�g���o�[�Ƌ��E��������E�B���h�E
	//	CW_USEDEFAULT,					//�\��x���W��OS�ɂ��C��
	//	CW_USEDEFAULT,					//�\��y���W��OS�ɂ��C��
	//	wrc.right - wrc.left,			//�E�B���h�E��
	//	wrc.bottom - wrc.top,			//�E�B���h�E��
	//	nullptr,						//�e�E�B���h�E�n���h��
	//	nullptr,						//���j���[�n���h��
	//	w.hInstance,					//�Ăяo���A�v���P�[�V�����n���h��
	//	nullptr);						//�ǉ��p�����[�^�[(�I�v�V����)

	////�E�B���h�E�\��
	//ShowWindow(hwnd, SW_SHOW);

	//MSG msg = {};

#pragma endregion

}