#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <random>
#include <fstream>


GameScene::GameScene() {}

GameScene::~GameScene() {
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCore::GetInstance();
	winApp_ = WinApp::GetInstance();
	input_ = Input::GetInstance();

	model_.reset(Model::Create());

	sceneManager_ = SceneManager::GetInstance();
}

void GameScene::Update() {
	
	if (input_->TriggerKey(DIK_SPACE))
	{
		sceneManager_->ChangeScene("TITLE");
	}


}

void GameScene::Draw() {

	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	
	// �[�x�o�b�t�@�N���A
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Model::PreDraw(commandList);

	

	// 3D�I�u�W�F�N�g�`��㏈��
	Model::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	


#pragma endregion
}

void GameScene::Finalize()
{
}
