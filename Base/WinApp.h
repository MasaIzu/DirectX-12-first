#pragma once
#include <Windows.h>
#include <cstdint>

/// <summary>
/// �E�B���h�E�Y�A�v���P�[�V����
/// </summary>
class WinApp {
public: // �ÓI�����o�ϐ�
	// �E�B���h�E�T�C�Y
	static const int window_width = 1280; // ����
	static const int window_height = 720; // �c��
	// �E�B���h�E�N���X��
	static const wchar_t kWindowClassName[];

	enum class SizeChangeMode {
		kNone,        //!< �T�C�Y�ύX�s��
		kNormal,      //!< ���R�ύX
		kFixedAspect, //!< �A�X�y�N�g����
	};

public: // �ÓI�����o�֐�
	/// <summary>
	/// �V���O���g���C���X�^���X�̎擾
	/// </summary>
	/// <returns>�V���O���g���C���X�^���X</returns>
	static WinApp* GetInstance();

	/// <summary>
	/// �E�B���h�E�v���V�[�W��
	/// </summary>
	/// <param name="hwnd">�E�B���h�E�n���h��</param>
	/// <param name="msg">���b�Z�[�W�ԍ�</param>
	/// <param name="wparam">���b�Z�[�W���1</param>
	/// <param name="lparam">���b�Z�[�W���2</param>
	/// <returns>����</returns>
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // �����o�֐�
	/// <summary>
	/// �Q�[���E�B���h�E�̍쐬
	/// <param name="title">�E�B���h�E�^�C�g��</param>
	/// <param name="windowStyle">�E�B���h�E�̏����X�^�C��</param>
	/// <param name="clientWidth">�E�B���h�E�̃N���C�A���g�̈�̏�����</param>
	/// <param name="clientHeight">�E�B���h�E�̃N���C�A���g�̈�̏�������</param>
	/// </summary>
	void CreateGameWindow(
		const char* title = "DirectXGame", UINT windowStyle = WS_OVERLAPPEDWINDOW,
		int32_t clientWidth = window_width, int32_t clientHeight = window_height);

	/// <summary>
	/// �Q�[���E�B���h�E�̔j��
	/// </summary>
	void TerminateGameWindow();

	/// <summary>
	/// ���b�Z�[�W�̏���
	/// </summary>
	/// <returns>�I�����ǂ���</returns>
	bool ProcessMessage();

	/// <summary>
	/// �E�B���h�E�n���h���̎擾
	/// </summary>
	/// <returns></returns>
	HWND GetHwnd() const { return hwnd_; }

	HINSTANCE GetHInstance() const { return wndClass_.hInstance; }

	/// <summary>
	/// �t���X�N���[���ݒ�
	/// </summary>
	/// <param name="fullscreen">�t���X�N���[���ɂ��邩�ǂ���</param>
	void SetFullscreen(bool fullscreen);

	/// <summary>
	/// �t���X�N���[�����ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsFullscreen() const;

	/// <summary>
	/// �T�C�Y�ύX���[�h�̐ݒ�
	/// </summary>
	/// <returns></returns>
	void SetSizeChangeMode(SizeChangeMode sizeChangeMode);

	/// <summary>
	/// �T�C�Y�ύX���[�h�̎擾
	/// </summary>
	/// <returns></returns>
	SizeChangeMode GetSizeChangeMode() const;

private: // �����o�֐�
	WinApp() = default;
	~WinApp() = default;
	WinApp(const WinApp&) = delete;
	const WinApp& operator=(const WinApp&) = delete;
private: // �����o�ϐ�
	// Window�֘A
	HWND hwnd_ = nullptr;   // �E�B���h�E�n���h��
	WNDCLASSEX wndClass_{}; // �E�B���h�E�N���X
	UINT windowStyle_;
	bool isFullscreen_ = false;
	RECT windowRect_;
	SizeChangeMode sizeChangeMode_ = SizeChangeMode::kNormal;
	float aspectRatio_;
};
