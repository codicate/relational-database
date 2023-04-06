#include "table.h"
#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * This is a simple table implementation that uses a hashtable to store the rows.
 * The hashtable is indexed by the primary key, and the value is a pointer to the row.
 * The table supports single table operations like insertion, lookup, and deletion.
 * And also relational algebra operations like projection, selection, and join.
 */
Table table_create(int capacity, int num_attributes, int primary_attribute, char** attributes) {
    Table table = malloc(sizeof(struct Table));
    table->hashtable = hashtable_create(capacity);
    table->num_attributes = num_attributes;

    // The primary attribute is the attribute that is used as the key for the hash table
    // If the primary attribute is -1, then the table is not indexed, and only linear time operations are supported
    table->primary_attribute = primary_attribute;

    // Save a copy of the attributes string array to prevent them being deallocated when it's out of scope/block
    table->attributes = malloc(sizeof(char*) * num_attributes);
    for (int i = 0; i < num_attributes; i++) {
        table->attributes[i] = malloc(sizeof(char) * (strlen(attributes[i]) + 1));
        strcpy(table->attributes[i], attributes[i]);
    }

    // Calculate the maximum width of each column for print formatting
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

// Print the schema line by line and indicates which is the primary attribute
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


char*** table_values(Table table) {
    return (char***) hashtable_values(table->hashtable);
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

    char*** rows = (char***) hashtable_values(table->hashtable);
    for (int i = 0; i < table_size(table); i++) {
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
