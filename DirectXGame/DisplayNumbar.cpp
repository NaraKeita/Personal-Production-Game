#include "DisplayNumbar.h"

using namespace KamataEngine;

void DisplayNumbar::Initialize() {
	// ワールド変換データの初期化
	worldTransform_.Initialize();

	// 色の設定
	objectColor_.Initialize();
	color_ = {0, 0, 0, 0};

	textureHandle_ = TextureManager::Load("number.png");
	charSize_ = {32.0f, 64.0f}; // 1文字分のサイズ

	for (int i = 0; i < 5; i++) {
		// 横位置をずらして生成
		KamataEngine::Vector2 pos = {200.0f + charSize_.x * i, 5.0f};
		sprite_[i] = Sprite::Create(textureHandle_, pos);
		sprite_[i]->SetSize(charSize_);
		sprite_[i]->SetTextureRect({0, 0}, charSize_);
	}
	/*KamataEngine::Vector2 startpos = {100.0f + charSize_.x, 5.0f};
	sprite_[0] = Sprite::Create(textureHandle_, startpos);
	sprite_[0]->SetSize(charSize_);
	sprite_[0]->SetTextureRect({0, 0}, charSize_);*/
}

void DisplayNumbar::Update() {
	frameCount_++;
	numberStart_++;
    number_++;
	numberTimer_++;
	
	// 始まる前のカウント用
	if (numberStart_ > 9) {
		numberStart_ = 0;
	}
	// スコア用
	if (number_ > 99999) {
		number_ = 0; // 5桁でループ
	}
	// 時間制限用
	if (numberTimer_ > 99) {
		numberTimer_ = 0; // 5桁でループ
	}

    worldTransform_.UpdateMatrix();
}

void DisplayNumbar::Draw() {
	int startNum_ = numberStart_;
	int num = number_;
	int timeNum = numberTimer_;

	for (int i = 1; i >= 0; i--) {
		int digitStart = startNum_ % 10;
		startNum_ /= 10;
		sprite_[i]->SetTextureRect({charSize_.x * digitStart, 0}, charSize_);
		sprite_[i]->Draw();
	}

	// スコア用
	for (int i = 4; i >= 0; i--) {
		int digit = num % 10;
		num /= 10;
		// 数字ごとにテクスチャの表示範囲を変更
		sprite_[i]->SetTextureRect({charSize_.x * digit, 0}, charSize_);
		sprite_[i]->Draw();
	}

	// 時間制限用
	for (int i = 1; i >= 0; i--) {
		int digitTimer = timeNum % 10;
		timeNum /= 10;
		// 数字ごとにテクスチャの表示範囲を変更
		sprite_[i]->SetTextureRect({charSize_.x * digitTimer, 0}, charSize_);
		sprite_[i]->Draw();
	}
}
