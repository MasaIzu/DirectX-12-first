#include "DirectXCore.h"
#include "GameScene.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "Audio.h"
#include "ErrorException.h"
#include "FPS.h"

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* winApp_ = nullptr;
	DirectXCore* directXCore_ = nullptr;
	// �ėp�@�\
	Input* input_ = nullptr;
	GameScene* gameScene_ = nullptr;

	// �Q�[���E�B���h�E�̍쐬
	winApp_ = new WinApp;
	winApp_->MakeWindow(L"�K���Q�[��");

	// DirectX����������
	directXCore_ = new DirectXCore;
	directXCore_->DirectXCoreInitialize(winApp_->Gethwnd(), winApp_->window_width, winApp_->window_height);

#pragma region �ėp�@�\������
	// ���͂̏�����
	input_ = Input::GetInstance();
	input_->Initialize();


	// �e�N�X�`���}�l�[�W���̏�����
	TextureManager::GetInstance()->Initialize(directXCore_->GetDevice());
	TextureManager::Load("white1x1.png");

	// �X�v���C�g�ÓI������
	Sprite::StaticInitialize(directXCore_->GetDevice(), winApp_->window_width, winApp_->window_height);

	// �f�o�b�O�e�L�X�g������
	

	// 3D���f���ÓI������
	Model::StaticInitialize();


#pragma endregion

	// �Q�[���V�[���̏�����
	gameScene_ = new GameScene();
	gameScene_->Initialize(directXCore_);

	FPS* fps = new FPS;

	// ���C�����[�v
	while (true) {
		//fps����
		fps->FpsControlBegin();

		// ���b�Z�[�W����
		if (winApp_->ProcessMessage()) {
			break;
		}

		// ���͊֘A�̖��t���[������
		input_->Update();
		// �Q�[���V�[���̖��t���[������
		gameScene_->Update();
		

		// �`��J�n
		directXCore_->PreDraw();
		// �Q�[���V�[���̕`��
		gameScene_->Draw();
		
		// �`��I��
		directXCore_->PostDraw();

		//FPS�Œ�
		fps->FpsControlEnd();
	}

	// �e����
	

	// �Q�[���E�B���h�E�̔j��
#pragma region  WindowsAPI��n��

	winApp_->TerminateGameWindow();

#pragma endregion
	return 0;
}