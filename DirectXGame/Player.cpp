#include "Player.h"

void Player::Initialize(Model* model, const Vector3& position) {
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	// NULLポインタをチェックする
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	worldTransform_.translation_ = position;
	
	// ワールド変換の初期化
	worldTransform_.Initialize();
	
}

void Player::Update() {
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.7f;

	// 押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT) || input_->PushKey(DIK_A)) {
		worldTransform_.translation_.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT) || input_->PushKey(DIK_D)) {
		worldTransform_.translation_.x += kCharacterSpeed;
	}

}

void Player::Draw(Camera& camera) {    
    model_->Draw(worldTransform_, camera);  
}