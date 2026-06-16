#include "Apple.h"

void Apple::Initialize(Camera* camera) {
	InitializeBase("apple", "bgm/appleBite.mp3", camera);
}

void Apple::Update() {
	FallingObject::Update();
}

void Apple::Draw() {
	FallingObject::Draw();
}

void Apple::OnHitPlayer() {
	// スコア加算
	score_ += 1;
	if (onGetApple_) onGetApple_(score_);
}
