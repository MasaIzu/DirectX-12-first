#pragma once
#include "Vector3.h"

class Matrix4 {

public:

	float m[4][4];

	Matrix4();

	//�P�ʍs���ݒ�
	Matrix4 Identity();

	//�g��k���s��̐ݒ�
	Matrix4 Scale(const Vector3& s);

	//��]�s��̐ݒ�
	Matrix4 RotateX(float angle);
	Matrix4 RotateY(float angle);
	Matrix4 RotateZ(float angle);

	//���s�ړ��s��̐ݒ�
	Matrix4 Translate(const Vector3& t);

	//���W�ϊ�
	Vector3 Transform(const Vector3& v, const Matrix4& m);

	//������Z�q�I�[�o�[���[�h
	Elements& operator *=(Elements& m1);

	//2�����Z�q�I�[�o�[���[�h
	Matrix4 operator *(const Matrix4& m1, const Matrix4& m2);
	Vector3 operator *(const Vector3& v, const Matrix4& m);

};