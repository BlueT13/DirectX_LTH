#pragma once

enum class ERenderOrder
{
	ColMap,
	Map,
	WeaponBack,
	Player,
	WeaponFront,
	Monster,
	Cursor,
};

enum class ECollisionOrder
{
	Player,
	Attack,
	Monster,
};