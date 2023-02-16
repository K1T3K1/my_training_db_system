#ifndef TABLE_H_
#define TABLE_H_

// Both tables and rows will need simple interfaces to be parsed
// from and to b-trees that will allow to perform fast operations
// on data
// Read, Write operations themselves will suffice without these
// data projections

struct table_interface{

};

struct table : table_interface{

};

struct row_interface{

};

struct row : row_interface{

};

#endif