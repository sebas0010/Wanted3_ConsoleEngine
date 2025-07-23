#pragma once

#include "Core.h"
#include "Math/Vector2.h"

// ��ü�� �ϴ� �� ����
// ��ġ ���� -> Vector2
// �ܼ� â�� �׸��� -> char
// ������ �̺�Ʈ �Լ� ȣ��
// BeginPlay/Tick/Draw

class Engine_API Actor
{
public:
	Actor();
	virtual ~Actor();

	// �̺�Ʈ �Լ�

	// ��ü �����ֱ�(Lifetime)�� �ѹ��� ȣ���(�ʱ�ȭ ����)
	virtual void BeginPlay();

	// ������ ���� ȣ�� (�ݺ��� �۾� / ���Ӽ� �۾�)
	virtual void Tick(float deltaTime);

	// �׸��� �Լ�
	virtual void Render();

	// BeginPlay ȣ�� ���� Ȯ��
	inline bool HasBeganPlay() const { return hasBeganPlay; }

private:
	// ��ü�� ��ġ
	Vector2 position;

	// �׸� ��.
	char image = ' ';

	// BeginPlay ȣ���� �Ǿ����� Ȯ��
	bool hasBeganPlay = false;
};