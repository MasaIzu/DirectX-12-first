#include "DirectXCommon.h"
#include <algorithm>
#include <cassert>
#include <vector>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Microsoft::WRL;

//DirectXCommon* DirectXCommon::GetInstance() {
//	static DirectXCommon instance;
//	return &instance;
//}
//
//void DirectXCommon::Initialize(WinApp* winApp, int32_t backBufferWidth, int32_t backBufferHeight) {
//	// nullptrチェック
//	assert(winApp);
//	assert(4 <= backBufferWidth && backBufferWidth <= 4096);
//	assert(4 <= backBufferHeight && backBufferHeight <= 4096);
//
//	winApp_ = winApp;
//	backBufferWidth_ = backBufferWidth;
//	backBufferHeight_ = backBufferHeight;
//
//	// DXGIデバイス初期化
//	InitializeDXGIDevice();
//
//	// コマンド関連初期化
//	InitializeCommand();
//
//	// スワップチェーンの生成
//	CreateSwapChain();
//
//	// レンダーターゲット生成
//	CreateFinalRenderTargets();
//
//	// 深度バッファ生成
//	CreateDepthBuffer();
//
//	// フェンス生成
//	CreateFence();
//}









