#include "Player.h"
#include "WinApp.h"
#include"MyMath.h"


void Player::Initialize(Model* model,float WindowWidth,float WindowHeight) {
	//NULL�|�C���^�`�F�b�N
	assert(model);
	model_ = model;

	//�V���O���C���X�^���X���擾����
	input_ = Input::GetInstance();


	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 2, -2, 3 };

	//3D���f���̍쐬
	modelBullet_ = Model::CreateFromOBJ("Bullet", true);
	playerModel_ = Model::CreateFromOBJ("juu", true);
	//3D���e�B�N���̃��[���h�g�����X�t�H�[��������
	worldTransform3DReticle_.Initialize();

	//���e�B�N���p�e�N�X�`���擾
	textureReticle = TextureManager::Load("aim.png");
	//�X�v���C�g����
	sprite2DReticle_.reset(Sprite::
		Create(textureReticle, Vector2(WindowWidth / 2, WindowHeight / 2 + 12),
			Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));

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
		Create(textureReticle_FULL, Vector2(300, 640), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));
	spriteHP_1.reset(Sprite::
		Create(textureReticle_1, Vector2(300, 640), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));
	spriteHP_2.reset(Sprite::
		Create(textureReticle_2, Vector2(300, 640), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));
	spriteHP_3.reset(Sprite::
		Create(textureReticle_3, Vector2(300, 640), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));
	spriteHP_4.reset(Sprite::
		Create(textureReticle_4, Vector2(300, 640), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));
	spriteHP_5.reset(Sprite::
		Create(textureReticle_5, Vector2(300, 640), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));
	spriteHP_6.reset(Sprite::
		Create(textureReticle_6, Vector2(300, 640), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));
	spriteHP_7.reset(Sprite::
		Create(textureReticle_7, Vector2(300, 640), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));

	DrawHpSelect = 0;
	playerHp = 7;
	isShake = 0;
	shakeTime = 10;

	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Player::Move() {


	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});


	//�s��X�V
	AffinTrans::affin(worldTransform_);
	worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	worldTransform_.TransferMatrix();
}

void Player::ReticleUpdate(const ViewProjection& viewProjection) {




}

void Player::Update(const ViewProjection& viewProjection) {

	Move();
	//�e���ˏ���
	//���˃^�C�}�[�J�E���g�_�E��
	BulletTimer--;
	//���e�B�N��
	ReticleUpdate(viewProjection);

	if (isShake == 1) {
		shakeTime--;
		if (shakeTime < 0) {
			isShake = 0;
		}
	}

	//���ԂɒB������
	if (BulletTimer <= 0) {
		Attack(viewProjection);				//�e�𔭎�
		BulletTimer = 20;	//���˃^�C�}�[��������
	}

	//�e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update(viewProjection);
	}
}

void Player::Draw(ViewProjection viewProjection_) {

	playerModel_->Draw(worldTransform_, viewProjection_);
	//�e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}


void Player::Attack(const ViewProjection& viewProjection_) {
	//if (input_->IsTriggerMouse(0) || input_->IsPressMouse(0)) {


	//	//�e�̑��x
	//	const float kBulletSpeed = 4.0f;
	//	Vector3 velocity(0, 0, kBulletSpeed);


	//	//���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
	//	velocity = bVelocity(velocity, worldTransform_);

	//	//���@����Ə��I�u�W�F�N�g�ւ̃x�N�g��
	//	velocity = viewProjection_.target - viewProjection_.eye;
	//	velocity = MyMath::vector3Normalize(velocity) * kBulletSpeed;

	//	//�e�𐶐���������
	//	std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
	//	newBullet->worldSet(&worldTransform_);
	//	//�e���J�����ʒu�ɃZ�b�g
	//	newBullet->Initialize(modelBullet_, MyMath::GetWorldTransform(worldTransform_.parent_->matWorld_), velocity, texture2dame, texture4dame);

	//	//�e�̓o�^
	//	bullets_.push_back(std::move(newBullet));
	//}

}

void Player::DrawSprite() {
	sprite2DReticle_->Draw();

	if (DrawHpSelect == 0) {
		if (playerHp == 7) {
			spriteHP_FULL->Draw();
		}
		else if (playerHp == 6) {
			spriteHP_1->Draw();
		}
		else if (playerHp == 5) {
			spriteHP_2->Draw();
		}
		else if (playerHp == 4) {
			spriteHP_3->Draw();
		}
		else if (playerHp == 3) {
			spriteHP_4->Draw();
		}
		else if (playerHp == 2) {
			spriteHP_5->Draw();
		}
		else if (playerHp == 1) {
			spriteHP_6->Draw();
		}
		else {
			spriteHP_7->Draw();
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

	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��ړ��������擾(���[���h���W)
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