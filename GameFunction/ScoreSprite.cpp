#include "ScoreSprite.h"

ScoreSprite::ScoreSprite()
{
}

ScoreSprite::~ScoreSprite()
{
}

void ScoreSprite::Initialize()
{
    Sprite::LoadTexture(10, L"Resources/TimeFont.png");
    for (int i = 0; i < 10; i++)
    {
        texBase.x = 64 * i;
        scoresprite[i] = Sprite::Create(10, { pos.x,pos.y }, { color.x,color.y,color.z,color.w }, { anker.x,anker.y });
        scoresprite[i]->SetSize({ size.x,size.y });
        scoresprite[i]->SetTextureRect({ texBase.x,texBase.y }, { texsize.x,texsize.y });
    }
}

void ScoreSprite::Draw(int num, Vector2 pos)
{
    scoresprite[num]->SetPosition({ pos.x,pos.y });
    scoresprite[num]->Draw();
}

void ScoreSprite::SetSize(Vector2 size)
{
}