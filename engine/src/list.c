
#include <stdlib.h>
#include <string.h>
#include "../list.h"

List* ListInit(uint32 data_length, uint32 start_capacity) {
	List* list = calloc(1, sizeof(List));

	list->buffer = malloc(data_length * start_capacity);
	list->data_length = data_length;
	list->capacity = start_capacity;
	list->length = 0;

	return list;
}

uint32 ListAppend(List* list, void* data) {
	if (list->length >= list->capacity) {

		list->capacity = list->capacity > 0
			? list->capacity * 2
			: 1;

		list->buffer = realloc(list->buffer, list->data_length * list->capacity);

	}

	uint32 index = list->length++;
	memcpy((uint8*)list->buffer + (index * list->data_length), data, list->data_length);;

	return index;
}

void* ListGet(List* list, uint32 index) {
	return (uint8*)list->buffer + (index * list->data_length);
}

void* ListRemove(List* list, uint32 index) {

	if (list->length == 1) {
		list->length = 0;
		return 0;
	}

	--list->length;

	uint8* item_ptr = (uint8*)list->buffer + (index * list->data_length);
	uint8* end_ptr = (uint8*)list->buffer + (list->length * list->data_length);
	memcpy(item_ptr, end_ptr, list->data_length);

}
