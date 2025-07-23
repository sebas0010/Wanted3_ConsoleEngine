#pragma once

#include "Core.h";
#include <vector>  // ũ�Ⱑ �˾Ƽ� ����Ǵ� ���� �迭

class Actor;
class Engine_API Level
{
public:
	Level();
	virtual ~Level();

	void AddActor(Actor* newActor);

	// ���� �̺�Ʈ �Լ�
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

private:
	// ������ ��ġ�� ��� ���͸� �����ϴ� �迭
	std::vector<Actor*> actors;
};