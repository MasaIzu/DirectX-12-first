#pragma once
#include <memory.h>
#include <list>
#include "Enemy.h"
#include "Collision.h"

//自機クラスの前方宣言
class Player;

//風クラスの前方宣言
class Wing;

class EnemyPop
{
public:// メンバ関数

	EnemyPop();
	void Initialize();

	// 更新処理
	void Update(Model* model);

	// 描画処理
	void Draw(const ViewProjection& viewProjection);

	//当たり判定(車の後ろにいる時)
	void CarBack();

	//当たり判定(交通事故)
	void TrafficAccidentEnemyVer();


public://ゲッターセッター
	int GetEnemyOverTakingCount();
	int GetTrafficAccidentFlag();
	void  SetPlayer(Player* player) { player_ = player; }
	void SetWing(Wing* wing) { wing_ = wing; }

	float GetGoalEmemyPos();

private:
	// 車種のパターンを抽選する関数
	void CarModelLottery();
private:// メンバ変数

	// 敵の生成パターンのリスト
	std::list<std::unique_ptr<Enemy>> enemy1;
	std::list<std::unique_ptr<Enemy>> enemy2;

	//自キャラ
	Player* player_ = nullptr;
	Collision* collision_ = nullptr;

	//風
	Wing* wing_ = nullptr;


	// 一つのレーンの幅
	float loadWidth = 18.5f;

	// 敵の位置のパターンの配列
	Vector3 enemyPos1[3] = { { 0 * loadWidth, 0, 32 * loadWidth},
							 {-2 * loadWidth, 0, 30 * loadWidth},
							 { 2 * loadWidth, 0, 31 * loadWidth} };

	Vector3 enemyPos2[3] = { {-1 * loadWidth, 0, 32 * loadWidth},
							 {-2 * loadWidth, 0, 31 * loadWidth},
							 { 1 * loadWidth, 0, 30 * loadWidth} };

	Vector3 enemyPos3[3] = { { 2 * loadWidth, 0, 32 * loadWidth},
							 {-1 * loadWidth, 0, 31 * loadWidth},
							 { 1 * loadWidth, 0, 30 * loadWidth} };

	Vector3 enemyPos4[4] = { { 2 * loadWidth, 0, 32 * loadWidth},
							 {-1 * loadWidth, 0, 31 * loadWidth},
							 { 0 * loadWidth, 0, 30 * loadWidth},
							 {-2 * loadWidth, 0, 34 * loadWidth} };

	Vector3 enemyPos5[4] = { { 1 * loadWidth, 0, 30 * loadWidth},
							 {-2 * loadWidth, 0, 33 * loadWidth},
							 {-1 * loadWidth, 0, 31 * loadWidth},
							 { 0 * loadWidth, 0, 34 * loadWidth} };
	// 敵のランダムパターン
	int carModelnum_ = 0;
	CarModel carModel_ = CarModel::truck;
	int carPattern_ = 0;

	// 敵のポップするタイマー
	int popTimer = 0;

	// 敵のポップする間隔のタイマー
	int popInterval = 2 * 60;

	int TrafficAccidentFlag;

	int overTakingCount = 200;

	// 敵のモデル
	Model* puriusModel = nullptr;
	Model* ferariModel = nullptr;
	Model* trakuModel = nullptr;

	// ゴールの敵
	std::unique_ptr<Enemy> GoalEnemy = nullptr;
	std::unique_ptr<Enemy> GoalFlagOBJ = nullptr;
	Model* GoalEnemyModel = nullptr;
	Model* GoalFlagOBJModel = nullptr;
	Vector3 GoalEnemyPos = { 0 * loadWidth, 0, 34 * loadWidth };
	bool goalFlag = false;
};

