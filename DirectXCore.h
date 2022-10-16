#pragma once
#include <Windows.h>
#include <cstdlib>
#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#include "WinApp.h"



class DirectXCore {
public://�����o�֐�
	//�V���O���g���C���X�^���X
	static DirectXCore* GetInstance();
	//�C�j�V�����C�Y
	void Initialize(
		WinApp* win, int32_t backBufferWidth = WinApp::window_width,
		int32_t backBufferHeight = WinApp::window_height);

	void InitializeDevice();/// �f�o�C�X������
	void InitializeCommand();/// �R�}���h�֘A������
	void InitializeSwapChain();/// �X���b�v�`�F�[���̐���
	void InitializeRenderTargetView();/// �����_�[�^�[�Q�b�g����
	void InitializeDepthBuffer();/// �[�x�o�b�t�@����
	void InitializeFence();/// �t�F���X����

	
	void PreDraw();/// �`��O����
	void PostDraw();/// �`��㏈��
	void ClearRenderTarget();/// �����_�[�^�[�Q�b�g�̃N���A
	void ClearDepthBuffer();/// �[�x�o�b�t�@�̃N���A

	int32_t GetBackBufferWidth() const;/// �o�b�N�o�b�t�@�̕��擾
	int32_t GetBackBufferHeight() const;/// �o�b�N�o�b�t�@�̍����擾

	ID3D12Device* GetDevice() { return device_.Get(); }/// �f�o�C�X�̎擾
	ID3D12GraphicsCommandList* GetCommandList() { return commandList_.Get(); }/// �`��R�}���h���X�g�̎擾

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



};