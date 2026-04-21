#include "RankManager.h"

RankManager::RankManager() = default;
RankManager::~RankManager() { delete rankSprite_; }

void RankManager::Initialize() {
	rankHandles_[0] = TextureManager::Load("rank/rank_S.png");
	rankHandles_[1] = TextureManager::Load("rank/rank_A.png");
	rankHandles_[2] = TextureManager::Load("rank/rank_B.png");
	rankHandles_[3] = TextureManager::Load("rank/rank_C.png");
	rankHandles_[4] = TextureManager::Load("rank/rank_D.png");

	for (int i = 0; i < 5; i++) {
		rankSprite_ = Sprite::Create(rankHandles_[i], {540.0f, 200.0f});
	}

}

//void RankManager::CreateRankSprite(Rank rank) {
//	int idx = static_cast<int>(rank);
//	if (rankHandles_[idx] != 0) {
//		rankSprite_ = Sprite::Create(rankHandles_[idx], {540.0f, 200.0f});
//	}
//}

void RankManager::Draw() {
	int rankIndex = 0;
	if (totalScore_ >= 0) {
		rankIndex = 0;
	} else if (totalScore_ >= 10) {
		rankIndex = 1;
	} else if (totalScore_ >= 15) {
		rankIndex = 2;
	} else if (totalScore_ >= 20) {
		rankIndex = 3;
	} else if(totalScore_ >= 25){
		rankIndex = 4;
	}
	rankSprite_[rankIndex].Draw();
}
