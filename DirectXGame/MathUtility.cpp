#include "MathUtility.h"
#include <cassert>
#include <cmath>

Matrix4x4 MakeIdentityMatrix() {
	static const Matrix4x4 result{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	                              0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	return result;
}

Matrix4x4 MakeRotateMatrix(const Vector3& r) { 

	Matrix4x4 result = {}; 

	Matrix4x4 rotateX = MakeRotateXMatrix(r.x);
	Matrix4x4 rotateY = MakeRotateYMatrix(r.y);
	Matrix4x4 rotateZ = MakeRotateZMatrix(r.z);

	result = Multiply(rotateX, Multiply(rotateY, rotateZ));

	return result;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) { 

	Matrix4x4 Sub = {};

	Sub.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	Sub.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	Sub.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	Sub.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];


	Sub.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	Sub.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	Sub.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	Sub.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];


	Sub.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][2];
	Sub.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	Sub.m[2][2] = m1.m[0][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	Sub.m[2][3] = m1.m[0][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];


	Sub.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	Sub.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	Sub.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	Sub.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];


	return Sub;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale) {

	Matrix4x4 result{scale.x, 0.0f, 0.0f,    0.0f, 0.0f, scale.y, 0.0f, 0.0f,
	                 0.0f,    0.0f, scale.z, 0.0f, 0.0f, 0.0f,    0.0f, 1.0f};

	return result;
}

Matrix4x4 MakeRotateXMatrix(float theta) {
	float sin = std::sin(theta);
	float cos = std::cos(theta);

	Matrix4x4 result{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cos,  sin,  0.0f,
	                 0.0f, -sin, cos,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	return result;
}

Matrix4x4 MakeRotateYMatrix(float theta) {
	float sin = std::sin(theta);
	float cos = std::cos(theta);

	Matrix4x4 result{cos, 0.0f, -sin, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	                 sin, 0.0f, cos,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	return result;
}

Matrix4x4 MakeRotateZMatrix(float theta) {
	float sin = std::sin(theta);
	float cos = std::cos(theta);

	Matrix4x4 result{cos,  sin,  0.0f, 0.0f, -sin, cos,  0.0f, 0.0f,
	                 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	return result;
}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result{1.0f, 0.0f, 0.0f, 0.0f, 0.0f,        1.0f,        0.0f,        0.0f,
	                 0.0f, 0.0f, 1.0f, 0.0f, translate.x, translate.y, translate.z, 1.0f};

	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate) {

	// スケーリング行列の作成
	Matrix4x4 matScale = MakeScaleMatrix(scale);

	Matrix4x4 matRotX = MakeRotateXMatrix(rot.x);
	Matrix4x4 matRotY = MakeRotateYMatrix(rot.y);
	Matrix4x4 matRotZ = MakeRotateZMatrix(rot.z);
	// 回転行列の合成
	Matrix4x4 matRot = matRotZ * matRotX * matRotY;

	// 平行移動行列の作成
	Matrix4x4 matTrans = MakeTranslateMatrix(translate);

	// スケーリング、回転、平行移動の合成
	Matrix4x4 matTransform = matScale * matRot * matTrans;

	return matTransform;
}

Vector3 Add(Vector3 v1, Vector3 v2) {
	Vector3 Add = {0, 0, 0};
	Add.x = v1.x + v2.x;
	Add.y = v1.y + v2.y;
	Add.z = v1.z + v2.z;
	return Add;
}

Vector3 Subtract(Vector3& v1, Vector3& v2) {
	Vector3 Sub = {0, 0, 0};
	Sub.x = v1.x - v2.x;
	Sub.y = v1.y - v2.y;
	Sub.z = v1.z - v2.z;
	return Sub;
}

Vector3 Multiply(float a, Vector3 v2) {
	Vector3 multi = {0, 0, 0};
	multi.x = a * v2.x;
	multi.y = a * v2.y;
	multi.z = a * v2.z;
	return multi;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 Trans;

	Trans.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] +
	          1.0f * matrix.m[3][0];
	Trans.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] +
	          1.0f * matrix.m[3][1];
	Trans.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] +
	          1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] +
	          1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	Trans.x /= w;
	Trans.y /= w;
	Trans.z /= w;

	return Trans;
};

Vector3 TransformNormal(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 TransN;

	TransN.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0];
	TransN.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1];
	TransN.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2];
	         

	return TransN;
};

Matrix4x4& operator*=(Matrix4x4& lhm, const Matrix4x4& rhm) {
	Matrix4x4 result{};

	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			for (size_t k = 0; k < 4; k++) {
				result.m[i][j] += lhm.m[i][k] * rhm.m[k][j];
			}
		}
	}
	lhm = result;
	return lhm;
}

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = m1;

	return result *= m2;
}

float Dot(Vector3 a, Vector3 b) {
	float r = 0.0f;
	r = a.x * b.x + a.y * b.y + a.z * b.z;
	return r;
}

float Length(Vector3 a) {
	float r = 0.f;
	r = sqrtf(Dot(a, a));
	return r;
}


Vector3 Normalize(const Vector3& v) { 
	float len = Length(v);
	Vector3 result = v;
	if (len != 0) {
		result.x /= len;
		result.y /= len;
		result.z /= len;
		
	}
	return result;
}
