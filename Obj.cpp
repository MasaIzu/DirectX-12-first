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
//	//�t�@�C���X�g���[��
//	std::ifstream file;
//	//.obj�t�@�C�����J��
//	file.open("Resources/triangle.obj");
//	//�t�@�C���I�[�v�����s���`�F�b�N
//	if (file.fail()) {
//		assert(0);
//	}
//
//	XMFLOAT3 position;//���_���W
//	XMFLOAT3 normals;//�@���x�N�g��
//	XMFLOAT3 texcoords;//�e�N�X�`��UV
//	//1�s���ǂ݂���
//	string line;
//	while (getline(file, line)) {
//		//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
//		std::istringstream line_stream(line);
//
//		//���p�X�y�[�X��؂�ōs�̐擪��������擾
//		string key;
//		getline(line_stream, key, ' ');
//		
//		
//
//	}
//	//�t�@�C�������
//	file.close();
//
//}
//
//void Obj::CreateObjModel(){
//	
//	HRESULT result = S_FALSE;
//
//	std::vector<VertexPosNormalUv> realVertices;
//	// ���_���W�̌v�Z�i�d������j
//	{
//		realVertices.resize((division + 1) * 2);
//		int index = 0;
//		float zValue;
//
//		// ���
//		zValue = prizmHeight / 2.0f;
//		for (int i = 0; i < division; i++)
//		{
//			XMFLOAT3 vertex;
//			vertex.x = radius * sinf(XM_2PI / division * i);
//			vertex.y = radius * cosf(XM_2PI / division * i);
//			vertex.z = zValue;
//			realVertices[index++].pos = vertex;
//		}
//		realVertices[index++].pos = XMFLOAT3(0, 0, zValue);	// ��ʂ̒��S�_
//		// �V��
//		zValue = -prizmHeight / 2.0f;
//		for (int i = 0; i < division; i++)
//		{
//			XMFLOAT3 vertex;
//			vertex.x = radius * sinf(XM_2PI / division * i);
//			vertex.y = radius * cosf(XM_2PI / division * i);
//			vertex.z = zValue;
//			realVertices[index++].pos = vertex;
//		}
//		realVertices[index++].pos = XMFLOAT3(0, 0, zValue);	// �V�ʂ̒��S�_
//	}
//
//	// ���_���W�̌v�Z�i�d���Ȃ��j
//	{
//		int index = 0;
//		// ���
//		for (int i = 0; i < division; i++)
//		{
//			unsigned short index0 = i + 1;
//			unsigned short index1 = i;
//			unsigned short index2 = division;
//
//			vertices[index++] = realVertices[index0];
//			vertices[index++] = realVertices[index1];
//			vertices[index++] = realVertices[index2]; // ��ʂ̒��S�_
//		}
//		// ��ʂ̍Ō�̎O�p�`��1�Ԗڂ̃C���f�b�N�X��0�ɏ�������
//		vertices[index - 3] = realVertices[0];
//
//		int topStart = division + 1;
//		// �V��
//		for (int i = 0; i < division; i++)
//		{
//			unsigned short index0 = topStart + i;
//			unsigned short index1 = topStart + i + 1;
//			unsigned short index2 = topStart + division;
//
//			vertices[index++] = realVertices[index0];
//			vertices[index++] = realVertices[index1];
//			vertices[index++] = realVertices[index2]; // �V�ʂ̒��S�_
//		}
//		// �V�ʂ̍Ō�̎O�p�`��1�Ԗڂ̃C���f�b�N�X��0�ɏ�������
//		vertices[index - 2] = realVertices[topStart];
//
//		// ����
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
//	// ���_�C���f�b�N�X�̐ݒ�
//	{
//		for (int i = 0; i < _countof(indices); i++)
//		{
//			indices[i] = i;
//		}
//	}
//
//	// �@�������̌v�Z
//	for (int i = 0; i < _countof(indices) / 3; i++)
//	{// �O�p�`�P���ƂɌv�Z���Ă���
//		// �O�p�`�̃C���f�b�N�X���擾
//		unsigned short index0 = indices[i * 3 + 0];
//		unsigned short index1 = indices[i * 3 + 1];
//		unsigned short index2 = indices[i * 3 + 2];
//		// �O�p�`���\�����钸�_���W���x�N�g���ɑ��
//		XMVECTOR p0 = XMLoadFloat3(&vertices[index0].pos);
//		XMVECTOR p1 = XMLoadFloat3(&vertices[index1].pos);
//		XMVECTOR p2 = XMLoadFloat3(&vertices[index2].pos);
//		// p0��p1�x�N�g���Ap0��p2�x�N�g�����v�Z
//		XMVECTOR v1 = XMVectorSubtract(p1, p0);
//		XMVECTOR v2 = XMVectorSubtract(p2, p0);
//		// �O�ς͗������琂���ȃx�N�g��
//		XMVECTOR normal = XMVector3Cross(v1, v2);
//		// ���K���i������1�ɂ���)
//		normal = XMVector3Normalize(normal);
//		// ���߂��@���𒸓_�f�[�^�ɑ��
//		XMStoreFloat3(&vertices[index0].normal, normal);
//		XMStoreFloat3(&vertices[index1].normal, normal);
//		XMStoreFloat3(&vertices[index2].normal, normal);
//	}
//
//	UINT sizeVB = static_cast<UINT>(sizeof(vertices));
//
//	// �q�[�v�v���p�e�B
//	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
//	// ���\�[�X�ݒ�
//	CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeVB);
//
//
//	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUv) * vertices.size());
//	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());
//
//	// ���_�o�b�t�@����
//	result = directXCore->GetDevice()->CreateCommittedResource(
//		&heapProps, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
//		IID_PPV_ARGS(&vertBuff));
//	assert(SUCCEEDED(result));
//
//	// ���_�o�b�t�@�ւ̃f�[�^�]��
//	VertexPosNormalUv* vertMap = nullptr;
//	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
//	if (SUCCEEDED(result)) {
//		//memcpy(vertMap, vertices, sizeof(vertices));
//		std::copy(vertices.begin(), vertices.end(), vertMap);
//		vertBuff->Unmap(0, nullptr);
//	}
//
//	// ���_�o�b�t�@�r���[�̍쐬
//	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
//	//vbView.SizeInBytes = sizeof(vertices);
//	vbView.SizeInBytes = sizeVB;
//	vbView.StrideInBytes = sizeof(vertices[0]);
//
//	UINT sizeIB = static_cast<UINT>(sizeof(indices));
//	// ���\�[�X�ݒ�
//	resourceDesc.Width = sizeIB;
//
//	// �C���f�b�N�X�o�b�t�@����
//	result = directXCore->GetDevice()->CreateCommittedResource(
//		&heapProps, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
//		IID_PPV_ARGS(&indexBuff));
//
//	// �C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
//	unsigned short* indexMap = nullptr;
//	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
//	if (SUCCEEDED(result)) {
//
//		//// �S�C���f�b�N�X�ɑ΂���
//		//for (int i = 0; i < _countof(indices); i++)
//		//{
//		//	indexMap[i] = indices[i];	// �C���f�b�N�X���R�s�[
//		//}
//
//		std::copy(indices.begin(), indices.end(), indexMap);
//		indexBuff->Unmap(0, nullptr);
//	}
//
//	// �C���f�b�N�X�o�b�t�@�r���[�̍쐬
//	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
//	ibView.Format = DXGI_FORMAT_R16_UINT;
//	//ibView.SizeInBytes = sizeof(indices);
//	ibView.SizeInBytes = sizeIB;
//}
