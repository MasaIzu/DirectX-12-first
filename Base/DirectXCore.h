#pragma once

#include <Windows.h>
#include <cstdlib>
#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#include "WinApp.h"

/// <summary>
/// DirectX�ėp
/// </summary>
class DirectXCore {
public: // �����o�֐�

	/// <summary>
	/// �V���O���g���C���X�^���X�̎擾
	/// </summary>
	/// <returns></returns>
	static DirectXCore* GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(
		WinApp* win, int32_t backBufferWidth = WinApp::window_width,
		int32_t backBufferHeight = WinApp::window_height);

	/// <summary>
	/// �`��O����
	/// </summary>
	void PreDraw();

	/// <summary>
	/// �`��㏈��
	/// </summary>
	void PostDraw();

	/// <summary>
	/// �����_�[�^�[�Q�b�g�̃N���A
	/// </summary>
	void ClearRenderTarget();

	/// <summary>
	/// �[�x�o�b�t�@�̃N���A
	/// </summary>
	void ClearDepthBuffer();

	/// <summary>
	/// �f�o�C�X�̎擾
	/// </summary>
	/// <returns>�f�o�C�X</returns>
	ID3D12Device* GetDevice() { return device_.Get(); }

	/// <summary>
	/// �`��R�}���h���X�g�̎擾
	/// </summary>
	/// <returns>�`��R�}���h���X�g</returns>
	ID3D12GraphicsCommandList* GetCommandList() { return commandList_.Get(); }

	/// <summary>
	/// �o�b�N�o�b�t�@�̕��擾
	/// </summary>
	/// <returns>�o�b�N�o�b�t�@�̕�</returns>
	int32_t GetBackBufferWidth() const;

	/// <summary>
	/// �o�b�N�o�b�t�@�̍����擾
	/// </summary>
	/// <returns>�o�b�N�o�b�t�@�̍���</returns>
	int32_t GetBackBufferHeight() const;

private: // �����o�ϐ�
	// �E�B���h�E�Y�A�v���P�[�V�����Ǘ�
	WinApp* winApp_;

	// Direct3D�֘A
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_;
	Microsoft::WRL::ComPtr<ID3D12Device> device_;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList_;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator_;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_;
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers_;
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer_;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap_;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap_;
	Microsoft::WRL::ComPtr<ID3D12Fence> fence_;
	UINT64 fenceVal_ = 0;
	int32_t backBufferWidth_ = 0;
	int32_t backBufferHeight_ = 0;

private: // �����o�֐�
	DirectXCore() = default;
	~DirectXCore() = default;
	DirectXCore(const DirectXCore&) = delete;
	const DirectXCore& operator=(const DirectXCore&) = delete;

	/// <summary>
	/// DXGI�f�o�C�X������
	/// </summary>
	void InitializeDXGIDevice();

	/// <summary>
	/// �X���b�v�`�F�[���̐���
	/// </summary>
	void CreateSwapChain();

	/// <summary>
	/// �R�}���h�֘A������
	/// </summary>
	void InitializeCommand();

	/// <summary>
	/// �����_�[�^�[�Q�b�g����
	/// </summary>
	void CreateFinalRenderTargets();

	/// <summary>
	/// �[�x�o�b�t�@����
	/// </summary>
	void CreateDepthBuffer();

	/// <summary>
	/// �t�F���X����
	/// </summary>
	void CreateFence();
};
