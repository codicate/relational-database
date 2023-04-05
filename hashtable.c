#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Hashtable {
    int size;
    int capacity;
    char** keys;
    void** rows;
};

Hashtable hashtable_create(int capacity) {
    Hashtable hashtable = malloc(sizeof(struct Hashtable));

    hashtable->size = 0;
    hashtable->capacity = capacity;
    hashtable->keys = malloc(sizeof(char*) * capacity);
    hashtable->rows = malloc(sizeof(void*) * capacity);

    for (int i = 0; i < capacity; i++) {
        hashtable->keys[i] = NULL;
        hashtable->rows[i] = NULL;
    }

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

int string_hash(Hashtable hashtable, const char* key) {
    if (strcmp(key, "*") == 0)
        return hashtable->size;

    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
        hash += key[i];
    return hash % hashtable->capacity;
}

int hashtable_put(Hashtable hashtable, char* key, void* values) {
    if (hashtable->size == hashtable->capacity) return -1;
    if (hashtable_contains(hashtable, key)) return -1;
    int index = string_hash(hashtable, key);

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
    int index = string_hash(hashtable, key);

    if (index < 0) {
        printf("index < 0\n");
    }

    int i = 1;
    while (hashtable->keys[index] != NULL) {
        if (index == -1) {
            return NULL;
        }
        if (strcmp(hashtable->keys[index], key) == 0)
            return hashtable->rows[index];
        index = (index + i * i) % hashtable->capacity;
        i++;
    }

    return NULL;
}

bool hashtable_contains(Hashtable hashtable, char* key) {
    return hashtable_get(hashtable, key) != NULL;
}

void* hashtable_get_by_index(Hashtable hashtable, int index) {
    return hashtable->rows[index];
}

char** hashtable_keys(Hashtable hashtable) {
    char** keys = malloc(sizeof(char*) * hashtable->size);
    int j = 0;
    for (int i = 0; i < hashtable->capacity; i++) {
        if (hashtable->keys[i] != NULL) {
            keys[j] = hashtable->keys[i];
            j++;
        }
    }
    return keys;
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

bool hashtable_remove(Hashtable hashtable, char* key) {
    int index = string_hash(hashtable, key);

    int i = 1;
    while (hashtable->keys[index] != NULL) {
        if (strcmp(hashtable->keys[index], key) == 0) {
            hashtable->keys[index] = NULL;
            hashtable->rows[index] = NULL;
            hashtable->size--;
            return true;
        }
        index = (index + i * i) % hashtable->capacity;
        i++;
    }

    return false;
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

Hashtable hashtable_union(Hashtable left, Hashtable right) {
    Hashtable union_table = hashtable_create(left->capacity + right->capacity);

    for (int i = 0; i < left->capacity; i++) {
        if (left->keys[i] != NULL)
            hashtable_put(union_table, left->keys[i], left->rows[i]);
    }

    for (int i = 0; i < right->capacity; i++) {
        if (right->keys[i] != NULL)
            hashtable_put(union_table, right->keys[i], right->rows[i]);
    }

    return union_table;
}

Hashtable hashtable_intersection(Hashtable left, Hashtable right) {
    Hashtable intersection_table = hashtable_create(left->capacity + right->capacity);

    for (int i = 0; i < left->capacity; i++) {
        if (left->keys[i] != NULL && hashtable_contains(right, left->keys[i]))
            hashtable_put(intersection_table, left->keys[i], left->rows[i]);
    }

    return intersection_table;
}

Hashtable hashtable_difference(Hashtable left, Hashtable right) {
    Hashtable difference_table = hashtable_create(left->capacity + right->capacity);

    for (int i = 0; i < left->capacity; i++) {
        if (left->keys[i] != NULL && !hashtable_contains(right, left->keys[i]))
            hashtable_put(difference_table, left->keys[i], left->rows[i]);
    }

    return difference_table;
}