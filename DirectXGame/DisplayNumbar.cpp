#include "DisplayNumbar.h"

using namespace KamataEngine;

void DisplayNumbar::Initialize() {
	// ワールド変換データの初期化
	worldTransform_.Initialize();

	// 色の設定
	objectColor_.Initialize();
	color_ = {0, 0, 0, 0};

	textureHandle_ = TextureManager::Load("number.png");
	charSize_ = {32.0f, 64.0f}; // 1文字分のサイズ（例）

	for (int i = 0; i < 5; i++) {
		// 横位置をずらして生成
		KamataEngine::Vector2 pos = {100.0f + charSize_.x * i, 5.0f};
		sprite_[i] = Sprite::Create(textureHandle_, pos);
		sprite_[i]->SetSize(charSize_);
		sprite_[i]->SetTextureRect({0, 0}, charSize_);
	}
}

void DisplayNumbar::Update() {
	frameCount_++;
    number_++;

	if (number_ > 99999) {
		number_ = 0; // 5桁でループ
	}
    
    worldTransform_.UpdateMatrix();
}

void DisplayNumbar::Draw() {
	int num = number_;
	for (int i = 4; i >= 0; i--) {
		int digit = num % 10;
		num /= 10;
		// 数字ごとにテクスチャの表示範囲を変更
		sprite_[i]->SetTextureRect({charSize_.x * digit, 0}, charSize_);
		sprite_[i]->Draw();
	}
}
