#include <stdio.h>
#include <string.h>
#include "table.h"
#include "database.h"

void query_one(char* name, char* team) {
    Table PNB = create_PNB();
    Table TPN = create_TPN();
    // What Number did Name wear when playing for Team?
    char*** PNBRows = table_lookup(PNB, (char*[]){"*", "*", "*"});
    // (1) for each tuple; t in PNB do
    for (int i = 0; i < table_size(PNB); i++) {
        // look through the PNBRows
        char** t = (char **) PNBRows[i];
        // (2) if t has name in its Name component then begin
        if (strcmp(t[1], name) == 0) {
            // (3) let i be the PlayerId component of tuple t;
            char *player_id = t[0];
            // (4) for each tuple s in TPN do
            char*** TPNRows = table_lookup(TPN, (char*[]){"*", "*", "*"});
            for (int j = 0; j < table_size(TPN); j++) {
                char** s = (char **) TPNRows[j];
                // (5) if s has team component and PlayerId component i then
                if (strcmp(s[0], team) == 0 && strcmp(s[1], player_id) == 0) {
                    // (6) print the Grade component of tuple s;
                    printf("%s played for %s and wore number %s\n", name, team, s[2]);
                }
            }
        }
    }
}

void query_two(char* name, char* date) {
    Table PNB = create_PNB();
    Table GPG = create_GPG();
    Table GHVD = create_GHVD();
    // How many goals did Name score on Date?
    char*** PNBRows = table_lookup(PNB, (char*[]){"*", "*", "*"});
    // (1) using the index on Name, find each tuple in the PNB with Name
    for (int i = 0; i < table_size(PNB); i++) {
        char** t = (char **) PNBRows[i];
        // (2) if t has name in its Name component then begin
        if (strcmp(t[1], name) == 0) {
            // (3) let i be the PlayerId component of tuple t;
            char *player_id = t[0];
            // (4) for each tuple s in GPG do
            char*** GPGRows = table_lookup(GPG, (char*[]){"*", "*", "*"});
            for (int j = 0; j < table_size(GPG); j++) {
                char** s = (char **) GPGRows[j];
                // (5) if s has PlayerId component i then
                if (strcmp(s[1], player_id) == 0) {
                    // (6) let i be the GameId component of tuple s;
                    char *game_id = s[0];
                    // (7) for each tuple r in GHVD do
                    char*** GHVDRows = table_lookup(GHVD, (char*[]){"*", "*", "*", "*"});
                    for (int k = 0; k < table_size(GHVD); k++) {
                        char** r = (char **) GHVDRows[k];
                        // (8) if r has GameId component i and Date component Date then
                        if (strcmp(r[0], game_id) == 0 && strcmp(r[3], date) == 0) {
                            // (9) print the Goals component of tuple r;
                            printf("%s scored %s goals on %s\n", name, s[2], date);
                        }
                    }
                }
            }
        }
    }
}

void query_one_repl(void) {
    char name[20];
    char team[20];
    char c[2];

    printf("\nQuery One: What Number did Name wear when playing for Team?\n");
    // Run in a loop and ask if the user wants to continue or stop
    // ask the user for name and team using fgets (remove the newline)
    while (1) {
        printf("Enter a name:");
        fgets(name, 20, stdin);
        name[strcspn(name, "\r\n")] = 0;
        printf("Enter a team:");
        fgets(team, 20, stdin);
        team[strcspn(team, "\r\n")] = 0;
        query_one(name, team);
        printf("\nContinue? (y/n):");
        fgets(c, 2, stdin);
        c[strcspn(c, "\r\n")] = 0;
        fflush(stdin);
        if (strcmp(c, "n") == 0) {
            break;
        }
    }
}

void query_two_repl(void) {
    char name[20];
    char date[20];
    char c[2];

    printf("\nQuery Two: How many goals did Name score on Date?\n");
    // Run in a loop and ask if the user wants to continue or stop
    // ask the user for name and date using fgets (remove the newline)
    while (1) {
        printf("Enter a name:");
        fgets(name, 20, stdin);
        name[strcspn(name, "\r\n")] = 0;
        printf("Enter a date:");
        fgets(date, 20, stdin);
        date[strcspn(date, "\r\n")] = 0;
        query_two(name, date);
        printf("\nContinue? (y/n):");
        fgets(c, 2, stdin);
        c[strcspn(c, "\r\n")] = 0;
        fflush(stdin);
        if (strcmp(c, "n") == 0) {
            break;
        }
    }
}