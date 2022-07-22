#include "Player.h"
#include"Input.h"

Input* input_ = Input::GetInstance();

Player* Player::GetInstance()
{
	static Player instance;
	return &instance;
}

void Player::Initializ(ID3D12Resource* constBuffMaterial){

	angle = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	eye = DirectX::XMFLOAT3(0, 0, -100);
	target = DirectX::XMFLOAT3(0, 0, 0);
	up = DirectX::XMFLOAT3(0, 1, 0);
	matView = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&eye), DirectX::XMLoadFloat3(&target), DirectX::XMLoadFloat3(&up));

	Red = 1.0f;
	Green = 1.0f;
	Blue = 1.0f;
	Alpha = 1.0f;
	Switch = 1;
	changeColor = 0;
	colorSpeed = 0.011;

	HRESULT result = S_FALSE;
	// 定数バッファのマッピング
	result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial); // マッピング
	assert(SUCCEEDED(result));
}

void Player::Updata()
{

	if (input_->PushKey(DIK_D) || input_->PushKey(DIK_A) || input_->PushKey(DIK_W) || input_->PushKey(DIK_S)) {
		if (input_->PushKey(DIK_D)) {
			angle.x += DirectX::XMConvertToRadians(1.0f);
			//angleラジアンだけy軸まわりに回転
			eye.x = -100 * sinf(angle.x);
			eye.z = -100 * cosf(angle.x);
		}
		else if (input_->PushKey(DIK_A)) {
			angle.x -= DirectX::XMConvertToRadians(1.0f);
			//angleラジアンだけy軸まわりに回転
			eye.x = -100 * sinf(angle.x);
			eye.z = -100 * cosf(angle.x);
		}
		else if (input_->PushKey(DIK_W)) {
			angle.y += DirectX::XMConvertToRadians(1.0f);
			//angleラジアンだけy軸まわりに回転
			eye.y = -100 * sinf(angle.y);
			eye.z = -100 * cosf(angle.y);
		}
		else if (input_->PushKey(DIK_S)) {
			angle.y -= DirectX::XMConvertToRadians(1.0f);
			//angleラジアンだけy軸まわりに回転
			eye.y = -100 * sinf(angle.y);
			eye.z = -100 * cosf(angle.y);
		}

		matView = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&eye), DirectX::XMLoadFloat3(&target), DirectX::XMLoadFloat3(&up));

	}


	if (Switch == 0) {

		if (input_->PushKey(DIK_O)) {
			if (Alpha < 1) {
				Alpha += colorSpeed;
			}
		}
		else if (input_->PushKey(DIK_L)) {
			if (Alpha > 0) {
				Alpha -= colorSpeed;
			}
		}
		if (input_->PushKey(DIK_Z)) {
			Switch = 1;
			Red = 1;
			Green = 1;
			Blue = 0;
		}

	}
	else {

		if (changeColor == 0) {

			Green -= colorSpeed;
			if (Green <= 0) {
				changeColor = 1;
				Green = 0;
			}
		}
		else if (changeColor == 1) {
			Blue += colorSpeed;
			if (Blue >= 1) {
				changeColor = 2;
				Blue = 1;
			}
		}
		else if (changeColor == 2) {
			Red -= colorSpeed;
			if (Red <= 0) {
				changeColor = 3;
				Red = 0;
			}
		}
		else if (changeColor == 3) {
			Green += colorSpeed;
			if (Green >= 1) {
				changeColor = 4;
				Green = 1;
			}
		}
		else if (changeColor == 4) {
			Blue -= colorSpeed;
			if (Blue <= 0) {
				changeColor = 5;
				Blue = 0;
			}
		}
		else if (changeColor == 5) {
			Red += colorSpeed;
			if (Red >= 1) {
				changeColor = 0;
				Red = 1;
			}
		}


		if (input_->PushKey(DIK_O)) {
			if (Alpha < 1) {
				Alpha += colorSpeed;
			}
		}
		else if (input_->PushKey(DIK_L)) {
			if (Alpha > 0) {
				Alpha -= colorSpeed;
			}
		}

		if (input_->PushKey(DIK_C)) {
			Switch = 0;
		}
	}
	constMap();
}

void Player::constMap()
{
	// 値を書き込むと自動的に転送される
	constMapMaterial->color = DirectX::XMFLOAT4(Red, Green, Blue, Alpha);              // RGBAで半透明の赤
}

Player::~Player()
{

}
