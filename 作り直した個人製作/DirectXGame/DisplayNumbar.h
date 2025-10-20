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

	void SetStartNumber(int number) { numberStart_ = std::clamp(number, 0, 99); }
	void SetNumber(int number) { number_ = std::clamp(number, 0, 99999); }
	void SetTimerNumber(int number) { numberTimer_ = std::clamp(number, 0, 99); }
	
public:
	// 色変更オブジェクト
	KamataEngine::ObjectColor objectColor_;
	// 色の数値
	KamataEngine::Vector4 color_;
	// 移動量
	KamataEngine::Vector3 velocity_;
	KamataEngine::Sprite* sprite_[5] = {};
	
private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	uint32_t textureHandle_ = 0;
	
	
	
	KamataEngine::Vector2 charSize_; // 1文字分

	int frameCount_ = 0;
	int numberStart_ = 0;
	int number_ = 0;
	int numberTimer_ = 0;
};
