#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>

struct Hashtable {
    TYPE type;
    int num_rows;
    int total_rows;
    void*** rows;
    void** keys;
};

Hashtable hashtable_create(TYPE type, int total_rows) {
    Hashtable hashtable = malloc(sizeof(Hashtable));

    hashtable->type = type;
    hashtable->num_rows = 0;
    hashtable->total_rows = total_rows;
    hashtable->keys = malloc(sizeof(void*) * total_rows);
    hashtable->rows = malloc(sizeof(void**) * total_rows);

    for (int i = 0; i < total_rows; i++) {
        hashtable->keys[i] = NULL;
        hashtable->rows[i] = NULL;
    }

    return hashtable;
}

void hashtable_free(Hashtable hashtable) {
    for (int i = 0; i < hashtable->num_rows; i++) {
        free(hashtable->keys[i]);
        free(hashtable->rows[i]);
    }

    free(hashtable->keys);
    free(hashtable->rows);
    free(hashtable);
}

int int_hash(void* key, int total_rows) {
    int num = *((int*)key);
    return num % total_rows;
}

int string_hash(void* key, int total_rows) {
    char* str = (char*) key;
    int hash = 0;
    for (int i = 0; str[i] != '\0'; i++)
        hash += str[i];
    return hash % total_rows;
}

int quadratic_probing(Hashtable hashtable, int index, void* value) {

    if (*(hashtable->keys[index]) != value) {
        int i = 1;
        while (hashtable->keys[(index + i) % hashtable->total_rows] != NULL)
            i++;
        index = (index + i) % hashtable->total_rows;
    }
    return index;
}

void hashtable_insert(Hashtable hashtable, void* key, void** values) {
    if (hashtable->num_rows == hashtable->total_rows) return;

    int index;
    switch (hashtable->type) {
        case INT:
            index = int_hash(key, hashtable->total_rows);
            break;
        case STRING:
            index = string_hash(key, hashtable->total_rows);
            break;
    }

    if (hashtable->rows[index] != NULL) {
        int i = 1;
        while (hashtable->rows[(index + i) % hashtable->total_rows] != NULL)
            i++;
        index = (index + i) % hashtable->total_rows;
    }

    hashtable->keys[index] = key;
    hashtable->rows[index] = values;
    hashtable->num_rows++;
}
