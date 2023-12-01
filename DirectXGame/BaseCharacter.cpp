#include "BaseCharacter.h"

void BaseCharacter::Initialize(const std::vector<Model*>& model) {

	model_ = model;
	worldTransform_.Initialize();
}

void BaseCharacter::Update() { 
	
	worldTransform_.UpdateMatrix(); 
}

void BaseCharacter::Draw(const std::vector<Model*>& model) {

	for (Model* model : model_) {

		model->Draw(worldTransform_, viewProjection_);
	}

}
