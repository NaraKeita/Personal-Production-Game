#include "RankManager.h"
//#include "../scene/SpringScene.h"
using namespace KamataEngine;
RankManager::RankManager() = default;
RankManager::~RankManager() { 
	delete rankSprite_;
	
}

void RankManager::Initialize() {
	rankHandles_[0] = TextureManager::Load("rank/rank_D.png");
	rankHandles_[1] = TextureManager::Load("rank/rank_C.png");
	rankHandles_[2] = TextureManager::Load("rank/rank_B.png");
	rankHandles_[3] = TextureManager::Load("rank/rank_A.png");
	rankHandles_[4] = TextureManager::Load("rank/rank_S.png");

	rankSprite_ = Sprite::Create(rankHandles_[0], {540.0f, 200.0f});
}

void RankManager::Update() {
	// ImGui::Begin("rankManager");
	// ImGui::DragInt("rank",)
	// ImGui::End();
	
}

void RankManager::Draw() {
	Sprite::PreDraw();
	// int totalScore = 0;
	int rank = 4;
	for (int rankIndex = 10; rankIndex < 40; rankIndex += 10) {
		if (totalScore_ >= rankIndex) {
			rank++;
		}
	}
	rankSprite_->SetTextureHandle(rankHandles_[rank]);
	rankSprite_->Draw();
	Sprite::PostDraw();
}
