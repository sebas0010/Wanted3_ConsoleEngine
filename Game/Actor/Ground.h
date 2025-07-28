#pragma once

#include "Actor/Actor.h"

class Ground : public Actor
{
    RTTI_DECLARATIONS(Ground, Actor)

public:
    Ground(const Vector2& position);
};