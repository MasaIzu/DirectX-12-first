#pragma once

#include "DirectXCore.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "affin.h"
#include "Player.h"
#include "Enemy.h"
#include <sstream>

#include "EnemyBullet.h"
#include "Select.h"
#include "RailCamera.h"
#include "Ground.h"
#include "Skydome.h"

#include "BaseScene.h"
#include "SceneManager.h"

/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene : public BaseScene{

public: // �����o�֐�
	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

public:


	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	// �I������
	void Finalize() override;

	/// <summary>
	/// �Փ˔���Ɖ���
	/// </summary>
	void CheckAllCollisions();

	/// <summary>
	/// �G�e��ǉ�
	/// </summary>
	/// <param name = "enemyBullet">�G�e</param>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet>& enemyBullet);

	/// <summary>
	/// �G�����f�[�^�̓ǂݍ���
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// �G�����R�}���h�̍X�V
	/// </summary>
	void UpdateEnemyPopCommands_phase1();
	void UpdateEnemyPopCommands_phase2();
	void UpdateEnemyPopCommands_phase3();
	void UpdateEnemyPopCommands_phase4();

	//�V�[���؂�ւ�
	enum class Scene {
		First,//�^�C�g��
		Second,//�`���[�g���A��
		Third,//�X�e�[�W2
		Four,//��肩��
		Boss,//�{�X
		Back,//ty&�^�C�g����
		Loser,//�G�[�X
	};


	/// <summary>
	/// �G�����֐�
	/// </summary>
	void MakeEnemy(Vector3 EnemyPos);

	/// <summary>
	/// �X�e�[�W���Ƃ̏�����
	/// </summary>
	void secondInitialize();

	/// <summary>
	/// �G�ƓG�̒e�A�v�f
	/// </summary>
	void enemyUpdate(int x);

	/// <summary>
	/// �G�̌�n��
	/// </summary>
	void enemybay();

	//�e���X�g���擾
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return enemyBullets_; }

private: // �����o�ϐ�
	DirectXCore* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0;
	//�e�N�X�`���n���h��
	uint32_t enemyTextureHandle_ = 0;
	//�e�N�X�`���n���h��
	uint32_t enemy50TextureHandle_ = 0;
	//���e�B�N���̃e�N�X�`���n���h��
	uint32_t ReticleTextureHandle_ = 0;
	//�e�N�X�`���n���h��
	uint32_t dame2Texture_ = 0;
	uint32_t dame4Texture_ = 0;
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransformDame_;

	// 3D���f��
	Model* model_ = nullptr;
	Model* EnemyModel_ = nullptr;
	//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
	////�f�o�b�O�J����
	//DebugCamera* debugCamera_ = nullptr;
	//�J���������
	float viewAngle = 0.0f;

	//�V�[������
	Scene scene_ = Scene::First;

	WinApp* winApp_ = nullptr;

	//�V�[�����s��
	WorldTransform nextScene;
	std::unique_ptr<Sprite> nextSprite;
	uint32_t nextTexture_ = 0;


	std::unique_ptr<Sprite> finSprite;
	uint32_t finTexture_ = 0;

	std::unique_ptr<Sprite> loserSprite;
	uint32_t loserTexture_ = 0;

	//���L����
	Player* player_ = nullptr;
	int playerRadius = 2;
	//���e
	int playerBulletRadius = 2;

	//�G�L����
	std::list<std::unique_ptr<Enemy>> enemys_;
	int enemyRadius = 3;
	//�G�e
	//�e
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	int enemyBulletRadius = 1;

	//Boss
	int bossRadius = 30;
	Model* BossModel_ = nullptr;
	Model* BossHandModel_ = nullptr;
	int bossHandRadius = 20;


	//�|�����G�̐�
	int DeadEnemys = 0;
	//�G�����R�}���h
	std::stringstream enemyPopCommand_phase1;
	std::stringstream enemyPopCommand_phase2;
	std::stringstream enemyPopCommand_phase3;
	std::stringstream enemyPopCommand_phase4;

	//Skydome
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	//���[���J����
	RailCamera* railCamera_ = nullptr;
	//Ground
	Ground* ground_ = nullptr;
	Model* modelGround_ = nullptr;

	//SelectGround
	Select* select_ = nullptr;
	Model* selectModelGround_ = nullptr;
	Model* modelDome_ = nullptr;

	//�ҋ@���t���O
	bool isStand_ = false;

	//�ҋ@�^�C�}�[
	int standTime_ = 0;

	//�V�[���؂�ւ��^�C�}�[
	int sceneChange = 180;

	//�`��p�̐؂�ւ�
	int changeDraw = 0;

	SceneManager* sceneManager_ = nullptr;

	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
};