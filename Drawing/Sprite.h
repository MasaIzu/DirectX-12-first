#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include"Vector3.h"
#include"Vector2.h"
#include"Vector4.h"
#include"Matrix4.h"
#include"MyMath.h"

/// <summary>
/// �X�v���C�g
/// </summary>
class Sprite
{
private: 
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPosUv
	{
		Vector3 pos; // xyz���W
		Vector2 uv;  // uv���W
	};

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		Vector4 color;	// �F (RGBA)
		Matrix4 mat;	// �R�c�ϊ��s��
	};

public: // �ÓI�����o�֐�

	/// �ÓI������
	static void StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	// �e�N�X�`���ǂݍ���
	static void LoadTexture(UINT texnumber, const wchar_t* filename);

	// �`��O����
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	// �`��㏈��
	static void PostDraw();

	// �X�v���C�g����
	static Sprite* Create(UINT texNumber, Vector2 position, Vector4 color = { 1, 1, 1, 1 }, Vector2 anchorpoint = { 0.0f, 0.0f }, bool isFlipX = false, bool isFlipY = false);

	// ���W�̎擾
	const Vector2& GetPosition() { return position; }

	//�J���[�ւ�
	void SetColor(const Vector4& color) { this->color = color; }



private: // �ÓI�����o�ϐ�
	// �e�N�X�`���̍ő喇��
	static const int srvCount = 512;
	// ���_��
	static const int vertNum = 4;
	// �f�o�C�X
	static ID3D12Device* device;
	// �f�X�N���v�^�T�C�Y
	static UINT descriptorSize;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootSignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelineState;
	// �ˉe�s��
	static Matrix4 matProjection;
	// �f�X�N���v�^�q�[�v
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// �e�N�X�`���o�b�t�@
	static ComPtr<ID3D12Resource> texBuff[srvCount];

public: // �����o�֐�

	// �R���X�g���N�^
	Sprite(UINT texNumber, Vector2 position, Vector2 size, Vector4 color, Vector2 anchorpoint, bool isFlipX, bool isFlipY);

	// ������
	bool Initialize();

	// �p�x�̐ݒ�
	void SetRotation(float rotation);

	// ���W�̐ݒ�
	void SetPosition(const Vector2& position);

	// �T�C�Y�̐ݒ�
	void SetSize(const Vector2& size);

	// �A���J�[�|�C���g�̐ݒ�
	void SetAnchorPoint(const Vector2& anchorpoint);

	// ���E���]�̐ݒ�
	void SetIsFlipX(bool isFlipX);

	// �㉺���]�̐ݒ�
	void SetIsFlipY(bool isFlipY);

	// �e�N�X�`���͈͐ݒ�
	void SetTextureRect(const Vector2& texBase, const Vector2& texSize);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private: // �����o�ϐ�

	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;

	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;

	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	// �e�N�X�`���ԍ�
	UINT texNumber = 0;

	// Z�����̉�]�p
	float rotation = 0.0f;

	// ���W
	Vector2 position{};

	// �X�v���C�g���A����
	Vector2 size = { 100.0f, 100.0f };

	// �A���J�[�|�C���g
	Vector2 anchorpoint = { 0, 0 };

	// ���[���h�s��
	Matrix4 matWorld{};

	// �F
	Vector4 color = { 1, 1, 1, 1 };

	// ���E���]
	bool isFlipX = false;

	// �㉺���]
	bool isFlipY = false;

	// �e�N�X�`���n�_
	Vector2 texBase = { 0, 0 };

	// �e�N�X�`�����A����
	Vector2 texSize = { 100.0f, 100.0f };

private: // �����o�֐�
	// ���_�f�[�^�]��
	void TransferVertices();
};