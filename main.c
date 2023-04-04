#include <stdio.h>
#include <stdlib.h>
#include "table.h"
#include "hashtable.h"

void query_table(Table table, char** query) {
    char*** result = table_lookup(table, query);

    printf("Query: ");
    for (int i = 0; i < table_num_attributes(table); i++) {
        printf("%s", query[i]);
        if (i < table_num_attributes(table) - 1)
            printf(", ");
    }
    printf("\n");

    if (result == NULL || result[0] == NULL) {
        printf("No results found.\n");
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

int main(void) {
    Table PNB = table_create(50, 3, 0, (char*[]){"PlayerId", "Name", "BirthDate"});
    print_schema(PNB);

    table_insert(PNB, (char*[]){"75196", "A. Moore", "28 Aug 1985"});
    table_insert(PNB, (char*[]){"59797", "G. Jones", "26 Dec 1986"});
    table_insert(PNB, (char*[]){"87977", "U. Hughes", "13 Feb 1990"});
    table_insert(PNB, (char*[]){"20945", "Q. Morgan", "14 Feb 1998"});
    table_insert(PNB, (char*[]){"70513", "G. King", "13 Apr 1993"});
    table_insert(PNB, (char*[]){"51213", "T. Sullivan", "24 Jun 1995"});
    table_insert(PNB, (char*[]){"61367", "A. Moore", "18 Mar 2000"});
    table_insert(PNB, (char*[]){"55870", "D. Hernandez", "25 Jul 1997"});
    table_insert(PNB, (char*[]){"47087", "W. Stewart", "5 Jan 1994"});
    table_insert(PNB, (char*[]){"39468", "G. Jones", "25 Feb 1990"});

    table_print(PNB);

    query_table(PNB, (char*[]){"*", "G", "*"});
}
