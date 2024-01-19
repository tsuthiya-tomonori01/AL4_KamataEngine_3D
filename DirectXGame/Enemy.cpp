#include "Enemy.h"
#include "MathUtility.h"

#define _USE_MATH_DEFINES
#include <math.h>

void Enemy::Initialize(const std::vector<Model*>& models) {

	BaseCharacter::Initialize(models);

	worldTransformEnemy_.Initialize();
	worldTransformEnemy_Left_.Initialize();
	worldTransformEnemy_Right_.Initialize();

	worldTransformEnemy_.translation_.y = 0.1f;

	worldTransformEnemy_Left_.translation_.y = 1.0f;
	worldTransformEnemy_Left_.translation_.x = -1.0f;

	worldTransformEnemy_Right_.translation_.y = 1.0f;
	worldTransformEnemy_Right_.translation_.x = 1.0f;

	worldTransformEnemy_.parent_ = &worldTransform_;
	worldTransformEnemy_Left_.parent_ = &worldTransformEnemy_;
	worldTransformEnemy_Right_.parent_ = &worldTransformEnemy_;
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
	worldTransformEnemy_Left_.UpdateMatrix();
	worldTransformEnemy_Right_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {

	models_[0]->Draw(worldTransformEnemy_, viewProjection);
	models_[1]->Draw(worldTransformEnemy_Left_, viewProjection);
	models_[2]->Draw(worldTransformEnemy_Right_, viewProjection);
}
