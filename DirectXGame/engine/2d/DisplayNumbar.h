#pragma once  
#include <algorithm> // これがないとclampが使えない
#include "KamataEngine.h"
#include "../scene/GameObject.h"

class DisplayNumbar : public GameObject {
public:
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	void SetNumber(int number) { number_ = std::clamp(number, 0, 99999); }
	void SetTimerNumber(int number) { numberTimer_ = std::clamp(number, 0, 99); }

	KamataEngine::Sprite* GetSprite(int num) { return sprite_[num]; }
	KamataEngine::Vector2 charSize_; // 1文字分
	
private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	uint32_t textureHandle_ = 0;
	
	
	
	int frameCount_ = 0;
	int number_ = 0;
	int numberTimer_ = 0;
	KamataEngine::Sprite* sprite_[5] = {};
};
