#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Tree {
public:
	void Initialize(Camera* camera);
	void Update();
	void Draw();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;

	float swingTime_;      // 揺れの経過時間
	bool swingActive_;     // 揺れ中かどうか
	float swingWaitTimer_; // 揺れ待機時間

	Camera* camera_ = nullptr;
};
