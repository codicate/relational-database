#ifndef DATABASE_HASHTABLE_H
#define DATABASE_HASHTABLE_H

typedef struct Hashtable* Hashtable;

Hashtable hashtable_create(int capacity);

//void hashtable_free(Hashtable hashtable);

int hashtable_size(Hashtable hashtable);

int hashtable_capacity(Hashtable hashtable);

int hashtable_put(Hashtable hashtable, char* key, void* values);

void** hashtable_get(Hashtable hashtable, char* key);

void** hashtable_get_by_index(Hashtable hashtable, int index);

int hashtable_remove(Hashtable hashtable, char* key);

void hashtable_print(Hashtable hashtable);

#endif //DATABASE_HASHTABLE_H
