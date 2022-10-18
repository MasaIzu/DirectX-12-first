//#include "Obj.h"
//#include <cassert>
//#include <d3dcompiler.h>
//#include <DirectXTex.h>
//
//#pragma comment(lib, "d3dcompiler.lib")
//
//using namespace DirectX;
//using namespace Microsoft::WRL;
//
//ComPtr<ID3D12Resource> Obj::vertBuff;
//ComPtr<ID3D12Resource> Obj::indexBuff;
//D3D12_VERTEX_BUFFER_VIEW Obj::vbView{};
//D3D12_INDEX_BUFFER_VIEW Obj::ibView{};
//std::vector<Obj::VertexPosNormalUv> Obj::vertices;
//std::vector<unsigned short> Obj::indices;
//
//void Obj::LoadObj(){
//	//ファイルストリーム
//	std::ifstream file;
//	//.objファイルを開く
//	file.open("Resources/triangle.obj");
//	//ファイルオープン失敗をチェック
//	if (file.fail()) {
//		assert(0);
//	}
//
//	XMFLOAT3 position;//頂点座標
//	XMFLOAT3 normals;//法線ベクトル
//	XMFLOAT3 texcoords;//テクスチャUV
//	//1行ずつ読みこむ
//	string line;
//	while (getline(file, line)) {
//		//1行分の文字列をストリームに変換して解析しやすくする
//		std::istringstream line_stream(line);
//
//		//半角スペース区切りで行の先頭文字列を取得
//		string key;
//		getline(line_stream, key, ' ');
//		
//		
//
//	}
//	//ファイルを閉じる
//	file.close();
//
//}
//
//void Obj::CreateObjModel(){
//	
//	HRESULT result = S_FALSE;
//
//	std::vector<VertexPosNormalUv> realVertices;
//	// 頂点座標の計算（重複あり）
//	{
//		realVertices.resize((division + 1) * 2);
//		int index = 0;
//		float zValue;
//
//		// 底面
//		zValue = prizmHeight / 2.0f;
//		for (int i = 0; i < division; i++)
//		{
//			XMFLOAT3 vertex;
//			vertex.x = radius * sinf(XM_2PI / division * i);
//			vertex.y = radius * cosf(XM_2PI / division * i);
//			vertex.z = zValue;
//			realVertices[index++].pos = vertex;
//		}
//		realVertices[index++].pos = XMFLOAT3(0, 0, zValue);	// 底面の中心点
//		// 天面
//		zValue = -prizmHeight / 2.0f;
//		for (int i = 0; i < division; i++)
//		{
//			XMFLOAT3 vertex;
//			vertex.x = radius * sinf(XM_2PI / division * i);
//			vertex.y = radius * cosf(XM_2PI / division * i);
//			vertex.z = zValue;
//			realVertices[index++].pos = vertex;
//		}
//		realVertices[index++].pos = XMFLOAT3(0, 0, zValue);	// 天面の中心点
//	}
//
//	// 頂点座標の計算（重複なし）
//	{
//		int index = 0;
//		// 底面
//		for (int i = 0; i < division; i++)
//		{
//			unsigned short index0 = i + 1;
//			unsigned short index1 = i;
//			unsigned short index2 = division;
//
//			vertices[index++] = realVertices[index0];
//			vertices[index++] = realVertices[index1];
//			vertices[index++] = realVertices[index2]; // 底面の中心点
//		}
//		// 底面の最後の三角形の1番目のインデックスを0に書き換え
//		vertices[index - 3] = realVertices[0];
//
//		int topStart = division + 1;
//		// 天面
//		for (int i = 0; i < division; i++)
//		{
//			unsigned short index0 = topStart + i;
//			unsigned short index1 = topStart + i + 1;
//			unsigned short index2 = topStart + division;
//
//			vertices[index++] = realVertices[index0];
//			vertices[index++] = realVertices[index1];
//			vertices[index++] = realVertices[index2]; // 天面の中心点
//		}
//		// 天面の最後の三角形の1番目のインデックスを0に書き換え
//		vertices[index - 2] = realVertices[topStart];
//
//		// 側面
//		for (int i = 0; i < division; i++)
//		{
//			unsigned short index0 = i + 1;
//			unsigned short index1 = topStart + i + 1;
//			unsigned short index2 = i;
//			unsigned short index3 = topStart + i;
//
//			if (i == division - 1)
//			{
//				index0 = 0;
//				index1 = topStart;
//			}
//
//			vertices[index++] = realVertices[index0];
//			vertices[index++] = realVertices[index1];
//			vertices[index++] = realVertices[index2];
//
//			vertices[index++] = realVertices[index2];
//			vertices[index++] = realVertices[index1];
//			vertices[index++] = realVertices[index3];
//		}
//	}
//
//	// 頂点インデックスの設定
//	{
//		for (int i = 0; i < _countof(indices); i++)
//		{
//			indices[i] = i;
//		}
//	}
//
//	// 法線方向の計算
//	for (int i = 0; i < _countof(indices) / 3; i++)
//	{// 三角形１つごとに計算していく
//		// 三角形のインデックスを取得
//		unsigned short index0 = indices[i * 3 + 0];
//		unsigned short index1 = indices[i * 3 + 1];
//		unsigned short index2 = indices[i * 3 + 2];
//		// 三角形を構成する頂点座標をベクトルに代入
//		XMVECTOR p0 = XMLoadFloat3(&vertices[index0].pos);
//		XMVECTOR p1 = XMLoadFloat3(&vertices[index1].pos);
//		XMVECTOR p2 = XMLoadFloat3(&vertices[index2].pos);
//		// p0→p1ベクトル、p0→p2ベクトルを計算
//		XMVECTOR v1 = XMVectorSubtract(p1, p0);
//		XMVECTOR v2 = XMVectorSubtract(p2, p0);
//		// 外積は両方から垂直なベクトル
//		XMVECTOR normal = XMVector3Cross(v1, v2);
//		// 正規化（長さを1にする)
//		normal = XMVector3Normalize(normal);
//		// 求めた法線を頂点データに代入
//		XMStoreFloat3(&vertices[index0].normal, normal);
//		XMStoreFloat3(&vertices[index1].normal, normal);
//		XMStoreFloat3(&vertices[index2].normal, normal);
//	}
//
//	UINT sizeVB = static_cast<UINT>(sizeof(vertices));
//
//	// ヒーププロパティ
//	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
//	// リソース設定
//	CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeVB);
//
//
//	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUv) * vertices.size());
//	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());
//
//	// 頂点バッファ生成
//	result = directXCore->GetDevice()->CreateCommittedResource(
//		&heapProps, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
//		IID_PPV_ARGS(&vertBuff));
//	assert(SUCCEEDED(result));
//
//	// 頂点バッファへのデータ転送
//	VertexPosNormalUv* vertMap = nullptr;
//	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
//	if (SUCCEEDED(result)) {
//		//memcpy(vertMap, vertices, sizeof(vertices));
//		std::copy(vertices.begin(), vertices.end(), vertMap);
//		vertBuff->Unmap(0, nullptr);
//	}
//
//	// 頂点バッファビューの作成
//	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
//	//vbView.SizeInBytes = sizeof(vertices);
//	vbView.SizeInBytes = sizeVB;
//	vbView.StrideInBytes = sizeof(vertices[0]);
//
//	UINT sizeIB = static_cast<UINT>(sizeof(indices));
//	// リソース設定
//	resourceDesc.Width = sizeIB;
//
//	// インデックスバッファ生成
//	result = directXCore->GetDevice()->CreateCommittedResource(
//		&heapProps, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
//		IID_PPV_ARGS(&indexBuff));
//
//	// インデックスバッファへのデータ転送
//	unsigned short* indexMap = nullptr;
//	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
//	if (SUCCEEDED(result)) {
//
//		//// 全インデックスに対して
//		//for (int i = 0; i < _countof(indices); i++)
//		//{
//		//	indexMap[i] = indices[i];	// インデックスをコピー
//		//}
//
//		std::copy(indices.begin(), indices.end(), indexMap);
//		indexBuff->Unmap(0, nullptr);
//	}
//
//	// インデックスバッファビューの作成
//	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
//	ibView.Format = DXGI_FORMAT_R16_UINT;
//	//ibView.SizeInBytes = sizeof(indices);
//	ibView.SizeInBytes = sizeIB;
//}
