#pragma once

#include "Sprite.h"
#include <memory>
#include "Vector2.h"
#include "Vector4.h"
#include <list>

class ScoreSprite
{
public:
    ScoreSprite();
    ~ScoreSprite();

    // �������̊֐�
    void Initialize();

    // �`��̊֐�
    void Draw(int num, Vector2 pos);

    void SetSize(Vector2 size);

private:
    // �X�v���C�g
    Sprite* scoresprite[10];

    // �������p�ϐ�
    Vector4 color = { 1, 1, 1, 1 };
    Vector2 anker = { 0, 0 };
    Vector2 size = { 18,28 };
    //�X�v���C�g�ꖇ������̃T�C�Y
    const Vector2 texsize = { 64,96 };
    Vector2 texBase = { 0,0 };

    // �ʒu
    Vector2 pos = { 800,200 };
};