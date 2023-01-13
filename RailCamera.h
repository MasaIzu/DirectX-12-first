#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "affin.h"
#include "Input.h"
#include "Vector2.h"
#include "WinApp.h"

/// <summary>
/// ���[���J����
/// </summary>
class RailCamera {
public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* winApp,const Vector3 pos, const Vector3 rad);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	Vector3 bVelocity(Vector3 velocity, WorldTransform& worldTransform);

	ViewProjection GetViewProjection();
	WorldTransform* GetWorldTransform();
	Vector3 GetTarget();
	//�J�����𓮂����Ȃ�0�~�߂�Ȃ�1
	void cameraSet(int x);

	void setShake(int x);
	//void SetMouseMovemont(Vector3 mouseMovement);
	void MousePosInitialize();

	void SetEye(Vector3 eye);

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
	//�L�[�C���v�b�g
	Input* input_ = nullptr;
	Vector2 MouseMove;
	//�}�E�X�̈ړ��ʕۑ�
	Vector2 mouseMoved;
	Vector3 Target;

	Vector3 cameraMoveY{ 0,0,0 };

	WinApp* winApp = nullptr;

	int isShake = 0;
	int cameraMoveFlag = 0;
};