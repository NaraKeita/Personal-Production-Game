#pragma once
#include "Player.h"
#include "KamataEngine.h"
#include <functional> // 最後に取ったリンゴの数を表示するのに必要

using namespace KamataEngine;

#include "FallingObject.h"

class Apple : public FallingObject {
public:
	void Initialize(Camera* camera);
	void Update() override;
	void Draw() override;
	void SetPosition(const Vector3& pos) { worldTransform_.translation_ = pos; }
	std::function<void(int)> onGetApple_; // コールバック
	void OnHitPlayer() override;
	
public:
	void SetOnGetApple(const std::function<void(int)>& func) { onGetApple_ = func; }  
	const Vector3& GetPosition() const { return worldTransform_.translation_; }
	float GetRadius() const { return radius_; }
	bool IsActive() const { return isActive_; }
	int SetScore(int num) { return score_ = num; }
	//uint32_t seAppleGet_ = 0; // 効果音

private:
	int score_ = 0;           // スコア
};
