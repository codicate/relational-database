#include "table.h"
#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>

struct Table {
    int num_attributes;
    int total_attributes;
    char** attributes;
    TYPE* types;
    int primary_attribute;

    int num_rows;
    int total_rows;
    void*** rows;
};

Table table_create(int total_attributes, int total_rows) {
    Table table = malloc(sizeof(Table));
    table->num_attributes = 0;
    table->total_attributes = total_attributes;
    table->attributes = malloc(sizeof(char*) * total_attributes);
    table->types = malloc(sizeof(TYPE) * total_attributes);
    table->primary_attribute = -1;

    table->num_rows = 0;
    table->total_rows = total_rows;
    table->rows = malloc(sizeof(void**) * total_rows);
    return table;
}

void table_free(Table table) {
    for (int i = 0; i < table->num_attributes; i++)
        free(table->attributes[i]);
    free(table->attributes);

    for (int i = 0; i < table->num_rows; i++)
        free(table->rows[i]);
    free(table->rows);

    free(table);
}

void table_add_attribute(Table table, char* name, TYPE type) {
    if (table->num_attributes == table->total_attributes) return;
    table->attributes[table->num_attributes] = name;
    table->types[table->num_attributes] = type;
    table->num_attributes++;
}

void table_add_primary_attribute(Table table, char* name, TYPE type) {
    if (table->num_attributes == table->total_attributes) return;
    if (table->primary_attribute == -1) return;
    table->primary_attribute = table->num_attributes;
    table_add_attribute(table, name, type);
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



void table_insert(Table table, void** values) {
    void* key = values[table->primary_attribute];
    TYPE key_type = table->types[table->primary_attribute];



    table->rows[index] = values;
    table->num_rows++;
}

void print_table(Table table) {
    for (int i = 0; i < table->num_rows; i++) {
        void** row = table->rows[i];
        for (int j = 0; j < table->num_attributes; j++) {
            TYPE type = table->types[j];
            switch (type) {
                case INT:
                    printf("%d", *((int*)row[j]));
                    break;
                case STRING:
                    printf("%s", (char*)row[j]);
                    break;
            }
            printf("\t");
        }
        printf("\n");
    }
}
