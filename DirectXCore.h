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
		WinApp* win, int32_t backBufferWidth = WinApp::window_width,
		int32_t backBufferHeight = WinApp::window_height);

	void InitializeDevice();/// デバイス初期化
	void InitializeCommand();/// コマンド関連初期化
	void InitializeSwapChain();/// スワップチェーンの生成
	void InitializeRenderTargetView();/// レンダーターゲット生成
	void InitializeDepthBuffer();/// 深度バッファ生成
	void InitializeFence();/// フェンス生成

	
	void PreDraw();/// 描画前処理
	void PostDraw();/// 描画後処理
	void ClearRenderTarget();/// レンダーターゲットのクリア
	void ClearDepthBuffer();/// 深度バッファのクリア

	int32_t GetBackBufferWidth() const;/// バックバッファの幅取得
	int32_t GetBackBufferHeight() const;/// バックバッファの高さ取得

	ID3D12Device* GetDevice() { return device_.Get(); }/// デバイスの取得
	ID3D12GraphicsCommandList* GetCommandList() { return commandList_.Get(); }/// 描画コマンドリストの取得

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