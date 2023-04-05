#include "database.h"
#include "table.h"

Table create_PNB(void) {
    Table PNB = table_create(50, 3, 0, (char*[]){"PlayerId", "Name", "BirthDate"});

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

    return PNB;
}

Table create_TPN(void) {
    Table TPN = table_create(50, 3, -1, (char*[]){"Team", "PlayerId", "Number"});

    table_insert(TPN, (char*[]){"Americans", "87977", "11"});
    table_insert(TPN, (char*[]){"Americans", "75196", "7"});
    table_insert(TPN, (char*[]){"Americans", "61367", "99"});
    table_insert(TPN, (char*[]){"Maple Leafs", "75196", "7"});
    table_insert(TPN, (char*[]){"Maple Leafs", "20945", "24"});
    table_insert(TPN, (char*[]){"Redwings", "70513", "10"});
    table_insert(TPN, (char*[]){"Redwings", "20945", "10"});
    table_insert(TPN, (char*[]){"Crunch", "51213", "1"});
    table_insert(TPN, (char*[]){"Crunch", "51213", "9"});
    table_insert(TPN, (char*[]){"Crunch", "55870", "13"});

    return TPN;
}

Table create_TC(void) {
    Table TC = table_create(50, 2, 0, (char*[]){"Team", "City"});

    table_insert(TC, (char*[]){"Americans", "Rochester"});
    table_insert(TC, (char*[]){"Maple Leafs", "Toronto"});
    table_insert(TC, (char*[]){"Redwings", "Detroit"});
    table_insert(TC, (char*[]){"Crunch", "Syracuse"});

    return TC;
}

Table create_GHVD(void) {
    Table GHVD = table_create(50, 4, 0, (char*[]){"GameId", "HomeTeam", "VisitorTeam", "Date"});

    table_insert(GHVD, (char*[]){"1", "Americans", "Maple Leafs", "3 Jan 2023"});
    table_insert(GHVD, (char*[]){"2", "Crunch", "Redwings", "3 Jan 2023"});
    table_insert(GHVD, (char*[]){"3", "Americans", "Crunch", "6 Jan 2023"});
    table_insert(GHVD, (char*[]){"4", "Redwings", "Maple Leafs", "6 Jan 2023"});
    table_insert(GHVD, (char*[]){"5", "Redwings", "Americans", "8 Jan 2023"});
    table_insert(GHVD, (char*[]){"6", "Maple Leafs", "Crunch", "8 Jan 2023"});
    table_insert(GHVD, (char*[]){"7", "Maple Leafs", "Crunch", "9 Jan 2023"});
    table_insert(GHVD, (char*[]){"8", "Americans", "Redwings", "10 Jan 2023"});
    table_insert(GHVD, (char*[]){"9", "Crunch", "Americans", "12 Jan 2023"});
    table_insert(GHVD, (char*[]){"10", "Redwings", "Maple Leafs", "12 Jan 2023"});

    return GHVD;
}

Table create_GPG(void) {
    Table GPG = table_create(50, 3, -1, (char*[]){"GameId", "PlayerId", "Goals"});

    table_insert(GPG, (char*[]){"2", "55870", "1"});
    table_insert(GPG, (char*[]){"2", "70513", "2"});
    table_insert(GPG, (char*[]){"3", "51213", "1"});
    table_insert(GPG, (char*[]){"5", "20945", "4"});
    table_insert(GPG, (char*[]){"6", "55870", "2"});
    table_insert(GPG, (char*[]){"7", "75196", "1"});
    table_insert(GPG, (char*[]){"8", "87977", "1"});
    table_insert(GPG, (char*[]){"8", "75196", "2"});
    table_insert(GPG, (char*[]){"9", "55870", "3"});
    table_insert(GPG, (char*[]){"9", "61367", "2"});

    return GPG;
}
