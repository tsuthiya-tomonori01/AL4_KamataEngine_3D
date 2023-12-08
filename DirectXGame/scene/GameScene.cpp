#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete debugCamera_; 
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance(); 
	
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	viewProjection_.Initialize();
	viewProjection_.farZ = 1600.0f;
	viewProjection_.UpdateMatrix();

	debugCamera_ = new DebugCamera(1280, 720);
	//debugCamera_->SetFarZ(1600.0f);

	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm.reset(Model::CreateFromOBJ("float_r_arm", true));

	player_ = std::make_unique<Player>();
	player_->Initialize(modelFighterBody_.get(),modelFighterHead_.get(),modelFighterL_arm.get(),modelFighterR_arm.get());

	modelSkydome_.reset(Model::CreateFromOBJ("skydome", true));

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(modelSkydome_.get());

	modelGround_.reset(Model::CreateFromOBJ("ground", true));

	ground_ = std::make_unique<Ground>();
	ground_->Initialize(modelGround_.get());

	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransform());

	player_->SetViewProjection(&followCamera_->GetViewProjection());

}

void GameScene::Update() {

	player_->Update();
	skydome_->Update();
	ground_->Update();

	#ifdef _DEBUG

	  if (input_->TriggerKey(DIK_Q)) 
	  {
		//isDebugCameraActive_;
	  }

    #endif // 

    if (isDebugCameraActive_) {
		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView; 
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		viewProjection_.UpdateMatrix();
	}
	else 
	{
		followCamera_->Update();

		viewProjection_.matView = followCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();
	}

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
