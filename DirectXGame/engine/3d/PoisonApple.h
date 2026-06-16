#pragma once
#include "KamataEngine.h"
#include "Player.h"

using namespace KamataEngine;

#include "FallingObject.h"

class PoisonApple : public FallingObject {
public:
	void Initialize(Camera* camera);
	void Update();
	void Draw();
	void SetActive(bool active) { isActive_ = active; }
	void SetPlayer(Player* player) { player_ = player; }
	void SetPosition(const Vector3& pos) { worldTransform_.translation_ = pos; }
	void OnHitPlayer() override;

public:
	const Vector3& GetPosition() const { return worldTransform_.translation_; }
	float GetRadius() const { return radius_; }
	bool IsActive() const { return isActive_; }
	//int score_ = 0;           // スコア
	
	//uint32_t seAppleGet_ = 0; // 効果音

private:
	// 特有のメンバがあればここに置く
};
