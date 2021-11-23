#include "matrix.h"
#include "simplesql.h"
void Write_csv (string FileName);
string ReWrite_csv (string FileName);
void SQL_test();

int main()
{
    cout<<"start"<<endl;
    Write_csv("test");
    ReWrite_csv("test");
    SQL_test();
    cout<<"finish"<<endl;
    return 0;
}
void Write_csv (string FileName)
{
    FileName +=".csv";
    string letters_and_numbers = "0123456789abcdefghijklmnopqrstuvwxyz";
    uint n = 1024, m = 6;
    matrix<string> A(n, m);
    srand(time(NULL));
    for(uint i = 0; i < n; i++)
        for(uint j = 0; j < m; j++)
        {
            string tmp;
            for(uint k = 0; k < 8; k++)
            {
               tmp.push_back(letters_and_numbers[rand() % (letters_and_numbers.size() - 1)]);
            }
            A[i][j] = tmp;
        }
    A.WriteOnFile(FileName);
    cout<<"Done writing file: "<< FileName<<endl;
}
string ReWrite_csv (string FileName)
{
    FileName +=".csv";
    matrix<string> A, B;
    A.ReadFromFile(FileName);
    bool ok = true;
    for(uint i = 0; i < A.size().first; i++)
    {
        for(uint j = 0; j < A.size().second; j++)
        {
            string tmp = A[i][j];
            for(uint k = 0; k < tmp.size(); k++)
            {
              if(tmp[k] == '1' || tmp[k] == '3' || tmp[k] == '5' || tmp[k] == '7' || tmp[k] == '9')
                  tmp[k] = '#';

            }
            A[i][j] = tmp;

            if(tmp[0] == 'a' || tmp[0] == 'e' || tmp[0] == 'i' || tmp[0] == 'o' || tmp[0] == 'u' || tmp[0] == 'y')
                ok = false;
        }
        if(ok)
            B.push_back(A(i));
        ok = true;
    }
    B.WriteOnFile("Rewrite_" +  FileName);
    cout <<"Done rewriting file: "<< FileName<<" in file: Rewrite_" <<FileName<<endl;
    return FileName;
}

void SQL_test()
{
    const char* db = R"(.\data_base.db)";
    SimpleSQL sqr(db);
    sqr.clearTable("TEST_TABLE");
    string table = "CREATE TABLE IF NOT EXISTS TEST_TABLE("
        "ROW_INDEX  INTEGER, "
        "COLUMN1    TEXT NOT NULL, "
        "COLUMN2    TEXT NOT NULL, "
        "COLUMN3    TEXT NOT NULL, "
        "COLUMN4    TEXT NOT NULL, "
        "COLUMN5    TEXT NOT NULL, "
        "COLUMN6    TEXT NOT NULL);";

    sqr.createDB();
    sqr.createTable(table.c_str());
    matrix<string> Data;
    Data.ReadFromFile("test.csv");
    for (uint i = 0; i < Data.size().first; i++)
    {
        string DataInput = "INSERT INTO TEST_TABLE (ROW_INDEX, COLUMN1, COLUMN2, COLUMN3,"
                   " COLUMN4, COLUMN5, COLUMN6) VALUES('" + std::to_string(i) + "',";
        for(uint j = 0; j< Data.size().second; j++)
        {
            if(j != 5) DataInput += "'" + Data[i][j] + "',";
            else DataInput += "'" + Data[i][j] + "'";
        }

        DataInput+= ");";

        sqr.insertData(DataInput.c_str()); // uncomment the deleteData above to avoid duplicates
        string numbers = "0123456789";
        string DataInput2 = "DELETE FROM TEST_TABLE WHERE COLUMN2 = '" + Data[i][1] +"';";
        if(numbers.find(Data[i][1][0]) < numbers.size())
        {
            sqr.deleteData(DataInput2.c_str());
        }
    }
    string show = "SELECT * FROM TEST_TABLE;";

    sqr.showData(show.c_str());
}
