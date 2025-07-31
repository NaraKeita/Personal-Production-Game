#include "SpringScene.h"
#include <cassert>
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

	// モデル
	//modelPlayer_ = Model::CreateFromOBJ("player"); // プレイヤー
	//modelSkydome_ = Model::CreateFromOBJ("skydome"); // 天球
	//modelGround_ = Model::CreateFromOBJ("ground"); // 地面
	//modelTree_ = Model::CreateFromOBJ("tree"); // 木

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

	/*ImGui::Begin("camera");
	ImGui::DragFloat3("camera:Toransform", camera_.translation_.x, 0.1f);
	ImGui::DragFloat3("camera:Rotation", camera_.rotation_.x, 0.1f);
	ImGui::End();*/

	//camera_.UpdateMatrix();
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

