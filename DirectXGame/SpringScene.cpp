#include "SpringScene.h"
#include "Collision.h"
#include <KamataEngine.h>

using namespace KamataEngine;

SpringScene::~SpringScene() {
	// 自キャラの開放
	delete player_;
	delete skydome_;
	delete ground_;
	delete tree_;
	delete apple_;
	delete poisonApple_;
	delete displayNumbar_;
	
}

void SpringScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 生成
	camera_ = new Camera();
	player_ = new Player();
	skydome_ = new Skydome();
	ground_ = new Ground();
	tree_ = new Tree();
	apple_ = new Apple();
	poisonApple_ = new PoisonApple();
	displayNumbar_ = new DisplayNumbar();

	// スコア設定
	apple_->score_ = 1;
	poisonApple_->poisonScore_ = -1;
	
	// 初期化
	camera_->Initialize();
	worldTransform_.Initialize();
	player_->Initialize(camera_);
	skydome_->Initialize(camera_);
	ground_->Initialize(camera_);
	tree_->Initialize(camera_);
	apple_->Initialize(camera_);
	apple_->SetPlayer(player_);
	poisonApple_->Initialize(camera_);
	poisonApple_->SetPlayer(player_);
	displayNumbar_->Initialize();
	
	// 軸方向
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(camera_);

}

void SpringScene::Update() { 
	player_->Update(); 
	skydome_->Update();
	tree_->Update();
	apple_->Update();
	poisonApple_->Update();
	displayNumbar_->Update();

	displayNumbar_->SetNumber(apple_->score_);
	displayNumbar_->SetNumber(poisonApple_->poisonScore_);


	
}

void SpringScene::Draw() {  
    // DirectXCommonのインスタンスを取得  
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();  

	//dxCommon->ClearDepthBuffer();  

    // 3Dモデル描画前処理
	Model::PreDraw();

    player_->Draw();  
	skydome_->Draw();
	ground_->Draw();
	tree_->Draw();
	apple_->Draw();
	poisonApple_->Draw();

    // 3Dモデル描画後処理  
    Model::PostDraw();  

	Sprite::PreDraw(dxCommon->GetCommandList());

	displayNumbar_->Draw();

	Sprite::PostDraw();
}


