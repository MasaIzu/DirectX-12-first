#pragma once

#include "DirectXCore.h"
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

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

private: // �����o�ϐ�
	DirectXCore* directXCore_ = nullptr;
	Input* input_ = nullptr;


	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;
	Model* model_;

		/// <summary>
		/// �Q�[���V�[���p
		/// </summary>
};
