#pragma once
#include "Character.h"


class CharacterLuigi : public Character
{
public:
	CharacterLuigi(Properties* props);
	~CharacterLuigi();

	void Update(float deltaTime) override;
	void AddGravity(float deltaTime);
private:
	LevelMap* m_current_level_map;

};



