#pragma once

class GameObject {
public:
	virtual ~GameObject() = default;
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Draw() {}

	virtual void SetActive(bool active) { isActive_ = active; }
	virtual bool IsActive() const { return isActive_; }

protected:
	bool isActive_ = true;
};
