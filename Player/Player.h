#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"Input.h"
#include"Vector3.h"
#include"Affin.h"
#include"Collision.h"

class Player {

public:
    Player();
    ~Player();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Updata();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw(ViewProjection viewProjection_);

    /// <summary>
    /// 動き更新
    /// </summary>
    void PlayerMove();

    /// <summary>
    /// 車の後ろにいた時の処理
    /// </summary>
    void EnemyCarBack();

    /// <summary>
    /// 車と車の衝突時処理
    /// </summary>
    void TrafficAccident();

    /// <summary>
    /// 車と車の衝突時処理(フラグ立て)
    /// </summary>
    void TrafficAccidentFlag();

    /// <summary>
    /// 始まった時のカウントダウン
    /// </summary>
    void countDown();

    /// <summary>
    /// スピードによる位置調整
    /// </summary>
    void SpeedAccordingPosition();



public://ゲッター

    /// <summary>
    /// スピードゲッター
    /// </summary>
    Vector3 GetPlayerPos();

    /// <summary>
    /// スピードゲッター
    /// </summary>
    float GetPlayerSpeed();

    /// <summary>
    /// 時速のゲッター
    /// </summary>
    float GetKmH();

    /// <summary>
    /// 動いてるフラグ
    /// </summary>
    int GetMovingFlag();

    /// <summary>
    /// 追い抜きセット
    /// </summary>
    void SetOverTakingCount(int count);

    /// <summary>
    /// スタートタイマー取得
    /// </summary>
    int GetTimer();

private:
    //ワールド変換データ
    WorldTransform worldTransform_;

    Input* input_ = nullptr;
    Model* model_ = nullptr;
    Collision* collision_ = nullptr;


    //メンバ変数
    float playerSpeed;
    float playerMaxAccelerator;
    float playerJumpSpeed;

    float kmH;//km/h 時速
    float gravity;

    int jumpFlag;
    int junpFrame;

    int leftFlag;
    int rightFlag;
    int moving;
    float nextPos;

    float enemyBackSpeed;

    float playerSideMove;
    int timer;
    int accidentFlag;

    float saveSpeed;
    int saveSpeedFlag;
    int overTakingCount;
    int speedTimer;

    int bustFlag;
    float bustMax;
};