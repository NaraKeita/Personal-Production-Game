#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Ground {
public:
	void Initialize(Model* model, const Vector3& position);
	void Update();
	void Draw(Camera& camera);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;

};
