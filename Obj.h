#pragma once
#include<fstream>
#include<sstream>
#include<string>
#include"Vector3.h"
#include <vector>
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include"DirectXCore.h"

using namespace std;

class Obj {

public:

	// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT3 normal; // �@���x�N�g��
		XMFLOAT3 uv;  // uv���W
	};

	/// <summary>
	/// obj�ǂݍ���
	/// </summary>
	void LoadObj();

	/// <summary>
	/// obj���f���̍쐬
	/// </summary>
	void CreateObjModel();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private: // �萔
	static const int division = 50;					// ������
	static const float radius;				// ��ʂ̔��a
	static const float prizmHeight;			// ���̍���
	static const int planeCount = division * 2 + division * 2;		// �ʂ̐�
	static const int vertexCount = planeCount * 3;		// ���_��

private://�ÓI�����o�ϐ�
	// ���_�o�b�t�@
	static ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	static ComPtr<ID3D12Resource> indexBuff;

	// ���_�o�b�t�@�r���[
	static D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	static D3D12_INDEX_BUFFER_VIEW ibView;
	// ���_�f�[�^�z��
	static VertexPosNormalUv vertices[vertexCount];
	// ���_�C���f�b�N�X�z��
	static unsigned short indices[planeCount * 3];


private://�����o�ϐ�
	DirectXCore* directXCore = DirectXCore::GetInstance();
	//���_�f�[�^�z��
	static std::vector<VertexPosNormalUv> vertices;
	//���_�C���f�b�N�X�z��
	static std::vector<unsigned short> indices;

};