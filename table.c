#include "table.h"
#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>

struct Table {
    int num_attributes;
    char** attributes;
    int primary_attribute;
    Hashtable hashtable;
};

Table table_create(int capacity, int num_attributes, int primary_attribute, char** attributes) {
    Table table = malloc(sizeof(struct Table));
    table->hashtable = hashtable_create(capacity);
    table->num_attributes = num_attributes;
    table->primary_attribute = primary_attribute;
    table->attributes = attributes;
    return table;
}

//void table_free(Table table) {
//    for (int i = 0; i < table->num_attributes; i++)
//        free(table->attributes[i]);
//    free(table->attributes);
//
//    for (int i = 0; i < table->num_rows; i++)
//        free(table->rows[i]);
//    free(table->rows);
//
//    free(table);
//}

void print_schema(Table table) {
    printf("Table schema:\n");
    for (int i = 0; i < table->num_attributes; i++) {
        printf("%s", table->attributes[i]);
        if (i == table->primary_attribute)
            printf(" (primary)");
        printf("\n");
    }
    printf("\n");
}

void table_insert(Table table, char** values) {
    char* key = values[table->primary_attribute];
    if (hashtable_get(table->hashtable, key) != NULL) return;
    hashtable_put(table->hashtable, key, values);
}

void table_print(Table table) {
    printf("Table contents:\n");
    for (int i = 0; i < table->num_attributes; i++) {
        printf("%s", table->attributes[i]);
        printf("\t\t");
    }
    printf("\n");

    int capacity = hashtable_capacity(table->hashtable);
    for (int i = 0; i < capacity; i++) {
        char** row = (char **) hashtable_get_by_index(table->hashtable, i);
        if (row == NULL) continue;

        for (int j = 0; j < table->num_attributes; j++) {
            printf("%s", row[j]);
            printf("\t\t");
        }
        printf("\n");
    }
    printf("\n");
}
