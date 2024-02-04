#pragma once
#include <iostream>
#include "base.h"
typedef struct Node {
	Base* base;
	struct Node* previous = NULL;
	struct Node* next = NULL;
} DoubleList;

void add_in_front(DoubleList** head, Base* base);		//adding in front
void add_in_back(DoubleList** head, Base* base);		