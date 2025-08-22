#pragma once  
#include <algorithm> // これがないとclampが使えない
#include "KamataEngine.h"

class DisplayNumbar {
public:
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	void SetNumber(int number) { number_ = std::clamp(number, 0, 99999); }
	void SetPoisonNumber(int number) { number_ = std::clamp(number, 0, 99999); }

public:
	// 色変更オブジェクト
	KamataEngine::ObjectColor objectColor_;
	// 色の数値
	KamataEngine::Vector4 color_;
	// 移動量
	KamataEngine::Vector3 velocity_;

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	uint32_t textureHandle_ = 0;
	
	KamataEngine::Sprite* sprite_[5] = {};
	
	KamataEngine::Vector2 charSize_; // 1文字分

	int frameCount_ = 0;
	int number_ = 0;
};
