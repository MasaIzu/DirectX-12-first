#pragma once

#include "Model.h"
#include "ViewProjection.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>
#include "FbxLoader.h"
#include "Vector3.h"
#include "Matrix4.h"


class Object3d
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	// 定数バッファ用データ構造体（座標変換行列用）
	struct ConstBufferDataTransform
	{
		Matrix4 viewproj;    // ビュープロジェクション行列
		Matrix4 world; // ワールド行列
		Vector3 cameraPos; // カメラ座標（ワールド座標）
	};

public: // 定数
	//ボーンの最大数
	static const int MAX_BONES = 32;

	//定数バッファ用のデータ構造体
	struct ConstBufferDataSkin
	{
		Matrix4 bones[MAX_BONES];
	};


public: // 静的メンバ関数
	/// <summary>
	/// グラフィックパイプラインの生成
	/// </summary>
	static void CreateGraphicsPipeline();
	// setter
	static void SetDevice(ID3D12Device* device) { Object3d::device = device; }
	static void SetCamera(ViewProjection camera) { Object3d::camera = camera; }

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;
	// カメラ
	static ViewProjection camera;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 描画
	/// </summary>
	void DebugDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// アニメーション開始
	/// </summary>
	void PlayAnimation();


	void SetModel(Model* model) { this->model = model; }

protected: // メンバ変数
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffTransform;
	// ローカルスケール
	Vector3 scale = { 0.1f,0.1f,0.1f };
	// X,Y,Z軸回りのローカル回転角
	Vector3 rotation = { 0,0,0 };
	// ローカル座標
	Vector3 position = { 0,0,0 };
	// ローカルワールド変換行列
	Matrix4 matWorld;
	// モデル
	Model* model = nullptr;

	//定数バッファ(スキン)
	ComPtr<ID3D12Resource> constBuffSkin;

	//1フレームの時間
	FbxTime frameTime;
	//アニメーション開始時間
	FbxTime startTime;
	//アニメーション終了時間
	FbxTime endTime;
	//現在時間(アニメーション)
	FbxTime currentTime;
	//アニメーション再生中
	bool isPlay = false;

};

