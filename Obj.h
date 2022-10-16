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

	// 頂点データ構造体
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT3 normal; // 法線ベクトル
		XMFLOAT3 uv;  // uv座標
	};

	/// <summary>
	/// obj読み込み
	/// </summary>
	void LoadObj();

	/// <summary>
	/// objモデルの作成
	/// </summary>
	void CreateObjModel();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // 定数
	static const int division = 50;					// 分割数
	static const float radius;				// 底面の半径
	static const float prizmHeight;			// 柱の高さ
	static const int planeCount = division * 2 + division * 2;		// 面の数
	static const int vertexCount = planeCount * 3;		// 頂点数

private://静的メンバ変数
	// 頂点バッファ
	static ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	static ComPtr<ID3D12Resource> indexBuff;

	// 頂点バッファビュー
	static D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	static D3D12_INDEX_BUFFER_VIEW ibView;
	// 頂点データ配列
	static VertexPosNormalUv vertices[vertexCount];
	// 頂点インデックス配列
	static unsigned short indices[planeCount * 3];


private://メンバ変数
	DirectXCore* directXCore = DirectXCore::GetInstance();
	//頂点データ配列
	static std::vector<VertexPosNormalUv> vertices;
	//頂点インデックス配列
	static std::vector<unsigned short> indices;

};