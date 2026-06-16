#pragma once
#include "KamataEngine.h"
#include <cstdint>
#include "../scene/GameObject.h"

class RankManager : public GameObject {
public:
	enum class Rank { S, A, B, C, D };

	RankManager();
	~RankManager();

	void SetAppleCount(int appleCount);
	void Initialize();
	void Update();
	void Draw();
	

private:
	Rank CalculateRank(int appleCount) const;
	uint32_t rankHandles_[5]{};
	KamataEngine::Sprite* rankSprite_;
	int totalScore_ = 0;
	int rank = 0;
};
