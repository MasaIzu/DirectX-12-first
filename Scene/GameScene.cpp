#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <time.h>
GameScene::GameScene() {}

GameScene::~GameScene() {

}

void GameScene::Initialize() {
	srand(time(nullptr));
	dxCommon_ = DirectXCore::GetInstance();
	input_ = Input::GetInstance();
	audio_.Initialize();

	//３Dモデルの生成
	model_ = Model::Create();

	// プレイヤーのnew
	player_ = new Player();

	// 敵の生成のnew
	enemyPop_ = new EnemyPop();
	enemy_ = new Enemy();
	enemyPop_->Initialize();

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	viewProjection_.eye.y += 70;
	viewProjection_.eye.z -= 80;
	viewProjection_.target.y += 2;
	gamePlayCameraPos = viewProjection_.eye;

	//カメラの位置替え
	viewProjection_.eye = { -70,63,-80 };
	keepCamera = viewProjection_.eye;
	cameraTransFlag = 0;
	cameraSpeed = { 1.0f, 1.0f, 1.0f };

	//道路生成
	loadModel_ = Model::CreateFromOBJ("load", true);
	load_ = new Load();
	load_->Initialize(loadModel_);

	//背景生成
	groundRightModel_ = Model::CreateFromOBJ("BackGroundRight", true);
	groundLeftModel_ = Model::CreateFromOBJ("BackGroundLeft", true);

	backGround_ = new BackGround();
	backGround_->Initialize(groundRightModel_, groundLeftModel_);

	//風生成
	wingModel_ = Model::CreateFromOBJ("wing", true);
	wing_ = new Wing();
	wing_->Initialize(wingModel_);

	viewProjection_.UpdateMatrix();
}

void GameScene::Update() {

	if (cameraTransFlag == 0) {
		if (input_->TriggerKey(DIK_SPACE)) {
			cameraTransFlag = 1;
		}
		if (keepCamera.x > viewProjection_.eye.x) {
			viewProjection_.eye.x += cameraSpeed.x;
		}
		if (keepCamera.y > viewProjection_.eye.y) {
			viewProjection_.eye.y += cameraSpeed.y;
		}
		if (keepCamera.z > viewProjection_.eye.z) {
			viewProjection_.eye.z += cameraSpeed.z;
		}

		if (keepCamera.x < viewProjection_.eye.x) {
			viewProjection_.eye.x -= cameraSpeed.x;
		}
		if (keepCamera.y < viewProjection_.eye.y) {
			viewProjection_.eye.y -= cameraSpeed.y;
		}
		if (keepCamera.z < viewProjection_.eye.z) {
			viewProjection_.eye.z -= cameraSpeed.z;
		}
	}
	else if (cameraTransFlag == 1) {
		if (input_->TriggerKey(DIK_SPACE)) {
			cameraTransFlag = 0;
		}
		if (gamePlayCameraPos.x > viewProjection_.eye.x) {
			viewProjection_.eye.x += cameraSpeed.x;
		}
		if (gamePlayCameraPos.y > viewProjection_.eye.y) {
			viewProjection_.eye.y += cameraSpeed.y;
		}
		if (gamePlayCameraPos.z > viewProjection_.eye.z) {
			viewProjection_.eye.z += cameraSpeed.z;
		}

		if (gamePlayCameraPos.x < viewProjection_.eye.x) {
			viewProjection_.eye.x -= cameraSpeed.x;
		}
		if (gamePlayCameraPos.y < viewProjection_.eye.y) {
			viewProjection_.eye.y -= cameraSpeed.y;
		}
		if (gamePlayCameraPos.z < viewProjection_.eye.z) {
			viewProjection_.eye.z -= cameraSpeed.z;
		}
	}
	viewProjection_.UpdateMatrix();

	player_->SetOverTakingCount(enemyPop_->GetEnemyOverTakingCount());
	player_->Updata();

	enemyPop_->SetPlayer(player_);
	enemyPop_->SetWing(wing_);
	enemyPop_->Update(model_);


	//道路更新
	load_->Update(player_->GetPlayerSpeed());
	//背景更新
	backGround_->Update(player_->GetPlayerSpeed());

	//風更新
	wing_->Update(player_->GetPlayerPos());

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	//背景描画
	backGround_->Draw(viewProjection_);

	//道路描画
	load_->Draw(viewProjection_);

	//風描画
	wing_->Draw(viewProjection_);

	// プレイヤーの描画
	player_->Draw(viewProjection_);

	// 敵の描画
	enemyPop_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
