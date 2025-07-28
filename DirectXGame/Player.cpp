#include "Player.h"
#include <numbers>
#include "MathUtilityForText.h"

void Player::Initialize(Model* model, const Vector3& position) {
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	// NULLポインタをチェックする
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	worldTransform_.translation_ = position;
	// 速度の初期化 worldTransform_.translation　に　velocityX_を入れている
	velocityX_ = 0.0f; 

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	
	// ワールド変換の初期化
	worldTransform_.Initialize();
	
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

	if (velocityX_ == 0.0f) {
		worldTransform_.rotation_.y = std::numbers::pi_v<float> / 1.0f;
	}

	// 速度に応じて位置を更新
	worldTransform_.translation_.x += velocityX_;
}

void Player::Draw(Camera& camera) {    
    model_->Draw(worldTransform_, camera);  
}