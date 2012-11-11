#include <map>
#include <vector>

#include "component.h"

// Implement ComponentStore using unique key-value pairs
class ComponentStore
{
private:
    std::map<COMP_TYPE, IComponent*> store;
public:
    
    // Element manipulation
    bool add(IComponent* c);
    void remove(COMP_TYPE t);
    
    // Element retrieval
    bool hasAll(std::vector<COMP_TYPE>* cts);
    IComponent* get(COMP_TYPE t);

    // Iterators
    inline std::map<COMP_TYPE, IComponent*>::iterator getIterator()
    {
        return store.begin();
    };
    inline std::map<COMP_TYPE, IComponent*>::iterator getIteratorEnd()
    {
        return store.end();
    };
};
