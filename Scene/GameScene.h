#pragma once

#include "Audio.h"
#include "DirectXCore.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "EnemyPop.h"
#include "Load.h"
#include "Enemy.h"
#include "Collision.h"
#include "wing.h"
#include "background.h"


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
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void camera(int x);

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


private: // メンバ変数
	//フェーズ
	Scene scene_ = Scene::Title;

	DirectXCore* dxCore_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	//ゲームクリア
	Sprite* TitleCar_ = nullptr;
	//最初のカウント
	Sprite* stert321[4];
	//スピードメーター
	Sprite* meter_ = nullptr;
	//メーターの針
	Sprite* needle = nullptr;


	//3Dモデル
	Model* model_ = nullptr;

	ViewProjection viewProjection_;

	//プレイヤー
	Player* player_ = nullptr;

	// 敵の生成
	EnemyPop* enemyPop_ = nullptr;

	Enemy* enemy_ = nullptr;

	//道路
	Model* loadModel_ = nullptr;
	Load* load_ = nullptr;

	//背景
	Model* groundRightModel_ = nullptr;
	BackGround* backGround_ = nullptr;

	Model* groundLeftModel_ = nullptr;

	//風
	Model* wingModel_ = nullptr;
	Wing* wing_ = nullptr;

	//当たり判定
	Collision* cali_ = nullptr;

	Vector3 gamePlayCameraPos;
	Vector3 keepCamera;

	int cameraTransFlag;
	Vector3 cameraSpeed;

	int cameraMoveFlag;
	int Timer;


	int rePlay;
	int title;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
