#ifndef TABLE_H_
#define TABLE_H_

#include <span>
#include <string>
#include "column.h"

// Both tables and rows will need simple interfaces to be parsed
// from and to b-trees that will allow to perform fast operations
// on data
// Read, Write operations themselves will suffice without these
// data projections

struct row{

};

struct table{
    std::string name;
    std::span<std::unique_ptr<column>> columns;
    std::span<std::unique_ptr<row>> rows;
};

#endif