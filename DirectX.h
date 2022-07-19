#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include <vector>
#include <string>
#include <dinput.h>
#include<wrl.h>




class DirectXCmd {

public:

	void DirectXInitializ(HWND hwnd);
	void Updata123(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap);
	void Updata5();

	ID3D12Device* Device();
	HRESULT Result();
	ID3D12GraphicsCommandList* CommandList();

private:
	HRESULT result;
	Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<IDXGIFactory6> dxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator = nullptr;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList = nullptr;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap = nullptr;
	//�A�_�v�^�[�̗񋓗p
	std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter4>>adapters;
	//�����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	Microsoft::WRL::ComPtr<IDXGIAdapter4> tmpAdapter = nullptr;
	DXGI_ADAPTER_DESC3 adapterDesc;

	D3D_FEATURE_LEVEL featureLevel;
	//�R�}���h�L���[�̐ݒ�
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	//�X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapchain1;

	//�o�b�N�o�b�t�@
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>backBuffers;

	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	//�f�X�N���v�^�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	//�����_�[�^�[�Q�b�g�r���[�̐ݒ�
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	//�t�F���X�̐���
	Microsoft::WRL::ComPtr<ID3D12Fence> fence = nullptr;
	
	//1.���\�[�X�o���A�ŏ������݉\�ɕύX
	D3D12_RESOURCE_BARRIER barrierDesc{};
	//�t�F���X�̐���
	UINT64 fenceVal = 0;


};