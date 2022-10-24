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
	DirectXCore* dxCore_ = nullptr;
	// �ėp�@�\
	Input* input_ = nullptr;
	GameScene* gameScene_ = nullptr;

	// �Q�[���E�B���h�E�̍쐬
	winApp_ = WinApp::GetInstance();
	winApp_->CreateGameWindow();

	// DirectX����������
	dxCore_ = DirectXCore::GetInstance();
	dxCore_->Initialize(winApp_);

#pragma region �ėp�@�\������
	// ���͂̏�����
	input_ = Input::GetInstance();
	input_->Initialize();

	// �I�[�f�B�I�̏�����
	Audio sound;
	sound.Initialize();

	// �e�N�X�`���}�l�[�W���̏�����
	TextureManager::GetInstance()->Initialize(dxCore_->GetDevice());
	TextureManager::Load("white1x1.png");

	// �X�v���C�g�ÓI������
	Sprite::StaticInitialize(dxCore_->GetDevice(), WinApp::window_width, WinApp::window_height);

	// �f�o�b�O�e�L�X�g������
	

	// 3D���f���ÓI������
	Model::StaticInitialize();


#pragma endregion

	// �Q�[���V�[���̏�����
	gameScene_ = new GameScene();
	gameScene_->Initialize();

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
		dxCore_->PreDraw();
		// �Q�[���V�[���̕`��
		gameScene_->Draw();
		
		// �`��I��
		dxCore_->PostDraw();

		//FPS�Œ�
		fps->FpsControlEnd();
	}

	// �e����
	sound.SoundUnload();

	// �Q�[���E�B���h�E�̔j��
#pragma region  WindowsAPI��n��

	winApp_->TerminateGameWindow();

#pragma endregion
	return 0;
}