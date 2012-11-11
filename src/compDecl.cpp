#include "compDecl.h"
#include "compTypes.h"

// Position
Position::Position()
{
    type = POSITION;
}

Position::Position(coord x, coord y)
{
    type = POSITION;
    this->x = x;
    this->y = y;
}

// Movement
Movement::Movement(Position* position)
{
    pos = position;
    type = MOVEMENT;
    mx = 0;
    my = 0;
}

// Render
Render::Render()
{
    type = RENDER;
}
