# relational-database

This is the implementation of a generic relational database. The database table is designed to take in any schema with
string data types, and supports single table operations such as insert, lookup, and delete, as well as relational algebra
operations such as select, project, and join. The table is implemented using a hashtable that uses primary index, if it
exists, as keys for hashing, and store the rows as values.


### Building the project:

```bash
gcc -std=c99 -pedantic -Wall -Werror -o database *.c
```

### Running the project:

```bash
./database
```
