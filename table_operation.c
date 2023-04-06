#include "table.h"
#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

char** query_row(char** row, char** query, int num_attributes) {
    for (int k = 0; k < num_attributes; k++) {
        if (strcmp(query[k], "*") != 0 && strcmp(query[k], row[k]) != 0)
            return NULL;
    }
    return row;
}

bool table_insert(Table table, char** values) {
    if (table_lookup(table, values) != NULL) return false;
    char* key = table->primary_attribute == -1 ? "*" : values[table->primary_attribute];

    char** values_copy = malloc(sizeof(char*) * table->num_attributes);
    for (int i = 0; i < table->num_attributes; i++) {
        values_copy[i] = malloc(sizeof(char) * (strlen(values[i]) + 1));
        strcpy(values_copy[i], values[i]);
    }

    hashtable_put(table->hashtable, key, values_copy);

    for (int i = 0; i < table->num_attributes; i++) {
        int len = strlen(values[i]);
        if (len > table->max_column_widths[i])
            table->max_column_widths[i] = len;
    }

    return true;
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

        if (j == 0) {
            return NULL;
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
