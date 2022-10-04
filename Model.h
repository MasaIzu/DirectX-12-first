#pragma once

#include "TextureManager.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DirectXMath.h>
#include <Windows.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <vector>
#include <wrl.h>

/// <summary>
/// 3D���f��
/// </summary>
class Model {
public: // �񋓎q
	/// <summary>
	/// ���[�g�p�����[�^�ԍ�
	/// </summary>
	enum class RoomParameter {
		kWorldTransform, // ���[���h�ϊ��s��
		kViewProjection, // �r���[�v���W�F�N�V�����ϊ��s��
		kTexture,        // �e�N�X�`��
	};

public: // �T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPosNormalUv {
		DirectX::XMFLOAT3 pos;    // xyz���W
		DirectX::XMFLOAT3 normal; // �@���x�N�g��
		DirectX::XMFLOAT2 uv;     // uv���W
	};

public: // �ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	/// <param name="window_width">��ʕ�</param>
	/// <param name="window_height">��ʍ���</param>
	static void StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	/// <summary>
	/// �`��O����
	/// </summary>
	/// <param name="commandList">�`��R�}���h���X�g</param>
	static void PreDraw(ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3D���f������
	/// </summary>
	/// <returns></returns>
	static Model* Create();

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* sDevice;
	// �f�X�N���v�^�T�C�Y
	static UINT sDescriptorHandleIncrementSize;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* sCommandList;
	// ���[�g�V�O�l�`��
	static Microsoft::WRL::ComPtr<ID3D12RootSignature> sRootSignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static Microsoft::WRL::ComPtr<ID3D12PipelineState> sPipelineState;

private: // �ÓI�����o�֐�
	/// <summary>
	/// �O���t�B�b�N�p�C�v���C������
	/// </summary>
	static void InitializeGraphicsPipeline();

public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(
		const WorldTransform& worldTransform, const ViewProjection& viewProjection,
		uint32_t textureHadle = 0);

	/// <summary>
	/// ���b�V���f�[�^����
	/// </summary>
	void CreateMesh();

private: // �����o�ϐ�
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView_;
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView_;
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices_;
	// ���_�C���f�b�N�X�z��
	std::vector<uint16_t> indices_;
	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff_;
	// �C���f�b�N�X�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff_;
};
