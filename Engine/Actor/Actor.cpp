#include "Actor.h"
#include "Utils/Utils.h"
#include "Engine.h"

#include <Windows.h>
#include <iostream>

Actor::Actor(const char image, Color color, const Vector2& position)
	: image(image), color(color), position(position)
{
}

Actor::~Actor()
{
}

// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��� (�ʱ�ȭ ����).
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

// ������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�).
void Actor::Tick(float deltaTime)
{
}

// �׸��� �Լ�.
void Actor::Render()
{
	// Win32 API.
	// Ŀ�� ��ġ �̵�.

	// �ܼ� ����� �����ϴ� �ڵ� ������.
	//static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ŀ�� ��ġ �� ����.
	COORD coord;
	coord.X = (short)position.x;
	coord.Y = (short)position.y;

	// Ŀ�� �̵�.
	//SetConsoleCursorPosition(handle, coord);
	Utils::SetConsolePosition(coord);

	// ���� ����.
	//SetConsoleTextAttribute(handle, (WORD)color);
	Utils::SetConsoleTextColor(static_cast<WORD>(color));

	// �׸���.
	std::cout << image;
}

void Actor::SetPosition(const Vector2& newPosition)
{
	//static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ŀ�� ��ġ �� ����.
	COORD coord;
	coord.X = (short)position.x;
	coord.Y = (short)position.y;

	// Ŀ�� �̵�.
	//SetConsoleCursorPosition(handle, coord);
	Utils::SetConsolePosition(coord);

	std::cout << ' ';

	position = newPosition;
}

Vector2 Actor::Position() const
{
	return position;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
	this->sortingOrder = sortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
	owner = newOwner;
}

Level* Actor::GetOwner()
{
	return owner;
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}