#pragma once

#include "DirectXCore.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <xaudio2.h>

#pragma comment(lib,"xaudio2.lib")

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
	void Initialize(DirectXCore* dxCore_);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();


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

	void DrawNunbers();


private: // �����o�ϐ�
	//�t�F�[�Y
	Scene scene_ = Scene::Title;

	DirectXCore* dxCore_ = nullptr;
	Input* input_ = nullptr;
	
};
