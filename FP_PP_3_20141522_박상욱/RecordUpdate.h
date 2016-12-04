#ifndef __PROG_RECORDUPDATE__
#define __PROG_RECORDUPDATE_

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

void RecordUpdate();
void MemberUpdate();
void MemberUpdate(string id);
void StockUpdate();
void PurchaseUpdate();
void PurchaseUpdate(string id);

#endif