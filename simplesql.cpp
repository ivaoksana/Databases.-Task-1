#include "simplesql.h"

SimpleSQL::SimpleSQL(const char * DB_name)
{
    _DB_name = new char;
    _DB_name = DB_name;
    _table = new char;

}
SimpleSQL::~SimpleSQL()
{
    _DB_name = nullptr;
    _table = nullptr;

}
bool SimpleSQL::createDB()
{
    sqlite3* DB;
    int exit = sqlite3_open(_DB_name, &DB);
    sqlite3_close(DB);
    if (!exit) return true;
    else return false;
}
bool SimpleSQL::createTable(const char* table_structure)
{
    sqlite3 *DB;
    char* messageError;
    try
    {
        int exit = sqlite3_open(_DB_name, &DB);
        exit = sqlite3_exec(DB, table_structure, NULL, 0, &messageError);
        if (exit != SQLITE_OK)
        {
            cerr << "Error in creating a Table." << endl;
            sqlite3_free(messageError);
        }
        sqlite3_close(DB);
    }
    catch (const exception& e)
    {
        cerr << e.what();
    }
    if (!exit) return true;
    else return false;
}
bool SimpleSQL::insertData(const char* DataInput)
{
    sqlite3* DB;
    char* messageError;

    int exit = sqlite3_open(_DB_name, &DB);
    exit = sqlite3_exec(DB, DataInput, NULL, 0, &messageError);
    sqlite3_close(DB);
    if (exit != SQLITE_OK) {
        cerr << "Error in insertData function." << endl;
        sqlite3_free(messageError);
        return false;
    }
    else return true;
}

bool SimpleSQL::deleteData(const char *DataInput)
{
    sqlite3* DB;
    char* messageError;
    int exit = sqlite3_open(_DB_name, &DB);

    exit = sqlite3_exec(DB, DataInput, callback, NULL, &messageError);
    sqlite3_close(DB);
    if (exit != SQLITE_OK) {
        cerr << "Error in deleteData function." << endl;
        sqlite3_free(messageError);
        return false;
    }
    else
        return true;
}

bool SimpleSQL::clearTable(const char *TableName)
{

    string str = "DELETE FROM'" + string(TableName) +"';";
    return deleteData(str.c_str());
}
bool SimpleSQL::showData(const char *DataInput)
{
    sqlite3* DB;
    char* messageError;

    int exit = sqlite3_open(_DB_name, &DB);
    exit = sqlite3_exec(DB, DataInput, callback, NULL, &messageError);
    sqlite3_close(DB);
    if (exit != SQLITE_OK)
    {
        cerr << "Error in selectData function." << endl;
        sqlite3_free(messageError);
        return false;
    }
    else
        return true;
}

// retrieve contents of database used by showData()
/* argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array, */
int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++) {
        // column name and value
        cout << azColName[i] << ": " << argv[i]<<endl;
    }

    cout << endl;

    return 0;
}

