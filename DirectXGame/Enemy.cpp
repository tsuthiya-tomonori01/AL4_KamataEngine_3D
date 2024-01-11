#include "Enemy.h"
#include "MathUtility.h"

#define _USE_MATH_DEFINES
#include <math.h>

void Enemy::Initialize(const std::vector<Model*>& models) {

	BaseCharacter::Initialize(models);

	worldTransformEnemy_.Initialize();
}

void Enemy::Update() {

	BaseCharacter::Update();

	const float speed = 0.1f;

	worldTransformEnemy_.rotation_.y += 0.01f;

	Vector3 move = {0.0f, 0.0f, speed};

	Matrix4x4 matRotY = MakeRotateYMatrix(worldTransformEnemy_.rotation_.y);

	move = TransformNormal(move, matRotY);

	worldTransformEnemy_.translation_ = Add(move,worldTransformEnemy_.translation_);

	worldTransformEnemy_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {

	models_[0]->Draw(worldTransformEnemy_, viewProjection);

}
