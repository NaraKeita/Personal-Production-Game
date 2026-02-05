#include "Collision.h"

bool CheckCollision(const KamataEngine::Vector3& posA, float radiusA, const KamataEngine::Vector3& posB, float radiusB) {
	float dx = posA.x - posB.x;
	float dy = posA.y - posB.y;
	float dz = posA.z - posB.z;
	float distanceSq = dx * dx + dy * dy + dz * dz;
	float radiusSum = radiusA + radiusB;
	return distanceSq <= (radiusSum * radiusSum);
}
