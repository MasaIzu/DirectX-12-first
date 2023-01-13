#include "Player.h"
#include "WinApp.h"
#include"MyMath.h"


void Player::Initialize(Model* model,float WindowWidth,float WindowHeight) {
	//NULLポインタチェック
	assert(model);
	model_ = model;

	//シングルインスタンスを取得する
	input_ = Input::GetInstance();

	Window_Width = WindowWidth;
	Window_Height = WindowHeight;

	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 2, -2, 3 };

	//3Dモデルの作成
	modelBullet_ = Model::CreateFromOBJ("Bullet", true);
	playerModel_ = Model::CreateFromOBJ("juu", true);
	//3Dレティクルのワールドトランスフォーム初期化
	worldTransform3DReticle_.Initialize();

	//レティクル用テクスチャ取得
	textureReticle = TextureManager::Load("aim.png");
	//スプライト生成
	sprite2DReticle_.reset(Sprite::
		Create(textureReticle));

	textureReticle_FULL = TextureManager::Load("HPbar/HPfull.png");
	textureReticle_1 = TextureManager::Load("HPbar/HP_1.png");
	textureReticle_2 = TextureManager::Load("HPbar/HP_2.png");
	textureReticle_3 = TextureManager::Load("HPbar/HP_3.png");
	textureReticle_4 = TextureManager::Load("HPbar/HP_4.png");
	textureReticle_5 = TextureManager::Load("HPbar/HP_5.png");
	textureReticle_6 = TextureManager::Load("HPbar/HP_6.png");
	textureReticle_7 = TextureManager::Load("HPbar/HP_ALL.png");


	texture2dame = TextureManager::Load("2dame.png");
	texture4dame = TextureManager::Load("4dame.png");


	spriteHP_FULL.reset(Sprite::
		Create(textureReticle_FULL));
	spriteHP_1.reset(Sprite::
		Create(textureReticle_1));
	spriteHP_2.reset(Sprite::
		Create(textureReticle_2));
	spriteHP_3.reset(Sprite::
		Create(textureReticle_3));
	spriteHP_4.reset(Sprite::
		Create(textureReticle_4));
	spriteHP_5.reset(Sprite::
		Create(textureReticle_5));
	spriteHP_6.reset(Sprite::
		Create(textureReticle_6));
	spriteHP_7.reset(Sprite::
		Create(textureReticle_7));

	DrawHpSelect = 0;
	playerHp = 7;
	isShake = 0;
	shakeTime = 10;

	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Player::Move() {


	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});


	//行列更新
	AffinTrans::affin(worldTransform_);
	worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	worldTransform_.TransferMatrix();
}

void Player::ReticleUpdate(const ViewProjection& viewProjection) {




}

void Player::Update(const ViewProjection& viewProjection) {

	Move();
	//弾発射処理
	//発射タイマーカウントダウン
	BulletTimer--;
	//レティクル
	ReticleUpdate(viewProjection);

	if (isShake == 1) {
		shakeTime--;
		if (shakeTime < 0) {
			isShake = 0;
		}
	}

	//時間に達したら
	if (BulletTimer <= 0) {
		Attack(viewProjection);				//弾を発射
		BulletTimer = 20;	//発射タイマーを初期化
	}

	//弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update(viewProjection);
	}
}

void Player::Draw(ViewProjection viewProjection_) {

	playerModel_->Draw(worldTransform_, viewProjection_);
	//弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}


void Player::Attack(const ViewProjection& viewProjection_) {
	if (input_->MouseInputTrigger(0) || input_->MouseInputing(0)) {


		//弾の速度ssssss
		const float kBulletSpeed = 4.0f;
		Vector3 velocity(0, 0, kBulletSpeed);


		//速度ベクトルを自機の向きに合わせて回転させる
		velocity = bVelocity(velocity, worldTransform_);

		//自機から照準オブジェクトへのベクトル
		velocity = viewProjection_.target - viewProjection_.eye;
		velocity = MyMath::vector3Normalize(velocity) * kBulletSpeed;

		//弾を生成し初期化
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		//newBullet->worldSet(&worldTransform_);
		//弾をカメラ位置にセット
		newBullet->Initialize(modelBullet_, viewProjection_.eye, velocity, texture2dame, texture4dame);

		//弾の登録
		bullets_.push_back(std::move(newBullet));
	}

}

void Player::DrawSprite() {
	sprite2DReticle_->Draw(Vector2(Window_Width / 2, Window_Height / 2 + 12),
		Vector4(1, 1, 1, 1));

	if (DrawHpSelect == 0) {
		if (playerHp == 7) {
			spriteHP_FULL->Draw(Vector2(300, 640), Vector4(1, 1, 1, 1));
		}
		else if (playerHp == 6) {
			spriteHP_1->Draw(Vector2(300, 640), Vector4(1, 1, 1, 1));
		}
		else if (playerHp == 5) {
			spriteHP_2->Draw(Vector2(300, 640), Vector4(1, 1, 1, 1));
		}
		else if (playerHp == 4) {
			spriteHP_3->Draw(Vector2(300, 640), Vector4(1, 1, 1, 1));
		}
		else if (playerHp == 3) {
			spriteHP_4->Draw(Vector2(300, 640), Vector4(1, 1, 1, 1));
		}
		else if (playerHp == 2) {
			spriteHP_5->Draw(Vector2(300, 640), Vector4(1, 1, 1, 1));
		}
		else if (playerHp == 1) {
			spriteHP_6->Draw(Vector2(300, 640), Vector4(1, 1, 1, 1));
		}
		else {
			spriteHP_7->Draw(Vector2(300, 640), Vector4(1, 1, 1, 1));
		}
	}

}

void Player::OnCollision() {
	playerHp--;
	isShake = 1;
	shakeTime = 30;
}

Vector3 Player::bVelocity(Vector3 velocity, WorldTransform& worldTransform) {

	Vector3 result = { 0, 0, 0 };


	result.x = velocity.x * worldTransform.matWorld_.m[0][0] +
		velocity.y * worldTransform.matWorld_.m[1][0] +
		velocity.z * worldTransform.matWorld_.m[2][0];

	result.y = velocity.x * worldTransform.matWorld_.m[0][1] +
		velocity.y * worldTransform.matWorld_.m[1][1] +
		velocity.z * worldTransform.matWorld_.m[2][1];

	result.z = velocity.x * worldTransform.matWorld_.m[0][2] +
		velocity.y * worldTransform.matWorld_.m[1][2] +
		velocity.z * worldTransform.matWorld_.m[2][2];

	return result;
}

Vector3 Player::GetWorldPosition() {

	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

int Player::GetShake() {
	return isShake;
}

int Player::GetPlayerHp() {
	return playerHp;
}

void Player::worldReticleSet(WorldTransform* worldTransform) {

	worldTransform_.parent_ = worldTransform;

}


void Player::SetTarget(Vector3 Target) {

	target_ = Target;

}

void Player::setDrawSelect(int x) {
	DrawHpSelect = x;
}