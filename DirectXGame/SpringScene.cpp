#include "SpringScene.h"

#include <math.h>
#include <KamataEngine.h>

using namespace KamataEngine;

SpringScene::~SpringScene() {
	// 自キャラの開放
	delete player_;
	delete skydome_;
	delete ground_;
	delete tree_;

	delete modelPlayer_;
	delete modelSkydome_;
	delete modelGround_;
	delete modelTree_;
}

void SpringScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	camera_ = new Camera();
	camera_->Initialize();

	// ワールドトランスフォーム
	worldTransform_.Initialize();
	
	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(camera_);

	// 天球の生成
	skydome_ = new Skydome();
	// 天球の初期化
	skydome_->Initialize(camera_);

	// 地面の生成
	ground_ = new Ground();
	// 地面の初期化
	ground_->Initialize(camera_);

	// 木の生成
	tree_ = new Tree();
	// 木の初期化
	tree_->Initialize(camera_);

	// 軸方向
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(camera_);

}

void SpringScene::Update() { 
	player_->Update(); 
	ground_->Update();
	tree_->Update();

}

void SpringScene::Draw() {  
    // DirectXCommonのインスタンスを取得  
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();  
	dxCommon->ClearDepthBuffer();

    // 3Dモデル描画前処理
	Model::PreDraw();

    player_->Draw();  
	skydome_->Draw();
	ground_->Draw();
	tree_->Draw();

    // 3Dモデル描画後処理  
    Model::PostDraw();  
}

