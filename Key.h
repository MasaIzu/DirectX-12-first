#pragma once
#include <dinput.h>
#include <cassert>


class Key {
public:
	void KeyInitializ(WNDCLASSEX w);
	void KeyUpdata();

	BYTE KeyGet();
private:
	//DirectInputの初期化
	IDirectInput8* directInput = nullptr;
	//キーボードデバイスの生成
	IDirectInputDevice8* keyboard = nullptr;

	// 全キーの入力状態を取得する
	BYTE key[256] = {};

};