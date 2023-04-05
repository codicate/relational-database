#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include <stdbool.h>

typedef enum {
    INT,
    STRING,
} TYPE;

typedef struct Table* Table;

Table table_create(int capacity, int num_attributes, int primary_attribute, char** attributes);

//void table_free(Table table);

int table_size(Table table);

int table_capacity(Table table);

int table_num_attributes(Table table);

//void table_add_attribute(Table table, char* name, TYPE type);
//
//void table_add_primary_attribute(Table table, char* name, TYPE type);

void print_schema(Table table);

bool table_insert(Table table, char** values);

char*** table_lookup(Table table, char** values);

bool table_delete(Table table, char** query);

void print_table(Table table);

void print_query_results(Table table, char*** results);

#endif //DATABASE_TABLE_H
