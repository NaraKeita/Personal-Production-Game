#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Skydome.h"

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
	// スカイドーム
	Skydome* skydome_ = nullptr;

	// モデル
	Model* modelPlayer_ = nullptr;
	Model* modelSkydome_ = nullptr;

	WorldTransform worldTransform_;
	Camera viewProjection_;
	Camera camera_;

};
