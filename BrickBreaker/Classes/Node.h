#pragma once
#include "Brick.h"

struct Node
{
    Brick* brick;
    int position;
    int y;
    Node* next;
    Node* prev;
};
