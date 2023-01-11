#include "DirectXCore.h"
#include "GameScene.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "Audio.h"
#include "ErrorException.h"
#include "FPS.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* winApp_ = nullptr;
	DirectXCore* directXCore_ = nullptr;
	// 汎用機能
	Input* input_ = nullptr;
	GameScene* gameScene_ = nullptr;

	// ゲームウィンドウの作成
	winApp_ = new WinApp;
	winApp_->MakeWindow(L"適当ゲーム");

	// DirectX初期化処理
	directXCore_ = new DirectXCore;
	directXCore_->DirectXCoreInitialize(winApp_->Gethwnd(), winApp_->window_width, winApp_->window_height);

#pragma region 汎用機能初期化
	// 入力の初期化
	input_ = Input::GetInstance();
	input_->Initialize();


	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(directXCore_->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(directXCore_->GetDevice(), winApp_->window_width, winApp_->window_height);

	// デバッグテキスト初期化
	

	// 3Dモデル静的初期化
	Model::StaticInitialize();


#pragma endregion

	// ゲームシーンの初期化
	gameScene_ = new GameScene();
	gameScene_->Initialize(directXCore_);

	FPS* fps = new FPS;

	// メインループ
	while (true) {
		//fps制限
		fps->FpsControlBegin();

		// メッセージ処理
		if (winApp_->ProcessMessage()) {
			break;
		}

		// 入力関連の毎フレーム処理
		input_->Update();
		// ゲームシーンの毎フレーム処理
		gameScene_->Update();
		

		// 描画開始
		directXCore_->PreDraw();
		// ゲームシーンの描画
		gameScene_->Draw();
		
		// 描画終了
		directXCore_->PostDraw();

		//FPS固定
		fps->FpsControlEnd();
	}

	// 各種解放
	

	// ゲームウィンドウの破棄
#pragma region  WindowsAPI後始末

	winApp_->DeleteGameWindow();

#pragma endregion
	return 0;
}