#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCore::GetInstance();
	audio_.Initialize();
	//�RD���f���̐���
	model_ = Model::Create();

	// �v���C���[��new
	player_ = new Player();

	// �G�̐�����new
	enemyPop_ = new EnemyPop();
	enemy_ = new Enemy();

	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();
	viewProjection_.eye.y += 15;
	viewProjection_.eye.z -= 80;
	viewProjection_.target = { 0,50,0 };
	viewProjection_.UpdateMatrix();

	//���H����
	loadModel_ = Model::CreateFromOBJ("load", true);
	load_ = new Load();
	load_->Initialize(loadModel_);

	//������
	wingModel_ = Model::CreateFromOBJ("wing", true);
	wing_ = new Wing();
	wing_->Initialize(wingModel_);

	textureHandle_ = TextureManager::Load("beel_idle.png");
	//�X�v���C�g
	sprite = Sprite::Create(textureHandle_, { 100,50 });

}

void GameScene::Update() {

	player_->Updata();

	enemyPop_->SetPlayer(player_);
	enemyPop_->SetWing(wing_);
	enemyPop_->Update(model_);

	viewProjection_.target = player_->GetPlayerPos();
	viewProjection_.UpdateMatrix();
	//���H�X�V
	load_->Update(player_->GetPlayerSpeed());

	//���X�V
	wing_->Update(player_->GetPlayerPos());

}

void GameScene::Draw() {

	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Model::PreDraw(commandList);

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	//���H�`��
	load_->Draw(viewProjection_);

	//���`��
	wing_->Draw(viewProjection_);

	// �v���C���[�̕`��
	player_->Draw(viewProjection_);

	// �G�̕`��
	enemyPop_->Draw(viewProjection_);

	// 3D�I�u�W�F�N�g�`��㏈��
	Model::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>
	sprite->Draw();
	
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();

#pragma endregion
}
