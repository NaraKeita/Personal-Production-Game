#include "Apple.h"
#include "../calculation/Collision.h"
#include <random>

void Apple::Initialize(Camera* camera) {
	audio_ = Audio::GetInstance();
	model_ = Model::CreateFromOBJ("apple");
	seAppleGet_ = audio_->LoadWave("bgm/appleBite.mp3");
	// ワールド変換の初期化
	worldTransform_.Initialize();
	camera_ = camera;

}

void Apple::Update() {
	if (!isActive_) return;
	worldTransform_.translation_.y -= fallSpeed_;
	worldTransform_.rotation_.z += 0.1f;

	// 地面のY座標
	constexpr float groundY = -5.0f;

	// 初期位置
	auto resetApple = [this]() {
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_real_distribution<float> dist(-8.0f, 8.0f);      // リンゴが落ちてくる範囲
		static std::uniform_real_distribution<float> speedDist(0.05f, 0.2f); // スピード範囲
		float randomX = dist(gen);
		worldTransform_.translation_ = {randomX, 10.0f, -20.0f};
		worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
		fallSpeed_ = speedDist(gen); // リセット時に初期速度に戻す
	};

	// 地面より下 or プレイヤーと当たったら初期位置に戻す
	bool isBelowGround = (worldTransform_.translation_.y < groundY);
   
	if (player_) {
		bool wasHit = isHitPlayer_; // これがないと音が連続で鳴り続ける
		isHitPlayer_ = CheckCollision(worldTransform_.translation_, radius_, player_->GetPosition(), player_->GetRadius());
		if (!wasHit && isHitPlayer_) {
			score_ += 1; // スコア加算
			if (onGetApple_) {
				onGetApple_(score_); // ここで通知
			}
			// 効果音再生
			audio_->PlayWave(seAppleGet_);
		}
	}

	// 一定のところまで落ちるかプレイヤーに当たったら元の位置に戻る
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
