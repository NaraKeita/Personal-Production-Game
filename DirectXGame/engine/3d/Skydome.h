#pragma once
#include "KamataEngine.h"
#include "../scene/GameObject.h"

using namespace KamataEngine;

class Skydome : public GameObject {
public:
	void Initialize(Camera* camera);
	void Update();
	void Draw();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	Camera* camera_ = nullptr;
};
