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
public:
	//namespace(Microsoft::WRL)�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

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

	/// <summary>
	/// �L�[�̃g���K�[���`�F�b�N
	/// </summary>
	/// <param name="keyNumber">�L�[�ԍ�( DIK_0 ��)</param>
	/// <returns>�g���K�[��</returns>
	bool TriggerKey(BYTE keyNumber) const;

private:
	Input() = default;
	~Input();

private://�����o�ϐ�
	ComPtr<IDirectInput8> directInput_;
	ComPtr<IDirectInputDevice8> devKeyboard_;
	// �S�L�[�̓��͏�Ԃ��擾����
	HWND hwnd_;
	//���̑S�L�[�̏��
	BYTE key_[256] = {};
	//�O��̑S�L�[�̏��
	BYTE keyPre_[256] = {};

};