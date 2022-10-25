#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <time.h>
#include "Vector2.h"
#include "Vector4.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
}

void GameScene::Initialize() {
	srand(time(nullptr));
	dxCore_ = DirectXCore::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
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
	viewProjection_.eye.x = 0;
	viewProjection_.eye.y += 70;
	viewProjection_.eye.z -= 80;
	viewProjection_.target.y += 2;
	gamePlayCameraPos = viewProjection_.eye;
	cameraMoveFlag = 0;
	Timer = 120;

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


	Sprite::LoadTexture(1, L"Resources/TitleCar.png");
	TitleCar_ = Sprite::Create(1, { 640.0f, 360.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	TitleCar_->SetSize({ 800.0f, 600.0f });


	//スタートのカウントののテクスチャ
	Sprite::LoadTexture(2, L"Resources/stert321.png");
	for (int i = 0; i < 3; i++) {

		stert321[i] = Sprite::Create(2, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		stert321[i]->SetTextureRect({ 256.0f - (128.0f * i), 0.0f }, { 128.0f, 192.0f });
		stert321[i]->SetSize({ 128.0f, 128.0f });

	}

	Sprite::LoadTexture(2, L"Resources/meter.png");
	meter_ = Sprite::Create(2, { 1180.0f, 620.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	meter_->SetSize({ 200.0f, 200.0f });


	//針のテクスチャ
	Sprite::LoadTexture(3, L"Resources/needle.png");
	needle = Sprite::Create(3, { 1180.0f, 620.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	needle->SetSize({ 7.0f, 170.0f });
	needle->SetRotation((PI / 180.0f) * -150.0f);


	rePlay = 0;
	title = 0;

	viewProjection_.UpdateMatrix();
}

void GameScene::Clean() {
	cameraMoveFlag = 0;
	cameraTransFlag = 0;

	if (rePlay == 1) {
		rePlay = 0;
		viewProjection_.eye = gamePlayCameraPos;
		scene_ = Scene::Stage;
	}
	else if (title == 1) {
		title = 0;
		viewProjection_.eye = keepCamera;
		scene_ = Scene::Title;
	}

}

void GameScene::Update() {

	if (cameraMoveFlag == 1) {
		if (Timer > 0) {
			Timer--;
		}
	}
	switch (scene_) {
	case GameScene::Scene::Blackout:
		break;
	case GameScene::Scene::Title:
		if (input_->TriggerKey(DIK_SPACE)) {
			cameraMoveFlag = 1;
		}
		camera(cameraMoveFlag);
		//タイトルと背景自動移動
		load_->Demo();
		backGround_->Demo();
		if (Timer == 0) {
			scene_ = Scene::Stage;
		}
		break;
	case GameScene::Scene::Stage:

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

		if (player_->GetPlayerPos().z > enemyPop_->GetGoalEmemyPos()) {
			scene_ = Scene::Result;
		}
		break;
	case GameScene::Scene::Result:
		camera(0);
		player_->Updata();
		//道路更新
		load_->Update(player_->GetPlayerSpeed());
		//背景更新
		backGround_->Update(player_->GetPlayerSpeed());
		//風更新
		wing_->Update(player_->GetPlayerPos());

		if (rePlay == 1 || title == 1) {
			scene_ = Scene::Initialize;
		}
		break;
	case GameScene::Scene::Initialize:
		//使ったもののおかたずけ
		Clean();

		break;
	default:
		break;
	}

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

	switch (scene_) {
	case GameScene::Scene::Blackout:
		break;
	case GameScene::Scene::Title:
		//背景描画
		backGround_->Draw(viewProjection_);
		//道路描画
		load_->Draw(viewProjection_);
		// プレイヤーの描画
		player_->Draw(viewProjection_);

		break;
	case GameScene::Scene::Stage:
		//背景描画
		backGround_->Draw(viewProjection_);
		//道路描画
		load_->Draw(viewProjection_);
		// プレイヤーの描画
		player_->Draw(viewProjection_);
		//風描画
		wing_->Draw(viewProjection_);
		// 敵の描画
		enemyPop_->Draw(viewProjection_);

		break;
	case GameScene::Scene::Result:
		//背景描画
		backGround_->Draw(viewProjection_);
		//道路描画
		load_->Draw(viewProjection_);
		// プレイヤーの描画
		player_->Draw(viewProjection_);

		break;
	case GameScene::Scene::Initialize:

		break;
	default:
		break;
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	switch (scene_) {
	case GameScene::Scene::Blackout:
		break;
	case GameScene::Scene::Title:

		break;
	case GameScene::Scene::Stage:
		/*if (player_->GetTimer() > 0) {
			stert321[(player_->GetTimer() / 60)]->Draw();
		}*/
		meter_->Draw();

		needle->SetRotation((((player_->GetKmH() / 400) * 240) - 150) * (PI / 180));
		needle->Draw();
		break;
	case GameScene::Scene::Result:
		TitleCar_->Draw();
		break;
	case GameScene::Scene::Initialize:

		break;
	default:
		break;
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::camera(int x) {
	if (x == 0) {
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
	else if (x == 1) {
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
}