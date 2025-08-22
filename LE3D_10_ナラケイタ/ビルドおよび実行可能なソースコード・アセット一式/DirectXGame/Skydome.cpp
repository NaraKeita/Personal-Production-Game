#include "Skydome.h"

void Skydome::Initialize(Camera* camera) {
	model_ = Model::CreateFromOBJ("skydome"); // 天球
	camera_ = camera;
	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Skydome::Update() {
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Skydome::Draw() { 
	Model::PreDraw();
	model_->Draw(worldTransform_, *camera_);
	Model::PostDraw();
}
