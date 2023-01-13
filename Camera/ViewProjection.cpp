#include "DirectXCore.h"
#include "ViewProjection.h"
#include "WinApp.h"
#include <cassert>
#include <d3dx12.h>
#include "MyMath.h"
#include<DirectXMath.h>

void ViewProjection::Initialize() {
	CreateConstBuffer();
	Map();
	UpdateMatrix();
}

void ViewProjection::CreateConstBuffer() {
	HRESULT result;

	// ヒーププロパティ
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// リソース設定
	CD3DX12_RESOURCE_DESC resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataViewProjection) + 0xff) & ~0xff);

	// 定数バッファの生成
	result = DirectXCore::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProps, // アップロード可能
		D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff_));
	assert(SUCCEEDED(result));
}

void ViewProjection::Map() {
	// 定数バッファとのデータリンク
	HRESULT result = constBuff_->Map(0, nullptr, (void**)&constMap);
	assert(SUCCEEDED(result));
}

void ViewProjection::UpdateMatrix() {

	// ビュー行列の生成
	Matrix4 tmp = MyMath::LookAtLH(eye, target, up);
	matView = MyMath::MatrixInverse(tmp);
	DirectX::XMVECTOR a = { eye.x,eye.y,eye.z };
	DirectX::XMVECTOR b = { target.x,target.y,target.z };
	DirectX::XMVECTOR c = { up.x,up.y,up.z };

	DirectX::XMMATRIX matView2 = DirectX::XMMatrixLookAtLH(a, b, c);

	// 透視投影による射影行列の生成
	matProjection = MyMath::PerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);
	DirectX::XMMATRIX matProjection2 = DirectX::XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);

	// 定数バッファに書き込み
	constMap->view = matView;
	constMap->projection = matProjection;
	constMap->cameraPos = eye;
}
