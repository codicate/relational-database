#include <stdio.h>
#include "table.h"
#include "database.h"
#include "part2.h"

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

void part2(void) {
    query_one_repl();
    query_two_repl();
}

void part3(void) {
    printf("Part Three\n");
    Table TPN = create_TPN();

    printf("All TPN tuples with player ID equals 51213:\n");
    Table result1 = table_select(TPN, 1, (char*[]){"PlayerId", "51213"});
    print_table(result1);

    printf("Teams of players with player ID equals 51213:\n");
    Table result2 = table_project(result1, 1, (char*[]){"Team"});
    print_table(result2);

    printf("A table of Games in GHVD that also have a player id and goals in GPG:\n");
    Table GHVD = create_GHVD();
    Table GPG = create_GPG();
    Table result3 = table_natural_join(GHVD, GPG);
    print_table(result3);

    printf("The player ID and goals of all games on 8 Jan 2023:\n");
    Table result4 = table_select(result3, 1, (char*[]){"Date", "8 Jan 2023"});
    Table result5 = table_project(result4, 2, (char*[]){"PlayerId", "Goals"});
    print_table(result5);
}

int main(void) {
    part1();
    part2();
    part3();
    return 0;
}
