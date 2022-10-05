#pragma once
#include "Vector3.h"

class Matrix4 {

public:

	float m[4][4];

	Matrix4();

	//単位行列を設定
	Matrix4 Identity();

	//拡大縮小行列の設定
	Matrix4 Scale(const Vector3& s);

	//回転行列の設定
	Matrix4 RotateX(float angle);
	Matrix4 RotateY(float angle);
	Matrix4 RotateZ(float angle);

	//平行移動行列の設定
	Matrix4 Translate(const Vector3& t);

	//座標変換
	Vector3 Transform(const Vector3& v, const Matrix4& m);

	//代入演算子オーバーロード
	Elements& operator *=(Elements& m1);

	//2項演算子オーバーロード
	Matrix4 operator *(const Matrix4& m1, const Matrix4& m2);
	Vector3 operator *(const Vector3& v, const Matrix4& m);

};