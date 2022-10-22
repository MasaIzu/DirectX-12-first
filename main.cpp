#include "DirectXCore.h"
#include "GameScene.h"
#include "TextureManager.h"
#include "WinApp.h"

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* winApp_ = nullptr;
	DirectXCore* dxCore_ = nullptr;
	// �ėp�@�\
	Input* input = nullptr;
	GameScene* gameScene = nullptr;

	// �Q�[���E�B���h�E�̍쐬
	winApp_ = WinApp::GetInstance();
	winApp_->WinApiInitialize();

	// DirectX����������
	dxCore_ = DirectXCore::GetInstance();
	dxCore_->Initialize(winApp_);

#pragma region �ėp�@�\������
	// ���͂̏�����
	input = Input::GetInstance();
	input->Initialize();

	// �e�N�X�`���}�l�[�W���̏�����
	TextureManager::GetInstance()->Initialize(dxCore_->GetDevice());
	TextureManager::Load("white1x1.png");

	// 3D���f���ÓI������
	Model::StaticInitialize();


#pragma endregion

	// �Q�[���V�[���̏�����
	gameScene = new GameScene();
	gameScene->Initialize();

	// ���C�����[�v
	while (true) {
		// ���b�Z�[�W����
		if (winApp_->ProcessMessage()) {
			break;
		}

		// ���͊֘A�̖��t���[������
		input->Updata();
		// �Q�[���V�[���̖��t���[������
		gameScene->Update();


		// �`��J�n
		dxCore_->PreDraw();
		// �Q�[���V�[���̕`��
		gameScene->Draw();

		// �`��I��
		dxCore_->PostDraw();
	}

	// �e����


	// �Q�[���E�B���h�E�̔j��
	winApp_->Finalize();

	return 0;
}