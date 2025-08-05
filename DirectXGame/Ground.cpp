#include "Ground.h"

void Ground::Initialize(Camera* camera) {
	Vector3 startGroundPos = {0.0f, -1.0f, 0.0f};
	model_ = Model::CreateFromOBJ("ground"); // 地面
	// ワールド変換の初期化
	worldTransform_.Initialize();
	camera_ = camera;

}

void Ground::Update() {
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Ground::Draw() {
	Model::PreDraw();
	model_->Draw(worldTransform_, *camera_);
	Model::PostDraw();
}
