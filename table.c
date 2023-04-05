#include "table.h"
#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct Table {
    int num_attributes;
    char** attributes;
    int primary_attribute;
    Hashtable hashtable;
    int* max_column_widths;
};

Table table_create(int capacity, int num_attributes, int primary_attribute, char** attributes) {
    Table table = malloc(sizeof(struct Table));
    table->hashtable = hashtable_create(capacity);
    table->num_attributes = num_attributes;
    table->primary_attribute = primary_attribute;
    table->attributes = attributes;

    table->max_column_widths = malloc(sizeof(int) * num_attributes);
    for (int i = 0; i < num_attributes; i++)
        table->max_column_widths[i] = strlen(attributes[i]);

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

int table_size(Table table) {
    return hashtable_size(table->hashtable);
}

int table_capacity(Table table) {
    return hashtable_capacity(table->hashtable);
}

int table_num_attributes(Table table) {
    return table->num_attributes;
}

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

bool table_insert(Table table, char** values) {
    char* key = values[table->primary_attribute];
    if (hashtable_get(table->hashtable, key) != NULL) return false;
    hashtable_put(table->hashtable, key, values);

    for (int i = 0; i < table->num_attributes; i++) {
        int len = strlen(values[i]);
        if (len > table->max_column_widths[i])
            table->max_column_widths[i] = len;
    }

    return true;
}

char** query_row(char** row, char** query, int num_attributes) {
    for (int k = 0; k < num_attributes; k++) {
        if (strcmp(query[k], "*") != 0 && strcmp(query[k], row[k]) != 0)
            return NULL;
    }
    return row;
}

char*** table_lookup(Table table, char** query) {
    char*** result = malloc(sizeof(char**) * hashtable_size(table->hashtable));

    if (table->primary_attribute == -1 || strcmp(query[table->primary_attribute], "*") == 0) {
        int size = hashtable_size(table->hashtable);
        char*** rows = (char***) hashtable_values(table->hashtable);

        int j = 0;
        for (int i = 0; i < size; i++) {
            char** row = query_row(rows[i], query, table->num_attributes);
            if (row != NULL) {
                result[j] = row;
                j++;
            }
        }

        return result;
    } else {
        char* key = query[table->primary_attribute];
        char** row = (char **) hashtable_get(table->hashtable, key);
        if (row == NULL) return NULL;

        result[0] = row;
        return result;
    }
}

bool table_delete(Table table, char** query) {
    if (table->primary_attribute == -1 || strcmp(query[table->primary_attribute], "*") == 0) {
        int size = hashtable_size(table->hashtable);
        char*** rows = (char***) hashtable_values(table->hashtable);

        bool found = false;
        for (int i = 0; i < size; i++) {
            char** row = rows[i];
            if (query_row(row, query, table->num_attributes) != NULL) {
                found = hashtable_remove(table->hashtable, row[table->primary_attribute]);
            }
        }

        return found;
    } else {
        char* key = query[table->primary_attribute];
        return hashtable_remove(table->hashtable, key);
    }
}

void print_spacer(Table table, int i, char* value) {
    for (int j = 0; j < table->max_column_widths[i] - strlen(value); j++)
        printf(" ");
    if (i != table->num_attributes - 1) printf(" | ");
}

void table_print(Table table) {
    printf("Table with %d rows:\n", table_size(table));
    for (int i = 0; i < table->num_attributes; i++) {
        printf("%s", table->attributes[i]);
        print_spacer(table, i, table->attributes[i]);
    }
    printf("\n");

    int size = hashtable_size(table->hashtable);
    char*** rows = (char***) hashtable_values(table->hashtable);
    for (int i = 0; i < size; i++) {
        char** row = rows[i];
        for (int j = 0; j < table->num_attributes; j++) {
            printf("%s", row[j]);
            print_spacer(table, j, row[j]);
        }
        printf("\n");
    }
    printf("\n");
}
