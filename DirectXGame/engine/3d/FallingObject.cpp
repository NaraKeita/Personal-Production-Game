#include "FallingObject.h"
#include "../calculation/Collision.h"
#include <random>

void FallingObject::InitializeBase(const std::string& modelName, const std::string& sePath, Camera* camera) {
	audio_ = Audio::GetInstance();
	model_ = Model::CreateFromOBJ(modelName.c_str());
	if (!sePath.empty()) {
		seHandle_ = audio_->LoadWave(sePath.c_str());
	}
	worldTransform_.Initialize();
	camera_ = camera;
}

void FallingObject::ResetPosition() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> dist(-8.0f, 8.0f);
	static std::uniform_real_distribution<float> speedDist(0.05f, 0.2f);
	float randomX = dist(gen);
	worldTransform_.translation_ = {randomX, 10.0f, -20.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	fallSpeed_ = speedDist(gen);
}

void FallingObject::Update() {
	if (!isActive_) return;
	worldTransform_.translation_.y -= fallSpeed_;
	worldTransform_.rotation_.z += 0.1f;

	constexpr float groundY = -5.0f;
	bool isBelowGround = (worldTransform_.translation_.y < groundY);

	if (player_) {
		bool wasHit = isHitPlayer_;
		isHitPlayer_ = CheckCollision(worldTransform_.translation_, radius_, player_->GetPosition(), player_->GetRadius());
		if (!wasHit && isHitPlayer_) {
			// 効果音再生（派生で追加処理をする）
			if (seHandle_) audio_->PlayWave(seHandle_);
			OnHitPlayer();
		}
	}

	if (isBelowGround || isHitPlayer_) {
		ResetPosition();
	}

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void FallingObject::Draw() {
	if (!isActive_) return;
	Model::PreDraw();
	if (model_ && camera_) model_->Draw(worldTransform_, *camera_);
	Model::PostDraw();
}
