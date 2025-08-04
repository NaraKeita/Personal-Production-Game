#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Skydome.h"
#include "Ground.h"
#include "Tree.h"
#include "Apple.h"

using namespace KamataEngine;

class SpringScene {
public:
	//SpringScene();
	~SpringScene();

	void Initialize();
	void Update();
	void Draw();
	std::vector<Apple*> apples_;

private:
	int score_ = 0; // スコア
	uint32_t seAppleGet_ = 0; // 効果音

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
	// リンゴ
	Apple* apple_ = nullptr;

	WorldTransform worldTransform_;
	
	Camera* camera_ = nullptr;

};
