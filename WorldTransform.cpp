#include "WorldTransform.h"
#include "DirectXCore.h"


void WorldTransform::Initialize(){
	CreateConstBuffer();
	Map();
	TransferMatrix();
}

void WorldTransform::CreateConstBuffer(){

	HRESULT result;

	//定数バッファのヒープ設定
	D3D12_HEAP_PROPERTIES heapProp{};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	//定数バッファのリソース設定
	D3D12_RESOURCE_DESC resdesc{};
	resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resdesc.Width = (sizeof(ConstBufferDataWorldTransform) + 0xff) & ~0xff;
	resdesc.Height = 1;
	resdesc.DepthOrArraySize = 1;
	resdesc.MipLevels = 1;
	resdesc.SampleDesc.Count = 1;
	resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//定数バッファの生成
	result = DirectXCore::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resdesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff_));
	assert(SUCCEEDED(result));

}

void WorldTransform::Map(){

	//定数バッファのマッピング
	HRESULT result = constBuff_->Map(0, nullptr, (void**)constMap);
	assert(SUCCEEDED(result));

}

void WorldTransform::TransferMatrix(){

	Matrix4 matScale, matRot, matTrans;

	//スケール、回転、平行移動行列の計算
	matScale = AffinTrans::Scale(scale_);
	matRot = AffinTrans::Initialize();
	matRot *= AffinTrans::Rotation(rotation_,6);
	matTrans = AffinTrans::Translation(translation_);

	//ワールド行列の合成
	matWorld_ = AffinTrans::Initialize();//変形をリセット
	matWorld_ *= matScale;//ワールド行列にスケーリングを反映
	matWorld_ *= matRot;//ワールド行列に回転を反映
	matWorld_ *= matTrans;//ワールド行列に平行移動を反映

	//親オブジェクトがあれば
	if (parent_ != nullptr) {
		//親オブジェクトのワールド行列を掛ける
		matWorld_ *= parent_->matWorld_;
	}
	//定数バッファへのデータ転送
	constMap->matWorld = matWorld_;

}
