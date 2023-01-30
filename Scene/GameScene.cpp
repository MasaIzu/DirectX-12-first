#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <random>
#include <fstream>


GameScene::GameScene() {}

GameScene::~GameScene() {
	// delete sprite;
	delete model_;
	delete player_;
	delete modelSkydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCore::GetInstance();
	winApp_ = WinApp::GetInstance();
	input_ = Input::GetInstance();

	textureHandle_ = TextureManager::Load("Black.png");
	ReticleTextureHandle_ = TextureManager::Load("aim.png");
	model_ = Model::Create();
	EnemyModel_ = Model::CreateFromOBJ("UFO", true);
	//3D���f���̍쐬
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	//Ground
	modelGround_ = Model::CreateFromOBJ("Ground", true);
	//select
	selectModelGround_ = Model::CreateFromOBJ("SelectGround", true);
	modelDome_ = Model::CreateFromOBJ("SelectSkydome", true);
	//�{�X
	BossModel_ = Model::CreateFromOBJ("boss", true);
	BossHandModel_ = Model::CreateFromOBJ("bossHand", true);

	//enemyHP�p�e�N�X�`���擾
	enemyTextureHandle_ = TextureManager::Load("HPbar/enemyHP.png");
	enemy50TextureHandle_ = TextureManager::Load("HPbar/enemyHP_50.png");
	nextTexture_ = TextureManager::Load("tobu.png");
	finTexture_ = TextureManager::Load("touboe.png");
	loserTexture_ = TextureManager::Load("Loser.png");
	dame2Texture_ = TextureManager::Load("2dame.png");
	dame4Texture_ = TextureManager::Load("4dame.png");


	//�X�v���C�g����
	nextSprite.reset(Sprite::Create(nextTexture_));

	//�X�v���C�g����
	finSprite.reset(Sprite::Create(finTexture_));

	//�X�v���C�g����
	loserSprite.reset(Sprite::Create(loserTexture_));


	worldTransformDame_.Initialize();


	//���L�����̐���
	player_ = new Player();
	//Skydome
	skydome_ = new Skydome();
	//���[���J����
	railCamera_ = new RailCamera();
	
	//Select
	select_ = new Select();
	

	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();
	//���L�����̏�����
	player_->Initialize(model_, winApp_->window_width, winApp_->window_height);
	//���[���J�����̏�����
	railCamera_->Initialize(winApp_,Vector3(0, -23, -50), Vector3(0.2, 0, 0));
	//skydome�̏�����
	skydome_->Initialize(modelSkydome_);
	//ground�̏�����
	//ground_->Initialize(selectModelGround_);
	//Select�̏�����
	select_->Initialize(selectModelGround_, modelDome_);
	
	sceneManager_ = SceneManager::GetInstance();

	//�t�@�C���̓ǂݍ���
	LoadEnemyPopData();

}

void GameScene::Update() {

	if (sceneChange > 0) {
		sceneChange--;
	}
	if (input_->TriggerKey(DIK_SPACE))
	{
		sceneManager_->ChangeScene("TITLE");
	}

	switch (scene_) {
	case Scene::First://�^�C�g��
	default:
		//�`��؂�ւ�
		changeDraw = 0;

		//���[���J����
		railCamera_->setShake(player_->GetShake());
		railCamera_->cameraSet(0);
		railCamera_->Update();
		//�s��̍Čv�Z
		viewProjection_.UpdateMatrix();

		//���L�����̍X�V
		player_->setDrawSelect(1);
		player_->SetTarget(railCamera_->GetTarget());
		player_->worldReticleSet(railCamera_->GetWorldTransform());
		player_->Update(railCamera_->GetViewProjection());

		if (input_->TriggerKey(DIK_RETURN)) {
			sceneChange = 120;
			scene_ = Scene::Second;
		}
		break;
	case Scene::Second://���ւ̏���
		//�`��؂�ւ�
		changeDraw = 1;
		if (sceneChange == 0) {

			secondInitialize();
			DeadEnemys = 0;
			scene_ = Scene::Third;
		}

		break;
	case Scene::Third://�X�e�[�W2
		//�`��؂�ւ�
		changeDraw = 2;

		if (player_->GetPlayerHp() <= 0) {
			scene_ = Scene::Loser;
		}

		//���[���J����
		railCamera_->setShake(player_->GetShake());
		railCamera_->Update();
		//�s��̍Čv�Z
		viewProjection_.UpdateMatrix();

		//���L�����̍X�V
		player_->setDrawSelect(0);
		player_->SetTarget(railCamera_->GetTarget());
		player_->worldReticleSet(railCamera_->GetWorldTransform());
		player_->Update(railCamera_->GetViewProjection());

		UpdateEnemyPopCommands_phase1();
		//�G�����R�}���h�[
		if (DeadEnemys > 9) {
			UpdateEnemyPopCommands_phase2();
		}
		if (DeadEnemys > 26) {
			UpdateEnemyPopCommands_phase3();
		}

		enemyUpdate(0);

		CheckAllCollisions();

		if (DeadEnemys == 60) {
			scene_ = Scene::Back;
			enemybay();
			DeadEnemys = 0;
		}

		break;

	case Scene::Four://��肩��
		//�`��؂�ւ�
		changeDraw = 3;

		railCamera_->cameraSet(1);
		railCamera_->Update();

		player_->setDrawSelect(0);
		player_->SetTarget(railCamera_->GetTarget());
		player_->worldReticleSet(railCamera_->GetWorldTransform());
		player_->Update(railCamera_->GetViewProjection());


		scene_ = Scene::Boss;
		sceneChange = 300;
		secondInitialize();
		break;
	case Scene::Boss://�{�X
		//�`��؂�ւ�
		changeDraw = 4;

		if (player_->GetPlayerHp() <= 0) {
			scene_ = Scene::Loser;
		}

		if (sceneChange == 0) {
			UpdateEnemyPopCommands_phase4();
		}
		railCamera_->setShake(player_->GetShake());
		railCamera_->cameraSet(0);
		railCamera_->Update();

		player_->setDrawSelect(0);
		player_->SetTarget(railCamera_->GetTarget());
		player_->worldReticleSet(railCamera_->GetWorldTransform());
		player_->Update(railCamera_->GetViewProjection());

		enemyUpdate(0);

		CheckAllCollisions();

		/*if (boss_->GetBossHp() < 0) {
			secondInitialize();
			scene_ = Scene::Back;
		}*/


		break;
	case Scene::Back://ty&�^�C�g����
		//�`��؂�ւ�
		changeDraw = 5;
		enemybay();
		if (input_->TriggerKey(DIK_RETURN)) {
			scene_ = Scene::First;
			secondInitialize();
		}

		break;

	case Scene::Loser://�G�[�X
		//�`��؂�ւ�
		changeDraw = 6;
		enemybay();
		if (input_->TriggerKey(DIK_RETURN)) {
			secondInitialize();
			scene_ = Scene::First;
		}

		break;
	}

}

void GameScene::Draw() {

	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	
	// �[�x�o�b�t�@�N���A
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Model::PreDraw(commandList);

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	if (changeDraw == 0) {
		select_->Draw(railCamera_->GetViewProjection());
	}
	if (changeDraw == 2 || changeDraw == 3 || changeDraw == 4) {
		//skydome_->Draw(railCamera_->GetViewProjection());
		select_->GameDraw(railCamera_->GetViewProjection());
		//ground_->Draw(railCamera_->GetViewProjection());
	}

	player_->Draw(railCamera_->GetViewProjection());

	for (std::unique_ptr<Enemy>& enemy_ : enemys_) {
		enemy_->Draw(railCamera_->GetViewProjection());
	}

	//�e�X�V
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
		bullet->Draw(railCamera_->GetViewProjection(), textureHandle_);
	}

	// 3D�I�u�W�F�N�g�`��㏈��
	Model::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	
	player_->DrawSprite();

	if (changeDraw == 1) {
		nextSprite->Draw(Vector2(winApp_->window_width / 2, winApp_->window_height / 2),
			Vector4(1, 1, 1, 1));
	}
	if (changeDraw == 5) {
		finSprite->Draw(Vector2(winApp_->window_width / 2, winApp_->window_height / 2),
			Vector4(1, 1, 1, 1));
	}
	if (changeDraw == 6) {
		loserSprite->Draw(Vector2(winApp_->window_width / 2, winApp_->window_height / 2),
			Vector4(1, 1, 1, 1));
	}


	
	
	//// �X�v���C�g�`��㏈��
	//Sprite::PostDraw();

#pragma endregion
}

void GameScene::Finalize()
{
}

void GameScene::CheckAllCollisions() {
	//����Ώۂ�A��B�̍��W
	Vector3 posA, posB;

	//���e���X�g�̎擾
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	//�G�e���X�g�̎擾
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = GetBullets();

#pragma region ���L�����ƓG�e�̓����蔻��

	//���L�����̍��W
	posA = player_->GetWorldPosition();

	//���L�����ƓG�e���ׂĂ̓����蔻��
	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {
		//�G�e�̍��W
		posB = bullet->GetWorldPosition();

		float a = posB.x - posA.x;
		float b = posB.y - posA.y;
		float c = posB.z - posA.z;

		float d = sqrt(a * a + b * b + c * c);

		if (d <= playerRadius + enemyBulletRadius) {
			//���L�����̏Փˎ��R�[���o�b�N���Ăяo��
			player_->OnCollision();
			//�G�e�̏Փˎ��R�[���o�b�N���Ăяo��
			bullet->OnCollision();
		}
	}

#pragma endregion

#pragma region ���e�ƓG�L�����̓����蔻��

	//�G�L�����̍��W
	for (std::unique_ptr<Enemy>& enemy_ : enemys_) {
		posA = enemy_->GetWorldPosition();

		//���L�����ƓG�e���ׂĂ̓����蔻��
		for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
			//���e�̍��W
			posB = bullet->GetWorldPosition();

			float a = posB.x - posA.x;
			float b = posB.y - posA.y;
			float c = posB.z - posA.z;

			float d = sqrt(a * a + b * b + c * c);

			if (d <= playerBulletRadius + enemyRadius) {

				//�G�L�����̏Փˎ��R�[���o�b�N���Ăяo��
				enemy_->OnCollision();

				//���e�̏Փˎ��R�[���o�b�N���Ăяo��
				bullet->OnCollision();

				DeadEnemys++;
			}
		}
	}
#pragma endregion

#pragma region ���e�ƓGBoss�̓����蔻��

	//posA = boss_->GetWorldPositionBoss();

	////���L�����ƓG�e���ׂĂ̓����蔻��
	//for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
	//	//���e�̍��W
	//	posB = bullet->GetWorldPosition();

	//	float a = posB.x - posA.x;
	//	float b = posB.y - posA.y;
	//	float c = posB.z - posA.z;

	//	float d = sqrt(a * a + b * b + c * c);

	//	if (d <= playerBulletRadius + bossRadius) {

	//		//�G�L�����̏Փˎ��R�[���o�b�N���Ăяo��
	//		boss_->OnCollisionBoss();

	//		//���e�̏Փˎ��R�[���o�b�N���Ăяo��
	//		bullet->OnCollision();

	//	}
	//}

#pragma endregion

#pragma region ���e�ƓGBossHand�̓����蔻��

	//posA = boss_->GetWorldPositionRight();

	////���L�����ƓG�e���ׂĂ̓����蔻��
	//for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
	//	//���e�̍��W
	//	posB = bullet->GetWorldPosition();

	//	float a = posB.x - posA.x;
	//	float b = posB.y - posA.y;
	//	float c = posB.z - posA.z;

	//	float d = sqrt(a * a + b * b + c * c);

	//	if (d <= playerBulletRadius + bossHandRadius) {

	//		//�G�L�����̏Փˎ��R�[���o�b�N���Ăяo��
	//		boss_->OnCollisionRight();

	//		//���e�̏Փˎ��R�[���o�b�N���Ăяo��
	//		bullet->OnCollision();

	//	}
	//}

#pragma endregion

#pragma region ���e�ƓGBossHand�̓����蔻��

	//posA = boss_->GetWorldPositionLeft();

	////���L�����ƓG�e���ׂĂ̓����蔻��
	//for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
	//	//���e�̍��W
	//	posB = bullet->GetWorldPosition();

	//	float a = posB.x - posA.x;
	//	float b = posB.y - posA.y;
	//	float c = posB.z - posA.z;

	//	float d = sqrt(a * a + b * b + c * c);

	//	if (d <= playerBulletRadius + bossHandRadius) {

	//		//�G�L�����̏Փˎ��R�[���o�b�N���Ăяo��
	//		boss_->OnCollisionLeft();

	//		//���e�̏Փˎ��R�[���o�b�N���Ăяo��
	//		bullet->OnCollision();

	//	}
	//}

#pragma endregion

#pragma region ���e�ƓG�e�̓����蔻��

	//���L�����ƓG�e���ׂĂ̓����蔻��
	//for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
	//	for (const std::unique_ptr<EnemyBullet>& bullet2 : enemyBullets) {

	//		//���e�̍��W
	//		posA = bullet->GetWorldPosition();

	//		//�G�e�̍��W
	//		posB = bullet2->GetWorldPosition();

	//		float a = posB.x - posA.x;
	//		float b = posB.y - posA.y;
	//		float c = posB.z - posA.z;

	//		float d = sqrt(a * a + b * b + c * c);

	//		if (d <= playerBulletRadius + enemyBulletRadius) {
	//			//���L�����̏Փˎ��R�[���o�b�N���Ăяo��
	//			bullet->OnCollision();
	//			//�G�e�̏Փˎ��R�[���o�b�N���Ăяo��
	//			bullet2->OnCollision();
	//		}
	//	}
	//}

#pragma endregion
}

void GameScene::AddEnemyBullet(std::unique_ptr<EnemyBullet>& enemyBullet) {
	//���X�g�ɓo�^����
	enemyBullets_.push_back(std::move(enemyBullet));
}

void GameScene::LoadEnemyPopData() {

	//�t�@�C�����J��
	std::ifstream file;
	file.open("Resources/enemyPop_phase1.csv");

	assert(file.is_open());

	// �o�b�t�@���N���A���܂��B
	enemyPopCommand_phase1.str("");
	// ��Ԃ��N���A���܂��B
	enemyPopCommand_phase1.clear(std::stringstream::goodbit);

	//�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	enemyPopCommand_phase1 << file.rdbuf();

	//�t�@�C�������
	file.close();

	file.open("Resources/enemyPop_phase2.csv");

	assert(file.is_open());

	// �o�b�t�@���N���A���܂��B
	enemyPopCommand_phase2.str("");
	// ��Ԃ��N���A���܂��B
	enemyPopCommand_phase2.clear(std::stringstream::goodbit);

	//�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	enemyPopCommand_phase2 << file.rdbuf();

	//�t�@�C�������
	file.close();

	//�t�@�C�����J��
	file.open("Resources/enemyPop_phase3.csv");

	assert(file.is_open());

	// �o�b�t�@���N���A���܂��B
	enemyPopCommand_phase3.str("");
	// ��Ԃ��N���A���܂��B
	enemyPopCommand_phase3.clear(std::stringstream::goodbit);

	//�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	enemyPopCommand_phase3 << file.rdbuf();

	//�t�@�C�������
	file.close();

	//�t�@�C�����J��
	file.open("Resources/enemyPop_phase4.csv");

	assert(file.is_open());

	// �o�b�t�@���N���A���܂��B
	enemyPopCommand_phase4.str("");
	// ��Ԃ��N���A���܂��B
	enemyPopCommand_phase4.clear(std::stringstream::goodbit);

	//�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	enemyPopCommand_phase4 << file.rdbuf();

	//�t�@�C�������
	file.close();

}


void GameScene::UpdateEnemyPopCommands_phase1() {
	//�ҋ@����
	if (isStand_) {
		standTime_--;
		if (standTime_ <= 0) {
			//�ҋ@����
			isStand_ = false;
		}
		return;
	}
	//1�s���̕����������ϐ�
	std::string line;

	//�R�}���h���s���[�v
	while (getline(enemyPopCommand_phase1, line)) {
		//1�s���̕��������X�g���[���ɕϊ����ĉ�܂��₷���Ȃ�
		std::istringstream line_stream(line);
		std::string word;
		//,��؂�ōs�̐擪�������擾
		getline(line_stream, word, ',');
		//"//"����n�܂�s�̓R�����g
		if (word.find("//") == 0) {
			//�R�����g�s���΂�
			continue;
		}
		// POP�R�}���h
		if (word.find("POP") == 0) {
			// X���W
			std::getline(line_stream, word, ',');
			float x = static_cast<float>(std::atof(word.c_str()));

			// Y���W
			std::getline(line_stream, word, ',');
			float y = static_cast<float>(std::atof(word.c_str()));

			// Z���W
			std::getline(line_stream, word, ',');
			float z = static_cast<float>(std::atof(word.c_str()));

			MakeEnemy(Vector3(x, y, z));
		}
		// WAIT�R�}���h
		else if (word.find("WAIT") == 0) {
			std::getline(line_stream, word, ',');

			//�҂�����
			int32_t waitTime = std::atoi(word.c_str());

			//�ҋ@�J�n
			isStand_ = true;
			standTime_ = waitTime;

			//���[�v�𔲂���
			break;
		}
	}
}

void GameScene::UpdateEnemyPopCommands_phase2() {
	//�ҋ@����
	if (isStand_) {
		standTime_--;
		if (standTime_ <= 0) {
			//�ҋ@����
			isStand_ = false;
		}
		return;
	}
	//1�s���̕����������ϐ�
	std::string line;

	//�R�}���h���s���[�v
	while (getline(enemyPopCommand_phase2, line)) {
		//1�s���̕��������X�g���[���ɕϊ����ĉ�܂��₷���Ȃ�
		std::istringstream line_stream(line);
		std::string word;
		//,��؂�ōs�̐擪�������擾
		getline(line_stream, word, ',');
		//"//"����n�܂�s�̓R�����g
		if (word.find("//") == 0) {
			//�R�����g�s���΂�
			continue;
		}
		// POP�R�}���h
		if (word.find("POP") == 0) {
			// X���W
			std::getline(line_stream, word, ',');
			float x = static_cast<float>(std::atof(word.c_str()));

			// Y���W
			std::getline(line_stream, word, ',');
			float y = static_cast<float>(std::atof(word.c_str()));

			// Z���W
			std::getline(line_stream, word, ',');
			float z = static_cast<float>(std::atof(word.c_str()));

			MakeEnemy(Vector3(x, y, z));
		}
		// WAIT�R�}���h
		else if (word.find("WAIT") == 0) {
			std::getline(line_stream, word, ',');

			//�҂�����
			int32_t waitTime = std::atoi(word.c_str());

			//�ҋ@�J�n
			isStand_ = true;
			standTime_ = waitTime;

			//���[�v�𔲂���
			break;
		}
	}
}

void GameScene::UpdateEnemyPopCommands_phase3() {
	//�ҋ@����
	if (isStand_) {
		standTime_--;
		if (standTime_ <= 0) {
			//�ҋ@����
			isStand_ = false;
		}
		return;
	}
	//1�s���̕����������ϐ�
	std::string line;

	//�R�}���h���s���[�v
	while (getline(enemyPopCommand_phase3, line)) {
		//1�s���̕��������X�g���[���ɕϊ����ĉ�܂��₷���Ȃ�
		std::istringstream line_stream(line);
		std::string word;
		//,��؂�ōs�̐擪�������擾
		getline(line_stream, word, ',');
		//"//"����n�܂�s�̓R�����g
		if (word.find("//") == 0) {
			//�R�����g�s���΂�
			continue;
		}
		// POP�R�}���h
		if (word.find("POP") == 0) {
			// X���W
			std::getline(line_stream, word, ',');
			float x = static_cast<float>(std::atof(word.c_str()));

			// Y���W
			std::getline(line_stream, word, ',');
			float y = static_cast<float>(std::atof(word.c_str()));

			// Z���W
			std::getline(line_stream, word, ',');
			float z = static_cast<float>(std::atof(word.c_str()));

			MakeEnemy(Vector3(x, y, z));
		}
		// WAIT�R�}���h
		else if (word.find("WAIT") == 0) {
			std::getline(line_stream, word, ',');

			//�҂�����
			int32_t waitTime = std::atoi(word.c_str());

			//�ҋ@�J�n
			isStand_ = true;
			standTime_ = waitTime;

			//���[�v�𔲂���
			break;
		}
	}
}

void GameScene::UpdateEnemyPopCommands_phase4() {
	//�ҋ@����
	if (isStand_) {
		standTime_--;
		if (standTime_ <= 0) {
			//�ҋ@����
			isStand_ = false;
		}
		return;
	}
	//1�s���̕����������ϐ�
	std::string line;

	//�R�}���h���s���[�v
	while (getline(enemyPopCommand_phase4, line)) {
		//1�s���̕��������X�g���[���ɕϊ����ĉ�܂��₷���Ȃ�
		std::istringstream line_stream(line);
		std::string word;
		//,��؂�ōs�̐擪�������擾
		getline(line_stream, word, ',');
		//"//"����n�܂�s�̓R�����g
		if (word.find("//") == 0) {
			//�R�����g�s���΂�
			continue;
		}
		// POP�R�}���h
		if (word.find("POP") == 0) {
			// X���W
			std::getline(line_stream, word, ',');
			float x = static_cast<float>(std::atof(word.c_str()));

			// Y���W
			std::getline(line_stream, word, ',');
			float y = static_cast<float>(std::atof(word.c_str()));

			// Z���W
			std::getline(line_stream, word, ',');
			float z = static_cast<float>(std::atof(word.c_str()));

			MakeEnemy(Vector3(x, y, z));
		}
		// WAIT�R�}���h
		else if (word.find("WAIT") == 0) {
			std::getline(line_stream, word, ',');

			//�҂�����
			int32_t waitTime = std::atoi(word.c_str());

			//�ҋ@�J�n
			isStand_ = true;
			standTime_ = waitTime;

			//���[�v�𔲂���
			break;
		}
	}
}


void GameScene::MakeEnemy(Vector3 EnemyPos) {

	//�G�L�����̐���
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	//�G�L�����̏�����
	newEnemy->Initialize(EnemyModel_, enemyTextureHandle_, enemy50TextureHandle_, EnemyPos, model_);

	//�G�L�����ɃA�h���X��n��
	newEnemy->SetPlayer(player_);

	//���X�g�ɓo�^����
	enemys_.push_back(std::move(newEnemy));

}


void GameScene::secondInitialize() {

	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();
	//���L�����̏�����
	player_->Initialize(model_, winApp_->window_width, winApp_->window_height);
	//���[���J�����̏�����
	railCamera_->Initialize(winApp_,Vector3(0, 0, -50), Vector3(0.2, 0, 0));
	
	LoadEnemyPopData();
}


void GameScene::enemyUpdate(int x) {
	//�f�X�t���O�̗������G���폜
	enemys_.remove_if([](std::unique_ptr<Enemy>& enemy) {
		return enemy->IsDead();
		});
	//�G�L�����̍X�V
	for (std::unique_ptr<Enemy>& enemy_ : enemys_) {
		enemy_->attackSet(x);
		enemy_->SetGameScene(this);
		enemy_->Update();
	}

	//�f�X�t���O�̗������e���폜
	enemyBullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
		});
	//�e�X�V
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
		bullet->Update();
	}
}

void GameScene::enemybay() {
	//�f�X�t���O�̗������G���폜
	enemys_.remove_if([](std::unique_ptr<Enemy>& enemy) {
		return enemy->IsDead();
		});
	//�G�L�����̍��W
	for (std::unique_ptr<Enemy>& enemy_ : enemys_) {
		enemy_->OnCollision();
	}
	//�f�X�t���O�̗������e���폜
	enemyBullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
		});
	//�e�X�V
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
		bullet->OnCollision();
	}
}