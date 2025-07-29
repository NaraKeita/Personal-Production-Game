#include "Ground.h"

void Ground::Initialize(Model* model, const Vector3& position) {
	// NULLポインタをチェックする
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	worldTransform_.translation_ = position;

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Ground::Update() {
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Ground::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }
