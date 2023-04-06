#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <random>
#include <fstream>
#include "FbxLoader.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCore::GetInstance();
	winApp_ = WinApp::GetInstance();
	input_ = Input::GetInstance();

	model_.reset(Model::CreateFromOBJ("UFO", true));

	model2_.reset(Model::CreateFromOBJ("boss", true));

	sceneManager_ = SceneManager::GetInstance();

	viewProjection_.Initialize();
	viewProjection_.eye = { 0,0,-100 };
	viewProjection_.UpdateMatrix();

	worldTransform_.Initialize();
	worldTransform_.translation_ = { 20,0,0 };
	worldTransform_.TransferMatrix();

	worldTransform2_.Initialize();
	worldTransform2_.translation_ = { 29,0,0 };
	worldTransform2_.scale_ = { 0.3f,0.3f,0.3f };
	worldTransform2_.TransferMatrix();

	FbxWorldTransform_.Initialize();
	FbxWorldTransform_.translation_ = { 0,-30,0 };
	FbxWorldTransform_.rotation_ = { 0,0,0 };
	FbxWorldTransform_.scale_ = { 0.1f,0.1f,0.1f };
	FbxWorldTransform_.TransferMatrix();

	fbxmodel = new FbxModel();
	
	fbxmodel = FbxLoader::GetInstance()->LoadModelFromFile("Player");
	fbxmodel->Initialize();

	modelAnim = new FbxAnimation();
	modelAnim->Load("Player");



}

void GameScene::Update() {
	
	if (input_->TriggerKey(DIK_SPACE))
	{
		sceneManager_->ChangeScene("TITLE");
	}

	if (input_->PushKey(DIK_UP)) {
		viewProjection_.target += Vector3(0, 0, 1.0f);
		viewProjection_.eye += Vector3(0, 0, 1.0f);
	}
	if (input_->PushKey(DIK_DOWN)) {
		viewProjection_.target += Vector3(0, 0, -1.0f);
		viewProjection_.eye += Vector3(0, 0, -1.0f);
	}

	if (input_->PushKey(DIK_LEFT)) {
		viewProjection_.target -= Vector3(1.0f, 0, 0);
		viewProjection_.eye -= Vector3(1.0f, 0, 0);
	}
	if (input_->PushKey(DIK_RIGHT)) {
		viewProjection_.target -= Vector3(-1.0f, 0, 0);
		viewProjection_.eye -= Vector3(-1.0f, 0, 0);
	}

	if (input_->PushKey(DIK_W)) {
		viewProjection_.target += Vector3(0, 1.0f, 0);
		viewProjection_.eye += Vector3(0, 1.0f, 0);
	}
	if (input_->PushKey(DIK_S)) {
		viewProjection_.target += Vector3(0, -1.0f, 0);
		viewProjection_.eye += Vector3(0, -1.0f, 0);
	}

	viewProjection_.UpdateMatrix();


	frem += 1.0f;

	if (input_->PushKey(DIK_P)) {
		frem = 0;
	}

	fbxmodel->ModelAnimation(frem, modelAnim->GetAnimation());

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	model_->Draw(worldTransform_, viewProjection_);

	model2_->Draw(worldTransform2_, viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();

	FbxModel::PreDraw(commandList);

	fbxmodel->Draw(FbxWorldTransform_, viewProjection_);

	FbxModel::PostDraw();

#pragma endregion

#pragma region 前景スプライト描画
	


#pragma endregion
}

void GameScene::Finalize()
{
}
