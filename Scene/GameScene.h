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
#include "ScoreSprite.h"
#include <xaudio2.h>

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

	void camera(int x);

	/// <summary>
	/// �g�������̂̂���������
	/// </summary>
	void Clean();

	enum class Scene {
		Blackout,//�Ó]�V�[��
		Title,//�^�C�g��
		Stage,//�o�g���X�e�[�W
		Result,//���U���g
		Initialize,//�������V�[��
	};

	/// <summary>
	/// alpha�l��ύX
	/// </summary>
	void AlphaChange(Scene x);


	void DrawNunbers();


private: // �����o�ϐ�
	//�t�F�[�Y
	Scene scene_ = Scene::Title;

	DirectXCore* dxCore_ = nullptr;
	Input* input_ = nullptr;
	//Audio* audio_ = nullptr;

	//�Q�[���N���A
	Sprite* TitleCar_ = nullptr;
	//�ŏ��̃J�E���g
	Sprite* stert321[3];
	//�X�s�[�h���[�^�[
	Sprite* meter_ = nullptr;
	//���[�^�[�̐j
	Sprite* needle = nullptr;
	//�^�C�g��
	Sprite* titleRogo = nullptr;
	//title���̃X�y�[�X
	Sprite* space = nullptr;
	//time
	Sprite* gameTime = nullptr;
	//�I�[�o�[�e�C�L���O�J�E���g
	Sprite* overTakingCount = nullptr;
	//123
	Sprite* numbers[10];
	//�Q�[���X�^�[�g
	Sprite* gameStart = nullptr;

	//�喃
	Sprite* timers[10];
	Sprite* timers1[10];
	Sprite* timers2[10];
	Sprite* coro;
	
	Sprite* OverTakingCount = nullptr;

	//�I�[�f�B�I
	SoundManager* sound_ = nullptr;
	SoundData soundData;


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

	//�w�i
	Model* groundRightModel_ = nullptr;
	BackGround* backGround_ = nullptr;

	Model* groundLeftModel_ = nullptr;

	//��
	Model* wingModel_ = nullptr;
	Wing* wing_ = nullptr;

	//�����蔻��
	Collision* cali_ = nullptr;

	Vector3 gamePlayCameraPos;
	Vector3 keepCamera;

	int cameraTransFlag;
	Vector3 cameraSpeed;

	int cameraMoveFlag;
	int Timer;

	float color;

	int rePlay;
	int title;
	int titleWaitTime;

	int number;

	int scoreTimer = 0;

	int scoreTimers[3] = { 0,0,0 };

	// �X�R�A�̕`��p
	int divScore = 1000;
	const int maxScoreNum = 3;
	int scoreNum[3] = { 0 };
	int scoreNum2[3] = { 0 };
	Vector2 spritePos = { 1100,15 };
	Vector2 sprite2Pos = { 1200,630 };
	ScoreSprite scoreSprite[3];
	ScoreSprite scoreSprite2[3];

	// ���U���g�V�[���p�̕ϐ�
	float BarAlpha = 0.0f;
	float BlackAlpha = 0.0f;
	Sprite* TitleFont[2];
	Sprite* RetryFont[2];
	Sprite* BlackFilter = nullptr;
	Sprite* ChangeFlag = nullptr;
	Vector2 retryPos = { 580,400 };
	Vector2 titlepos = { 280,400 };
	int waitTimer = 0;

	//�@��������̃X�v���C�g
	Sprite* spaceSousa = nullptr;
	Sprite* ReanChageSousa = nullptr;

	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
};
