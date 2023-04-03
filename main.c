#include <stdio.h>
#include "table.h"

int main(void) {
    Table table = table_create(10);
    table_add_primary_attribute(table, "id");
}
