#pragma once
#include "KamataEngine.h"
#include "Player.h"

using namespace KamataEngine;

class PoisonApple {
public:
	void Initialize(Camera* camera);
	void Update();
	void Draw();
	void SetActive(bool active) { isActive_ = active; }
	void SetPlayer(const Player* player) { player_ = player; }
	void SetPosition(const Vector3& pos) { worldTransform_.translation_ = pos; }

public:
	const Vector3& GetPosition() const { return worldTransform_.translation_; }
	float GetRadius() const { return radius_; }
	bool IsActive() const { return isActive_; }
	int poisonScore_ = 0;           // スコア
	uint32_t seAppleGet_ = 0; // 効果音

private:
	Audio* audio_ = nullptr;
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	Camera* camera_ = nullptr;
	bool isActive_ = true;
	bool isHitPlayer_ = false;
	const Player* player_ = nullptr;

	float fallSpeed_ = 0.1f; // 初期落下速度
	
	float radius_ = 1.0f; // モデルの大きさに合わせて調整
};
