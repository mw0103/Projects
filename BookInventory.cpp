#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Book_Database.h"


using namespace std;


//--------------------------------------------
// Function: getNextLine() 
// Purpose:  Read a line from a data file.
//   The next non-comment line read from file
//   is stored in line char array.
//   An empty string is stored if the end of
//   file is reached.
// Returns: bool - true if a valid line was
//   read, false if end of file is reached. 
//--------------------------------------------
bool Book_Database::getNextLine(char* line, int lineLen)
{
    int    done = false;
    while (!done)
    {
        m_InFile.getline(line, lineLen);

        if (m_InFile.good())    // If a line was successfully read
        {
            if (strlen(line) == 0)  // Skip any blank lines
                continue;
            else if (line[0] == '#')  // Skip any comment lines
                continue;
            else return true;    // Got a valid data line so return with this line
        }
        else // No valid line read, meaning we reached the end of file
        {
            strcpy(line, ""); // Copy empty string into line as sentinal value
            return false;
        }
    } // end while
    return false; // Cannot reach this point but include a return to avoid compiler warning
                  //   that not all paths return a value.
}

Book_Database::Book_Database()
{
    m_pRoot = nullptr;
    size = 0;
    sentinel = false;
}

Book_Database::~Book_Database()
{
    ClearList(m_pRoot);
}

//--------------------------------------------
// Function: readDatabase()
// Purpose: Read the inventory data file and
//		build the list.
// Returns: True if successful read
//--------------------------------------------
bool Book_Database::readDatabase(const char* filename)
{
    char     line[128];
    int      numBooks;
    // define other variables here as needed
    char tempname[128];
    long tempsn;
    int tempcl;
    double tempcst;
    int tempcount;
    m_InFile.open(filename, ifstream::in);
    if (!m_InFile.is_open())
    {
        // m_InFile.is_open() returns false if the file could not be found or
        //    if for some other reason the open failed.
        cout << "Unable to open file" << filename << "\nProgram terminating...\n";
        return false;
    }
    // Read number of books
    getNextLine(line, 128);
    numBooks = atoi(line);
    for (int i = 0; i < numBooks; i++)
    {
        getNextLine(line, 128);
       
        BookRecord* temp = new BookRecord;
        temp->setStockNum(atoi(line));

        getNextLine(line, 128);
        temp->setName(line);
        
        getNextLine(line, 128);
        temp->setClassification(atoi(line));
        
        getNextLine(line, 128);
        temp->setCost(atof(line));

        getNextLine(line, 128);
        temp->setNumberInStock(atof(line));

        addBook(temp);
    }
    return true;
}

bool Book_Database::addBook(BookRecord* br)
{
    InsertBook(m_pRoot, br);
    return false;
}



BookRecord* Book_Database::removeBook(long stockNum)
{
    Remove(m_pRoot, stockNum);
    return nullptr;
}

void Book_Database::PrintAll(BookRecord* rt)
{   
    if (rt->m_pLeft != nullptr) {
        PrintAll(rt->m_pLeft);
    }

    rt->printRecord();

    if (rt->m_pRight != nullptr) {
        PrintAll(rt->m_pRight);
    }
}

void Book_Database::InsertBook(BookRecord*& root, BookRecord* br)
{

    if (root == nullptr) {
        char name[128];
        br->getName(name);
        root = new BookRecord;
        root->m_iClassification = br->m_iClassification;
        root->m_dCost = br->m_dCost;
        root->setName(name);
        root->m_iCount = br->m_iCount;
        root->m_IStockNum = br->m_IStockNum;
        //m_pRoot = root;


        root->m_pLeft = nullptr;
        root->m_pRight = nullptr;

        size++;
    }
    else {
        if (root->getStockNum() > br->getStockNum()) {
            InsertBook(root->m_pLeft, br);
        }

        else {
            InsertBook(root->m_pRight, br);
        }
    }
}

void Book_Database::searchByStockNumber(long sn, BookRecord* br)
{
    if (sentinel) {
        return;
    }

    if (sn == br->m_IStockNum) {
        br->printRecord();
        sentinel = true;
        m_found = br;
        return;
    }

    else {
        if (br->m_pLeft != nullptr) {
            searchByStockNumber(sn, br->m_pLeft);
        }

        if (br->m_pRight != nullptr) {
            searchByStockNumber(sn, br->m_pRight);
        }
    }
    
    
}

void Book_Database::DeleteNode(BookRecord*& br)
{
    char name[128];
    BookRecord* temp;
    BookRecord* data;

    data = new BookRecord;

    
    temp = br;
    if (br->m_pLeft == nullptr) {
        br = br->m_pRight;
        delete temp;
    }
    else if (br->m_pRight == nullptr) {
        br = br->m_pLeft;
        delete temp;
    }
    else {
        GetPredecessor(br->m_pLeft, data);
        br->m_dCost = data->m_dCost;
        br->m_iClassification = data->m_iClassification;
        br->m_iCount = data->m_iCount;
        br->m_IStockNum = data->m_IStockNum;
        data->getName(name);
        br->setName(name);
        Remove(br->m_pLeft, data->m_IStockNum);
    }
}

void Book_Database::Remove(BookRecord*& br, long sn)
{
    if (sn < br->m_IStockNum && br->m_pLeft != nullptr) {
        Remove(br->m_pLeft, sn);
    }
    else if (sn > br->m_IStockNum && br->m_pRight != nullptr) {
        Remove(br->m_pRight, sn);
    }
    else {
        DeleteNode(br);
    }
}

void Book_Database::GetPredecessor(BookRecord* br, BookRecord*& tr)
{
    char name[128];
    while (br->m_pRight != nullptr) {
        br = br->m_pRight;
    }

    br->getName(name);
    tr->setName(name);
    tr->m_dCost = br->m_dCost;
    tr->m_iCount = br->m_iCount;
    tr->m_iClassification = br->m_iClassification;
    tr->m_IStockNum = br->m_IStockNum;

}

int Book_Database::getNumInStock(BookRecord* br, long sn)
{
    if (sentinel) {
        return numinstock;
    }

    if (br->m_IStockNum == sn) {
        cout << br->m_iCount;
        numinstock = br->m_iCount;
        sentinel = true;
        return numinstock;
    }

    if (br->m_pLeft != nullptr) {
        getNumInStock(br->m_pLeft, sn);
    }

    if (br->m_pRight != nullptr) {
        getNumInStock(br->m_pRight, sn);
    }
}



void Book_Database::searchByCost(double min, double max, BookRecord* rt)
{
    if ((rt != nullptr) && (rt->m_dCost >= min) && (rt->m_dCost <= max)) {
        rt->printRecord();
        sentinel = true;
    }
    
    if (rt->m_pLeft != nullptr) {
        searchByCost(min, max, rt->m_pLeft);
    }

    
    if (rt->m_pRight != nullptr) {
        searchByCost(min, max, rt->m_pRight);
    }
}

void Book_Database::searchByClassification(int cl, BookRecord* rt)
{
    if ((rt != nullptr) && (rt->m_iClassification == cl)) {
        rt->printRecord();
        sentinel = true;

    }

    if (rt->m_pLeft != nullptr) {
        searchByClassification(cl, rt->m_pLeft);
    }    
    if (rt->m_pRight != nullptr) {
        searchByClassification(cl, rt->m_pRight);
    }
}

void Book_Database::ClearList(BookRecord* rt)
{
    if (rt != nullptr) {
        delete rt;
    }
    
    else {
        if (rt->m_pLeft != nullptr) {
            ClearList(rt->m_pLeft);
        }
        if (rt->m_pRight != nullptr) {
            ClearList(rt->m_pRight);
        }
    }
}

BookRecord* Book_Database::searchByStockNumber(long stockNum)
{
    sentinel = false;
    m_found = nullptr;

    searchByStockNumber(stockNum, m_pRoot);
    if (sentinel) {
        return m_found;
    }

    else {
        cout << "No Book" << endl;
        return nullptr;
    }
}

void Book_Database::searchByClassification(int cl)
{
    sentinel = false;
    searchByClassification(cl, m_pRoot);
    if (!sentinel) {
        cout << "Book not found!" << endl;
    }
}

void Book_Database::searchByCost(double min, double max)
{
    sentinel = false;
    searchByCost(min, max, m_pRoot);

    if (!sentinel) {
        cout << "Book not found!" << endl;
    }
}

int Book_Database::getNumInStock(long sn)
{
    numinstock = 0;
    sentinel = false;
    getNumInStock(m_pRoot, sn);
    if (!sentinel) {
        cout << "Book not Found!" << endl;
    }
    return numinstock;
}

void Book_Database::PrintAll()
{
    PrintAll(m_pRoot);
}

