#pragma once

enum class ERenderOrder
{
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
	Player,
	Attack,
	Monster,
};