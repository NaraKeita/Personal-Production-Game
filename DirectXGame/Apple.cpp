#include "Apple.h"
#include "Collision.h"
#include <random>

void Apple::Initialize(Camera* camera) {
	audio_ = Audio::GetInstance();
	model_ = Model::CreateFromOBJ("apple");
	// ワールド変換の初期化
	worldTransform_.Initialize();
	camera_ = camera;
}

void Apple::Update() {
	if (!isActive_) return;
	worldTransform_.translation_.y -= 0.1f;
	worldTransform_.rotation_.z += 0.1f;

	// 地面のY座標
	constexpr float groundY = -5.0f;

	// 初期位置
	auto resetApple = [this]() {
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_real_distribution<float> dist(-8.0f, 8.0f);
		float randomX = dist(gen);
		worldTransform_.translation_ = {randomX, 20.0f, -20.0f};
		worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	};

	// 地面より下 or プレイヤーと当たったら初期位置に戻す
	bool isBelowGround = (worldTransform_.translation_.y < groundY);
   
	if (player_) {
		// if (IsActive() && CheckCollision(player_->GetPosition(), player_->GetRadius(), GetPosition(), GetRadius())) {
		//	SetActive(false); // リンゴを消す
		//	score_ += 10; // スコア加算（例: 10点）
		//	// 効果音再生
		//	audio_->PlayWave(seAppleGet_);
		//}
		isHitPlayer_ = CheckCollision(worldTransform_.translation_, radius_, player_->GetPosition(), player_->GetRadius());
		//SetActive(false);
		score_ += 10; // スコア加算（例: 10点）
		//効果音再生
		audio_->PlayWave(seAppleGet_);   
	}

	if (isBelowGround || isHitPlayer_) {
		resetApple();
	}

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Apple::Draw() {
	if (!isActive_) return;
	Model::PreDraw();
	model_->Draw(worldTransform_, *camera_);
	Model::PostDraw();
}
