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
//	// nullptr�`�F�b�N
//	assert(winApp);
//	assert(4 <= backBufferWidth && backBufferWidth <= 4096);
//	assert(4 <= backBufferHeight && backBufferHeight <= 4096);
//
//	winApp_ = winApp;
//	backBufferWidth_ = backBufferWidth;
//	backBufferHeight_ = backBufferHeight;
//
//	// DXGI�f�o�C�X������
//	InitializeDXGIDevice();
//
//	// �R�}���h�֘A������
//	InitializeCommand();
//
//	// �X���b�v�`�F�[���̐���
//	CreateSwapChain();
//
//	// �����_�[�^�[�Q�b�g����
//	CreateFinalRenderTargets();
//
//	// �[�x�o�b�t�@����
//	CreateDepthBuffer();
//
//	// �t�F���X����
//	CreateFence();
//}









