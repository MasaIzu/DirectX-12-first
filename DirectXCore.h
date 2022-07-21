#pragma once
#include <Windows.h>
#include <cstdlib>
#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#include "WinApp.h"



class DirectXCore {
public://メンバ関数
	//シングルトンインスタンス
	static DirectXCore* GetInstance();
	//イニシャライズ
	void Initialize(
		WinApp* win, int32_t backBufferWidth = WinApp::kWindowWidth,
		int32_t backBufferHeight = WinApp::kWindowHeight);

	void InitializeDXGIDevice();/// DXGIデバイス初期化
	void InitializeCommand();/// コマンド関連初期化
	void CreateSwapChain();/// スワップチェーンの生成
	void CreateFinalRenderTargets();/// レンダーターゲット生成
	void CreateDepthBuffer();/// 深度バッファ生成
	void CreateFence();/// フェンス生成

private: // メンバ変数
// ウィンドウズアプリケーション管理
	WinApp* winApp_;

	// Direct3D関連
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