#include "Select.h"

void Select::Initialize(Model* GroundModel, Model* modelDome) {
	//NULL�|�C���^�`�F�b�N
	assert(GroundModel);
	GroundModel_ = GroundModel;
	//���[���h�ϊ��̏�����
	worldGroundTransform_.Initialize();

	worldGroundTransform_.translation_ = Vector3(0, -25.0f, 0);
	worldGroundTransform_.scale_ = Vector3(600, 100, 600);
	worldGroundTransform_.matWorld_ *= MyMath::Translation(worldGroundTransform_.translation_);
	worldGroundTransform_.matWorld_ *= MyMath::Scale(worldGroundTransform_.scale_);

	//NULL�|�C���^�`�F�b�N
	assert(modelDome);
	modelDome_ = modelDome;
	//���[���h�ϊ��̏�����
	worldDomeTransform_.Initialize();
	worldDomeTransform_.scale_ = Vector3(600, 600, 600);
	worldDomeTransform_.matWorld_ *= MyMath::Scale(worldDomeTransform_.scale_);

	taitolModel_ = Model::Create();
	textureHandle_ = TextureManager::Load("taitol_Maverick.png");
	startTrans.Initialize();
	startTrans.translation_ = Vector3{ 0,-16,-40 };
	startTrans.scale_ = Vector3(6, 3, 1);
	startTrans.rotation_ = Vector3(-0.2, 0, 0);
	startTrans.matWorld_ *= MyMath::Scale(startTrans.scale_);

	textureHandle2_ = TextureManager::Load("setumei.png");
	startTrans2.Initialize();
	startTrans2.translation_ = Vector3{ 14,-16,-43 };
	startTrans2.scale_ = Vector3(6, 3, 1);
	startTrans2.rotation_ = Vector3(-0.2, 0.9, 0);
	startTrans2.matWorld_ *= MyMath::Scale(startTrans2.scale_);




	//�s��̓]��
	AffinTrans::affin(startTrans);
	AffinTrans::affin(startTrans2);
	worldGroundTransform_.TransferMatrix();
	worldDomeTransform_.TransferMatrix();
	startTrans.TransferMatrix();
	startTrans2.TransferMatrix();
}

void Select::Update() {

}

void Select::Draw(ViewProjection viewProjection_) {
	//3D���f���`��
	GroundModel_->Draw(worldGroundTransform_, viewProjection_);
	modelDome_->Draw(worldDomeTransform_, viewProjection_);
	taitolModel_->Draw(startTrans, viewProjection_, textureHandle_);
	taitolModel_->Draw(startTrans2, viewProjection_, textureHandle2_);
}

void Select::GameDraw(ViewProjection viewProjection_) {
	//3D���f���`��
	GroundModel_->Draw(worldGroundTransform_, viewProjection_);
}