#pragma once

#include "Matrix4.h"
#include "Vector3.h"
#include "WorldTransform.h"
#include "WinApp.h"

namespace AffinTrans {

	Matrix4 Initialize();
	Matrix4 Scale(Vector3 scale);
	Matrix4 Rotation(Vector3 rotation, int X_1_Y_2_Z_3_XYZ_6);
	Vector3 Vector3Rotation(Matrix4 rotation);
	Matrix4 Translation(Vector3 move);
	Vector3 DebugMove(Matrix4 Move);
	//ベクトルの正規化(いっぺんにやる)
	Vector3 vector3Normalize(const Vector3& v);
	//ベクトルと行列の掛け算(出力Vector3)
	Vector3 MatVector(Matrix4 matrix4, Vector3 vector3);
	Vector3 MulVector3(Vector3 vector3, Vector3 s);

	const Vector3 SubVec(Vector3 v, Vector3 v2);

	Vector3 GetWorldTransform(Matrix4 matrix4);
	const Vector3 AddVector3(const Vector3 v1, const Vector3 v2);
	Vector3 DivVecMat(const Vector3& vector3, const Matrix4& matrix4);

	Matrix4 setViewportMat(WinApp* window, const Vector3& v);
	Matrix4 MatrixInverse(Matrix4 pOut);

	Matrix4 LookAtLH(Vector3 eye, Vector3 target, Vector3 up);
	Matrix4 PerspectiveFovLH(float fovAngleY, float  aspectRatio, float  nearZ, float farZ);


}; // namespace AffinTrans