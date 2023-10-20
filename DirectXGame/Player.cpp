#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_.y = 0.2f;
}

void Player::Update() { 

	worldTransform_.UpdateMatrix(); 

}

void Player::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}
