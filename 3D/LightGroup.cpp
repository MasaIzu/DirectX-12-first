#include "LightGroup.h"
#include "DirectXCore.h"
#include <assert.h>

using namespace DirectX;

LightGroup* LightGroup::Create(DirectXCore* directXCore) {
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	LightGroup* instance = new LightGroup();

	// ������
	instance->Initialize(directXCore);

	return instance;
}

void LightGroup::Initialize(DirectXCore* directXCore) {

	DefaultLightSetting();

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff);

	HRESULT result;
	// �萔�o�b�t�@�̐���
	result = directXCore->GetDevice()->CreateCommittedResource(
		&heapProps, // �A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff_));
	assert(SUCCEEDED(result));

	// �萔�o�b�t�@�Ƃ̃f�[�^�����N
	result = constBuff_->Map(0, nullptr, (void**)&constMap_);
	assert(SUCCEEDED(result));

	// �萔�o�b�t�@�փf�[�^�]��
	TransferConstBuffer();
}

void LightGroup::Update() {
	// �l�̍X�V���������������萔�o�b�t�@�ɓ]������
	if (dirty_) {
		TransferConstBuffer();
		dirty_ = false;
	}
}

void LightGroup::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex) {
	// �萔�o�b�t�@�r���[���Z�b�g
	cmdList->SetGraphicsRootConstantBufferView(
		rootParameterIndex, constBuff_->GetGPUVirtualAddress());
}

void LightGroup::TransferConstBuffer() {
	// ����
	constMap_->ambientColor = ambientColor_;
	// ���s����
	for (int i = 0; i < kDirLightNum; i++) {
		// ���C�g���L���Ȃ�ݒ��]��
		if (dirLights_[i].IsActive()) {
			constMap_->dirLights[i].active = 1;
			constMap_->dirLights[i].lightv = -dirLights_[i].GetLightDir();
			constMap_->dirLights[i].lightcolor = dirLights_[i].GetLightColor();
		}
		// ���C�g�������Ȃ烉�C�g�F��0��
		else {
			constMap_->dirLights[i].active = 0;
		}
	}
	// �_����
	for (int i = 0; i < kPointLightNum; i++) {
		// ���C�g���L���Ȃ�ݒ��]��
		if (pointLights_[i].IsActive()) {
			constMap_->pointLights[i].active = 1;
			constMap_->pointLights[i].lightpos = pointLights_[i].GetLightPos();
			constMap_->pointLights[i].lightcolor = pointLights_[i].GetLightColor();
			constMap_->pointLights[i].lightatten = pointLights_[i].GetLightAtten();
		}
		// ���C�g�������Ȃ烉�C�g�F��0��
		else {
			constMap_->pointLights[i].active = 0;
		}
	}
	// �X�|�b�g���C�g
	for (int i = 0; i < kSpotLightNum; i++) {
		// ���C�g���L���Ȃ�ݒ��]��
		if (spotLights_[i].IsActive()) {
			constMap_->spotLights[i].active = 1;
			constMap_->spotLights[i].lightv = -spotLights_[i].GetLightDir();
			constMap_->spotLights[i].lightpos = spotLights_[i].GetLightPos();
			constMap_->spotLights[i].lightcolor = spotLights_[i].GetLightColor();
			constMap_->spotLights[i].lightatten = spotLights_[i].GetLightAtten();
			constMap_->spotLights[i].lightfactoranglecos = spotLights_[i].GetLightFactorAngleCos();
		}
		// ���C�g�������Ȃ烉�C�g�F��0��
		else {
			constMap_->spotLights[i].active = 0;
		}
	}
	// �ۉe
	for (int i = 0; i < kCircleShadowNum; i++) {
		// �L���Ȃ�ݒ��]��
		if (circleShadows_[i].IsActive()) {
			constMap_->circleShadows[i].active = 1;
			constMap_->circleShadows[i].dir = -circleShadows_[i].GetDir();
			constMap_->circleShadows[i].casterPos = circleShadows_[i].GetCasterPos();
			constMap_->circleShadows[i].distanceCasterLight =
				circleShadows_[i].GetDistanceCasterLight();
			constMap_->circleShadows[i].atten = circleShadows_[i].GetAtten();
			constMap_->circleShadows[i].factorAngleCos = circleShadows_[i].GetFactorAngleCos();
		}
		// �����Ȃ�F��0��
		else {
			constMap_->circleShadows[i].active = 0;
		}
	}
}

void LightGroup::DefaultLightSetting() {
	dirLights_[0].SetActive(true);
	dirLights_[0].SetLightColor({ 1.0f, 1.0f, 1.0f });
	dirLights_[0].SetLightDir({ 0.0f, -1.0f, 0.0f, 0 });

	dirLights_[1].SetActive(true);
	dirLights_[1].SetLightColor({ 1.0f, 1.0f, 1.0f });
	dirLights_[1].SetLightDir({ +0.5f, +0.1f, +0.2f, 0 });

	dirLights_[2].SetActive(true);
	dirLights_[2].SetLightColor({ 1.0f, 1.0f, 1.0f });
	dirLights_[2].SetLightDir({ -0.5f, +0.1f, -0.2f, 0 });
}

void LightGroup::SetAmbientColor(const XMFLOAT3& color) {
	ambientColor_ = color;
	dirty_ = true;
}

void LightGroup::SetDirLightActive(int index, bool active) {
	assert(0 <= index && index < kDirLightNum);

	dirLights_[index].SetActive(active);
}

void LightGroup::SetDirLightDir(int index, const XMVECTOR& lightdir) {
	assert(0 <= index && index < kDirLightNum);

	dirLights_[index].SetLightDir(lightdir);
	dirty_ = true;
}

void LightGroup::SetDirLightColor(int index, const XMFLOAT3& lightcolor) {
	assert(0 <= index && index < kDirLightNum);

	dirLights_[index].SetLightColor(lightcolor);
	dirty_ = true;
}

void LightGroup::SetPointLightActive(int index, bool active) {
	assert(0 <= index && index < kPointLightNum);

	pointLights_[index].SetActive(active);
}

void LightGroup::SetPointLightPos(int index, const XMFLOAT3& lightpos) {
	assert(0 <= index && index < kPointLightNum);

	pointLights_[index].SetLightPos(lightpos);
	dirty_ = true;
}

void LightGroup::SetPointLightColor(int index, const XMFLOAT3& lightcolor) {
	assert(0 <= index && index < kPointLightNum);

	pointLights_[index].SetLightColor(lightcolor);
	dirty_ = true;
}

void LightGroup::SetPointLightAtten(int index, const XMFLOAT3& lightAtten) {
	assert(0 <= index && index < kPointLightNum);

	pointLights_[index].SetLightAtten(lightAtten);
	dirty_ = true;
}

void LightGroup::SetSpotLightActive(int index, bool active) {
	assert(0 <= index && index < kSpotLightNum);

	spotLights_[index].SetActive(active);
}

void LightGroup::SetSpotLightDir(int index, const XMVECTOR& lightdir) {
	assert(0 <= index && index < kSpotLightNum);

	spotLights_[index].SetLightDir(lightdir);
	dirty_ = true;
}

void LightGroup::SetSpotLightPos(int index, const XMFLOAT3& lightpos) {
	assert(0 <= index && index < kSpotLightNum);

	spotLights_[index].SetLightPos(lightpos);
	dirty_ = true;
}

void LightGroup::SetSpotLightColor(int index, const XMFLOAT3& lightcolor) {
	assert(0 <= index && index < kSpotLightNum);

	spotLights_[index].SetLightColor(lightcolor);
	dirty_ = true;
}

void LightGroup::SetSpotLightAtten(int index, const XMFLOAT3& lightAtten) {
	assert(0 <= index && index < kSpotLightNum);

	spotLights_[index].SetLightAtten(lightAtten);
	dirty_ = true;
}

void LightGroup::SetSpotLightFactorAngle(int index, const XMFLOAT2& lightFactorAngle) {
	assert(0 <= index && index < kSpotLightNum);

	spotLights_[index].SetLightFactorAngle(lightFactorAngle);
	dirty_ = true;
}

void LightGroup::SetCircleShadowActive(int index, bool active) {
	assert(0 <= index && index < kCircleShadowNum);

	circleShadows_[index].SetActive(active);
}

void LightGroup::SetCircleShadowCasterPos(int index, const XMFLOAT3& casterPos) {
	assert(0 <= index && index < kCircleShadowNum);

	circleShadows_[index].SetCasterPos(casterPos);
	dirty_ = true;
}

void LightGroup::SetCircleShadowDir(int index, const XMVECTOR& lightdir) {
	assert(0 <= index && index < kCircleShadowNum);

	circleShadows_[index].SetDir(lightdir);
	dirty_ = true;
}

void LightGroup::SetCircleShadowDistanceCasterLight(int index, float distanceCasterLight) {
	assert(0 <= index && index < kCircleShadowNum);

	circleShadows_[index].SetDistanceCasterLight(distanceCasterLight);
	dirty_ = true;
}

void LightGroup::SetCircleShadowAtten(int index, const XMFLOAT3& lightAtten) {
	assert(0 <= index && index < kCircleShadowNum);

	circleShadows_[index].SetAtten(lightAtten);
	dirty_ = true;
}

void LightGroup::SetCircleShadowFactorAngle(int index, const XMFLOAT2& lightFactorAngle) {
	assert(0 <= index && index < kCircleShadowNum);

	circleShadows_[index].SetFactorAngle(lightFactorAngle);
	dirty_ = true;
}
