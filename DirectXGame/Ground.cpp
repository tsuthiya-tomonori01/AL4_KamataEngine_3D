#include "Ground.h"
#include <cassert>

void Ground::Initialize(Model* model) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();

}

void Ground::Update() {

	worldTransform_.TransferMatrix();

}

void Ground::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

}
