#pragma once
#include "UIManager.h"
#include "Animal/AnimalCat.h"
#include "AnimalDataBase.h"
#include "Animal/PhysicsManager.h"
#include "stdafx.h"

class AnimalUnion
{
private:
	const Array<String> AnimalID = { U"🐘", U"🐧", U"🐐", U"🐤" };
	const Array<int> ScoreID = { 200,400,600,2000 };
	AnimalDataBase* animal_dataBase = AnimalDataBase::GetInstance();

public:
	AnimalUnion(){}
	~AnimalUnion(){}
	void ChackUnionTest(std::vector<Animal*>& animals,PhysicsManager* physics,
		Array<P2Body>& bodies, UIManager* score);
	bool ChackUnion(Animal* target1, Animal* target2);
	Animal* Union(Animal* target);

};

