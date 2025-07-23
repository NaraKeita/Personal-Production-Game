#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;

class Player {
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(Camera& camera);

public:
	Input* input_ = nullptr;

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// X方向の速度
	float velocityX_;
};
