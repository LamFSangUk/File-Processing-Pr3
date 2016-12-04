#ifndef __PROG_RECORDSEARCH__
#define __PROG_RECORDSEARCH__

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

void RecordSearch();
Member MemberSearch(string id,int *flag);
Stock StockSearch(string id,int *flag);
void PurchaseSearch();
void PurchaseSearch(string id);

#endif