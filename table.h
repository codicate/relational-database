#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

typedef enum {
    INT,
    STRING,
} TYPE;

typedef struct Table* Table;

Table table_create(int capacity, int num_attributes, int primary_attribute, char** attributes);

//void table_free(Table table);

//void table_add_attribute(Table table, char* name, TYPE type);
//
//void table_add_primary_attribute(Table table, char* name, TYPE type);

void print_schema(Table table);

void table_insert(Table table, char** values);

void table_print(Table table);

#endif //DATABASE_TABLE_H
