#pragma once

#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

#include "BaseCharacter.h"

class Player : public BaseCharacter {

public:

	void Initialize(const std::vector<Model*>& model) override;

	void Update();

	void Draw(const ViewProjection& viewProjection) override;

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	void SetViewProjection(const ViewProjection* viewProjection) {

		viewProjection_ = viewProjection;
	}

	////浮遊ギミック初期化
	//void InitializeFloatingGimmick();

	////浮遊ギミックに更新
	//void UpdateFloatingGimmick();

private:
	 
	WorldTransform worldTransform_;

	/*WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	Model* modelBody_ = nullptr;
	Model* modelHead_ = nullptr;
	Model* modelL_arm_ = nullptr;
	Model* modelR_arm_ = nullptr;*/

	Model* model_ = nullptr;

	const ViewProjection* viewProjection_ = nullptr; 

	Vector3 velocity_ = {};

	float floatingParameter_ = 0.0f;
};