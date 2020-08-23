#pragma once
enum class ObservedEvents
{
	gemPickup = 0,
	goldPickup = 1,
	enemyKill = 2,
	playerHit = 3,
	extraLifeEarned = 4,
	outOfLives = 5
};

enum class CollisionTags
{
	player = 0,
	enemy = 1,
	gem = 2,
	gold = 3,
	goldBag = 4,
	fireBall = 5,
	wall = 6
};