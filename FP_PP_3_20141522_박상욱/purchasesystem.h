#ifndef __PROG_PURCHASESYSTEM__
#define __PROG_PURCHASESYSTEM__

#include<iostream>
#include<string>
#include<map>
#include<vector>
#include"class_member.h"
#include"conio.h"
#include "btree.h"
#include "btree.cpp"

using namespace std;

void purchasesystem();
void AdminMode();
void UserMode(string);
void PurchaseUser(string user_id);
void MyInfoAdmin(string user_id);
void MemberFileCompaction();
void StockFileCompaction();
void PurchaseFileCompaction();

extern map<string,int> Purchasemap;
extern map<string, vector<int> > PMwithMember, PMwithStock;

extern bool keymap[128];
extern BTree <char> bt;

#endif