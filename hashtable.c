#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Hashtable {
    int size;
    int capacity;
    void** rows;
    char** keys;
};

Hashtable hashtable_create(int capacity) {
    Hashtable hashtable = malloc(sizeof(struct Hashtable));

    hashtable->size = 0;
    hashtable->capacity = capacity;
    hashtable->keys = malloc(sizeof(char*) * capacity);
    hashtable->rows = malloc(sizeof(void*) * capacity);

    return hashtable;
}

//void hashtable_free(Hashtable hashtable) {
//    for (int i = 0; i < hashtable->num_rows; i++) {
//        free(hashtable->keys[i]);
//        free(hashtable->rows[i]);
//    }
//
//    free(hashtable->keys);
//    free(hashtable->rows);
//    free(hashtable);
//}

int hashtable_size(Hashtable hashtable) {
    return hashtable->size;
}

int hashtable_capacity(Hashtable hashtable) {
    return hashtable->capacity;
}

int string_hash(const char* key, int total_rows) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
        hash += key[i];
    return hash % total_rows;
}

int hashtable_put(Hashtable hashtable, char* key, void* values) {
    if (hashtable->size == hashtable->capacity) return -1;
    int index = string_hash(key, hashtable->capacity);

    int i = 1;
    while (hashtable->keys[index] != NULL) {
        index = (index + i * i) % hashtable->capacity;
        i++;
    }

    hashtable->keys[index] = key;
    hashtable->rows[index] = values;
    hashtable->size++;
    return index;
}

void* hashtable_get(Hashtable hashtable, char* key) {
    int index = string_hash(key, hashtable->capacity);

    int i = 1;
    while (hashtable->keys[index] != NULL) {
        if (strcmp(hashtable->keys[index], key) == 0)
            return hashtable->rows[index];
        index = (index + i * i) % hashtable->capacity;
        i++;
    }

    return NULL;
}

void* hashtable_get_by_index(Hashtable hashtable, int index) {
    return hashtable->rows[index];
}

void** hashtable_values(Hashtable hashtable) {
    void** values = malloc(sizeof(void*) * hashtable->size);
    int j = 0;
    for (int i = 0; i < hashtable->capacity; i++) {
        if (hashtable->keys[i] != NULL) {
            values[j] = hashtable->rows[i];
            j++;
        }
    }
    return values;
}

int hashtable_remove(Hashtable hashtable, char* key) {
    int index = string_hash(key, hashtable->capacity);

    int i = 1;
    while (hashtable->keys[index] != NULL) {
        if (strcmp(hashtable->keys[index], key) == 0) {
            hashtable->keys[index] = NULL;
            hashtable->rows[index] = NULL;
            hashtable->size--;
            return index;
        }
        index = (index + i * i) % hashtable->capacity;
        i++;
    }

    return -1;
}

void hashtable_print(Hashtable hashtable) {
    printf("Hashtable:\n");
    for (int i = 0; i < hashtable->capacity; i++) {
        printf("%d: ", i);
        if (hashtable->keys[i] != NULL) {
            printf("%s: ", hashtable->keys[i]);
            printf("%p ",  (void*) hashtable->rows[i]);
        }
        printf("\n");
    }
    printf("\n");
}
