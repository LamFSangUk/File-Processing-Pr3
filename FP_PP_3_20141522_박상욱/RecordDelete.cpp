#include "RecordDelete.h"
#include "RecordSearch.h"
#include "purchasesystem.h"

void RecordDelete(){
	while (1) {
		system("cls");

		cout << " -Record-Delete----------------" << endl;
		cout << " 1. Member Records Delete" << endl;
		cout << " 2. Stock Records Delete" << endl;
		cout << " 3. Purchase Records Delete" << endl;
		cout << " 4. Exit to AdminMode" << endl;
		cout << " ------------------------------" << endl;
		cout << ">> ";

		int mode;
		cin >> mode;

		switch (mode) {
		case 1:
			MemberDelete();
			break;
		case 2:
			StockDelete();
			break;
		case 3:
			PurchaseDelete();
			break;
		case 4: return;
		default:
			cin.clear();
			break;

		}
	}
	return;
}

void MemberDelete() {
	DelimFieldBuffer buf ('|', STDMAXBUF);
	TextIndexedFile<Member> StdIdxedFile(buf, LENID,10000);
	StdIdxedFile.Open ("fileOfMember");

	cout << " Please Input your Member ID to Delete: ";

	string input;
	cin >> input;

	//MemberFile.Open("fileOfMember.dat", ios::out);

	int delSizeMem = 0;
	int delSizePur = 0;
	//int idx = Membermap[input];
	int find_flag=-1;

	Member m;
	m=MemberSearch(input,&find_flag);

	if (find_flag==-1) {
		cout << " There is Not Correct Member ID" << endl;
	}
	else {
		delSizeMem=StdIdxedFile.Delete(m);
		//Membermap.erase(input);

		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile<Purchase> PurchaseFile(buffer);

		PurchaseFile.Open("fileOfPurchase.dat", ios::out);

		int delpurchasecount = PMwithMember[input].size();
		
		for (int i = 0; i < delpurchasecount; i++) {
			int recaddr=bt.Search(PMwithMember[input][i]);
			bt.Remove(PMwithMember[input][i]);
			keymap[PMwithMember[input][i]]=false;
			delSizePur += PurchaseFile.Delete(recaddr);
			num_purchase--;
		}
		PMwithMember.erase(input);

		PurchaseFile.Close();

		//num_member--;
		cout << " [DELETE SUCCESS!]" << endl;
	}

	
	cout << " Press any button to return to Record Delete" << endl;
	cout << ">> ";
	_getch();


	TotalMemberDelSize += delSizeMem;
	TotalPurchaseDelSize += delSizePur;

	StdIdxedFile.Close();

	return;
}

void MemberDelete(string user_id) {
	DelimFieldBuffer buf ('|', STDMAXBUF);
	TextIndexedFile<Member> StdIdxedFile(buf, LENID,10000);
	StdIdxedFile.Open ("fileOfMember");

	//MemberFile.Open("fileOfMember.dat", ios::out);

	int delSizeMem = 0;
	int delSizePur = 0;
	//int idx = Membermap[input];
	int find_flag=-1;

	Member m;
	m=MemberSearch(user_id,&find_flag);

	if (find_flag==-1) {
		cout << " There is Not Correct Member ID" << endl;
	}
	else {
		//delSize=MemberFile.Delete(idx);
		//Membermap.erase(input);

		delSizeMem=StdIdxedFile.Delete(m);

		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile<Purchase> PurchaseFile(buffer);

		PurchaseFile.Open("fileOfPurchase.dat", ios::out);

		int delpurchasecount = PMwithMember[user_id].size();

		for (int i = 0; i < delpurchasecount; i++) {
			int recaddr=bt.Search(PMwithMember[user_id][i]);
			bt.Remove(PMwithMember[user_id][i]);
			keymap[PMwithMember[user_id][i]]=false;
			delSizePur += PurchaseFile.Delete(recaddr);
			num_purchase--;
		}
		PMwithMember.erase(user_id);

		PurchaseFile.Close();

		//num_member--;
		cout << " [DELETE SUCCESS!]" << endl;
	}

	TotalMemberDelSize += delSizeMem;
	TotalPurchaseDelSize += delSizePur;
	StdIdxedFile.Close();

	return;
}

void StockDelete() {
	DelimFieldBuffer buf ('|', STDMAXBUF);
	TextIndexedFile<Stock> StdIdxedFile(buf, LENID,10000);
	StdIdxedFile.Open ("fileOfStock");
	
	cout << " Please Input your Stock ID to Delete: ";

	string input;
	cin >> input;

	//StockFile.Open("fileOfStock.dat", ios::out);

	int delSizeSto = 0;
	int delSizePur = 0;
	//int idx = Stockmap[input];
	int find_flag=-1;

	Stock s;
	s=StockSearch(input,&find_flag);

	if (find_flag == 0) {
		cout << " There is Not Correct Stock ID" << endl;
	}
	else {
		//delSize = StockFile.Delete(idx);
		delSizeSto = StdIdxedFile.Delete(s);
		//Stockmap.erase(input);

		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile<Purchase> PurchaseFile(buffer);

		PurchaseFile.Open("fileOfPurchase.dat", ios::out);

		int delpurchasecount = PMwithStock[input].size();
		for (int i = 0; i < delpurchasecount; i++) {
			int recaddr=bt.Search(PMwithStock[input][i]);
			bt.Remove(PMwithStock[input][i]);
			keymap[PMwithStock[input][i]]=false;
			delSizePur += PurchaseFile.Delete(recaddr);
			num_purchase--;
		}
		PMwithStock.erase(input);

		PurchaseFile.Close();

		//(*num_stock)--;
		cout << " [DELETE SUCCESS!]" << endl;
	}

	
	cout << " Press any button to return to Record Delete" << endl;
	cout << ">> ";
	_getch();

	TotalStockDelSize += delSizeSto;
	TotalPurchaseDelSize += delSizePur;
	StdIdxedFile.Close();

	return;
}

void PurchaseDelete() {
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Purchase> PurchaseFile(buffer);

	cout << " Please Input your Purchase ID to Delete: ";

	string input;
	cin >> input;

	PurchaseFile.Open("fileOfPurchase.dat", ios::out);

	int delSize = 0;
	char key = Purchasemap[input];
	
	if (key == 0) {
		cout << " There is Not Correct Purchase ID" << endl;
	}
	else {
		Purchase p;
		int recaddr=bt.Search(key);
		
		PurchaseFile.Read(p,recaddr);
		delSize = PurchaseFile.Delete(recaddr);
		Purchasemap.erase(input);
		//TODO:Delete PMwithMember,PMwithStock
		for(int i=0;i<PMwithMember[p.getMemberId()].size();i++){
			if(PMwithMember[p.getMemberId()][i]==key) {
				PMwithMember[p.getMemberId()].erase(PMwithMember[p.getMemberId()].begin()+i);
				break;
			}
		}
		for(int i=0;i<PMwithStock[p.getStockId()].size();i++){
			if(PMwithStock[p.getStockId()][i]==key) {
				PMwithStock[p.getStockId()].erase(PMwithStock[p.getStockId()].begin()+i);
				break;
			}
		}
		
		keymap[key]=false;
		
		bt.Remove(key);
		num_purchase--;
		cout << " [DELETE SUCCESS!]" << endl;
	}

	cout << " Press any button to return to Record Delete" << endl;
	cout << ">> ";
	_getch();

	TotalPurchaseDelSize += delSize;
	PurchaseFile.Close();

	return;
}

void PurchaseDelete(string user_id) {
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Purchase> PurchaseFile(buffer);

	cout << " Please Input your Purchase ID to Delete: ";

	string input;
	cin >> input;

	PurchaseFile.Open("fileOfPurchase.dat", ios::in|ios::out);

	int delSize = 0;
	int idx = Purchasemap[input];
	if (idx == 0) {
		cout << " There is Not Correct Purchase ID" << endl;
	}
	else {
		Purchase p;
		PurchaseFile.Read(p,idx);
		if(user_id==p.getMemberId()){
			delSize = PurchaseFile.Delete(idx);
			Purchasemap.erase(input);
			//TODO:Delete PMwithMember,PMwithStock
			for(int i=0;i<PMwithMember[user_id].size();i++){
				if(PMwithMember[user_id][i]==idx) {
					PMwithMember[user_id].erase(PMwithMember[user_id].begin()+i);
					break;
				}
			}
			for(int i=0;i<PMwithStock[p.getStockId()].size();i++){
				if(PMwithStock[p.getStockId()][i]==idx) {
					PMwithStock[p.getStockId()].erase(PMwithStock[p.getStockId()].begin()+i);
					break;
				}
			}
			num_purchase--;
			cout << " [DELETE SUCCES!]" << endl;
		}
		else
			cout << " Invalid Access!" << endl;
	}

	cout << " Press any button to return to Record Delete" << endl;
	cout << ">> ";
	_getch();

	TotalPurchaseDelSize += delSize;
	PurchaseFile.Close();

	return;
}