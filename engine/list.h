
#pragma once

#include "types.h"

typedef struct _List {
	void* buffer;
	uint32 data_length;
	uint32 capacity;
	uint32 length;
} List;

List* ListInit(uint32 data_length, uint32 start_capacity);
uint32 ListAppend(List* list, void* data);
void* ListGet(List* list, uint32 index);
void* ListRemove(List* list, uint32 index);
