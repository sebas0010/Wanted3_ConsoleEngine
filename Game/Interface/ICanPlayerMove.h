#pragma once

#include "Math/Vector2.h"

// �÷��̾ �̵��� �� �ִ��� Ȯ���� �� ����� �������̽�.
class ICanPlayerMove
{
public:
	virtual bool CanPlayerMove(
		const Vector2& playerPosition,
		const Vector2& newPosition
	) = 0;
};