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

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataViewProjection) + 0xff) & ~0xff);

	// �萔�o�b�t�@�̐���
	result = DirectXCore::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProps, // �A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff_));
	assert(SUCCEEDED(result));
}

void ViewProjection::Map() {
	// �萔�o�b�t�@�Ƃ̃f�[�^�����N
	HRESULT result = constBuff_->Map(0, nullptr, (void**)&constMap);
	assert(SUCCEEDED(result));
}

void ViewProjection::UpdateMatrix() {

	// �r���[�s��̐���
	Matrix4 tmp = MyMath::LookAtLH(eye, target, up);
	matView = MyMath::MatrixInverse(&tmp);
	DirectX::XMVECTOR a = { eye.x,eye.y,eye.z };
	DirectX::XMVECTOR b = { target.x,target.y,target.z };
	DirectX::XMVECTOR c = { up.x,up.y,up.z };

	DirectX::XMMATRIX matView2 = DirectX::XMMatrixLookAtLH(a, b, c);

	// �������e�ɂ��ˉe�s��̐���
	matProjection = MyMath::PerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);
	DirectX::XMMATRIX matProjection2 = DirectX::XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);

	// �萔�o�b�t�@�ɏ�������
	constMap->view = matView;
	constMap->projection = matProjection;
	constMap->cameraPos = eye;
}
