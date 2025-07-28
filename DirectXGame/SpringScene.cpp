#include "SpringScene.h"
#include <cassert>
#include <math.h>
#include <KamataEngine.h>

using namespace KamataEngine;

SpringScene::~SpringScene() {
	// 自キャラの開放
	delete player_;

	delete modelPlayer_;
	delete modelSkydome_;
}

void SpringScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	camera_.Initialize();

	// モデル
	modelPlayer_ = Model::CreateFromOBJ("player"); // プレイヤー
	modelSkydome_ = Model::CreateFromOBJ("skydome"); // スカイドーム

	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(modelPlayer_, worldTransform_.translation_);

	// スカイドームの生成
	skydome_ = new Skydome();
	// スカイドームの初期化
	skydome_->Initialize(modelSkydome_,worldTransform_.translation_);

	// 軸方向
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(&viewProjection_);

}

void SpringScene::Update() { 
	player_->Update(); 
}

void SpringScene::Draw() {  
    // DirectXCommonのインスタンスを取得  
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();  
	dxCommon->ClearDepthBuffer();

    // 3Dモデル描画前処理
	Model::PreDraw();

    player_->Draw(camera_);  
	skydome_->Draw(camera_);

    // 3Dモデル描画後処理  
    Model::PostDraw();  
}

