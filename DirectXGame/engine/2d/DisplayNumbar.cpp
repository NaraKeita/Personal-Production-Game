#include "DisplayNumbar.h"
#include <iostream>

using namespace KamataEngine;

void DisplayNumbar::Initialize() {
	//// ワールド変換データの初期化
	// worldTransform_.Initialize();

	textureHandle_ = TextureManager::Load("number.png");
	charSize_ = {32.0f, 64.0f}; // 1文字分のサイズ

	for (int i = 0; i < 5; i++) {
		// 横位置をずらして生成
		KamataEngine::Vector2 pos = {200.0f + charSize_.x * i, 5.0f};
		sprite_[i] = Sprite::Create(textureHandle_, pos);
		if (!sprite_[i]) {
			std::cerr << "DisplayNumbar: Sprite::Create failed for index " << i << std::endl;
			continue;
		}
		sprite_[i]->SetSize(charSize_);
		sprite_[i]->SetTextureRect({0, 0}, charSize_);
	}

	if (textureHandle_ == 0) {
		std::cerr << "DisplayNumbar: TextureManager::Load returned 0 for 'number.png'" << std::endl;
	}
}

void DisplayNumbar::Update() {
	frameCount_++;
	number_++;
	numberTimer_++;

	// スコア用
	if (number_ > 99999) {
		number_ = 0; // 5桁でループ
	}
	// 時間制限用
	if (numberTimer_ > 99) {
		numberTimer_ = 0; // 5桁でループ
	}

	//ImGui::Begin("timer");
	//ImGui::DragInt("numberTimer_", &numberTimer_);
	//ImGui::End();

	// worldTransform_.UpdateMatrix();
}

void DisplayNumbar::Draw() {
	Sprite::PreDraw();
	int num = number_;
	int timeNum = numberTimer_;

	// スコア用
	for (int i = 4; i >= 0; i--) {
		int digit = num % 10;
		num /= 10;
		// 数字ごとにテクスチャの表示範囲を変更
		if (sprite_[i]) {
		sprite_[i]->SetTextureRect({charSize_.x * digit, 0}, charSize_);
		sprite_[i]->Draw();
	}
	}

	// 時間制限用
	for (int i = 1; i >= 0; i--) {
		int digitTimer = timeNum % 10;
		timeNum /= 10;
		// 数字ごとにテクスチャの表示範囲を変更
		if (sprite_[i]) {
		sprite_[i]->SetTextureRect({charSize_.x * digitTimer, 0}, charSize_);
		sprite_[i]->Draw();
	}
}
	Sprite::PostDraw();
}
