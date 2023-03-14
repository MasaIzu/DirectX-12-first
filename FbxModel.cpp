#include "DirectXCore.h"
#include "FbxModel.h"
#include <algorithm>
#include <cassert>
#include <d3dcompiler.h>
#include <fstream>
#include <sstream>

#include<atldef.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace std;
using namespace Microsoft::WRL;

/// <summary>
/// 静的メンバ変数の実体
/// </summary>
const std::string FbxModel::kBaseDirectory = "Resources/";
const std::string FbxModel::kDefaultModelName = "cube";
UINT FbxModel::sDescriptorHandleIncrementSize_ = 0;
ID3D12GraphicsCommandList* FbxModel::sCommandList_ = nullptr;
ComPtr<ID3D12RootSignature> FbxModel::sRootSignature_;
ComPtr<ID3D12PipelineState> FbxModel::sPipelineState_;
std::unique_ptr<LightGroup> FbxModel::lightGroup;

void FbxModel::StaticInitialize() {

	// パイプライン初期化
	InitializeGraphicsPipeline();

	// ライト生成
	lightGroup.reset(LightGroup::Create());
}

void FbxModel::InitializeGraphicsPipeline() {
	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob> vsBlob;    // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob;    // ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト


	// 頂点シェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/shaders/ObjVS.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0, &vsBlob, &errorBlob);
	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n(
			(char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// ピクセルシェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/shaders/ObjPS.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0, &psBlob, &errorBlob);
	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n(
			(char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// 頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
	  {// xy座標(1行で書いたほうが見やすい)
	   "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT,
	   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	  {// 法線ベクトル(1行で書いたほうが見やすい)
	   "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT,
	   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	  {// uv座標(1行で書いたほうが見やすい)
	   "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT,
	   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	// グラフィックスパイプラインの流れを設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	// サンプルマスク
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定
	// ラスタライザステート
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	// gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
	// gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
	//  デプスステンシルステート
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

	// レンダーターゲットのブレンド設定
	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA全てのチャンネルを描画
	blenddesc.BlendEnable = true;
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

	// ブレンドステートの設定
	gpipeline.BlendState.RenderTarget[0] = blenddesc;

	// 深度バッファのフォーマット
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	// 頂点レイアウトの設定
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	// 図形の形状設定（三角形）
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 1;                       // 描画対象は1つ
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0〜255指定のRGBA
	gpipeline.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	// デスクリプタレンジ
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0 レジスタ

	// ルートパラメータ
	CD3DX12_ROOT_PARAMETER rootparams[5];
	rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[1].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[2].InitAsConstantBufferView(2, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[3].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[4].InitAsConstantBufferView(3, 0, D3D12_SHADER_VISIBILITY_ALL);

	// スタティックサンプル
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

	// ルートシグネチャの設定
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(
		_countof(rootparams), rootparams, 1, &samplerDesc,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob;
	// バージョン自動判定のシリアライズ
	result = D3DX12SerializeVersionedRootSignature(
		&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	// ルートシグネチャの生成
	result = DirectXCore::GetInstance()->GetDevice()->CreateRootSignature(
		0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&sRootSignature_));
	assert(SUCCEEDED(result));

	gpipeline.pRootSignature = sRootSignature_.Get();

	// グラフィックスパイプラインの生成
	result = DirectXCore::GetInstance()->GetDevice()->CreateGraphicsPipelineState(
		&gpipeline, IID_PPV_ARGS(&sPipelineState_));
	assert(SUCCEEDED(result));
}

FbxModel* FbxModel::Create() {
	// メモリ確保
	FbxModel* instance = new FbxModel;
	instance->Initialize();

	return instance;
}

FbxModel* FbxModel::CreateFromFbx(const std::string& modelname, bool smoothing) {
	// メモリ確保
	FbxModel* instance = new FbxModel;
	instance->Initialize();

	return instance;
}

void FbxModel::PreDraw(ID3D12GraphicsCommandList* commandList) {
	// PreDrawとPostDrawがペアで呼ばれていなければエラー
	assert(FbxModel::sCommandList_ == nullptr);

	// コマンドリストをセット
	sCommandList_ = commandList;

	// パイプラインステートの設定
	commandList->SetPipelineState(sPipelineState_.Get());
	// ルートシグネチャの設定
	commandList->SetGraphicsRootSignature(sRootSignature_.Get());
	// プリミティブ形状を設定
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void FbxModel::PostDraw() {
	// コマンドリストを解除
	sCommandList_ = nullptr;
}

FbxModel::~FbxModel() {
	for (auto m : meshes_) {
		delete m;
	}
	meshes_.clear();

	for (auto m : materials_) {
		delete m.second;
	}
	materials_.clear();
}

void FbxModel::Initialize() {
	// モデル読み込み
	//LoadModelFromFile(modelname);

	// メッシュのマテリアルチェック
	for (auto& m : meshes_) {
		// マテリアルの割り当てがない
		if (m->GetMaterial() == nullptr) {
			if (defaultMaterial_ == nullptr) {
				// デフォルトマテリアルを生成
				defaultMaterial_ = Material::Create();
				defaultMaterial_->name_ = "no material";
				materials_.emplace(defaultMaterial_->name_, defaultMaterial_);
			}
			// デフォルトマテリアルをセット
			m->SetMaterial(defaultMaterial_);
		}
	}

	// メッシュのバッファ生成
	for (auto& m : meshes_) {

		Vector3 ambient_ = { 1.0f, 1.0f, 1.0f };
		Vector3 diffuse_ = { 0.0f, 0.0f, 0.0f };
		Vector3 specular_ = { 0.0f, 0.0f, 0.0f };
		float alpha_ = 1.0f;

		m->SetLight(ambient_, diffuse_, specular_, alpha_);

		m->CreateBuffers();
	}

	// マテリアルの数値を定数バッファに反映
	for (auto& m : materials_) {

		m.second->Update();
	}

}


void FbxModel::Draw(
	const WorldTransform& worldTransform, const ViewProjection& viewProjection) {

	for (int i = 0; i < meshes_.size(); i++) {

		// ライトの描画
		lightGroup->Draw(sCommandList_, 4);

		// CBVをセット（ワールド行列）
		sCommandList_->SetGraphicsRootConstantBufferView(0, worldTransform.constBuff_->GetGPUVirtualAddress());

		// CBVをセット（ビュープロジェクション行列）
		sCommandList_->SetGraphicsRootConstantBufferView(1, viewProjection.constBuff_->GetGPUVirtualAddress());


		// 全メッシュを描画
		meshes_[i]->Draw(sCommandList_, 2, 3,3);
	}
}
//
//void FbxModel::Draw(
//	const WorldTransform& worldTransform, const ViewProjection& viewProjection,
//	uint32_t textureHadle) {
//
//	// ライトの描画
//	lightGroup->Draw(sCommandList_, 4);
//
//	// CBVをセット（ワールド行列）
//	sCommandList_->SetGraphicsRootConstantBufferView(0, worldTransform.constBuff_->GetGPUVirtualAddress());
//
//	// CBVをセット（ビュープロジェクション行列）
//	sCommandList_->SetGraphicsRootConstantBufferView(1, viewProjection.constBuff_->GetGPUVirtualAddress());
//
//	// 全メッシュを描画
//	for (auto& mesh : meshes_) {
//		mesh->Draw(
//			sCommandList_, 2, 3,
//			textureHadle);
//	}
//}


void FbxModel::ModelAnimation(float frame, aiAnimation* Animation) {

	Matrix4 mxIdentity = MyMath::MakeIdentity();
	Node* pNode = &nodes[0];
	

	FLOAT TicksPerSecond = (FLOAT)(Animation->mTicksPerSecond != 0 ? Animation->mTicksPerSecond : 25.0f);

	FLOAT TimeInTicks = frame * TicksPerSecond;
	FLOAT AnimationTime = fmod(TimeInTicks, (FLOAT)Animation->mDuration);

	for (Mesh* mesh : meshes_)
	{
		ReadNodeHeirarchy(mesh, Animation, AnimationTime, pNode, mxIdentity);

		UINT nNumBones = (UINT)mesh->bones.size();

		for (UINT i = 0; i < nNumBones; i++)
		{
			mesh->vecBones[i].matrix = mesh->bones[mesh->vecBones[i].name]->matrix;
		}
	}
}


void FbxModel::ReadNodeHeirarchy(Mesh* mesh, aiAnimation* Animation, FLOAT AnimationTime, Node* pNode, Matrix4& mxIdentity) {

	Matrix4 mxNodeTransformation = MyMath::MakeIdentity();
	mxNodeTransformation = pNode->transform;

	Matrix4 mxThisTrans = mxNodeTransformation;

	std::string strNodeName(pNode->name);

	const aiNodeAnim* pNodeAnim = FindNodeAnim(Animation, strNodeName);

	if (pNodeAnim)
	{
		//スケーリング
		Vector3 vScaling = {};
		CalcInterpolatedScaling(vScaling, AnimationTime, pNodeAnim);
		Matrix4 mxScaling;
		mxScaling = MyMath::Rotation(vScaling,6);

		//回転角
		Vector4 vRotationQ = {};
		CalcInterpolatedRotation(vRotationQ, AnimationTime, pNodeAnim);
		Matrix4 mxRotationM = Quaternion(vRotationQ).Rotate();

		//移動
		Vector3 vTranslation = {};
		CalcInterpolatedPosition(vTranslation, AnimationTime, pNodeAnim);
		Matrix4 mxTranslationM;
		mxTranslationM = MyMath::Translation(vTranslation);

		Matrix4 affin = MyMath::Initialize();
		affin *= mxScaling;
		affin *= mxRotationM;
		affin *= mxTranslationM;

		mxNodeTransformation = affin;
	}

}


aiNodeAnim* FbxModel::FindNodeAnim(const aiAnimation* pAnimation, const std::string& strNodeName)
{
	for (UINT i = 0; i < pAnimation->mNumChannels; i++)
	{
		if (std::string(pAnimation->mChannels[i]->mNodeName.data) == strNodeName)
		{
			return pAnimation->mChannels[i];
		}
	}

	return nullptr;
}

void FbxModel::CalcInterpolatedScaling(Vector3& mxOut, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumScalingKeys == 1)
	{
		mxOut = MyMath::AssimpVector3(pNodeAnim->mScalingKeys[0].mValue);
		return;
	}

	UINT ScalingIndex = 0;
	if (!FindScaling(AnimationTime, pNodeAnim, ScalingIndex))
	{
		mxOut = Vector3(1.0f, 1.0f, 1.0f);
		return;
	}

	UINT NextScalingIndex = (ScalingIndex + 1);
	ATLASSERT(NextScalingIndex < pNodeAnim->mNumScalingKeys);
	float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
	ATLASSERT(Factor >= 0.0f && Factor <= 1.0f);

	mxOut = lerp(MyMath::AssimpVector3(pNodeAnim->mScalingKeys[ScalingIndex].mValue), MyMath::AssimpVector3(pNodeAnim->mScalingKeys[NextScalingIndex].mValue), Factor);

}

void FbxModel::CalcInterpolatedRotation(Vector4& mxOut, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumRotationKeys == 1)
	{
		mxOut = MyMath::AssimpQuaternionVec4(pNodeAnim->mRotationKeys[0].mValue);
		return;
	}

	UINT RotationIndex = 0;
	if (!FindRotation(AnimationTime, pNodeAnim, RotationIndex))
	{
		mxOut = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
		return;
	}

	UINT NextRotationIndex = (RotationIndex + 1);
	ATLASSERT(NextRotationIndex < pNodeAnim->mNumRotationKeys);
	float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime
		- pNodeAnim->mRotationKeys[RotationIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
	ATLASSERT(Factor >= 0.0f && Factor <= 1.0f);

	mxOut = MyMath::QuaternionSlerp(
		pNodeAnim->mRotationKeys[RotationIndex].mValue
		, pNodeAnim->mRotationKeys[NextRotationIndex].mValue
		, Factor);

}

void FbxModel::CalcInterpolatedPosition(Vector3& mxOut, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumPositionKeys == 1)
	{
		mxOut = MyMath::AssimpVector3(pNodeAnim->mPositionKeys[0].mValue);
		return;
	}

	UINT PositionIndex = 0;
	if (!FindPosition(AnimationTime, pNodeAnim, PositionIndex))
	{
		mxOut = Vector3(0.0f, 0.0f, 0.0f);
		return;
	}

	UINT NextPositionIndex = (PositionIndex + 1);

	ATLASSERT(NextPositionIndex < pNodeAnim->mNumPositionKeys);
	float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
	ATLASSERT(Factor >= 0.0f && Factor <= 1.0f);

	mxOut = lerp(MyMath::AssimpVector3(pNodeAnim->mPositionKeys[PositionIndex].mValue), MyMath::AssimpVector3(pNodeAnim->mPositionKeys[NextPositionIndex].mValue), Factor);
}

bool FbxModel::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim, UINT& nPosIndex)
{
	nPosIndex = 0;
	if (!(pNodeAnim->mNumPositionKeys > 0))
	{
		return FALSE;
	}

	for (UINT i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++)
	{
		if ((AnimationTime >= (float)pNodeAnim->mPositionKeys[i].mTime)
			&& (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime))
		{
			nPosIndex = i;
			return TRUE;
		}
	}

	return FALSE;
}

bool FbxModel::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim, UINT& nRotationIndex)
{
	nRotationIndex = 0;
	if (!(pNodeAnim->mNumRotationKeys > 0))
	{
		return FALSE;
	}

	for (UINT i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++)
	{

		if ((AnimationTime >= (float)pNodeAnim->mRotationKeys[i].mTime)
			&& (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime))
		{
			nRotationIndex = i;
			return TRUE;
		}
	}

	return FALSE;
}

bool FbxModel::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim, UINT& nScalingIndex)
{
	nScalingIndex = 0;
	if (!(pNodeAnim->mNumScalingKeys > 0))
	{
		return FALSE;
	}

	for (UINT i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++)
	{
		if ((AnimationTime >= (float)pNodeAnim->mScalingKeys[i].mTime)
			&& (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime))
		{
			nScalingIndex = i;
			return TRUE;
		}
	}

	return FALSE;
}