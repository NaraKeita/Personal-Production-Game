#include "Tree.h"

void Tree::Initialize(Camera* camera) {
	worldTransform_.Initialize();
	camera_ = camera;
	model_ = Model::CreateFromOBJ("tree");
	// 揺れ制御用変数の初期化
	swingTime_ = 0.0f;
	swingActive_ = true;
	swingWaitTimer_ = 0.0f;
}

void Tree::Update() {
	// 揺れパラメータ
	const float swingAmplitude = 0.06f; // 揺れの角度
	const float swingSpeed = 10.0f;		// 揺れる速さ
	const float swingDuration = 5.0f;	// 揺れる時間（秒）
	const float swingWait = 5.0f;		// 揺れが止まっている時間 (秒)

	if (swingActive_) {
		// 揺れ中
		swingTime_ += 1.0f / 60.0f;
		float swingValue = std::sin(swingTime_ * swingSpeed) * swingAmplitude;
		worldTransform_.rotation_.y = swingValue;
		if (swingTime_ > swingDuration) {
			swingActive_ = false;
			swingWaitTimer_ = 0.0f;
			// 揺れを止める
			worldTransform_.rotation_.y = 0.0f;
		}
	} else {
		// 待機中
		swingWaitTimer_ += 1.0f / 60.0f;
		if (swingWaitTimer_ > swingWait) {
			swingActive_ = true;
			swingTime_ = 0.0f;
		}
	}

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Tree::Draw() {
	Model::PreDraw();
	model_->Draw(worldTransform_, *camera_);
	Model::PostDraw();
}
