#include "PoisonApple.h"

void PoisonApple::Initialize(Camera* camera) {
	InitializeBase("poison", "bgm/voiceOfHeaven.mp3", camera);
}

void PoisonApple::Update() {
	// 速度差をつけたい場合は fallSpeed_ を調整する
	FallingObject::Update();
}

void PoisonApple::Draw() {
	FallingObject::Draw();
}

void PoisonApple::OnHitPlayer() {
	// プレイヤーのスピードを遅くする
	if (player_) player_->SetSpeed(0.05f);
}
