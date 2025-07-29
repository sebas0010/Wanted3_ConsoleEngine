#pragma once

#include "Level/Level.h"
#include <vector>
#include "Actor/Actor.h"

struct MenuItem
{
	// �Լ� ������ ����
	typedef void (*OnSelected)();
	//using OnSelected = void (*)();

	MenuItem(const char* text, OnSelected onSelected)
		: onSelected(onSelected)
	{
		size_t length = strlen(text) + 1;
		menuText = new char[length];
		strcpy_s(menuText, length, text);
	}

	~MenuItem()
	{
		SafeDeleteArray(menuText);
	}
	// �޴� �ؽ�Ʈ
	char* menuText = nullptr;

	// �޴� ���� �� ������ ����
	OnSelected onSelected = nullptr;
};

class MenuLevel : public Level
{
	RTTI_DECLARATIONS(MenuLevel, Level)

public:
	MenuLevel();
	~MenuLevel();

	virtual void Tick(float deltaTime) override;
	virtual void Render() override;
private:
	// ���� ���õ� �������� �ε���
	int currentIndex = 0;

	// ������ ���� ����
	Color selectedColor = Color::Green;
	// ������ �̼��� ����
	Color unselectedColor = Color::White;
	// ������ �迭
	std::vector<MenuItem*> items;
	
	// �޴� ������ ��
	int length = 0;
};