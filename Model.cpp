#include "Model.h"
#include <DirectXTex.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

/// <summary>
/// �ÓI�����o�ϐ��̎���
/// </summary>
ID3D12Device* Model::sDevice = nullptr;
UINT Model::sDescriptorHandleIncrementSize = 0;
ID3D12GraphicsCommandList* Model::sCommandList = nullptr;
ComPtr<ID3D12RootSignature> Model::sRootSignature;
ComPtr<ID3D12PipelineState> Model::sPipelineState;

void Model::StaticInitialize(ID3D12Device* device, int window_width, int window_height) {
    // nullptr�`�F�b�N
    assert(device);

    sDevice = device;

    // �p�C�v���C��������
    InitializeGraphicsPipeline();
}

void Model::PreDraw(ID3D12GraphicsCommandList* commandList) {
    // PreDraw��PostDraw���y�A�ŌĂ΂�Ă��Ȃ���΃G���[
    assert(Model::sCommandList == nullptr);

    // �R�}���h���X�g���Z�b�g
    sCommandList = commandList;

    // �p�C�v���C���X�e�[�g�̐ݒ�
    commandList->SetPipelineState(sPipelineState.Get());
    // ���[�g�V�O�l�`���̐ݒ�
    commandList->SetGraphicsRootSignature(sRootSignature.Get());
    // �v���~�e�B�u�`���ݒ�
    commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Model::PostDraw() {
    // �R�}���h���X�g������
    sCommandList = nullptr;
}

Model* Model::Create() {
    // 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
    Model* object3d = new Model();
    assert(object3d);

    // ������
    object3d->Initialize();

    return object3d;
}

void Model::InitializeGraphicsPipeline() {
    HRESULT result = S_FALSE;
    ComPtr<ID3DBlob> vsBlob;    // ���_�V�F�[�_�I�u�W�F�N�g
    ComPtr<ID3DBlob> psBlob;    // �s�N�Z���V�F�[�_�I�u�W�F�N�g
    ComPtr<ID3DBlob> errorBlob; // �G���[�I�u�W�F�N�g

    // ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
    result = D3DCompileFromFile(
        L"Resources/shaders/BasicVS.hlsl", // �V�F�[�_�t�@�C����
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
        "main", "vs_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
        0, &vsBlob, &errorBlob);
    if (FAILED(result)) {
        // errorBlob����G���[���e��string�^�ɃR�s�[
        std::string errstr;
        errstr.resize(errorBlob->GetBufferSize());

        std::copy_n((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), errstr.begin());
        errstr += "\n";
        // �G���[���e���o�̓E�B���h�E�ɕ\��
        OutputDebugStringA(errstr.c_str());
        exit(1);
    }

    // �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
    result = D3DCompileFromFile(
        L"Resources/shaders/BasicPS.hlsl", // �V�F�[�_�t�@�C����
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
        "main", "ps_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
        0, &psBlob, &errorBlob);
    if (FAILED(result)) {
        // errorBlob����G���[���e��string�^�ɃR�s�[
        std::string errstr;
        errstr.resize(errorBlob->GetBufferSize());

        std::copy_n((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), errstr.begin());
        errstr += "\n";
        // �G���[���e���o�̓E�B���h�E�ɕ\��
        OutputDebugStringA(errstr.c_str());
        exit(1);
    }

    // ���_���C�A�E�g
    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
      {// xy���W(1�s�ŏ������ق������₷��)
       "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT,
       D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
      {// �@���x�N�g��(1�s�ŏ������ق������₷��)
       "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT,
       D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
      {// uv���W(1�s�ŏ������ق������₷��)
       "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT,
       D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
    };

    // �O���t�B�b�N�X�p�C�v���C���̗����ݒ�
    D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
    gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
    gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

    // �T���v���}�X�N
    gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�
    // ���X�^���C�U�X�e�[�g
    gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    // gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
    // gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
    //  �f�v�X�X�e���V���X�e�[�g
    gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

    // �����_�[�^�[�Q�b�g�̃u�����h�ݒ�
    D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
    blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA�S�Ẵ`�����l����`��
    blenddesc.BlendEnable = true;
    blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
    blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
    blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

    blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
    blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
    blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

    // �u�����h�X�e�[�g�̐ݒ�
    gpipeline.BlendState.RenderTarget[0] = blenddesc;

    // �[�x�o�b�t�@�̃t�H�[�}�b�g
    gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;

    // ���_���C�A�E�g�̐ݒ�
    gpipeline.InputLayout.pInputElementDescs = inputLayout;
    gpipeline.InputLayout.NumElements = _countof(inputLayout);

    // �}�`�̌`��ݒ�i�O�p�`�j
    gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

    gpipeline.NumRenderTargets = 1;                            // �`��Ώۂ�1��
    gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0�`255�w���RGBA
    gpipeline.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

    // �f�X�N���v�^�����W
    CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
    descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0 ���W�X�^

    // ���[�g�p�����[�^
    CD3DX12_ROOT_PARAMETER rootparams[3] = {};
    rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
    rootparams[1].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_ALL);
    rootparams[2].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);

    // �X�^�e�B�b�N�T���v���[
    CD3DX12_STATIC_SAMPLER_DESC samplerDesc =
        CD3DX12_STATIC_SAMPLER_DESC(0, D3D12_FILTER_MIN_MAG_MIP_LINEAR);

    // ���[�g�V�O�l�`���̐ݒ�
    CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
    rootSignatureDesc.Init_1_0(
        _countof(rootparams), rootparams, 1, &samplerDesc,
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ComPtr<ID3DBlob> rootSigBlob;
    // �o�[�W������������̃V���A���C�Y
    result = D3DX12SerializeVersionedRootSignature(
        &rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
    // ���[�g�V�O�l�`���̐���
    result = sDevice->CreateRootSignature(
        0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
        IID_PPV_ARGS(&sRootSignature));
    assert(SUCCEEDED(result));

    gpipeline.pRootSignature = sRootSignature.Get();

    // �O���t�B�b�N�X�p�C�v���C���̐���
    result = sDevice->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&sPipelineState));
    assert(SUCCEEDED(result));
}

void Model::CreateMesh() {
    HRESULT result = S_FALSE;

    vertices_ = {
        //  x      y      z       nx     ny    nz       u     v
        // �O
          {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}}, // ����
          {{-1.0f, +1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // ����
          {{+1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}}, // �E��
          {{+1.0f, +1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}}, // �E��
          // ��(�O�ʂ�Z���W�̕������t)
            {{+1.0f, -1.0f, +1.0f}, {0.0f, 0.0f, +1.0f}, {0.0f, 1.0f}}, // ����
            {{+1.0f, +1.0f, +1.0f}, {0.0f, 0.0f, +1.0f}, {0.0f, 0.0f}}, // ����
            {{-1.0f, -1.0f, +1.0f}, {0.0f, 0.0f, +1.0f}, {1.0f, 1.0f}}, // �E��
            {{-1.0f, +1.0f, +1.0f}, {0.0f, 0.0f, +1.0f}, {1.0f, 0.0f}}, // �E��
            // ��
              {{-1.0f, -1.0f, +1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, // ����
              {{-1.0f, +1.0f, +1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // ����
              {{-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // �E��
              {{-1.0f, +1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // �E��
              // �E�i���ʂ�X���W�̕������t�j
                {{+1.0f, -1.0f, -1.0f}, {+1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, // ����
                {{+1.0f, +1.0f, -1.0f}, {+1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // ����
                {{+1.0f, -1.0f, +1.0f}, {+1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // �E��
                {{+1.0f, +1.0f, +1.0f}, {+1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // �E��
                // ��
                  {{+1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}}, // ����
                  {{+1.0f, -1.0f, +1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}}, // ����
                  {{-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}}, // �E��
                  {{-1.0f, -1.0f, +1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}}, // �E��
                  // ��i���ʂ�Y���W�̕������t�j
                    {{-1.0f, +1.0f, -1.0f}, {0.0f, +1.0f, 0.0f}, {0.0f, 1.0f}}, // ����
                    {{-1.0f, +1.0f, +1.0f}, {0.0f, +1.0f, 0.0f}, {0.0f, 0.0f}}, // ����
                    {{+1.0f, +1.0f, -1.0f}, {0.0f, +1.0f, 0.0f}, {1.0f, 1.0f}}, // �E��
                    {{+1.0f, +1.0f, +1.0f}, {0.0f, +1.0f, 0.0f}, {1.0f, 0.0f}}, // �E��
    };

    // ���_�C���f�b�N�X�̐ݒ�
    indices_ = { 0,  1,  3,  3,  2,  0,

                4,  5,  7,  7,  6,  4,

                8,  9,  11, 11, 10, 8,

                12, 13, 15, 15, 14, 12,

                16, 17, 19, 19, 18, 16,

                20, 21, 23, 23, 22, 20 };

    // ���_�f�[�^�̃T�C�Y
    UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUv) * vertices_.size());

    {
        // �q�[�v�v���p�e�B
        CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        // ���\�[�X�ݒ�
        CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeVB);

        // ���_�o�b�t�@����
        result = sDevice->CreateCommittedResource(
            &heapProps, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
            IID_PPV_ARGS(&vertBuff_));
        assert(SUCCEEDED(result));
    }

    // �C���f�b�N�X�f�[�^�̃T�C�Y
    UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * indices_.size());

    {
        // �q�[�v�v���p�e�B
        CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        // ���\�[�X�ݒ�
        CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeIB);

        // �C���f�b�N�X�o�b�t�@����
        result = sDevice->CreateCommittedResource(
            &heapProps, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
            IID_PPV_ARGS(&indexBuff_));
        assert(SUCCEEDED(result));
    }

    // ���_�o�b�t�@�ւ̃f�[�^�]��
    VertexPosNormalUv* vertMap = nullptr;
    result = vertBuff_->Map(0, nullptr, (void**)&vertMap);
    if (SUCCEEDED(result)) {
        std::copy(vertices_.begin(), vertices_.end(), vertMap);
        vertBuff_->Unmap(0, nullptr);
    }

    // �C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
    uint16_t* indexMap = nullptr;
    result = indexBuff_->Map(0, nullptr, (void**)&indexMap);
    if (SUCCEEDED(result)) {
        std::copy(indices_.begin(), indices_.end(), indexMap);

        indexBuff_->Unmap(0, nullptr);
    }

    // ���_�o�b�t�@�r���[�̍쐬
    vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress();
    vbView_.SizeInBytes = sizeVB;
    vbView_.StrideInBytes = sizeof(vertices_[0]);

    // �C���f�b�N�X�o�b�t�@�r���[�̍쐬
    ibView_.BufferLocation = indexBuff_->GetGPUVirtualAddress();
    ibView_.Format = DXGI_FORMAT_R16_UINT;
    ibView_.SizeInBytes = sizeIB;
}

void Model::Initialize() {
    // nullptr�`�F�b�N
    assert(sDevice);

    // ���b�V������
    CreateMesh();
}

void Model::Draw(
    const WorldTransform& worldTransform, const ViewProjection& viewProjection,
    uint32_t textureHadle) {
    // nullptr�`�F�b�N
    assert(sDevice);
    assert(sCommandList);
    assert(worldTransform.constBuff_.Get());

    // ���_�o�b�t�@�̐ݒ�
    sCommandList->IASetVertexBuffers(0, 1, &vbView_);
    // �C���f�b�N�X�o�b�t�@�̐ݒ�
    sCommandList->IASetIndexBuffer(&ibView_);

    // CBV���Z�b�g�i���[���h�s��j
    sCommandList->SetGraphicsRootConstantBufferView(
        static_cast<UINT>(RoomParameter::kWorldTransform),
        worldTransform.constBuff_->GetGPUVirtualAddress());

    // CBV���Z�b�g�i�r���[�v���W�F�N�V�����s��j
    sCommandList->SetGraphicsRootConstantBufferView(
        static_cast<UINT>(RoomParameter::kViewProjection),
        viewProjection.constBuff_->GetGPUVirtualAddress());

    // SRV���Z�b�g
    TextureManager::GetInstance()->SetGraphicsRootDescriptorTable(
        sCommandList, static_cast<UINT>(RoomParameter::kTexture), textureHadle);

    // �`��R�}���h
    sCommandList->DrawIndexedInstanced(static_cast<UINT>(indices_.size()), 1, 0, 0, 0);
}
