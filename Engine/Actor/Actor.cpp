#include "Actor.h"

Actor::Actor()
{

}
Actor::~Actor()
{

}
// ��ü �����ֱ�(Lifetime)�� �ѹ��� ȣ���(�ʱ�ȭ ����)
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

// ������ ���� ȣ�� (�ݺ��� �۾� / ���Ӽ� �۾�)
void Actor::Tick(float deltaTime)
{

}

// �׸��� �Լ�
void Actor::Render()
{

}