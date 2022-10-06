#include "Input.h"

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
		winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput_, nullptr);
	assert(SUCCEEDED(result));

	// �L�[�{�[�h�f�o�C�X�̐���
	result = directInput_->CreateDevice(GUID_SysKeyboard, &devKeyboard_, NULL);
	assert(SUCCEEDED(result));

	// ���̓f�[�^�`���̃Z�b�g
	result = devKeyboard_->SetDataFormat(&c_dfDIKeyboard); // �W���`��
	assert(SUCCEEDED(result));

}

void Input::Updata() {
	HRESULT result;

	//�O��̃L�[���͂�ۑ�
	memcpy(keyPre_, key_, sizeof(key_));

	// �L�[�{�[�h���̎擾�J�n
	result = devKeyboard_->Acquire();
	result = devKeyboard_->GetDeviceState(sizeof(key_), key_);

}

Input* Input::GetInstance() {
	static Input instance;
	return &instance;
}


bool Input::PushKey(BYTE keyNumber) const {

	// 0�łȂ���Ή����Ă���
	if (key_[keyNumber]) {
		return true;
	}

	// �����Ă��Ȃ�
	return false;
}

bool Input::TriggerKey(BYTE keyNumber) const {
	// 0�łȂ���Ή����Ă���
	if (keyPre_[keyNumber]) {
		return false;
	}

	// �����Ă��Ȃ�
	return true;
}