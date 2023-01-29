#pragma once
#include "DirectXCore.h"
#include "GameScene.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "Input.h"
#include "FPS.h"
#include "ImGuiManager.h"

#include "SceneManager.h"

class Framework {
public:
	//virtual�����o�֐�
	//������
	virtual void Initialize();

	//�X�V
	virtual void Update();

	//�`��
	virtual void Draw() = 0;

	//�I������
	virtual void Finalize();

	//�I���`�F�b�N
	virtual bool isPlayMyGame();

public://�f�X�g���N�^
	virtual ~Framework() = default;

public:
	//�����o�֐�
	//���s
	void Run();

	WinApp* GetWinApp() { return winApp_; }
	DirectXCore* GetDirectXCore() { return directXCore_; }

protected:


	WinApp* winApp_ = nullptr;
	DirectXCore* directXCore_ = nullptr;
	// �ėp�@�\
	Input* input_ = nullptr;
	ImGuiManager* imGui = nullptr;
	FPS* fps = nullptr;

	SceneManager* sceneManager_ = nullptr;
	AbstractSceneFactory* sceneFactory_ = nullptr;

	bool isEndRequst = false;
};