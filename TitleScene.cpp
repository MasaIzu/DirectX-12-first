#include "TitleScene.h"

void TitleScene::Initialize()
{
	input = Input::GetInstance();

	loserTexture_ = TextureManager::Load("Loser.png");
	sprite_.reset(Sprite::Create(loserTexture_));
	sceneManager_ = SceneManager::GetInstance();
}

void TitleScene::Update()
{
	if (input->TriggerKey(DIK_SPACE))
	{
		sceneManager_->ChangeScene("GAMEPLAY");
	}
}

void TitleScene::Draw()
{
	sprite_->Draw({50,50},{1,1,1,1});
}

void TitleScene::Finalize()
{
}
