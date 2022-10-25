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
		scoresprite_[i] = Sprite::Create(10, {pos.x,pos.y}, {color.x,color.y,color.z,color.w}, {anker.x,anker.y});
		scoresprite_[i]->SetSize({ size_.x,size_.y });
		scoresprite_[i]->SetTextureRect({ texBase.x,texBase.y }, { texsize.x,texsize.y });
	}
}

void ScoreSprite::Draw(int num, Vector2 pos)
{
	scoresprite_[num]->SetPosition({pos.x,pos.y});
	scoresprite_[num]->Draw();
}

void ScoreSprite::SetSize(Vector2 size)
{
}
