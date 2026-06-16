#include "RankManager.h"

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
	
	for (int appleCount = 0; appleCount < 50; appleCount++) {
		if (totalScore_ >= appleCount) {
			rank++;
		}
	}
}

void RankManager::Draw() {
	/*Sprite::PreDraw();*/
	// int totalScore = 0;
	
	
	rankSprite_->SetTextureHandle(rankHandles_[rank]);
	rankSprite_->Draw();
	/*Sprite::PostDraw();*/
}
