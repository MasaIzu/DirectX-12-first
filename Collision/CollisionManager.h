#pragma once

#include<forward_list>

#include"CollisionPrimitive.h"
#include "RaycastHit.h"

#include<d3d12.h>
#include "QueryCallback.h"

class BaseCollider;

class CollisionManager {
public:
	static CollisionManager* GetInstance();

public://メンバ関数

	inline void AddCollider(BaseCollider* collider) {
		colliders.push_front(collider);
	}

	inline void RemoveCollider(BaseCollider* collide) {
		colliders.remove(collide);
	}

	void CheckAllCollisions(DirectX::XMMATRIX* worldPos);

	bool Raycast(const Ray& ray, RaycastHit* hitInfo, DirectX::XMMATRIX* worldPos, float maxDistance = D3D12_FLOAT32_MAX);


	//レイキャストオーバーロード
	bool Raycast(const Ray& ray, unsigned short attribute, DirectX::XMMATRIX* worldPos, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);

	void QuerySphere(const Sphere& sphere, QueryCallback* callback, DirectX::XMMATRIX* worldPos, unsigned short attribute = (unsigned short)0xffffffff);

private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator = (const CollisionManager&) = delete;

	//コライダーのリスト
	std::forward_list<BaseCollider*> colliders;

};