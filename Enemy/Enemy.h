#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Affin.h"
#include <cassert>
#include "collision.h"
#include "Player.h"

enum class CarModel {
	truck,// トラック（遅い車）
	prius,// プリウス（一般車）
	ferrari,// フェラーリ（速い車）
};

//自機クラスの前方宣言
class Player;

class Enemy
{
public:// メンバ関数

	// 初期化処理関数
	void Initialize(Model* model, Vector3& pos, CarModel carModel);

	// 更新処理関数
	void Update();

	// 車線変更処理関数
	void Lane1ChangeCheck(Vector3& pos);

	void Lane5ChangeCheck(Vector3& pos);

	void LaneChangeCheck(Vector3& pos);

	void LeftLaneChangeCheck(Vector3& pos);

	void RightLaneChangeCheck(Vector3& pos);

	// エネミーの車のモデルの種類のゲッター
	CarModel GetCarModel() { return carModel_; }

	// ポジションのゲッター
	Vector3 GetPos() { return worldTransform_.translation_; }

	// ワールドトランスフォームのゲッター
	WorldTransform GetWorldTransform() { return worldTransform_; }

	// 車線変更フラグのゲッター
	bool laneChangeFlag() const { return laneChangeFlag_; }

	bool lane1ChangeFlag() const { return lane1ChangeFlag_; }

	bool lane5ChangeFlag() const { return lane5ChangeFlag_; }

	bool leftLaneChangeFlag() const { return leftLaneChangeFlag_; }

	bool rightLaneChangeFlag() const { return rightLaneChangeFlag_; }

	// セッター
	void SetWouldTransform(WorldTransform worldTransform);

	void SetLeftLaneChangeFlag(bool leftLaneChangeFlag);

	void  SetPlayer(Player* player) { player_ = player; }

	// 描画処理関数
	void Draw(const ViewProjection& viewProjection);

	// 死亡フラグを渡す
	bool IsDead() const { return isDead_; }

	//フラグ勃起
	void ContactPlayer();
	bool ContactFlag() { return contactFlag; }

	//プレイヤーに抜かれた時
	int playerOverTaking;

private:// メンバ変数

	// ワールド変換データ
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;

	// 速度全般
	// 進む速度
	Vector3 moveSpeed_ = { 0.0f,0.0f,1.0f };
	// 回転速度
	Vector3 rotationSpeed_ = { 0.1f,0.1f, 0.1f };

	// デスフラグ
	bool isDead_ = false;

	// 車のパターン
	CarModel carModel_ = CarModel::prius;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 生きている時間
	int lifeTimer = 0;
	int lifeInterval = 5 * 60;

	// 一つのレーンの幅
	float loadWidth = 18.5f;

	// 車線変更フラグ
	bool laneChangeFlag_ = false;
	bool lane1ChangeFlag_ = false;
	bool lane5ChangeFlag_ = false;
	bool leftLaneChangeFlag_ = false;
	bool rightLaneChangeFlag_ = false;

	// 車線変更を行う際の前のの車との判定をとる半径
	float laneRadius = 8 * 10;

	// 最初の位置を保存
	Vector3 initPos;

	//当たった判定フラグ
	bool contactFlag = false;

	//まっすぐに当たった場合
	bool contactVer0 = false;
	int fukitobiTimeMax = 60;
	int fukitobiTime = 0;

	//右移動中に当たった場合
	bool contactVer1 = false;
	//左移動中に当たった場合
	bool contactVer2 = false;

	Collision* collision_ = nullptr;
	Player* player_ = nullptr;
};

