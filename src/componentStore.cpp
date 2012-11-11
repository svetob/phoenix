#include "componentStore.h"

bool ComponentStore::add(IComponent* c)
{
    COMP_TYPE t = c->getType();
    std::map<COMP_TYPE, IComponent*>::const_iterator lb = store.lower_bound(t);
    if (lb != store.end() && !(store.key_comp()(t, lb->first)))
    {
        // Value already exists;
        return false;
    }
    else
    {
        // Value does not exist already, insert value
        store.insert(lb, std::map<COMP_TYPE, IComponent*>::value_type(t, c));
        return true;
    }
}

void ComponentStore::remove(COMP_TYPE t)
{
    store.erase(t);
}

IComponent* ComponentStore::get(COMP_TYPE t)
{
    std::map<COMP_TYPE, IComponent*>::const_iterator lb = store.lower_bound(t);
    if (lb != store.end() && !(store.key_comp()(t, lb->first)))
    {
        return lb->second;
    }
    else
    {
        // Value doesn't exist
        return NULL;
    }
}

bool ComponentStore::hasAll(std::vector<COMP_TYPE>* cts)
{
    std::map<COMP_TYPE, IComponent*>::const_iterator lb;
    std::vector<COMP_TYPE>::iterator it;
    for (it = cts->begin(); it != cts->end(); ++it)
    {
        COMP_TYPE t = *it._Ptr;
        lb = store.lower_bound(t);
        if (lb == store.end() || store.key_comp()(t, lb->first))
            return false;
    }
    return true;
}
