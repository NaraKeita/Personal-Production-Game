#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Ground {
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
