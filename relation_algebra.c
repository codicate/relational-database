#include "table.h"
#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

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

Table table_project(Table table, int num_attributes, char** attributes) {
    char*** rows = table_values(table);
    if (rows == NULL) return NULL;

    int valid_attributes = 0;
    int* attribute_index = malloc(sizeof(int) * num_attributes);
    for (int i = 0; i < num_attributes; i++) {
        for (int j = 0; j < table->num_attributes; j++) {
            if (strcmp(attributes[i], table->attributes[j]) == 0) {
                attribute_index[valid_attributes] = j;
                valid_attributes++;
            }
        }
    }

    if (valid_attributes == 0) return NULL;
    Table result = table_create(hashtable_capacity(table->hashtable), num_attributes, -1, attributes);

    for (int i = 0; i < table_size(table); i++) {
        char** row = malloc(sizeof(char*) * valid_attributes);

        for (int j = 0; j < valid_attributes; j++) {
            row[j] = malloc(sizeof(char) * (strlen(rows[i][attribute_index[j]]) + 1));
            strcpy(row[j], rows[i][attribute_index[j]]);
        }

        table_insert(result, row);
    }
    return result;
}

Table table_natural_join(Table left, Table right) {
    Hashtable left_attributes = hashtable_create(left->num_attributes);
    for (int i = 0; i < left->num_attributes; i++)
        hashtable_put(left_attributes, left->attributes[i], "*");

    Hashtable right_attributes = hashtable_create(right->num_attributes);
    for (int i = 0; i < right->num_attributes; i++)
        hashtable_put(right_attributes, right->attributes[i], "*");

    Hashtable common_attributes = hashtable_intersection(left_attributes, right_attributes);
    if (hashtable_size(common_attributes) == 0) return NULL;

    Hashtable right_unique_attributes = hashtable_difference(right_attributes, common_attributes);
    int new_attributes_len = hashtable_size(left_attributes) + hashtable_size(right_unique_attributes);
    char** new_attributes = malloc(sizeof(char*) * new_attributes_len);
    for (int i = 0; i < hashtable_size(left_attributes); i++)
        new_attributes[i] = left->attributes[i];
    for (int i = 0; i < hashtable_size(right_unique_attributes); i++)
        new_attributes[hashtable_size(left_attributes) + i] = hashtable_keys(right_unique_attributes)[i];

    Table result = table_create(hashtable_capacity(left->hashtable) * hashtable_capacity(right->hashtable), new_attributes_len, -1, new_attributes);
    Table lookup_table = table_project(left, hashtable_size(common_attributes), hashtable_keys(common_attributes));
    char*** left_rows = table_values(left);

    char*** lookup_values = table_values(lookup_table);
    for (int i = 0; i < table_size(left); i++) {
        char** lookup_row = lookup_values[i];
        char** attribute_names = hashtable_keys(common_attributes);
        char** query = malloc(sizeof(char*) * hashtable_size(common_attributes) * 2);
        for (int j = 0; j < hashtable_size(common_attributes); j++) {
            query[j*2] = attribute_names[j];
            query[j*2+1] = lookup_row[j];
        }

        Table query_result = table_select(right, hashtable_size(common_attributes) * 2, query);
        if (query_result == NULL) continue;

        Table projected_result = table_project(query_result, hashtable_size(right_unique_attributes), hashtable_keys(right_unique_attributes));
        char*** projected_values = table_values(projected_result);

        for (int j = 0; j < table_size(projected_result); j++) {
            char** projected_row = projected_values[j];
            char** new_row = malloc(sizeof(char*) * new_attributes_len);

            int k = 0;
            while (k < hashtable_size(left_attributes)) {
                new_row[k] = malloc(sizeof(char) * (strlen(left_rows[i][k]) + 1));
                strcpy(new_row[k], left_rows[i][k]);
                k++;
            }

            int l = 0;
            while (l < hashtable_size(right_unique_attributes)) {
                new_row[k] = malloc(sizeof(char) * (strlen(projected_row[l]) + 1));
                strcpy(new_row[k], projected_row[l]);
                k++;
                l++;
            }

            table_insert(result, new_row);
        }
    }

    return result;
}
