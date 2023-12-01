#pragma once

#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Player {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

private:
	 
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	const ViewProjection* viewProjection_ = nullptr; 

	Vector3 velocity_ = {};

	float floatingParameter_ = 0.0f;
};