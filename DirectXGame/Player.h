#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;

enum class LRDirection { 
	kRight,
	kLeft,
};

class Player {
public:
	void Initialize(Camera* camera);
	void Update();
	void Draw();

	const Vector3& GetPosition() const { return worldTransform_.translation_; }
	float GetRadius() const { return radius_; }

public:
	Input* input_ = nullptr;
	LRDirection lrDirection_ = LRDirection::kRight;

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	Camera* camera_ = nullptr;

	// モデル
	Model* model_ = nullptr;
	// X方向の速度
	float velocityX_;

	// 旋回時間(秒)
	static inline const float kTimeTurn = 0.3f;
	// 旋回開始時の角度x
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	// キャラクターの移動速さ
	float kCharacterSpeed = 0.5f;
	float kFriction = 0.03f;

	float radius_ = 1.0f; // モデルの大きさに合わせて調整
};
