#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <time.h>
#include "Vector2.h"
#include "Vector4.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete TitleCar_;
	for (int i = 0; i < 3; i++) {
		delete stert321[i];
	}
	delete meter_;
	delete needle;
}

void GameScene::Initialize() {
	srand(time(nullptr));
	dxCore_ = DirectXCore::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//�RD���f���̐���
	model_ = Model::Create();

	// �v���C���[��new
	player_ = new Player();

	// �G�̐�����new
	enemyPop_ = new EnemyPop();
	enemy_ = new Enemy();
	enemyPop_->Initialize();

	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();
	viewProjection_.eye.x = 0;
	viewProjection_.eye.y += 70;
	viewProjection_.eye.z -= 80;
	viewProjection_.target.y += 2;
	gamePlayCameraPos = viewProjection_.eye;
	cameraMoveFlag = 0;
	Timer = 120;

	//�J�����̈ʒu�ւ�
	viewProjection_.eye = { -70,63,-80 };
	keepCamera = viewProjection_.eye;
	cameraTransFlag = 0;
	cameraSpeed = { 1.0f, 1.0f, 1.0f };


	//���H����
	loadModel_ = Model::CreateFromOBJ("load", true);
	load_ = new Load();
	load_->Initialize(loadModel_);

	//�w�i����
	groundRightModel_ = Model::CreateFromOBJ("BackGroundRight", true);
	groundLeftModel_ = Model::CreateFromOBJ("BackGroundLeft", true);

	backGround_ = new BackGround();
	backGround_->Initialize(groundRightModel_, groundLeftModel_);

	//������
	wingModel_ = Model::CreateFromOBJ("wing", true);
	wing_ = new Wing();
	wing_->Initialize(wingModel_);


	Sprite::LoadTexture(1, L"Resources/TitleCar.png");
	TitleCar_ = Sprite::Create(1, { 640.0f, 360.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	TitleCar_->SetSize({ 800.0f, 600.0f });


	//�X�^�[�g�̃J�E���g�̂̃e�N�X�`��
	Sprite::LoadTexture(2, L"Resources/stert321.png");
	for (int i = 0; i < 3; i++) {

		stert321[i] = Sprite::Create(2, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		stert321[i]->SetTextureRect({ 256.0f - (128.0f * i), 0.0f }, { 128.0f, 192.0f });
		stert321[i]->SetSize({ 128.0f, 128.0f });

	}

	Sprite::LoadTexture(3, L"Resources/meter.png");
	meter_ = Sprite::Create(3, { 1150.0f, 600.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	meter_->SetSize({ 200.0f, 200.0f });


	//�j�̃e�N�X�`��
	Sprite::LoadTexture(4, L"Resources/needle.png");
	needle = Sprite::Create(4, { 1150.0f, 600.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	needle->SetSize({ 7.0f, 170.0f });
	needle->SetRotation(-150.0f);

	Sprite::LoadTexture(5, L"Resources/TitleRogo.png");
	titleRogo = Sprite::Create(5, { 350.0f, 220.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	titleRogo->SetSize({ 608.0f, 246.0f });

	Sprite::LoadTexture(6, L"Resources/Space.png");
	space = Sprite::Create(6, { 800.0f, 520.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	space->SetSize({ 200.0f, 100.0f });


	Sprite::LoadTexture(7, L"Resources/TimeFont.png");
	gameTime = Sprite::Create(7, { 75.0f, 50.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	gameTime->SetSize({ 100.0f, 30.0f });

	Sprite::LoadTexture(8, L"Resources/300.png");
	overTakingCount = Sprite::Create(8, { 1150.0f, 75.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
	overTakingCount->SetSize({ 150.0f, 75.0f });

	Sprite::LoadTexture(9, L"Resources/123.png");
	for (int i = 0; i < 9; i++) {

		numbers[i] = Sprite::Create(9, { 1080.0f, 75.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.5f });
		numbers[i]->SetTextureRect({ 800.0f - (80.0f * i), 0.0f }, { 800.0f, 80.0f });
		numbers[i]->SetSize({ 80.0f, 80.0f });

	}

	color = 1.0f;
	rePlay = 0;
	title = 0;
	number = 0;

	for (int i = 0; i < maxScoreNum; i++)
	{
		scoreSprite[i].Initialize();
		scoreSprite2[i].Initialize();
	}

	viewProjection_.UpdateMatrix();
}

void GameScene::Clean() {
	cameraMoveFlag = 0;
	cameraTransFlag = 0;
	color = 1.0f;

	if (rePlay == 1) {
		rePlay = 0;
		viewProjection_.eye = gamePlayCameraPos;
		scene_ = Scene::Stage;
	}
	else if (title == 1) {
		title = 0;
		viewProjection_.eye = keepCamera;
		scene_ = Scene::Title;
	}

}

void GameScene::Update() {

	if (cameraMoveFlag == 1) {
		if (Timer > 0) {
			Timer--;
		}
	}
	switch (scene_) {
	case GameScene::Scene::Blackout:
		break;
	case GameScene::Scene::Title:
		if (input_->TriggerKey(DIK_SPACE)) {
			cameraMoveFlag = 1;
		}
		AlphaChange(scene_);
		camera(cameraMoveFlag);
		//�^�C�g���Ɣw�i�����ړ�
		load_->Demo();
		backGround_->Demo();
		if (Timer == 0) {
			scene_ = Scene::Stage;
		}
		break;
	case GameScene::Scene::Stage:


		player_->SetOverTakingCount(enemyPop_->GetEnemyOverTakingCount());
		player_->Updata();

		enemyPop_->SetPlayer(player_);
		enemyPop_->SetWing(wing_);
		enemyPop_->Update(model_);

		number = enemyPop_->GetEnemyOverTakingCount();

		//���H�X�V
		load_->Update(player_->GetPlayerSpeed());
		//�w�i�X�V
		backGround_->Update(player_->GetPlayerSpeed());
		//���X�V
		wing_->Update(player_->GetPlayerPos());

		if (player_->GetPlayerPos().z > enemyPop_->GetGoalEmemyPos()) {
			scene_ = Scene::Result;
		}
		break;
	case GameScene::Scene::Result:
		camera(0);
		player_->Updata();
		//���H�X�V
		load_->Update(player_->GetPlayerSpeed());
		//�w�i�X�V
		backGround_->Update(player_->GetPlayerSpeed());
		//���X�V
		wing_->Update(player_->GetPlayerPos());

		if (rePlay == 1 || title == 1) {
			scene_ = Scene::Initialize;
		}
		break;
	case GameScene::Scene::Initialize:
		//�g�������̂̂���������
		Clean();

		break;
	default:
		break;
	}

}

void GameScene::Draw() {

	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* commandList = dxCore_->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCore_->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Model::PreDraw(commandList);

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	switch (scene_) {
	case GameScene::Scene::Blackout:
		break;
	case GameScene::Scene::Title:
		//�w�i�`��
		backGround_->Draw(viewProjection_);
		//���H�`��
		load_->Draw(viewProjection_);
		// �v���C���[�̕`��
		player_->Draw(viewProjection_);

		break;
	case GameScene::Scene::Stage:
		//�w�i�`��
		backGround_->Draw(viewProjection_);
		//���H�`��
		load_->Draw(viewProjection_);
		// �v���C���[�̕`��
		player_->Draw(viewProjection_);
		//���`��
		wing_->Draw(viewProjection_);
		// �G�̕`��
		enemyPop_->Draw(viewProjection_);


		break;
	case GameScene::Scene::Result:
		//�w�i�`��
		backGround_->Draw(viewProjection_);
		//���H�`��
		load_->Draw(viewProjection_);
		// �v���C���[�̕`��
		player_->Draw(viewProjection_);

		break;
	case GameScene::Scene::Initialize:

		break;
	default:
		break;
	}

	// 3D�I�u�W�F�N�g�`��㏈��
	Model::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

	switch (scene_) {
	case GameScene::Scene::Blackout:
		break;
	case GameScene::Scene::Title:
		titleRogo->Draw();
		space->Draw();
		break;
	case GameScene::Scene::Stage:
		if (player_->GetTimer() > 0) {
			stert321[(player_->GetTimer() / 60)]->Draw();
		}
		meter_->Draw();
		gameTime->Draw();
		needle->SetRotation((((player_->GetKmH() / 400.0f) * 240.0f) - 150.0f));
		needle->Draw();
		overTakingCount->Draw();
		DrawNunbers();
		break;
	case GameScene::Scene::Result:
		TitleCar_->Draw();
		break;
	case GameScene::Scene::Initialize:

		break;
	default:
		break;
	}

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::camera(int x) {
	if (x == 0) {
		if (keepCamera.x > viewProjection_.eye.x) {
			viewProjection_.eye.x += cameraSpeed.x;
		}
		if (keepCamera.y > viewProjection_.eye.y) {
			viewProjection_.eye.y += cameraSpeed.y;
		}
		if (keepCamera.z > viewProjection_.eye.z) {
			viewProjection_.eye.z += cameraSpeed.z;
		}

		if (keepCamera.x < viewProjection_.eye.x) {
			viewProjection_.eye.x -= cameraSpeed.x;
		}
		if (keepCamera.y < viewProjection_.eye.y) {
			viewProjection_.eye.y -= cameraSpeed.y;
		}
		if (keepCamera.z < viewProjection_.eye.z) {
			viewProjection_.eye.z -= cameraSpeed.z;
		}
	}
	else if (x == 1) {
		if (gamePlayCameraPos.x > viewProjection_.eye.x) {
			viewProjection_.eye.x += cameraSpeed.x;
		}
		if (gamePlayCameraPos.y > viewProjection_.eye.y) {
			viewProjection_.eye.y += cameraSpeed.y;
		}
		if (gamePlayCameraPos.z > viewProjection_.eye.z) {
			viewProjection_.eye.z += cameraSpeed.z;
		}

		if (gamePlayCameraPos.x < viewProjection_.eye.x) {
			viewProjection_.eye.x -= cameraSpeed.x;
		}
		if (gamePlayCameraPos.y < viewProjection_.eye.y) {
			viewProjection_.eye.y -= cameraSpeed.y;
		}
		if (gamePlayCameraPos.z < viewProjection_.eye.z) {
			viewProjection_.eye.z -= cameraSpeed.z;
		}
	}

	viewProjection_.UpdateMatrix();
}

void GameScene::AlphaChange(Scene x) {

	if (x == Scene::Title) {
		if (cameraMoveFlag == 1) {
			color -= 0.01;
		}
	}
	

	titleRogo->SetColor({ 1,1,1,color });
}

void GameScene::DrawNunbers() {
	divScore = 1000;
	for (int i = 0; i < maxScoreNum; i++)
	{
		scoreNum[i] = enemyPop_->GetEnemyOverTakingCount() % divScore / (divScore / 10);
		divScore = divScore / 10;
		spritePos.x = 990 - ((1 - i) * 40);
		scoreSprite[i].Draw(scoreNum[i], spritePos);
	}
	divScore = 1000;
	for (int i = 0; i < maxScoreNum; i++)
	{
		scoreNum2[i] = (int)player_->GetKmH() % divScore / (divScore / 10);
		divScore = divScore / 10;
		sprite2Pos.x = 1180 - ((1 - i) * 35);
		scoreSprite2[i].DrawSpeed(scoreNum2[i], sprite2Pos);
	}
}
