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

/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene {

public: // �����o�֐�
	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private: // �����o�ϐ�
	DirectXCore* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio audio_;

	//3D���f��
	Model* model_ = nullptr;

	ViewProjection viewProjection_;

	//�v���C���[
	Player* player_ = nullptr;

	// �G�̐���
	EnemyPop* enemyPop_ = nullptr;

	Enemy* enemy_ = nullptr;

	//���H
	Model* loadModel_ = nullptr;
	Load* load_ = nullptr;

	//�X�v���C�g
	Sprite* sprite = nullptr;

	//�e�N�X�`���o���h��
	uint32_t textureHandle_ = 0u;

	//��
	Model* wingModel_ = nullptr;
	Wing* wing_ = nullptr;

	//�����蔻��
	Collision* cali_ = nullptr;


	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
};
