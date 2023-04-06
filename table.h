#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include <stdbool.h>
#include "hashtable.h"

typedef enum {
    INT,
    STRING,
} TYPE;

struct Table {
    int num_attributes;
    int primary_attribute;
    char** attributes;
    Hashtable hashtable;
    int* max_column_widths;
};

typedef struct Table* Table;

Table table_create(int capacity, int num_attributes, int primary_attribute, char** attributes);

//void table_free(Table table);

int table_size(Table table);

int table_capacity(Table table);

int table_num_attributes(Table table);

//void table_add_attribute(Table table, char* name, TYPE type);
//
//void table_add_primary_attribute(Table table, char* name, TYPE type);

char*** table_values(Table table);

void print_schema(Table table);

void print_table(Table table);

void print_query_results(Table table, char*** results);

bool table_insert(Table table, char** values);

char*** table_lookup(Table table, char** values);

bool table_delete(Table table, char** query);

Table table_select(Table table, int query_pair_len, char** select_query);

Table table_project(Table table, int num_attributes, char** attributes);

Table table_natural_join(Table left, Table right);

#endif //DATABASE_TABLE_H
