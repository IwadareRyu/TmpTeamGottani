#pragma once
class AnimalUnion
{
private:
	const Array<String> AnimalID = { U"🐘", U"🐧", U"🐐", U"🐤" };

public:
	AnimalUnion();
	~AnimalUnion(){}
	void ChackUnion(MultiPolygon target1,MultiPolygon target2);
	void Union(MultiPolygon target1, MultiPolygon target2);

};

