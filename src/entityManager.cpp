#include <iterator>
#include <algorithm>
#include <math.h>

#include "entityManager.h"

using namespace std;

// ---------------------------------------------------------------------
// Asserts (i.e. Unit tests)
// ---------------------------------------------------------------------

// These will be VERY important for debugging. ANY discrepancy in this
// manager will be fatal! Should be called once per frame

bool assertSetsEqual(EntityManager* em)
{
    // TODO: Assert that all sets contain exactly the same entities
    return true;
}

bool assertEntityCount(EntityManager* em)
{
    // TODO: Assert the entity count in all sets matches the amount of
    // calls to insert/remove. Needs observer class or event structure.
    return true;
}

bool assertKeysCorrect(EntityManager* em)
{
    // TODO: Assert all entities are assigned to correct keys
    return true;
}


// ---------------------------------------------------------------------
// Comparators
// ---------------------------------------------------------------------

struct TestEntity: public less<Entity*>
{
    bool operator()(Entity* e1, Entity* e2)
    {
        return (e1->getId() < e2->getId());
    }
} compEntity;


// ---------------------------------------------------------------------
// Set operations
// ---------------------------------------------------------------------

template <class T> inline void copySet(const set<T>* from, const set<T>* to)
{
    set<T>::iterator it;
    for (it = from->begin(); it != from->end(); ++it)
        to->insert(*it._Ptr);
}

// ---------------------------------------------------------------------
// EntityManager
// ---------------------------------------------------------------------

EntityManager::EntityManager()
{
    entAll = new set<Entity*, less<Entity*>, allocator<Entity*>>(compEntity);
    entByComp = new map<COMP_TYPE, set<Entity*>*, less<COMP_TYPE>,
                        allocator<pair<const COMP_TYPE, set<Entity*>*>>>();
}

EntityManager::~EntityManager()
{
    delete entAll;

    // Delete entByComp and all its entries
    map<COMP_TYPE, set<Entity*>*>::iterator it;
    for (it = entByComp->begin(); it != entByComp->end(); ++it)
    {
        delete it->second;
    }
    delete entByComp;
}

void EntityManager::insert(Entity* e)
{
    //TODO: Assert 'e' not in 'entities' 
    
    entAll->insert(e);
    
    // Insert by component
    map<COMP_TYPE, IComponent*>::iterator it;
    for (it = e->getComponentIterator(); it != e->getComponentIteratorEnd(); ++it)
    {
        COMP_TYPE t = it->first;
        if (entByComp->count(t))
        {
            // Set of this type of component exists
            set<Entity*>* se = entByComp->find(t)->second;
            se->insert(e);
        }
        else
        {
            // Add first component of this type
            set<Entity*>* se = new set<Entity*, less<Entity*>, allocator<Entity*>>(compEntity);
            se->insert(e);
            entByComp->insert( pair<COMP_TYPE, set<Entity*>*>(t, se) );
        }
    }

    // Insert by name
    /*const char* name = e->getName();
    if (entByName->count(name))
    {
        // Set of components of this name exists
        set<Entity*>* se = entByName->find(name)->second;
        se->insert(e);
    }
    else
    {
        // Add first component of this name
        set<Entity*>* se = new set<Entity*, less<Entity*>, allocator<Entity*>>(compEntity);
        se->insert(e);
        entByName->insert( pair<COMP_TYPE, set<Entity*>*>(name, se) );
    }*/

}

void EntityManager::remove(Entity* e)
{
    //TODO: Assert 'e' in 'entities' 
    entAll->erase(e);

    // Delete by component
    map<COMP_TYPE, IComponent*>::iterator it;
    for (it = e->getComponentIterator(); it != e->getComponentIteratorEnd(); ++it)
    {
        COMP_TYPE t = it->first;
        entByComp->find(t)->second->erase(e);
    }
}

const set<Entity*>* EntityManager::getByComponent(COMP_TYPE t)
{
    if (entByComp->count(t))
        return entByComp->find(t)->second;
    else
        return NULL;
}

set<Entity*>* EntityManager::getByComponents(vector<COMP_TYPE>* cts)
{
    int s = cts->size();
    if (s == 0)
        return NULL;
    else if (s == 1)
    {
        const set<Entity*> *ret = getByComponent(cts[0][0]); // Get first (and only) item
        return new set<Entity*, less<Entity*>, allocator<Entity*>>(ret->begin(), ret->end());
    }
    else
    {
        const set<Entity*> *first = NULL, *next;
        set<Entity*> *current = NULL, *buffer;
        vector<COMP_TYPE>::iterator it;

        it = cts->begin();

        // Get first item
        do {
            first = getByComponent(*it._Ptr);
            ++it;
        } while (first == NULL && it != cts->end());

        // Then perform intersection on subsequent items
        while (it != cts->end() )
        {
            next = getByComponent(*it._Ptr);
            if (next != NULL)
            {
                buffer = new set<Entity*, less<Entity*>, allocator<Entity*>>(compEntity);
                if (current == NULL)
                {
                    set_intersection(first->begin(), first->end(), next->begin(),
                             next->end(), inserter(*buffer, buffer->end()));
                }
                else
                {
                    set_intersection(current->begin(), current->end(), next->begin(),
                             next->end(), inserter(*buffer, buffer->end()));
                    delete current;
                }
                current = buffer;
            }
            ++it;
        }

        if (current == NULL)
        {
            if (first == NULL)
                return NULL;
            else
            {
                // Return copy of first
                return new set<Entity*, less<Entity*>, allocator<Entity*>>(first->begin(), first->end());
            }
        }
        else
            return current;
    }
}

