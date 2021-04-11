#include "BookRecord.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <algorithm>
#pragma warning(disable : 4996)
using namespace std;

BookRecord::BookRecord() {
	for (int i = 0; i < 127; i++) {
		m_sName[i] = '\0';
	};
	m_IStockNum = 0;
	m_iClassification = 0;
	m_dCost = 0.0;
	m_iCount = 0;
	m_pLeft = nullptr;
	m_pRight = nullptr;

};
void::BookRecord::set_Left(BookRecord* br) {
	m_pLeft = br;
	
};

void::BookRecord::set_Right(BookRecord* br) {
	m_pRight = br;
}

void::BookRecord::set_Parent(BookRecord* br) {
	m_pParent = br;
}

BookRecord::BookRecord(const char *name, long sn, int cl, double cost) {

	strcpy(m_sName, name);
	m_IStockNum = sn;
	m_iClassification = cl;
	m_dCost = cost;
	m_iCount = 1;
	cout << "Your Record is being created" << endl;

}

long::BookRecord::getStockNum() {
	return m_IStockNum;
};

void::BookRecord::getName(char* name) {
	strcpy(name, m_sName);
};

void::BookRecord::setName(const char* name) {
	strcpy(m_sName, name);
};

void::BookRecord::setStockNum(long sn) {
	m_IStockNum = sn;
};

void::BookRecord::getClassification(int& cl) {
	cl = m_iClassification;
};

void::BookRecord::setClassification(int cl) {
	m_iClassification = cl;
};

void::BookRecord::getCost(double* c) {
	*c = m_dCost;
};

void::BookRecord::setCost(double c) {
	m_dCost = c;
};

int::BookRecord::getNumberInStock() {
	return m_iCount;
}

void::BookRecord::setNumberInStock(int count) {
	m_iCount = count;
}

void::BookRecord::printRecord() {
	cout << m_sName << '\t' << '\t' << m_IStockNum << '\t' << m_iClassification << '\t' << m_dCost << '\t' << m_iCount << '\t' << endl;
	

}

