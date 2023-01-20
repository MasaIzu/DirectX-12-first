#include "SphereCollider.h"
//#include "Object3d.h"

using namespace DirectX;

void SphereCollider::Update(DirectX::XMMATRIX* w)
{
	// ワールド行列から座標を抽出
	const XMMATRIX& matWorld = *w;

	// 球のメンバ変数を更新
	Sphere::center = matWorld.r[3] + offset;
	Sphere::radius = radius;
}
