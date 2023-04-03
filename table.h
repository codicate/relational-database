#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

typedef struct Table* Table;

Table table_create(int num_attributes, int num_rows);

void table_free(Table table);

void table_add_attribute(Table table, char* name, TYPE type);

void table_add_primary_attribute(Table table, char* name, TYPE type);

void print_schema(Table table);

void table_insert(Table table, void** values);

#endif //DATABASE_TABLE_H
