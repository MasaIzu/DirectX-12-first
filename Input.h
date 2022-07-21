#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include <array>
#include <vector>
#include <wrl.h>

#include <XInput.h>
#define DIRECTINPUT_VERSION 0x0800 // DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include"WinApp.h"

class Input {
public://�����o�֐�
	static Input* GetInstance();
	
	void Initialize();
	void Updata();



	/// <summary>
	/// �L�[�̉������`�F�b�N
	/// </summary>
	/// <param name="keyNumber">�L�[�ԍ�( DIK_0 ��)</param>
	/// <returns>������Ă��邩</returns>
	bool PushKey(BYTE keyNumber) const;
private:
	Input();
	~Input();

private://�����o�ϐ�
	Microsoft::WRL::ComPtr<IDirectInput8> dInput_;
	Microsoft::WRL::ComPtr<IDirectInputDevice8> devKeyboard_;
	// �S�L�[�̓��͏�Ԃ��擾����
	HWND hwnd_;
	std::array<BYTE, 256> key_;
	std::array<BYTE, 256> keyPre_;

};