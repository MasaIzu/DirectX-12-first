#pragma once
#include <xaudio2.h>
#include <fstream>
#include <wrl.h>

#pragma comment(lib,"xaudio2.lib")



//チャンクヘッダ
struct ChunkHeader
{
	char id[4]; //チャンク毎のID
	int32_t size;   //チャンクのサイズ
};
//RIFFチャンク
struct RiffHeader
{
	ChunkHeader chunk;  // "RIFF"
	char type[4];   // "WAVE"
};
//FMTチャンク
struct FormatChunk
{
	ChunkHeader chunk;  // "fmt"
	WAVEFORMATEX fmt;   // 波形フォーマット
};
//音声データ
struct SoundData
{
	//波形フォーマット
	WAVEFORMATEX wfex;
	//バッファの先頭アドレス
	BYTE* pBuffer;
	//バッファのサイズ
	unsigned int bufferSize;
};

class Audio {
public:		//メンバ関数
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	
	// インスタンス化
	static Audio* GetInstance();

	//初期化
	void Initialize();
	//音声読み込み
	void SoundLoadWave(const char* filename);
	//音声データ解放
	void SoundUnload();
	//音声再生
	void SoundPlayWave();
	// 音声停止
	void StopWave(const SoundData& soundData);
	//音声リセット→データ開放
	void Reset();

	////xAudio2情報
	//ComPtr<IXAudio2> GetAudio();
	////データ情報
	//SoundData GetSound() { return soundData; }

private:
	Audio() = default;
	~Audio() = default;

	Audio(const Audio&) = delete;
	Audio& operator = (const Audio&) = delete;

private:	//メンバ変数
	//サウンド再生
	ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice;
	//再生する波形データの設定
	XAUDIO2_BUFFER buf{};
	//音声データ
	SoundData soundData;
};