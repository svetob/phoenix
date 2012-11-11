/**
 * Needing to define all components and systems in one place is a
 * fundamental design flaw. But we do it for the moment...
 */
#ifndef _DECL_H
#define _DECL_H

#include "component.h"
#include "compTypes.h"

typedef float coord;

class Position: public IComponent
{
public:
    coord x, y;

    Position();
    Position(coord x, coord y);
    inline void set(coord x_, coord y_) { x = x_; y = y_; };
    inline void shift(coord x_, coord y_) { x += x_; y += y_; };
};

class Movement: public IComponent
{
public:
    coord mx, my;
    Position* pos;

    Movement(Position* position);
    inline void setVector(coord vx, coord vy) { mx = vx; my = vy; };
    inline void addVector(coord vx, coord vy) { mx += vx; my += vy; };
};
    
class Render: public IComponent
{
public:
    bool visible;

    Render();
};

#endif