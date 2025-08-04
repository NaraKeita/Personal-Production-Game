#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Skydome.h"
#include "Ground.h"
#include "Tree.h"

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
	// 天球
	Skydome* skydome_ = nullptr;
	// 地面
	Ground* ground_ = nullptr;
	// 木
	Tree* tree_ = nullptr;

	// モデル
	Model* modelPlayer_ = nullptr;
	Model* modelSkydome_ = nullptr;
	Model* modelGround_ = nullptr;
	Model* modelTree_ = nullptr;

	WorldTransform worldTransform_;
	
	Camera* camera_ = nullptr;

};
