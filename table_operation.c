#include "table.h"
#include "hashtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool table_insert(Table table, char** values) {
    // check if the row already exists
    if (table_lookup(table, values, false) != NULL) return false;

    // if the table does not have a primary attribute, use a dummy key and insert without hashing
    char* key = table->primary_attribute == -1 ? "*" : values[table->primary_attribute];

    // Save a copy of the attributes string array to prevent them being deallocated when it's out of scope/block
    char** values_copy = malloc(sizeof(char*) * table->num_attributes);
    for (int i = 0; i < table->num_attributes; i++) {
        values_copy[i] = malloc(sizeof(char) * (strlen(values[i]) + 1));
        strcpy(values_copy[i], values[i]);
    }

    hashtable_put(table->hashtable, key, values_copy);

    // recalculate the maximum width of each column for print formatting
    for (int i = 0; i < table->num_attributes; i++) {
        int len = strlen(values[i]);
        if (len > table->max_column_widths[i])
            table->max_column_widths[i] = len;
    }

    return true;
}

// loop through all the values of a row. If it's a wild card, ignore. Else, compare the value to the query
char** query_row(char** row, char** query, int num_attributes) {
    for (int k = 0; k < num_attributes; k++) {
        if (strcmp(query[k], "*") != 0 && strcmp(query[k], row[k]) != 0)
            return NULL;
    }
    return row;
}

char*** table_lookup(Table table, char** query, bool print) {
    char*** result = malloc(sizeof(char**) * hashtable_size(table->hashtable));
    int result_len = 0;

    // if either there's no primary attribute, or primary attribute is a wild card, loop through all the rows
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

        result_len = j;
        if (j == 0)  {
            if(print) printf("No results found.\n\n");
            return NULL;
        }

    // if primary attribute is specified, use it as the key for constant time hash table look up
    } else {
        char* key = query[table->primary_attribute];
        char** row = (char **) hashtable_get(table->hashtable, key);
        if (row == NULL) {
            if(print) printf("No results found.\n\n");
            return NULL;
        }

        result[0] = row;
        result_len = 1;
    }

    if (print) {
        printf("Querying: {");
        for (int i = 0; i < table->num_attributes; i++) {
            printf("%s", query[i]);
            if (i < table->num_attributes - 1)
                printf(", ");
        }
        printf("}\n");

        int num_columns = table_num_attributes(table);
        for (int i = 0; i < result_len; i++) {
            for (int j = 0; j < num_columns; j++) {
                printf("%s", result[i][j]);
                if (j < num_columns - 1)
                    printf(", ");
            }
            printf("\n");
        }
        printf("\n");
    }

    return result;
}

bool table_delete(Table table, char** query) {
    // if either there's no primary attribute, or primary attribute is a wild card, loop through all the rows
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
