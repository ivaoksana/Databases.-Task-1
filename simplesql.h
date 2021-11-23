#ifndef SIMPLESQL_H
#define SIMPLESQL_H
#include "matrix.h"
#include "sqlite3.h"

class SimpleSQL
{
private:
    const char* _DB_name;
    const char* _table;
public:
    SimpleSQL(const char* _DB_name);
    ~SimpleSQL();
    bool createDB();
    bool createTable(const char* table_structure);
    bool deleteData(const char* DataInput);
    bool insertData(const char* DataInput);
    bool showData(const char *DataInput);
    bool clearTable(const char *TableName);

};
int callback(void* NotUsed, int argc, char** argv, char** azColName);
#endif // SIMPLESQL_H
