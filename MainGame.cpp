#include "MainGame.h"
#include "SceneFactory.h"


void MainGame::Initialize()
{
	// ���N���X�̏���������
	Framework::Initialize();

	sceneFactory_ = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory_);
	SceneManager::GetInstance()->ChangeScene("TITLE");
}

void MainGame::Finalize()
{
	// ���N���X�̏I������
	Framework::Finalize();
}

void MainGame::Update()
{
	// ���N���X�̍X�V����
	Framework::Update();
}

void MainGame::Draw()
{
	// �Q�[���V�[���̕`��
	sceneManager_->Draw();
}
