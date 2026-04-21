#pragma once
#include "KamataEngine.h"
#include <cstdint>
using namespace KamataEngine;

class RankManager {
public:
	enum class Rank { S, A, B, C, D };

	RankManager();
	~RankManager();

	void Initialize();
	/*void CreateRankSprite(Rank rank);*/
	void Draw();
	int totalScore_ = 0;

private:
	uint32_t rankHandles_[5]{};
	Sprite* rankSprite_ = nullptr;
};
