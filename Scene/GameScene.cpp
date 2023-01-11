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

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCore_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCore_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>


	// スプライト描画後処理
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
