#include "Player.h"

Player::Player(const Vector2& position)
	: Actor('P', Color::Red, position)
{
}

void Player::Tick(float deltaTime)
{
	//Actor::Tick(deltaTime);
	super::Tick(deltaTime);

	// @Todo: �Է�ó�� �ؾ� ��.
}