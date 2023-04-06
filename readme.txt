CSC173
Project 4 (Relational Data Mode)

Henry Liu
hliu68@u.rochester.edu

Suchith Hegde
shegde@u.rochester.edu

Info:

This is the implementation of a generic relational database. The database table is designed to take in any schema with
string data types, and supports single table operations such as insert, lookup, and delete, as well as relational algebra
operations such as select, project, and join. The table is implemented using a hashtable that uses primary index, if it
exists, as keys for hashing, and store the rows as values.


For myself:

cd "/mnt/c/Users/codicate/OneDrive/Desktop/school/CSC 173/relational-database"


Building the project:

gcc -std=c99 -pedantic -Wall -Werror -o database *.c


Running the project:

./database