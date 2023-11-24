#include "Player.h"
#include <cassert>
#include "MathUtility.h"

#define _USE_MATH_DEFINES
#include <math.h>

void Player::Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm) {

	assert(modelBody,modelHead,modelL_arm,modelR_arm);

	modelBody_ = modelBody;
	modelHead_ = modelHead;
	modelL_arm_ = modelL_arm;
	modelR_arm_ = modelR_arm;

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

