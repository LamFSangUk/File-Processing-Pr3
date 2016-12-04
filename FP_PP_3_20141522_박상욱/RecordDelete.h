#ifndef __PROG_RECORDDELETE__
#define __PROG_RECORDDELETE_

#include "class_member.h"
#include "class_stock.h"
#include "class_purchase.h"
#include "recfile.h"
#include "delim.h"
#include "textind.h"
#include "tindbuff.h"
#include "indfile.h"
#include "buffile.h"
#include <conio.h>
#include <map>
#include <vector>

using namespace std;

extern int num_purchase;
extern int TotalMemberDelSize;
extern int TotalStockDelSize;
extern int TotalPurchaseDelSize;


void RecordDelete();
void MemberDelete();
void MemberDelete(string id);
void StockDelete();
void PurchaseDelete();
void PurchaseDelete(string id);

#endif