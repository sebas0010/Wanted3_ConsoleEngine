#include "Player.h"
#include "Engine.h"
#include "Input.h"
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

#include <iostream>

Player::Player(const Vector2& position)
	: Actor('P', Color::Red, position)
{
	// �׸� �� ����� ���� ���� ����.
	SetSortingOrder(3);
}

void Player::BeginPlay()
{
	super::BeginPlay();

	// �������̽� ������.
	if (GetOwner())
	{
		canPlayerMoveInterface 
			= dynamic_cast<ICanPlayerMove*>(GetOwner());

		if (!canPlayerMoveInterface)
		{
			std::cout << "Can not cast owner level to ICanPlayerMove.\n";
		}
	}
}

void Player::Tick(float deltaTime)
{
	//Actor::Tick(deltaTime);
	super::Tick(deltaTime);

	// ESC ����.
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().Quit();
		QuitGame();
		return;
	}

	// �Է�ó��.

	// �̵� ���� - �̵��ϱ� ���� �̵��� ��ġ�� �� �� �ִ��� �Ǵ� �� �̵�.
	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		// �̵� ���� �̵� �������� Ȯ��.
		if (canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x + 1, Position().y)))
		{
			Vector2 position = Position();
			position.x += 1;
			SetPosition(position);
		}
	}

	if (Input::Get().GetKeyDown(VK_LEFT))
	{
		bool result = canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x - 1, Position().y)
		);

		if (result)
		{
			Vector2 position = Position();
			position.x -= 1;
			SetPosition(position);
		}
	}

	if (Input::Get().GetKeyDown(VK_UP))
	{
		if (canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x, Position().y - 1)))
		{
			Vector2 position = Position();
			position.y -= 1;
			SetPosition(position);
		}
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		if (canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x, Position().y + 1)))
		{
			Vector2 position = Position();
			position.y += 1;
			SetPosition(position);
		}
	}
}