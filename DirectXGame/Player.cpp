#include "Player.h"

void Player::Initialize(Model* model, const Vector3& position) {
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	// NULLポインタをチェックする
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	worldTransform_.translation_ = position;
	// 速度の初期化
	velocityX_ = 0.0f; 
	
	// ワールド変換の初期化
	worldTransform_.Initialize();
	
}

void Player::Update() {  
	worldTransform_.UpdateMatrix();  
	worldTransform_.TransferMatrix();  

	// キャラクターの移動速さ  
	static const float kCharacterSpeed = 0.5f;  
	static const float kFriction = 0.01f;

	// 入力による加速
	if (input_->PushKey(DIK_LEFT) || input_->PushKey(DIK_A)) {
		velocityX_ = -kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT) || input_->PushKey(DIK_D)) {
		velocityX_ = kCharacterSpeed;
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
	// 速度に応じて位置を更新
	worldTransform_.translation_.x += velocityX_;
}

void Player::Draw(Camera& camera) {    
    model_->Draw(worldTransform_, camera);  
}