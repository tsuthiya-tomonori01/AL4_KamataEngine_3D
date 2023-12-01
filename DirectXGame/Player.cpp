#include "Player.h"
#include <cassert>
#include "MathUtility.h"

#define _USE_MATH_DEFINES
#include <math.h>

void Player::Initialize(Model* model) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_.y = 0.2f;
}

void Player::Update() { 

	XINPUT_STATE joyState;
	
	if (Input::GetInstance()->GetJoystickState(0,joyState)) {

		const float speed = 0.3f;

		velocity_ = {
			(float)joyState.Gamepad.sThumbLX / SHRT_MAX,
			0.0f,
			(float)joyState.Gamepad.sThumbLY / SHRT_MAX
};

		velocity_ = Multiply(speed, Normalize(velocity_));

		Matrix4x4 rotate = MakeRotateMatrix(viewProjection_->rotation_);

		// ここでカメラの角度分進ベクトルを回転させてる
		velocity_ = TransformNormal(velocity_, rotate);

		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

		worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
		//worldTransform_.rotation_.x = std::atan2(-velocity_.y, velocity_.z);
	}

	worldTransform_.UpdateMatrix(); 

}

void Player::Draw(ViewProjection& viewProjection) { 
	
	model_->Draw(worldTransform_, viewProjection); 
}

