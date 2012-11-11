#ifndef _COMPONENT_H
#define _COMPONENT_H

typedef int COMP_TYPE;

class IComponent
{
protected:
    COMP_TYPE type;
public:
    inline COMP_TYPE getType() { return type; };
};

#endif