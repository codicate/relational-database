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
    table->attributes = malloc(sizeof(char*) * num_attributes);
    for (int i = 0; i < num_attributes; i++) {
        table->attributes[i] = malloc(sizeof(char) * (strlen(attributes[i]) + 1));
        strcpy(table->attributes[i], attributes[i]);
    }

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

void print_spacer(Table table, int i, char* value) {
    for (int j = 0; j < table->max_column_widths[i] - strlen(value); j++)
        printf(" ");
    if (i != table->num_attributes - 1) printf(" | ");
}

void print_table(Table table) {
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

void print_query_results(Table table, char*** result) {
    printf("Query result:\n");

    if (result == NULL || result[0] == NULL) {
        printf("No results found.\n");
        printf("\n");
        return;
    }

    int num_columns = table_num_attributes(table);
    for (int i = 0; result[i] != NULL; i++) {
        for (int j = 0; j < num_columns; j++) {
            printf("%s", result[i][j]);
            if (j < num_columns - 1)
                printf(", ");
        }
        printf("\n");
    }
    printf("\n");
}

Table table_select(Table table, int query_pair_len, char** select_query) {
    Table result = table_create(hashtable_capacity(table->hashtable), table->num_attributes, table->primary_attribute, table->attributes);

    char** lookup_query = malloc(sizeof(char*) * table->num_attributes);
    for (int i = 0; i < table->num_attributes; i++) {
        for (int j = 0; j < query_pair_len; j+=2) {
            char* attribute = select_query[j];
            char* value = select_query[j+1];

            if (strcmp(table->attributes[i], attribute) == 0) {
                lookup_query[i] = malloc(sizeof(char) * (strlen(value) + 1));
                strcpy(lookup_query[i], value);
            } else {
                lookup_query[i] = malloc(sizeof(char) * 2);
                strcpy(lookup_query[i], "*");
            }
        }
    }

    char*** rows = table_lookup(table, lookup_query);
    if (rows == NULL) return result;

    for (int i = 0; rows[i] != NULL; i++)
        table_insert(result, rows[i]);
    return result;
}
