#include "worldTransform.h"
#include "DirectXCore.h"


void WorldTransform::Initialize(){
	CreateConstBuffer();
	Map();
	TransferMatrix();
}

void WorldTransform::CreateConstBuffer(){

	HRESULT result;

	//�萔�o�b�t�@�̃q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	//�萔�o�b�t�@�̃��\�[�X�ݒ�
	D3D12_RESOURCE_DESC resdesc{};
	resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resdesc.Width = (sizeof(ConstBufferDataWorldTransform) + 0xff) & ~0xff;
	resdesc.Height = 1;
	resdesc.DepthOrArraySize = 1;
	resdesc.MipLevels = 1;
	resdesc.SampleDesc.Count = 1;
	resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//�萔�o�b�t�@�̐���
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

	//�萔�o�b�t�@�̃}�b�s���O
	HRESULT result = constBuff_->Map(0, nullptr, (void**)constMap);
	assert(SUCCEEDED(result));

}

void WorldTransform::TransferMatrix(){

	DirectX::XMMATRIX matScale, matRot, matTrans;

	//�X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = DirectX::XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	matRot = DirectX::XMMatrixIdentity();
	matRot *= DirectX::XMMatrixRotationX(rotation_.x);
	matRot *= DirectX::XMMatrixRotationY(rotation_.y);
	matRot *= DirectX::XMMatrixRotationZ(rotation_.z);
	matTrans = DirectX::XMMatrixTranslation(translation_.x, translation_.y, translation_.z);

	//���[���h�s��̍���
	matWorld_ = DirectX::XMMatrixIdentity();//�ό`�����Z�b�g
	matWorld_ *= matScale;//���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld_ *= matRot;//���[���h�s��ɉ�]�𔽉f
	matWorld_ *= matTrans;//���[���h�s��ɕ��s�ړ��𔽉f

	//�e�I�u�W�F�N�g�������
	if (parent_ != nullptr) {
		//�e�I�u�W�F�N�g�̃��[���h�s����|����
		matWorld_ *= parent_->matWorld_;
	}
	//�萔�o�b�t�@�ւ̃f�[�^�]��
	constMap->matWorld = matWorld_;

}
