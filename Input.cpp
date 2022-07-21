#include "Input.h"

Input* Input::GetInstance() {
	static Input instance;
	return &instance;
}

Input::~Input() {
	if (devKeyboard_) {
		devKeyboard_->Unacquire();
	}
}

void Input::Initialize() {
	WinApp* winApp = WinApp::GetInstance();

	hwnd_ = winApp->GetHwnd();
	HRESULT result = S_FALSE;

	// DirectInput�I�u�W�F�N�g�̐���
	result = DirectInput8Create(
		winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput_, nullptr);
	assert(SUCCEEDED(result));

	// �L�[�{�[�h�f�o�C�X�̐���
	result = dInput_->CreateDevice(GUID_SysKeyboard, &devKeyboard_, NULL);
	assert(SUCCEEDED(result));

	// ���̓f�[�^�`���̃Z�b�g
	result = devKeyboard_->SetDataFormat(&c_dfDIKeyboard); // �W���`��
	assert(SUCCEEDED(result));

}

void Input::Updata(){

	// �L�[�{�[�h���̎擾�J�n
	devKeyboard_->Acquire();
	// �L�[�̓���
	key_.fill(0);
	devKeyboard_->GetDeviceState((DWORD)size(key_), key_.data());

}



bool Input::PushKey(BYTE keyNumber) const {

	// 0�łȂ���Ή����Ă���
	if (key_[keyNumber]) {
		return true;
	}

	// �����Ă��Ȃ�
	return false;
}

