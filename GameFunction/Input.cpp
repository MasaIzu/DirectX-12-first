#include "Input.h"
#include "WinApp.h"
#include <cassert>

#include <basetsd.h>
#include <commctrl.h>
#include <dbt.h>
#include <oleauto.h>
#include <shellapi.h>
#include <wbemidl.h>
#include <wrl/client.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include <dinputd.h>
#include <memory>


Input* Input::GetInstance() {
	static Input instance;
	return &instance;
}

Input::~Input() {
	if (devKeyboard_) {
		devKeyboard_->Unacquire();
	}
}

void Input::Initialize()
{
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

	// 排他制御レベルのセット
	result = devKeyboard_->SetCooperativeLevel(
		hwnd_, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::Update()
{
	// 前回のキー入力を保存
	memcpy(keyPre, key, sizeof(key));

	// キーボード情報の取得開始
	devKeyboard_->Acquire();

	// 全キーの入力状態を取得する
	devKeyboard_->GetDeviceState(sizeof(key), key);

}

bool Input::PushKey(BYTE keyNumber)
{
	// 指定したキーを押していればtrueを返す
	if (key[keyNumber]) {
		return true;
	}

	// そうでなければfalseを返す
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	// 指定キーを前フレームで押していなく、今のフレームで押していればtrueを返す
	if (!keyPre[keyNumber] && key[keyNumber]) {
		return true;
	}

	// そうでなければfalseを返す
	return false;
}

bool Input::ReleasedKey(BYTE keyNumber)
{
	// 指定キーを前フレームで押していて、今のフレームで押していなければtrueを返す
	if (keyPre[keyNumber] && !key[keyNumber]) {
		return true;
	}

	// そうでなければfalseを返す
	return false;
}