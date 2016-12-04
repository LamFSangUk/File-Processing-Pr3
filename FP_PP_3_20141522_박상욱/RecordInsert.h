#ifndef __PROG_RECORDINSERT__
#define __PROG_RECORDINSERT__

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
#include<vector>

using namespace std;

extern int num_purchase;

void RecordInsert();
void MemberInsert();
void StockInsert();
void PurchaseInsert();
void PurchaseInsert(string user_id);

#endif