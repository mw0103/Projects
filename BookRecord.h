#pragma once
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <string.h>
#include <string>;
#pragma warning(disable : 4996)
using namespace std;


class BookRecord
{
    BookRecord* m_pLeft;
    BookRecord* m_pRight;
    BookRecord* m_pParent;
    char m_sName[128];
    long m_IStockNum;
    int m_iClassification ;
    double m_dCost;
    int m_iCount;
    friend class Book_Database;



    

public:

    BookRecord();

    void set_Left(BookRecord* br);
    void set_Right(BookRecord* br);
    void set_Parent(BookRecord* br);
    long getStockNum();
    void getName(char* name);
    void setName(const char* name);
    void setStockNum(long sn);
    void getClassification(int& cl);
    void setClassification(int cl);
    void getCost(double* c);
    void setCost(double c);
    int getNumberInStock();
    void setNumberInStock(int count);
    void printRecord();


    BookRecord(const char* name, long sn, int cl, double cost);

};
 
