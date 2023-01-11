#pragma once

#include "DirectXCore.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <xaudio2.h>

#pragma comment(lib,"xaudio2.lib")

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCore* dxCore_);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	/// <summary>
	/// 使ったもののおかたずけ
	/// </summary>
	void Clean();

	enum class Scene {
		Blackout,//暗転シーン
		Title,//タイトル
		Stage,//バトルステージ
		Result,//リザルト
		Initialize,//初期化シーン
	};

	void DrawNunbers();


private: // メンバ変数
	//フェーズ
	Scene scene_ = Scene::Title;

	DirectXCore* dxCore_ = nullptr;
	Input* input_ = nullptr;
	
};
