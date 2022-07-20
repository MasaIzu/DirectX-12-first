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
//	/// シングルトンインスタンスの取得
//	/// </summary>
//	/// <returns></returns>
//	static DirectXCommon* GetInstance();
//
//	/// <summary>
//	/// 初期化
//	/// </summary>
//	void Initialize(
//		WinApp* win, int32_t backBufferWidth = WinApp::kWindowWidth,
//		int32_t backBufferHeight = WinApp::kWindowHeight);
//
//	/// <summary>
//	/// 描画前処理
//	/// </summary>
//	void PreDraw();
//
//	/// <summary>
//	/// 描画後処理
//	/// </summary>
//	void PostDraw();
//
//	/// <summary>
//	/// レンダーターゲットのクリア
//	/// </summary>
//	void ClearRenderTarget();
//
//	/// <summary>
//	/// 深度バッファのクリア
//	/// </summary>
//	void ClearDepthBuffer();
//
//
//	/// <summary>
//	/// バックバッファの幅取得
//	/// </summary>
//	/// <returns>バックバッファの幅</returns>
//	int32_t GetBackBufferWidth() const;
//
//	/// <summary>
//	/// バックバッファの高さ取得
//	/// </summary>
//	/// <returns>バックバッファの高さ</returns>
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
//	// ウィンドウズアプリケーション管理
//	WinApp* winApp_;
//
//	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
//	Microsoft::WRL::ComPtr<ID3D12Device> device;
//	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList = nullptr;
//	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator = nullptr;
//	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue = nullptr;
//	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain = nullptr;
//	//バックバッファ
//	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>backBuffers;
//	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer_;
//	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap = nullptr;
//	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap_;
//	//フェンスの生成
//	Microsoft::WRL::ComPtr<ID3D12Fence> fence = nullptr;
//	Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
//	//フェンスの生成
//	UINT64 fenceVal = 0;
//	
//	int32_t backBufferWidth_ = 0;
//	int32_t backBufferHeight_ = 0;
//	
//	////アダプターの列挙用
//	//std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter4>>adapters;
//	////ここに特定の名前を持つアダプターオブジェクトが入る
//	//Microsoft::WRL::ComPtr<IDXGIAdapter4> tmpAdapter = nullptr;
//	//DXGI_ADAPTER_DESC3 adapterDesc;
//
//	//D3D_FEATURE_LEVEL featureLevel;
//	////コマンドキューの設定
//	//D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
//	////スワップチェーンの設定
//	//DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
//	//Microsoft::WRL::ComPtr<IDXGISwapChain1> swapchain1;
//
//	////デスクリプタヒープの設定
//	//D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
//	////デスクリプタヒープのハンドルを取得
//	//D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
//	////レンダーターゲットビューの設定
//	//D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
//	//
//	//
//	////1.リソースバリアで書き込み可能に変更
//	//D3D12_RESOURCE_BARRIER barrierDesc{};
//	
//	private: // メンバ関数
//		DirectXCommon() = default;
//		~DirectXCommon() = default;
//		DirectXCommon(const DirectXCommon&) = delete;
//		const DirectXCommon& operator=(const DirectXCommon&) = delete;
//
//		/// <summary>
//		/// DXGIデバイス初期化
//		/// </summary>
//		void InitializeDXGIDevice();
//
//		/// <summary>
//		/// スワップチェーンの生成
//		/// </summary>
//		void CreateSwapChain();
//
//		/// <summary>
//		/// コマンド関連初期化
//		/// </summary>
//		void InitializeCommand();
//
//		/// <summary>
//		/// レンダーターゲット生成
//		/// </summary>
//		void CreateFinalRenderTargets();
//
//		/// <summary>
//		/// 深度バッファ生成
//		/// </summary>
//		void CreateDepthBuffer();
//
//		/// <summary>
//		/// フェンス生成
//		/// </summary>
//		void CreateFence();

};