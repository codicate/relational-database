#ifndef DATABASE_HASHTABLE_H
#define DATABASE_HASHTABLE_H

#include <stdbool.h>

typedef struct Hashtable* Hashtable;

Hashtable hashtable_create(int capacity);

//void hashtable_free(Hashtable hashtable);

int hashtable_size(Hashtable hashtable);

int hashtable_capacity(Hashtable hashtable);

int hashtable_put(Hashtable hashtable, char* key, void* values);

void* hashtable_get(Hashtable hashtable, char* key);

bool hashtable_contains(Hashtable hashtable, char* key);

void* hashtable_get_by_index(Hashtable hashtable, int index);

char** hashtable_keys(Hashtable hashtable);

void** hashtable_values(Hashtable hashtable);

bool hashtable_remove(Hashtable hashtable, char* key);

void hashtable_print(Hashtable hashtable);

Hashtable hashtable_union(Hashtable left, Hashtable right);

Hashtable hashtable_intersection(Hashtable left, Hashtable right);

Hashtable hashtable_difference(Hashtable left, Hashtable right);

#endif //DATABASE_HASHTABLE_H
