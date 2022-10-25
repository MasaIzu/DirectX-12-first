#include "Audio.h"
#include <cassert>

Audio* Audio::GetInstance()
{
    static Audio* audio = new Audio;
    return audio;
}

//������
void Audio::Initialize() {
    HRESULT result;

    //XAudio�G���W���̃C���X�^���X�𐶐�
    result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
    //�}�X�^�[�{�C�X�𐶐�
    result = xAudio2->CreateMasteringVoice(&masterVoice);
}

//�����ǂݍ���
void Audio::SoundLoadWave(const char* filename)
{
    HRESULT result;

    //�t�@�C�����̓X�g���[���̃C���X�^���X
    std::ifstream file;
    //.wav�t�@�C�����o�C�i�����[�h�ŊJ��
    file.open(filename, std::ios_base::binary);
    //�t�@�C���I�[�v�����s�����o����
    assert(file.is_open());

    //RIFF�w�b�_�[�̓ǂݍ���
    RiffHeader riff;
    file.read((char*)&riff, sizeof(riff));
    //�t�@�C����RIFF���`�F�b�N
    if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
        assert(0);
    }
    //�^�C�v��WAVE���`�F�b�N
    if (strncmp(riff.type, "WAVE", 4) != 0) {
        assert(0);
    }
    //Format�`�����N�̓ǂݍ���
    FormatChunk format = {};
    //�`�����N�w�b�_�[�̊m�F
    file.read((char*)&format, sizeof(ChunkHeader));
    if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
        assert(0);
    }

    //�`�����N�{�̂̓ǂݍ���
    assert(format.chunk.size <= sizeof(format.fmt));
    file.read((char*)&format.fmt, format.chunk.size);

    //Data�`�����N�̓ǂݍ���
    ChunkHeader data;
    file.read((char*)&data, sizeof(data));
    //JUNK�`�����N�����o�����ꍇ
    if (strncmp(data.id, "JUNK", 4) == 0) {
        //�ǂݎ��ʒu��JUNK�`�����N�̏I���܂Ői�߂�
        file.seekg(data.size, std::ios_base::cur);
        //�ēǂݍ���
        file.read((char*)&data, sizeof(data));
    }
    if (strncmp(data.id, "data", 4) != 0) {
        assert(0);
    }

    //Data�`�����N�̃f�[�^���i�g�`�f�[�^�j�̓ǂݍ���
    char* pBuffer = new char[data.size];
    file.read(pBuffer, data.size);

    //Wave�t�@�C�������
    file.close();

    soundData.wfex = format.fmt;
    soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
    soundData.bufferSize = data.size;
}

//�����f�[�^���
void Audio::SoundUnload() {
    //XAudio2���
    xAudio2.Reset();

    //�o�b�t�@�̃����������
    delete[] soundData.pBuffer;

    soundData.pBuffer = 0;
    soundData.bufferSize = 0;
    soundData.wfex = {};
}

//�����Đ�
void Audio::SoundPlayWave() {
    HRESULT result;

    //�g�`�t�H�[�}�b�g������SourceVoice�̐���
    IXAudio2SourceVoice* pSourceVoice = nullptr;
    result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
    assert(SUCCEEDED(result));


    buf.pAudioData = soundData.pBuffer;
    buf.AudioBytes = soundData.bufferSize;
    buf.Flags = XAUDIO2_END_OF_STREAM;

    //�g�`�f�[�^�̍Đ�
    result = pSourceVoice->SubmitSourceBuffer(&buf);
    result = pSourceVoice->Start();

}

void Audio::StopWave(const SoundData& soundData)
{
    HRESULT result;
    //�g�`�t�H�[�}�b�g������SourceVoice�̐���
    IXAudio2SourceVoice* pSourceVoice = nullptr;
    result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
    assert(SUCCEEDED(result));

    XAUDIO2_VOICE_STATE state;
    pSourceVoice->GetState(&state);
    if (state.BuffersQueued == 0)
    {
        return;
    }
    result = pSourceVoice->Stop(0);
    result = pSourceVoice->FlushSourceBuffers();
    result = pSourceVoice->SubmitSourceBuffer(&buf);
}