#include "AnimalUnion.h"


void AnimalUnion::ChackUnionTest(std::vector<Animal*>& animals, PhysicsManager* physics,
		Array<P2Body>& bodies, UIManager* score)
{
	if (bodies.size() < 2) return;
	for (auto it_i = bodies.begin(); it_i != bodies.end() - 1;)
	{
		for (auto it_j = it_i + 1; it_j != bodies.end();)
		{
			int animal_i  = std::distance(bodies.begin(),it_i);
			int animal_j = std::distance(bodies.begin(), it_j);
			bool isUnion = ChackUnion(animals[animal_i], animals[animal_j]);
			if (isUnion)
			{
				auto animal = animals[animal_i];
				score->AddScoreRef(animal->GetScore());
				auto unionObject = Union(animal);
				//it_iとit_jのオブジェクトの削除
				animals.erase(animals.begin() + animal_j);
				it_j = bodies.erase(it_j);
				animals.erase(animals.begin() + animal_i);
				it_i = bodies.erase(it_i);
				if (unionObject->GetSize() >= 1)
				{
					physics->CreateBall(unionObject);
				}
				return;
			}
			else
			{
				it_j++;
			}
		}
		it_i++;
	}
}

bool AnimalUnion::ChackUnion(Animal* target1, Animal* target2)
{
	if (target1->GetImage() == target2->GetImage() && target1->CheckCollision(*target2))
	{
		return true;
	}
	return false;
}

Animal* AnimalUnion::Union(Animal* target)
{
	int index = 0;
	for (auto i = 0; i < animal_dataBase->animal_data.size(); i++)
	{
		if (target->GetImage() == animal_dataBase->animal_data[i]->texture_)
		{
			index = i + 1;
			break;
		}
	}
	if (index >= animal_dataBase->animal_data.size())
	{
		auto data = animal_dataBase->animal_data[0];
		
		Animal* newAnimal = new AnimalCat(target->GetPosition(),data->texture_, data->score_, 0);
		return newAnimal;
	}
	else
	{
		auto data = animal_dataBase->animal_data[index];

		Animal* newAnimal = new AnimalCat(target->GetPosition(), data->texture_, data->score_, data->size_);
		return newAnimal;
	}
}
