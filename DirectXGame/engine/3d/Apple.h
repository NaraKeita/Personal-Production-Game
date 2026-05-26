#pragma once
#include "Player.h"
#include "KamataEngine.h"
#include <functional> // 最後に取ったリンゴの数を表示するのに必要

using namespace KamataEngine;

class Apple : public GameObject {
public:
	void Initialize(Camera* camera);
	void Update();
	void Draw();
	void SetActive(bool active) { isActive_ = active; }
	void SetPlayer(const Player* player) { player_ = player; }
	void SetPosition(const Vector3& pos) { worldTransform_.translation_ = pos; }
	std::function<void(int)> onGetApple_; // コールバック
	
public:
	void SetOnGetApple(const std::function<void(int)>& func) { onGetApple_ = func; }  
	const Vector3& GetPosition() const { return worldTransform_.translation_; }
	float GetRadius() const { return radius_; }
	bool IsActive() const { return isActive_; }
	int SetScore(int num) { return score_ = num; }
	//uint32_t seAppleGet_ = 0; // 効果音

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
	int score_ = 0;           // スコア
	uint32_t seAppleGet_ = 0; // 効果音

	float fallSpeed_ = 0.1f;  // 初期落下速度
	float radius_ = 1.0f; // モデルの大きさに合わせて調整
};
