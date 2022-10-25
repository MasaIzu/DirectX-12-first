#include "Audio.h"
#include <cassert>

Audio* Audio::GetInstance()
{
    static Audio* audio = new Audio;
    return audio;
}

//初期化
void Audio::Initialize() {
    HRESULT result;

    //XAudioエンジンのインスタンスを生成
    result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
    //マスターボイスを生成
    result = xAudio2->CreateMasteringVoice(&masterVoice);
}

//音声読み込み
void Audio::SoundLoadWave(const char* filename)
{
    HRESULT result;

    //ファイル入力ストリームのインスタンス
    std::ifstream file;
    //.wavファイルをバイナリモードで開く
    file.open(filename, std::ios_base::binary);
    //ファイルオープン失敗を検出する
    assert(file.is_open());

    //RIFFヘッダーの読み込み
    RiffHeader riff;
    file.read((char*)&riff, sizeof(riff));
    //ファイルがRIFFかチェック
    if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
        assert(0);
    }
    //タイプがWAVEかチェック
    if (strncmp(riff.type, "WAVE", 4) != 0) {
        assert(0);
    }
    //Formatチャンクの読み込み
    FormatChunk format = {};
    //チャンクヘッダーの確認
    file.read((char*)&format, sizeof(ChunkHeader));
    if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
        assert(0);
    }

    //チャンク本体の読み込み
    assert(format.chunk.size <= sizeof(format.fmt));
    file.read((char*)&format.fmt, format.chunk.size);

    //Dataチャンクの読み込み
    ChunkHeader data;
    file.read((char*)&data, sizeof(data));
    //JUNKチャンクを検出した場合
    if (strncmp(data.id, "JUNK", 4) == 0) {
        //読み取り位置をJUNKチャンクの終わりまで進める
        file.seekg(data.size, std::ios_base::cur);
        //再読み込み
        file.read((char*)&data, sizeof(data));
    }
    if (strncmp(data.id, "data", 4) != 0) {
        assert(0);
    }

    //Dataチャンクのデータ部（波形データ）の読み込み
    char* pBuffer = new char[data.size];
    file.read(pBuffer, data.size);

    //Waveファイルを閉じる
    file.close();

    soundData.wfex = format.fmt;
    soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
    soundData.bufferSize = data.size;
}

//音声データ解放
void Audio::SoundUnload() {
    //XAudio2解放
    xAudio2.Reset();

    //バッファのメモリを解放
    delete[] soundData.pBuffer;

    soundData.pBuffer = 0;
    soundData.bufferSize = 0;
    soundData.wfex = {};
}

//音声再生
void Audio::SoundPlayWave() {
    HRESULT result;

    //波形フォーマットを元にSourceVoiceの生成
    IXAudio2SourceVoice* pSourceVoice = nullptr;
    result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
    assert(SUCCEEDED(result));


    buf.pAudioData = soundData.pBuffer;
    buf.AudioBytes = soundData.bufferSize;
    buf.Flags = XAUDIO2_END_OF_STREAM;

    //波形データの再生
    result = pSourceVoice->SubmitSourceBuffer(&buf);
    result = pSourceVoice->Start();

}

void Audio::StopWave(const SoundData& soundData)
{
    HRESULT result;
    //波形フォーマットを元にSourceVoiceの生成
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