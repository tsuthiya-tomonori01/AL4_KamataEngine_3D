#include "Player.h"
#include <cassert>
#include "MathUtility.h"

#define _USE_MATH_DEFINES
#include <math.h>

void Player::Initialize(const std::vector<Model*>& models) {

	BaseCharacter::Initialize(models);

	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
}

void Player::Update() { 

	BaseCharacter::Update();

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
	}
}

void Player::Draw(const ViewProjection& viewProjection) {

	modelBody_->Draw(worldTransformBody_,viewProjection);

	modelHead_->Draw(worldTransformHead_, viewProjection);

	modelL_arm_->Draw(worldTransformL_arm_, viewProjection);

	modelR_arm_->Draw(worldTransformR_arm_, viewProjection);

}

void Player::InitializeFloatingGimmick() {

	floatingParameter_ = 0.0f;

}

void Player::UpdateFloatingGimmick() { 
	
	//浮遊移動のサイクル
	const uint16_t A_frame = 120;

	//1フレームでのパラメーター加算値
	const float Step = 2.0f * M_PI / A_frame;

	//パラメーターを1ステップ分加算
	floatingParameter_ += Step;

	//２πを超えたら０に戻す
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * M_PI);

	//
	const float Width_F = 0.5f;

	//
	worldTransform_.translation_.y = std::sin(floatingParameter_) * Width_F;

}

