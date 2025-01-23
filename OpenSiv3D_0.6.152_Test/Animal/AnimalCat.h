#pragma once
#include "AnimalBase.h"

class AnimalCat : public Animal
{
private:
	Vec3 velocity_;  // 動物の速度（重力を適用するために使用）

public:
	AnimalCat(const Vec2& position, const Texture& image, const int score, const float size)
		: Animal(position, image, score, size), velocity_(0, 0, 0)  // 初期速度を0に設定
	{
	}

	void Start() override
	{
	}

	void Update(Vec2 setPos) override
	{
		if (position_.y > 200) {
			is_spown = true;
		}
		SetPosition(setPos);
		Draw();
	}

	void Draw() const override
	{
		Circle{ position_.xy(), size_ }.draw();
		image_.scaled(size_ * 0.1).drawAt(position_.xy());
	}
};
