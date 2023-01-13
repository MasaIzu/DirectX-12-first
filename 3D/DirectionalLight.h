#pragma once
#include "Vector3.h"
#include "Vector4.h"

/// <summary>
/// ���s����
/// </summary>
class DirectionalLight
{
private: 


public: // �T�u�N���X

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		Vector4 lightv;
		Vector3 lightcolor;
		unsigned int active;
	};

public: // �����o�֐�

	/// <summary>
	/// ���C�g�������擾
	/// </summary>
	/// <returns>���C�g����</returns>
	inline const Vector4& GetLightDir() { return lightdir; }

	/// <summary>
	/// ���C�g�F���Z�b�g
	/// </summary>
	/// <param name="lightcolor">���C�g�F</param>
	inline void SetLightColor(const Vector3& lightcolor) { this->lightcolor = lightcolor; }

	/// <summary>
	/// ���C�g�F���擾
	/// </summary>
	/// <returns>���C�g�F</returns>
	inline const Vector3& GetLightColor() { return lightcolor; }

	/// <summary>
	/// �L���t���O���Z�b�g
	/// </summary>
	/// <param name="active">�L���t���O</param>
	inline void SetActive(bool active) { this->active = active; }

	/// <summary>
	/// �L���`�F�b�N
	/// </summary>
	/// <returns>�L���t���O</returns>
	inline bool IsActive() { return active; }

private: // �����o�ϐ�
	// ���C�g�����i�P�ʃx�N�g���j
	Vector4 lightdir = { 1,0,0,0 };
	// ���C�g�F
	Vector3 lightcolor = { 1,1,1 };
	// �L���t���O
	bool active = false;
};

