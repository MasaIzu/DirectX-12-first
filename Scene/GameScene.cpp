#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <time.h>
#include "Vector2.h"
#include "Vector4.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	
}

void GameScene::Initialize(DirectXCore* dxCore) {
	dxCore_ = dxCore;
	input_ = Input::GetInstance();
	
}

void GameScene::Clean() {
	
	
}

void GameScene::Update() {

	

}

void GameScene::Draw() {

	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* commandList = dxCore_->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCore_->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Model::PreDraw(commandList);

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	

	// 3D�I�u�W�F�N�g�`��㏈��
	Model::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>


	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();

#pragma endregion
}



//void GameScene::DrawNunbers() {
//	divScore = 1000;
//	for (int i = 0; i < maxScoreNum; i++)
//	{
//		scoreNum[i] = enemyPop_->GetEnemyOverTakingCount() % divScore / (divScore / 10);
//		divScore = divScore / 10;
//		spritePos.x = 990 - ((1 - i) * 40);
//		scoreSprite[i].Draw(scoreNum[i], spritePos);
//	}
//	divScore = 1000;
//	for (int i = 0; i < maxScoreNum; i++)
//	{
//		scoreNum2[i] = (int)player_->GetKmH() % divScore / (divScore / 10);
//		divScore = divScore / 10;
//		sprite2Pos.x = 1180 - ((1 - i) * 35);
//		scoreSprite2[i].DrawSpeed(scoreNum2[i], sprite2Pos);
//	}
//}
