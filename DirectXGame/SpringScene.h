#pragma once
#include "KamataEngine.h"
#include "Player.h"

using namespace KamataEngine;

class SpringScene {
public:
	//SpringScene();
	~SpringScene();

	void Initialize();
	void Update();
	void Draw();


private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	// 自キャラ
	Player* player_ = nullptr;

	// プレイヤーのモデル
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	Camera viewProjection_;
	Camera camera_;

};
