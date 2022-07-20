#pragma once
#include <Windows.h>
#include <cstdlib>
#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#include "WinApp.h"



class DirectXCommon {

public:

//	/// <summary>
//	/// �V���O���g���C���X�^���X�̎擾
//	/// </summary>
//	/// <returns></returns>
//	static DirectXCommon* GetInstance();
//
//	/// <summary>
//	/// ������
//	/// </summary>
//	void Initialize(
//		WinApp* win, int32_t backBufferWidth = WinApp::kWindowWidth,
//		int32_t backBufferHeight = WinApp::kWindowHeight);
//
//	/// <summary>
//	/// �`��O����
//	/// </summary>
//	void PreDraw();
//
//	/// <summary>
//	/// �`��㏈��
//	/// </summary>
//	void PostDraw();
//
//	/// <summary>
//	/// �����_�[�^�[�Q�b�g�̃N���A
//	/// </summary>
//	void ClearRenderTarget();
//
//	/// <summary>
//	/// �[�x�o�b�t�@�̃N���A
//	/// </summary>
//	void ClearDepthBuffer();
//
//
//	/// <summary>
//	/// �o�b�N�o�b�t�@�̕��擾
//	/// </summary>
//	/// <returns>�o�b�N�o�b�t�@�̕�</returns>
//	int32_t GetBackBufferWidth() const;
//
//	/// <summary>
//	/// �o�b�N�o�b�t�@�̍����擾
//	/// </summary>
//	/// <returns>�o�b�N�o�b�t�@�̍���</returns>
//	int32_t GetBackBufferHeight() const;
//
//	void DirectXInitializ(WinApp* winApi);
//	void Updata123(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap);
//	void Updata5();
//
//	ID3D12Device* GetDevice(){ return device.Get(); };
//	ID3D12GraphicsCommandList* GetCommandList(){ return commandList.Get(); };
//
//private:
//
//	// �E�B���h�E�Y�A�v���P�[�V�����Ǘ�
//	WinApp* winApp_;
//
//	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
//	Microsoft::WRL::ComPtr<ID3D12Device> device;
//	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList = nullptr;
//	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator = nullptr;
//	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue = nullptr;
//	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain = nullptr;
//	//�o�b�N�o�b�t�@
//	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>backBuffers;
//	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer_;
//	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap = nullptr;
//	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap_;
//	//�t�F���X�̐���
//	Microsoft::WRL::ComPtr<ID3D12Fence> fence = nullptr;
//	Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
//	//�t�F���X�̐���
//	UINT64 fenceVal = 0;
//	
//	int32_t backBufferWidth_ = 0;
//	int32_t backBufferHeight_ = 0;
//	
//	////�A�_�v�^�[�̗񋓗p
//	//std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter4>>adapters;
//	////�����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
//	//Microsoft::WRL::ComPtr<IDXGIAdapter4> tmpAdapter = nullptr;
//	//DXGI_ADAPTER_DESC3 adapterDesc;
//
//	//D3D_FEATURE_LEVEL featureLevel;
//	////�R�}���h�L���[�̐ݒ�
//	//D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
//	////�X���b�v�`�F�[���̐ݒ�
//	//DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
//	//Microsoft::WRL::ComPtr<IDXGISwapChain1> swapchain1;
//
//	////�f�X�N���v�^�q�[�v�̐ݒ�
//	//D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
//	////�f�X�N���v�^�q�[�v�̃n���h�����擾
//	//D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
//	////�����_�[�^�[�Q�b�g�r���[�̐ݒ�
//	//D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
//	//
//	//
//	////1.���\�[�X�o���A�ŏ������݉\�ɕύX
//	//D3D12_RESOURCE_BARRIER barrierDesc{};
//	
//	private: // �����o�֐�
//		DirectXCommon() = default;
//		~DirectXCommon() = default;
//		DirectXCommon(const DirectXCommon&) = delete;
//		const DirectXCommon& operator=(const DirectXCommon&) = delete;
//
//		/// <summary>
//		/// DXGI�f�o�C�X������
//		/// </summary>
//		void InitializeDXGIDevice();
//
//		/// <summary>
//		/// �X���b�v�`�F�[���̐���
//		/// </summary>
//		void CreateSwapChain();
//
//		/// <summary>
//		/// �R�}���h�֘A������
//		/// </summary>
//		void InitializeCommand();
//
//		/// <summary>
//		/// �����_�[�^�[�Q�b�g����
//		/// </summary>
//		void CreateFinalRenderTargets();
//
//		/// <summary>
//		/// �[�x�o�b�t�@����
//		/// </summary>
//		void CreateDepthBuffer();
//
//		/// <summary>
//		/// �t�F���X����
//		/// </summary>
//		void CreateFence();

};