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
		WinApp* win, int32_t backBufferWidth = WinApp::kWindowWidth,
		int32_t backBufferHeight = WinApp::kWindowHeight);

	void InitializeDXGIDevice();/// DXGI�f�o�C�X������
	void InitializeCommand();/// �R�}���h�֘A������
	void CreateSwapChain();/// �X���b�v�`�F�[���̐���
	void CreateFinalRenderTargets();/// �����_�[�^�[�Q�b�g����
	void CreateDepthBuffer();/// �[�x�o�b�t�@����
	void CreateFence();/// �t�F���X����

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