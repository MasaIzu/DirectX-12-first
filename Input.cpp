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

	// DirectInputオブジェクトの生成
	result = DirectInput8Create(
		winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput_, nullptr);
	assert(SUCCEEDED(result));

	// キーボードデバイスの生成
	result = dInput_->CreateDevice(GUID_SysKeyboard, &devKeyboard_, NULL);
	assert(SUCCEEDED(result));

	// 入力データ形式のセット
	result = devKeyboard_->SetDataFormat(&c_dfDIKeyboard); // 標準形式
	assert(SUCCEEDED(result));

}

void Input::Updata(){

	// キーボード情報の取得開始
	devKeyboard_->Acquire();
	// キーの入力
	key_.fill(0);
	devKeyboard_->GetDeviceState((DWORD)size(key_), key_.data());

}



bool Input::PushKey(BYTE keyNumber) const {

	// 0でなければ押している
	if (key_[keyNumber]) {
		return true;
	}

	// 押していない
	return false;
}

