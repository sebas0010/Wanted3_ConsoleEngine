#include "Target.h"

Target::Target(const Vector2& position)
	: Actor('T', Color::Blue, position)
{
	// �׸� �� ����� ���� ���� ����.
	SetSortingOrder(1);
}