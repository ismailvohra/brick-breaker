#pragma once
#include"Fire.h"
#include"Object.h"

struct node
{
    Object* unit;
    node* next;
    node* prev;

    ~node()
    {
        delete unit;
    }
};
