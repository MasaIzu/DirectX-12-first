#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <cassert>
#include "Input.h"
#include "ViewProjection.h"
#include <memory>
#include <list>

class Collision {
public:
    //プレイヤーとエネミーの座標を入る
    //プレイヤーの半径をx,y,zの順に入れる
    //エネミーの半径をx,y,zの順に入れる
    bool BoxCollision(Vector3 player, Vector3 enemy, Vector3 playerWidth,Vector3 enemyWidth);
    bool BoxCollision(Vector3 player, Vector3 enemy, Vector3 playerWidth, Vector3 enemyWidth,bool flag);

    void Contact(int playerMove ,Vector3 player,WorldTransform enemy,Vector3 enemyRotationMove, Vector3 enemyMove);
private:
    //ワールド変換データ
    WorldTransform worldTransform;

    //モデル
    Model* model = nullptr;
    //モデル
    Model* enemyBulletModel = nullptr;

    
};
