﻿#include "../stdafx.h"
#include "AnimalBase.h"

int Animal::GetScore() const
{
	return score_;
}

float Animal::GetSize() const
{
	return size_;
}


Vec3 Animal::GetPosition() const
{
	return position_;
}

void Animal::SetPosition(const Vec3& position)
{
	position_ = position;
}

Texture Animal::GetImage() const
{
	return image_;
}

bool Animal::CheckCollision(const Animal& other) const
{
	// 簡単な距離ベースの接触判定
	return std::abs(size_ - other.GetSize()) < 5.0;
}
