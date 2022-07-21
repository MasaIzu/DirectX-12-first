#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include <array>
#include <vector>
#include <wrl.h>

#include <XInput.h>
#define DIRECTINPUT_VERSION 0x0800 // DirectInputのバージョン指定
#include <dinput.h>
#include"WinApp.h"

class Input {
public://メンバ関数
	static Input* GetInstance();
	
	void Initialize();
	void Updata();



	/// <summary>
	/// キーの押下をチェック
	/// </summary>
	/// <param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <returns>押されているか</returns>
	bool PushKey(BYTE keyNumber) const;
private:
	Input();
	~Input();

private://メンバ変数
	Microsoft::WRL::ComPtr<IDirectInput8> dInput_;
	Microsoft::WRL::ComPtr<IDirectInputDevice8> devKeyboard_;
	// 全キーの入力状態を取得する
	HWND hwnd_;
	std::array<BYTE, 256> key_;
	std::array<BYTE, 256> keyPre_;

};