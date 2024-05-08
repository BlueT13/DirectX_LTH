#pragma once

enum class EUpdateOrder
{
	None,
	Map,
	Cursor,
	Player,
	Monster,
	Background,
};

enum class ERenderOrder
{
	None,
	ColMap,
	Background_0,
	Background_1,
	Background_2,
	Map,
	WeaponBack,
	AfterImage,
	Player,
	WeaponFront,
	Monster,
	Cursor,
};

enum class ECollisionOrder
{
	None,
	Player,
	PlayerAttack,
	Monster,
	MonsterAttack,
};