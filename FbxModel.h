#pragma once

#include <string>
#include <vector>
#include <DirectXMath.h>
#include <DirectXTex.h>
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>

#include <Mesh.h>
#include "Material.h"
#include <Light.h>
#include <WorldTransform.h>
#include <ViewProjection.h>

// �m�[�h
struct Node
{
	//���O
	std::string name;
	//���[�J���ό`�s��
	Matrix4 transform;
	//�O���[�o���ό`�s��
	Matrix4 globalTransform;
	//�e�m�[�h
	Node* parent = nullptr;
	//�q�m�[�h
	std::vector<Node*>childrens;

};

class FbxModel
{
public:
	// �t�����h�N���X
	friend class FbxLoader;

public://�萔
	static const int MAX_BONE_INDICES = 4;

private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using TexMetadata = DirectX::TexMetadata;
	using ScratchImage = DirectX::ScratchImage;
	// std::���ȗ�
	using string = std::string;
	template <class T> using vector = std::vector<T>;

public: // �T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPosNormalUvFbxSkin
	{
		DirectX::XMFLOAT3 pos; // xyz���W
		DirectX::XMFLOAT3 normal; // �@���x�N�g��
		DirectX::XMFLOAT2 uv;  // uv���W

		UINT boneIndex[MAX_BONE_INDICES];
		float boneWeight[MAX_BONE_INDICES];
	};


private:
	// Microsoft::WRL::���ȗ�
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;


public:

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		Vector4 color;	// �F (RGBA)
		Matrix4 mat;	// �R�c�ϊ��s��
	};

private:
	static const std::string kBaseDirectory;
	static const std::string kDefaultModelName;

private: // �ÓI�����o�ϐ�
	// �f�X�N���v�^�T�C�Y
	static UINT sDescriptorHandleIncrementSize_;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* sCommandList_;
	// ���[�g�V�O�l�`��
	static Microsoft::WRL::ComPtr<ID3D12RootSignature> sRootSignature_;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static Microsoft::WRL::ComPtr<ID3D12PipelineState> sPipelineState_;
	// ���C�g
	static std::unique_ptr<LightGroup> lightGroup;

public: // �ÓI�����o�֐�
	// �ÓI������
	static void StaticInitialize();

	// �O���t�B�b�N�X�p�C�v���C���̏�����
	static void InitializeGraphicsPipeline();

	// 3D���f������
	static FbxModel* Create();

	// OBJ�t�@�C�����烁�b�V������
	static FbxModel* CreateFromFbx(const std::string& modelname, bool smoothing = false);

	// �`��O����
	static void PreDraw(ID3D12GraphicsCommandList* commandList);

	// �`��㏈��
	static void PostDraw();

public: // �����o�֐�
	// �f�X�g���N�^
	~FbxModel();

	// ������
	void Initialize();

	// �`��
	//void Draw(
	//	const WorldTransform& worldTransform, const ViewProjection& viewProjection);

	void Draw(const WorldTransform& worldTransform, const ViewProjection& viewProjection);

	void ModelAnimation(float frame,aiAnimation* Animation);

	void ReadNodeHeirarchy(Mesh* mesh, aiAnimation* Animation, FLOAT AnimationTime, Node*pNode,Matrix4& mxIdentity);

	aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string& strNodeName);
	
	void CalcInterpolatedScaling(Vector3& mxOut, float AnimationTime, const aiNodeAnim* pNodeAnim);

	bool FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim, UINT& nScalingIndex);
	
	void CalcInterpolatedRotation(Vector4& mxOut, float AnimationTime, const aiNodeAnim* pNodeAnim);

	bool FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim, UINT& nRotationIndex);
	
	void CalcInterpolatedPosition(Vector3& mxOut, float AnimationTime, const aiNodeAnim* pNodeAnim);
	
	bool FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim, UINT& nPosIndex);
	

	// ���b�V���R���e�i���擾
	inline const std::vector<Mesh*>& GetMeshes() { return meshes_; }

private:

	// �m�[�h�z��
	std::vector<Node> nodes;


	Matrix4 globalInverseTransform;

	// ���O
	std::string name_;
	// ���b�V���R���e�i
	std::vector<Mesh*> meshes_;
	// �}�e���A���R���e�i
	std::unordered_map<std::string, Material*> materials_;
	// �f�t�H���g�}�e���A��
	Material* defaultMaterial_ = nullptr;




};

