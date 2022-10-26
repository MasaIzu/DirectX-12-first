#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <time.h>
#include "Vector2.h"
#include "Vector4.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete TitleCar_;
	for (int i = 0; i < 3; i++) {
		delete stert321[i];
	}
	delete meter_;
	delete needle;
}

void GameScene::Initialize() {
	srand(time(nullptr));
	dxCore_ = DirectXCore::GetInstance();
	input_ = Input::GetInstance();
	//audio_ = Audio::GetInstance();
	//３Dモデルの生成
	model_ = Model::Create();

	// プレイヤーのnew
	player_ = new Player();

	// 敵の生成のnew
	enemyPop_ = new EnemyPop();
	enemy_ = new Enemy();
	enemyPop_->Initialize();
	enemyPop_->LoadTexture();

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

		stert321[i] = Sprite::Create(2, {640.0f, 300.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		stert321[i]->SetTextureRect({ 256.0f - (128.0f * i), 0.0f }, { 128.0f, 192.0f });
		stert321[i]->SetSize({ 96.0f, 128.0f });

	}

	Sprite::LoadTexture(3, L"Resources/meter.png");
	meter_ = Sprite::Create(3, { 1150.0f, 600.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	meter_->SetSize({ 200.0f, 200.0f });


	//針のテクスチャ
	Sprite::LoadTexture(4, L"Resources/needle.png");
	needle = Sprite::Create(4, { 1150.0f, 600.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	needle->SetSize({ 7.0f, 170.0f });
	needle->SetRotation(-150.0f);

	Sprite::LoadTexture(5, L"Resources/TitleRogo.png");
	titleRogo = Sprite::Create(5, { 350.0f, 220.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	titleRogo->SetSize({ 608.0f, 246.0f });

	Sprite::LoadTexture(6, L"Resources/Space.png");
	space = Sprite::Create(6, { 600.0f, 600.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	space->SetSize({ 200.0f, 100.0f });


	Sprite::LoadTexture(7, L"Resources/TimeFont.png");
	gameTime = Sprite::Create(7, { 75.0f, 50.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	gameTime->SetSize({ 100.0f, 30.0f });

	Sprite::LoadTexture(8, L"Resources/200.png");
	overTakingCount = Sprite::Create(8, { 1150.0f, 75.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	overTakingCount->SetSize({ 150.0f, 75.0f });

	Sprite::LoadTexture(9, L"Resources/123-export.png");
	for (int i = 0; i < 9; i++) {

		numbers[i] = Sprite::Create(9, { 1080.0f, 75.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
		numbers[i]->SetTextureRect({ 800.0f - (80.0f * i), 0.0f }, { 800.0f, 80.0f });
		numbers[i]->SetSize({ 80.0f, 80.0f });

	}

	//リザルトシーンで使うスプライトのロード
	Sprite::LoadTexture(12, L"Resources/TITLEYellow.png");
	Sprite::LoadTexture(13, L"Resources/TITLEBlack.png");
	TitleFont[0] = Sprite::Create(12, { 380,480 });
	TitleFont[0]->SetSize({ 220,50 });
	TitleFont[1] = Sprite::Create(13, { 380,480 });
	TitleFont[1]->SetSize({ 220,50 });

	Sprite::LoadTexture(14, L"Resources/RETRYYellow.png");
	Sprite::LoadTexture(15, L"Resources/RETRYBlack.png");
	RetryFont[0] = Sprite::Create(14, { 680,480 });
	RetryFont[0]->SetSize({ 220,50 });
	RetryFont[1] = Sprite::Create(15, { 680,480 });
	RetryFont[1]->SetSize({ 220,50 });

	Sprite::LoadTexture(16, L"Resources/UnkoFlag.png");
	ChangeFlag = Sprite::Create(16, { titlepos.x ,titlepos.y });

	Sprite::LoadTexture(17, L"Resources/titleselects.png");
	gameStart = Sprite::Create(17, { 600.0f, 500.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	gameStart->SetSize({ 400.0f, 100.0f });
	Sprite::LoadTexture(18, L"Resources/kakusi.png");
	BlackFilter = Sprite::Create(18, { 0,0 });




	for (int i = 0; i < 10; i++) {
		//一
		timers[i] = Sprite::Create(9, { 310.0f, 65.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
		timers[i]->SetTextureRect({ 0.0f + (80.0f * i), 0.0f }, { 80.0f, 80.0f });
		timers[i]->SetSize({ 80.0f, 80.0f });
		//十
		timers1[i] = Sprite::Create(9, { 250.0f, 65.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
		timers1[i]->SetTextureRect({ 0.0f + (80.0f * i), 0.0f }, { 80.0f, 80.0f });
		timers1[i]->SetSize({ 80.0f, 80.0f });
		//分
		timers2[i] = Sprite::Create(9, { 170.0f, 65.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
		timers2[i]->SetTextureRect({ 0.0f + (80.0f * i), 0.0f }, { 80.0f, 80.0f });
		timers2[i]->SetSize({ 80.0f, 80.0f });
	}

	Sprite::LoadTexture(19, L"Resources/coron.png");
	coro = Sprite::Create(19, { 220.0f, 65.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });

	Sprite::LoadTexture(20, L"Resources/JumpFont.png");
	spaceSousa = Sprite::Create(20, { 50,450 });
	spaceSousa->SetSize({ 200,80 });

	Sprite::LoadTexture(21, L"Resources/ReanChageFont.png");
	ReanChageSousa = Sprite::Create(21, { 50,550 });
	ReanChageSousa->SetSize({ 200,80 });

	
	Sprite::LoadTexture(22, L"Resources/OverTakeFont.png");
	OverTakingCount = Sprite::Create(22, { 850,40 });
	OverTakingCount->SetSize({ 100,30 });


	color = 1.0f;
	rePlay = 0;
	title = 0;
	number = 0;
	titleWaitTime = 0;

	sound_ = new SoundManager();
	sound_->Initialize();
	soundData = sound_.SoundLoadWave("game.wav");

	for (int i = 0; i < maxScoreNum; i++)
	{
		scoreSprite[i].Initialize();
		scoreSprite2[i].Initialize();
	}

	viewProjection_.UpdateMatrix();
}

void GameScene::Clean() {
	cameraMoveFlag = 1; 
	color = 0.0f;

	if (rePlay == 1) {
		camera(cameraMoveFlag);
		if (Timer == 0) {
			if (player_->GetPlayerSpeed() < 1) {
				BarAlpha = 0;
				BlackAlpha = 0;
				waitTimer = 0;
				enemyPop_->Initialize();
				player_->Initialize();
				scene_ = Scene::Stage;
				rePlay = 0;
			}
		}
	}
	else if (title == 1) {
		if (Timer == 0) {
			if (player_->GetPlayerSpeed() < 1) {
				BarAlpha = 0;
				BlackAlpha = 0;
				waitTimer = 0;
				enemyPop_->Initialize();
				player_->Initialize();
				cameraMoveFlag = 0;
				Timer = 120;
				scene_ = Scene::Title;
				title = 0;
				titleWaitTime = 10;
			}
		}
	}
	
}

void GameScene::Update() {

	if (cameraMoveFlag == 1) {
		if (Timer > 0) {
			Timer--;
		}
	}
	if (titleWaitTime > 0) {
		titleWaitTime--;
	}

	switch (scene_) {
	case GameScene::Scene::Blackout:
		break;
	case GameScene::Scene::Title:
		if (titleWaitTime == 0) {
			if (input_->TriggerKey(DIK_SPACE)) {
				cameraMoveFlag = 1;
			}
		}
		AlphaChange(scene_);
		camera(cameraMoveFlag);
		//タイトルと背景自動移動
		load_->Demo();
		backGround_->Demo();
		if (Timer == 0) {
			scene_ = Scene::Stage;
		}
		break;
	case GameScene::Scene::Stage:

		timers[scoreTimers[0]]->SetColor({ 1,1,1,1 });
		timers1[scoreTimers[1]]->SetColor({ 1,1,1,1 });
		timers2[scoreTimers[2]]->SetColor({ 1,1,1,1 });
		coro->SetColor({ 1,1,1,1 });
		if (player_->GetTimer() <= 0) {
			scoreTimer++;
		}
		
		scoreTimers[0] = (scoreTimer / 60) % 10;
		scoreTimers[1] = (scoreTimer / 600) % 6;
		scoreTimers[2] = (scoreTimer / 3600) % 10;

		player_->SetOverTakingCount(enemyPop_->GetEnemyOverTakingCount());
		player_->Updata();

		enemyPop_->SetPlayer(player_);
		enemyPop_->SetWing(wing_);
		enemyPop_->Update(model_);

		number = enemyPop_->GetEnemyOverTakingCount();

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
		player_->ResetSpeed(0);
		waitTimer++;
		if (waitTimer >= 0.5 * 60) {
			BarAlpha += 0.01f;
			BlackAlpha += 0.02f;
			// スプライトの徐々に描画する処理
			BlackFilter->SetColor({ 1,1,1,BlackAlpha });
			RetryFont[0]->SetColor({ 1,1,1,BarAlpha });
			RetryFont[1]->SetColor({ 1,1,1,BarAlpha });
			TitleFont[0]->SetColor({ 1,1,1,BarAlpha });
			TitleFont[1]->SetColor({ 1,1,1,BarAlpha });
			TitleCar_->SetColor({ 1,1,1,BarAlpha });
			ChangeFlag->SetColor({ 1,1,1,BarAlpha });
			
			timers[scoreTimers[0]]->SetColor({ 1,1,1,BarAlpha });
			timers1[scoreTimers[1]]->SetColor({ 1,1,1,BarAlpha });
			timers2[scoreTimers[2]]->SetColor({ 1,1,1,BarAlpha });
			coro->SetColor({ 1, 1, 1, BarAlpha });
			
			// アルファ値が限界を超えない処理
			if (BarAlpha >= 1.0f)
			{
				BarAlpha = 1.0f;
			}

			if (BlackAlpha >= 0.9f)
			{
				BlackAlpha = 0.9f;
			}
		}
		// シーンチェンジタイトル
		if (BlackAlpha == 0.9f) {
			if (ChangeFlag->GetPosition().x == titlepos.x)
			{
				if (input_->TriggerKey(DIK_SPACE)) {
					title = true;
				}
			}
			// シーンチェンジゲームシーン
			if (ChangeFlag->GetPosition().x == retryPos.x) {
				if (input_->TriggerKey(DIK_SPACE)) {
					rePlay = true;
				}
			}
		}
		if (input_->TriggerKey(DIK_LEFT)) {
			ChangeFlag->SetPosition({ titlepos.x,titlepos.y });
		}
		if (input_->TriggerKey(DIK_RIGHT)) {
			ChangeFlag->SetPosition({ retryPos.x,retryPos.y });
		}
		if(ChangeFlag)
		//道路更新
		load_->Update(player_->GetPlayerSpeed());
		//背景更新
		backGround_->Update(player_->GetPlayerSpeed());
		//風更新
		wing_->Update(player_->GetPlayerPos());

		if (rePlay == 1 || title == 1) {
			viewProjection_.eye = keepCamera;
			Timer = 120;
			scene_ = Scene::Initialize;
		}
		break;
	case GameScene::Scene::Initialize:
		//使ったもののおかたずけ
		Clean();
		scoreTimer = 0;
		player_->ResetSpeed(1);
		//道路更新
		load_->Update(player_->GetPlayerSpeed());
		//背景更新
		backGround_->Update(player_->GetPlayerSpeed());

		BarAlpha -= 0.03f;
		BlackAlpha -= 0.03f;
		// スプライトの徐々に描画する処理
		BlackFilter->SetColor({ 1,1,1,BlackAlpha });
		RetryFont[0]->SetColor({ 1,1,1,BarAlpha });
		RetryFont[1]->SetColor({ 1,1,1,BarAlpha });
		TitleFont[0]->SetColor({ 1,1,1,BarAlpha });
		TitleFont[1]->SetColor({ 1,1,1,BarAlpha });
		TitleCar_->SetColor({ 1,1,1,BarAlpha });
		ChangeFlag->SetColor({ 1,1,1,BarAlpha });

		break;
	default:
		break;
	}

}

void GameScene::Draw() {

	//オーディオ
	sound_->SoundPlayWave()

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
		//背景描画
		backGround_->Draw(viewProjection_);
		//道路描画
		load_->Draw(viewProjection_);
		// プレイヤーの描画
		player_->Draw(viewProjection_);

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
		if (titleWaitTime == 0) {
			titleRogo->Draw();
			space->Draw();
			gameStart->Draw();
		}
		break;
	case GameScene::Scene::Stage:
		if (player_->GetTimer() > 0) {
			stert321[(player_->GetTimer() / 60)]->Draw();
		}
		meter_->Draw();
		gameTime->Draw();
		needle->SetRotation((((player_->GetKmH() / 400.0f) * 240.0f) - 150.0f));
		needle->Draw();
		overTakingCount->Draw();
		DrawNunbers();

		timers[scoreTimers[0]]->SetPosition({ 350.0f, 65.0f });
		timers1[scoreTimers[1]]->SetPosition({ 280.0f, 65.0f });
		timers2[scoreTimers[2]]->SetPosition({ 170.0f, 65.0f });
		coro->SetPosition({ 230.0f,65.0f });
		timers[scoreTimers[0]]->Draw();
		timers1[scoreTimers[1]]->Draw();
		timers2[scoreTimers[2]]->Draw();
		coro->Draw();
		spaceSousa->Draw();
		ReanChageSousa->Draw();
		OverTakingCount->Draw();

		break;
	case GameScene::Scene::Result:
		if (waitTimer >= 0.5 * 60) {
			BlackFilter->Draw();
			TitleCar_->Draw();
			ChangeFlag->Draw();
			if (ChangeFlag->GetPosition().x == titlepos.x)
			{
				TitleFont[0]->Draw();
			}
			else {
				TitleFont[1]->Draw();
			}
			if (ChangeFlag->GetPosition().x == retryPos.x) {
				RetryFont[0]->Draw();
			}
			else {
				RetryFont[1]->Draw();
			}
		
			timers[scoreTimers[0]]->SetPosition({ 740.0f,200.0f });
			timers1[scoreTimers[1]]->SetPosition({ 670.0f,200.0f });
			timers2[scoreTimers[2]]->SetPosition({ 560.0f,200.0f });
			coro->SetPosition({ 620.0f,200.0f });
			timers[scoreTimers[0]]->Draw();
			timers1[scoreTimers[1]]->Draw();
			timers2[scoreTimers[2]]->Draw();
			coro->Draw();
		}
		
		break;
	case GameScene::Scene::Initialize:
		BlackFilter->Draw();
		TitleCar_->Draw();
		ChangeFlag->Draw();
		if (ChangeFlag->GetPosition().x == titlepos.x)
		{
			TitleFont[0]->Draw();
		}
		else {
			TitleFont[1]->Draw();
		}
		if (ChangeFlag->GetPosition().x == retryPos.x) {
			RetryFont[0]->Draw();
		}
		else {
			RetryFont[1]->Draw();
		}
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

void GameScene::AlphaChange(Scene x) {

	if (x == Scene::Title) {
		if (cameraMoveFlag == 0) {
			if (color < 1.0f) {
				color += 0.03;
			}
		}
		else if (cameraMoveFlag == 1) {
			if (color > 0.0f) {
				color -= 0.01;
			}
		}
	}
	
	gameStart->SetColor({ 1,1,1,color });
	space->SetColor({ 1,1,1,color });
	titleRogo->SetColor({ 1,1,1,color });
}

void GameScene::DrawNunbers() {
	divScore = 1000;
	for (int i = 0; i < maxScoreNum; i++)
	{
		scoreNum[i] = enemyPop_->GetEnemyOverTakingCount() % divScore / (divScore / 10);
		divScore = divScore / 10;
		spritePos.x = 990 - ((1 - i) * 40);
		scoreSprite[i].Draw(scoreNum[i], spritePos);
	}
	divScore = 1000;
	for (int i = 0; i < maxScoreNum; i++)
	{
		scoreNum2[i] = (int)player_->GetKmH() % divScore / (divScore / 10);
		divScore = divScore / 10;
		sprite2Pos.x = 1180 - ((1 - i) * 35);
		scoreSprite2[i].DrawSpeed(scoreNum2[i], sprite2Pos);
	}
}
