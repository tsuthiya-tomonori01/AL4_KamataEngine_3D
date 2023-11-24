#pragma once

///
/// AL3サンプルプログラム用の数学ライブラリ。
/// MT3準拠で、KamataEngine内部の数学ライブラリと重複する。
///

#include "Matrix4x4.h"
#include "Vector3.h"

Vector3 Add(Vector3 v1, Vector3 v2);

Vector3 Subtract(Vector3& v1, Vector3& v2);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

Vector3 TransformNormal(const Vector3& vector, const Matrix4x4& matrix);

float Dot(Vector3 a, Vector3 b);
float Length(Vector3 a);
Vector3 Normalize(const Vector3& v);
    // アフィン変換行列の作成
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);
Vector3 Multiply(float a, Vector3 v2);
    // 代入演算子オーバーロード
Matrix4x4& operator*=(Matrix4x4& lhm, const Matrix4x4& rhm);

// 2項演算子オーバーロード
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Matrix4x4 MakeRotateZMatrix(float theta);
Matrix4x4 MakeRotateYMatrix(float theta);
Matrix4x4 MakeRotateXMatrix(float theta);
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
Matrix4x4 MakeIdentityMatrix();
Matrix4x4 MakeRotateMatrix(const Vector3& r);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);