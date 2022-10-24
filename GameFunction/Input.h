#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include <array>
#include <vector>
#include <wrl.h>
#define DIRECTINPUT_VERSION 0x0800 //DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include "WinApp.h"

// ����
class Input
{
public:
	// namespace�̏ȗ�
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �����o�֐�

	static Input* GetInstance();
	// ������
	void Initialize();

	// �X�V
	void Update();

	/// <summary>
	/// �L�[�̉����������`�F�b�N(������)
	/// </summary>
	/// <param name="keyNumber">�L�[�ԍ�(DIK_0 ��)</param>
	/// <returns>������Ă��邩</returns>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	/// �L�[�̃g���K�[���`�F�b�N(�������u��)
	/// </summary>
	/// <param name="keyNumber">�L�[�ԍ�(DIK_0 ��)</param>
	/// <returns>�g���K�[��</returns>
	bool TriggerKey(BYTE keyNumber);

	/// <summary>
	/// �L�[�̃g���K�[���`�F�b�N(�������u��)
	/// </summary>
	/// <param name="keyNumber">�L�[�ԍ�(DIK_0 ��)</param>
	/// <returns>�g���K�[��</returns>
	bool ReleasedKey(BYTE keyNumber);

private:
	Input() = default;
	~Input();
	Input(const Input&) = delete;
	const Input& operator=(const Input&) = delete;

private:// �ÓI�����o�ϐ�

	// DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> dInput_ = nullptr;

	// �L�[�{�[�h�̃f�o�C�X
	ComPtr<IDirectInputDevice8> devKeyboard_ = nullptr;

	// �S�L�[�̏��
	BYTE key[256] = {};

	// �O��̑S�L�[�̏��
	BYTE keyPre[256] = {};

	// WindowsAPI
	WinApp* winApp_ = nullptr;

	HWND hwnd_;
};
