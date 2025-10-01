#include "PoisonApple.h"
#include "Collision.h"
#include <random>

void PoisonApple::Initialize(Camera* camera) {
	audio_ = Audio::GetInstance();
	model_ = Model::CreateFromOBJ("poison");
	seAppleGet_ = audio_->LoadWave("mokugyo.wav");
	// ワールド変換の初期化
	worldTransform_.Initialize();
	camera_ = camera;
}

void PoisonApple::Update() {
	if (!isActive_)
		return;
	worldTransform_.translation_.y -= 0.09f;
	worldTransform_.rotation_.z += 0.1f;

	// 地面のY座標
	constexpr float groundY = -5.0f;

	// 初期位置
	auto resetApple = [this]() {
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_real_distribution<float> dist(-8.0f, 8.0f);
		float randomX = dist(gen);
		worldTransform_.translation_ = {randomX, 10.0f, -20.0f};
		worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
		fallSpeed_ = 0.1f; // リセット時に初期速度に戻す
	};

	// 地面より下 or プレイヤーと当たったら初期位置に戻す
	bool isBelowGround = (worldTransform_.translation_.y < groundY);

	if (player_) {
		bool wasHit = isHitPlayer_; // これがないと音が連続で鳴り続ける
		isHitPlayer_ = CheckCollision(worldTransform_.translation_, radius_, player_->GetPosition(), player_->GetRadius());
		if (!wasHit && isHitPlayer_) {
			score_ -= 1; // スコア加算
			// プレイヤーのスピードを遅くする
			Player* mutablePlayer = const_cast<Player*>(player_);
			//mutablePlayer->SetSpeed(0.1f); // 例: 通常0.3f→0.1fに減速
			mutablePlayer->AddPoisonHit(); // 毒リンゴヒット回数を加算＆スピード減少
    
			// 効果音再生
			audio_->PlayWave(seAppleGet_);
		}
	}

	if (isBelowGround || isHitPlayer_) {
		resetApple();
	}

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void PoisonApple::Draw() {
	if (!isActive_)
		return;
	Model::PreDraw();
	model_->Draw(worldTransform_, *camera_);
	Model::PostDraw();
}
