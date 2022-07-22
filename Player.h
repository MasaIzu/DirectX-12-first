#pragma once
#include <DirectXMath.h>
#include <d3d12.h>

class Player {
public:
	static Player* GetInstance();
	void Initializ(ID3D12Resource* constBuffMaterial);
	void Updata();

	void constMap();

	DirectX::XMMATRIX GetMatView() { return matView; };
private:
	Player() = default;
	~Player();

private://メンバ変数
	float Red;
	float Green;
	float Blue;
	float Alpha;
	int Switch;
	int changeColor;
	float colorSpeed;
	DirectX::XMFLOAT3 angle; //カメラの回転
	//ビュー変換行列
	DirectX::XMMATRIX matView;
	DirectX::XMFLOAT3 eye;
	DirectX::XMFLOAT3 target;
	DirectX::XMFLOAT3 up;

	// 定数バッファ用データ構造体（マテリアル）
	struct ConstBufferDataMaterial {
		DirectX::XMFLOAT4 color; // 色 (RGBA)
	};
	ConstBufferDataMaterial* constMapMaterial = nullptr;

};