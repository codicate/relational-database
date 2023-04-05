#include <stdio.h>
#include "table.h"
#include "database.h"

void part1(void) {
    printf("Part One\n");
    Table TPN = create_TPN();
    Table TC = create_TC();
    Table GHVD = create_GHVD();

    char*** result1 = table_lookup(TPN, (char*[]){"Americans", "61367", "99"});
    print_query_results(TPN, result1);

    char*** result2 = table_lookup(TPN, (char*[]){"Crunch", "51213", "*"});
    print_query_results(TPN, result2);

    char*** result3 = table_lookup(TC, (char*[]){"Americans", "Toronto"});
    print_query_results(TC, result3);

    table_delete(GHVD, (char*[]){"4", "Redwings", "Maple Leafs", "6 Jan 2023"});
    print_table(GHVD);

    table_delete(GHVD, (char*[]){"*", "Redwings", "Crunch", "*"});
    print_table(GHVD);

    table_delete(GHVD, (char*[]){"*", "Americans", "*", "*"});
    print_table(GHVD);

    table_insert(TC, (char*[]){"Ice Pilots", "Pensacola"});
    print_table(TC);

    table_insert(TC, (char*[]){"Crunch", "Syracuse"});
    print_table(TC);
}

void query_one(char* name, char* team) {
//    Table PNB = create_PNB();
//    Table TPN = create_TPN();

}

void query_two(char* name, char* date) {
//    Table PNB = create_PNB();
//    Table GHVD = create_GHVD();
//    Table GPG = create_GPG();

}

void query_repl(char* parameter1, char* parameter2) {

}

void part3(void) {
    printf("Part Three\n");
    Table TPN = create_TPN();
    Table result1 = table_select(TPN, 1, (char*[]){"PlayerId", "51213"});
    print_table(result1);
}

int main(void) {
//    part1();
    part3();
}
