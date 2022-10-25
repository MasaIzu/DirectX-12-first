#pragma once
#include <xaudio2.h>
#include <fstream>
#include <wrl.h>

#pragma comment(lib,"xaudio2.lib")



//�`�����N�w�b�_
struct ChunkHeader
{
	char id[4]; //�`�����N����ID
	int32_t size;   //�`�����N�̃T�C�Y
};
//RIFF�`�����N
struct RiffHeader
{
	ChunkHeader chunk;  // "RIFF"
	char type[4];   // "WAVE"
};
//FMT�`�����N
struct FormatChunk
{
	ChunkHeader chunk;  // "fmt"
	WAVEFORMATEX fmt;   // �g�`�t�H�[�}�b�g
};
//�����f�[�^
struct SoundData
{
	//�g�`�t�H�[�}�b�g
	WAVEFORMATEX wfex;
	//�o�b�t�@�̐擪�A�h���X
	BYTE* pBuffer;
	//�o�b�t�@�̃T�C�Y
	unsigned int bufferSize;
};

class Audio {
public:		//�����o�֐�
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	
	// �C���X�^���X��
	static Audio* GetInstance();

	//������
	void Initialize();
	//�����ǂݍ���
	void SoundLoadWave(const char* filename);
	//�����f�[�^���
	void SoundUnload();
	//�����Đ�
	void SoundPlayWave();
	// ������~
	void StopWave(const SoundData& soundData);
	//�������Z�b�g���f�[�^�J��
	void Reset();

	////xAudio2���
	//ComPtr<IXAudio2> GetAudio();
	////�f�[�^���
	//SoundData GetSound() { return soundData; }

private:
	Audio() = default;
	~Audio() = default;

	Audio(const Audio&) = delete;
	Audio& operator = (const Audio&) = delete;

private:	//�����o�ϐ�
	//�T�E���h�Đ�
	ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice;
	//�Đ�����g�`�f�[�^�̐ݒ�
	XAUDIO2_BUFFER buf{};
	//�����f�[�^
	SoundData soundData;
};