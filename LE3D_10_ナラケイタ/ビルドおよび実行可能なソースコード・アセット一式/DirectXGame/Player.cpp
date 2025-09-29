#include "Player.h"
#include <numbers>
#include "MathUtilityForText.h" // 旋回をやりたいから入れている

void Player::Initialize(Camera* camera) {
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	model_ = Model::CreateFromOBJ("player",true);

	// 速度の初期化 worldTransform_.translation　に　velocityX_を入れている
	velocityX_ = 0.0f; 

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	// 位置
	worldTransform_.translation_ = {0.0f, 0.0f, -20.0f};
	
	// ワールド変換の初期化
	worldTransform_.Initialize();
	camera_ = camera;
}

void Player::Update() {  
	worldTransform_.UpdateMatrix();  
	worldTransform_.TransferMatrix();  
	
	// 入力による加速
	if (input_->PushKey(DIK_LEFT) || input_->PushKey(DIK_A)) {
		velocityX_ = -kCharacterSpeed;
		if (lrDirection_ != LRDirection::kLeft) {
			lrDirection_ = LRDirection::kLeft;
			turnFirstRotationY_ = worldTransform_.rotation_.y;
			turnTimer_ = kTimeTurn;
		}
	} else if (input_->PushKey(DIK_RIGHT) || input_->PushKey(DIK_D)) {
		velocityX_ = kCharacterSpeed;
		// 左移動中の右入力
		if (lrDirection_ != LRDirection::kRight) {
			lrDirection_ = LRDirection::kRight;
			turnFirstRotationY_ = worldTransform_.rotation_.y;
			turnTimer_ = kTimeTurn;
		}
	} else {
		// キー入力がない場合は徐々に減速
		if (velocityX_ > 0.0f) {
			velocityX_ -= kFriction;
			if (velocityX_ < 0.0f)
				velocityX_ = 0.0f;
		} else if (velocityX_ < 0.0f) {
			velocityX_ += kFriction;
			if (velocityX_ > 0.0f)
				velocityX_ = 0.0f;
		}
	}

	// 旋回制御
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1.0f / 60.0f; // 旋回タイマーを1/60秒分カウントダウンする
		                            // 左右の自キャラ角度テーブル
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};

		// 状況に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		// 自キャラの角度を設定する
		worldTransform_.rotation_.y = EaseInOut(destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTurn);

		MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	}

	// 速度に応じて位置を更新
	worldTransform_.translation_.x += velocityX_;
}

void Player::Draw() {
	Model::PreDraw();
    model_->Draw(worldTransform_,*camera_);
	Model::PostDraw();
}