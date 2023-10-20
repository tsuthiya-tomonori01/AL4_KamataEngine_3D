#pragma once

#include "WorldTransform.h"
#include "Model.h"

class Player {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

};