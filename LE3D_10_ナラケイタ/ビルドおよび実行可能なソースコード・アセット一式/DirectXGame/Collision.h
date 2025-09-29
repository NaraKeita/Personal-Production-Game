#pragma once
#include <KamataEngine.h>

// 球同士の当たり判定
bool CheckCollision(const KamataEngine::Vector3& posA, float radiusA, const KamataEngine::Vector3& posB, float radiusB);