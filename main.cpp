#include "DirectXCore.h"
#include "GameScene.h"
#include "TextureManager.h"
#include "WinApp.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* winApp_ = nullptr;
	DirectXCore* dxCore_ = nullptr;
	// 汎用機能
	Input* input = nullptr;
	GameScene* gameScene = nullptr;

	// ゲームウィンドウの作成
	winApp_ = WinApp::GetInstance();
	winApp_->WinApiInitialize();

	// DirectX初期化処理
	dxCore_ = DirectXCore::GetInstance();
	dxCore_->Initialize(winApp_);

#pragma region 汎用機能初期化
	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCore_->GetDevice());
	TextureManager::Load("white1x1.png");

	// 3Dモデル静的初期化
	Model::StaticInitialize();


#pragma endregion

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize();

	// メインループ
	while (true) {
		// メッセージ処理
		if (winApp_->ProcessMessage()) {
			break;
		}

		// 入力関連の毎フレーム処理
		input->Updata();
		// ゲームシーンの毎フレーム処理
		gameScene->Update();


		// 描画開始
		dxCore_->PreDraw();
		// ゲームシーンの描画
		gameScene->Draw();

		// 描画終了
		dxCore_->PostDraw();
	}

	// 各種解放


	// ゲームウィンドウの破棄
	winApp_->Finalize();

	return 0;
}