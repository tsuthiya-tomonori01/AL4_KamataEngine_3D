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

	worldTransformHammer_.Initialize();

	worldTransformBody_.translation_.y = 0.0f;
	worldTransformHead_.translation_.y = 1.5f;

	worldTransformL_arm_.translation_.y = 1.25f;
	worldTransformL_arm_.translation_.x = -0.5f;

	worldTransformR_arm_.translation_.y = 1.25f;
	worldTransformR_arm_.translation_.x = 0.5f;

	worldTransformHammer_.translation_.x = -0.5f;

	InitializeFloatingGimmick();

	worldTransformBody_.parent_ = &worldTransform_;
	worldTransformHead_.parent_ = &worldTransformBody_;
	worldTransformL_arm_.parent_ = &worldTransformBody_;
	worldTransformR_arm_.parent_ = &worldTransformBody_;

	worldTransformHammer_.parent_ = &worldTransformL_arm_;
	worldTransformHammer_.parent_ = &worldTransformR_arm_;
}

void Player::Update() { 

	if (behaviorRequest_) {

		behavior_ = behaviorRequest_.value();

		switch (behavior_) {
		case Behavior::kRoot:
		default:
			BehaviorRootInitialize();
			break;
		case Behavior::kAttack:
			BehaviorAttackInitialize();
			break;
		}

		behaviorRequest_ = std::nullopt;
	}
	switch (behavior_) {
	case Behavior::kRoot:
	default:
		BehaviorRootUpdate();
		break;
	case Behavior::kAttack:
		BehaviorAttackUpdate();
		break;
	}

	BaseCharacter::Update();

	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
	worldTransformHammer_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) {

	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_arm_, viewProjection);
	models_[3]->Draw(worldTransformR_arm_, viewProjection);

	if (behavior_ == Behavior::kAttack) {

		models_[4]->Draw(worldTransformHammer_, viewProjection);
	}
}

void Player::InitializeFloatingGimmick() {

	floatingParameter_ = 0.0f;
}

void Player::UpdateFloatingGimmick() { 
	
	//浮遊移動のサイクル
	const uint16_t A_frame = 120;

	//1フレームでのパラメーター加算値
	const float Step = (float)(2.0f * M_PI / A_frame);

	//パラメーターを1ステップ分加算
	floatingParameter_ += Step;

	//２πを超えたら０に戻す
	floatingParameter_ = (float)std::fmod(floatingParameter_, 2.0f * M_PI);

	//
	const float Width_F = 0.3f;

	//
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * Width_F;

}

void Player::BehaviorRootInitialize() {}

void Player::BehaviorRootUpdate() {

	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		const float speed = 0.3f;

		velocity_ = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX};

		velocity_ = Multiply(speed, Normalize(velocity_));

		Matrix4x4 rotate = MakeRotateMatrix(viewProjection_->rotation_);

		// ここでカメラの角度分進ベクトルを回転させてる
		velocity_ = TransformNormal(velocity_, rotate);

		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

		worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
	}

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_X) {

			behaviorRequest_ = Behavior::kAttack;
		}
	}

	UpdateFloatingGimmick();
}

void Player::BehaviorAttackInitialize() {

	if (behavior_ == Behavior::kAttack) {

	}
}

void Player::BehaviorAttackUpdate() {

	if (behavior_ == Behavior::kAttack) {



	}
}

