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

private://�����o�ϐ�
	float Red;
	float Green;
	float Blue;
	float Alpha;
	int Switch;
	int changeColor;
	float colorSpeed;
	DirectX::XMFLOAT3 angle; //�J�����̉�]
	//�r���[�ϊ��s��
	DirectX::XMMATRIX matView;
	DirectX::XMFLOAT3 eye;
	DirectX::XMFLOAT3 target;
	DirectX::XMFLOAT3 up;

	// �萔�o�b�t�@�p�f�[�^�\���́i�}�e���A���j
	struct ConstBufferDataMaterial {
		DirectX::XMFLOAT4 color; // �F (RGBA)
	};
	ConstBufferDataMaterial* constMapMaterial = nullptr;

};