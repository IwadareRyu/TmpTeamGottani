#include "stdafx.h"
#include "Player.h"
#include "Stage.h"
#include "Animal/PhysicsManager.h"
#include "Animal/AnimalCat.h"

void Player::Start()
{
	
}

void Player::Update()
{
	const double delta = (Scene::DeltaTime() * 200);

	// 上下左右キーで移動
	if (KeyLeft.pressed())
	{
		animal_pos.x -= delta;
		cursor_pos.x -= delta;
	}

	if (KeyRight.pressed())
	{
		animal_pos.x += delta;
		cursor_pos.x += delta;
	}

	// [C] キーが押されたら中央に戻る
	if (KeyC.down())
	{
		animal_pos.x = Scene::Center().x;
		cursor_pos.x = Scene::Center().x;
	}

	// [スペース] キーが押されたら動物をドロップする
	if (KeySpace.down())
	{
		DropAnimal(); // 動物を落とす処理
	}

}

void Player::Draw() const
{
	texture_.scaled(0.2).rotated(-90_deg).draw(cursor_pos);
	current_texture.texture_.scaled(current_texture.size_ * 0.1f).draw(animal_pos);
}

void Player::DropAnimal()
{
	Animal* newAnimal = new AnimalCat(animal_pos, current_texture.texture_, current_texture.score_, current_texture.size_);
	physics_manager->CreateBall(newAnimal);
	int randomIndex = Random<int>(2);
	current_texture = *(animal_database->animal_data[randomIndex]);
}
