
#pragma once
#include<d3d12.h>
#include<DirectXMath.h>
class Mesh
{
private:

	HRESULT result;
	ID3D12PipelineState* pipelineStage = nullptr;
	ID3D12RootSignature* rootSignature;
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	DirectX::XMFLOAT3 vertices[3];


public:
	void draw(ID3D12GraphicsCommandList* commandList);
	Mesh(ID3D12Device* device, DirectX::XMFLOAT3 vert[]);
};

