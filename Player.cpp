#include "Player.h"

void Player::Initialize(Model* model, const Vector3& position) {
	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	
	worldTransform_.translation_ = {2, 2, 20};
    
	input_ = Input::GetInstance();
	// NULLポインタをチェックする
	assert(model);
	model_ = model;

}

void Player::Update() {
	//worldTransform_.UpdateMatrix();

	worldTransform_.TransferMatrix();

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.7f;

	// 押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT) || input_->PushKey(DIK_A)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT) || input_->PushKey(DIK_D)) {
		move.x += kCharacterSpeed;
	}

	// 座標移動（ベクトルの加算）
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;

	// 移動限界座標
	const float kMoveLimitX = 35;
	const float kMoveLimitY = 19;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

}

void Player::Draw(Camera* camera) {
	model_->Draw(worldTransform_, *camera);
}