#include "RecordSearch.h"
//#include "btree.h"
//#include "btree.cpp"
#include "purchasesystem.h"

void RecordSearch() {

	while (1) {
		system("cls");

		cout << " -Record-Search----------------" << endl;
		cout << " 1. Member Records Search" << endl;
		cout << " 2. Stock Records Search" << endl;
		cout << " 3. Purchase Records Search" << endl;
		cout << " 4. Exit to AdminMode" << endl;
		cout << " ------------------------------" << endl;
		cout << ">> ";

		int mode;
		cin >> mode;
		cin.ignore();

		string input;
		Member m;
		Stock s;
		Purchase p;
		int find_flag=-1;

		switch (mode) {
		case 1: 

			cout << " Please Input your Member ID : ";

			cin >> input;

			m=MemberSearch(input,&find_flag);

			if(find_flag>=0){//Find Success
				cout << m;
			}
			else{
				cout << " There is Not Correct Member ID" << endl;
			}
			cout << " Press any button to return to AdminMode" << endl;
			cout << ">> ";
			_getch();
			return;

		case 2: 
			cout << " Please Input your Stock ID : ";

			cin >> input;

			s=StockSearch(input,&find_flag);

			if(find_flag>=0){//Find Success
				cout << s;
			}
			else{
				cout << " There is Not Correct Stock ID" << endl;
			}
			cout << " Press any button to return to AdminMode" << endl;
			cout << ">> ";
			_getch();
			return;

		case 3: 
			PurchaseSearch();
			return;
		case 4: return;
		default: 
			cin.clear();
			break;

		}


	}
	return;
}

Member MemberSearch(string id,int *flag) {

	// Read and Write with TextIndexedFile
	DelimFieldBuffer buf ('|', STDMAXBUF);
	TextIndexedFile<Member> StdIdxedFile(buf, LENID,10000);
	StdIdxedFile.Open ("fileOfMember");

	Member m;
	int find=StdIdxedFile.Read ((char*)id.c_str(), m);	

	*flag=find;

	return m;
}

Stock StockSearch(string id,int *flag){
	DelimFieldBuffer buf ('|', STDMAXBUF);
	TextIndexedFile<Stock> StdIdxedFile(buf, LENID,10000);
	StdIdxedFile.Open ("fileOfStock");

	Stock s;
	int find=StdIdxedFile.Read ((char*)id.c_str(), s);	

	*flag=find;

	return s;
}

void PurchaseSearch() {
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Purchase> PurchaseFile(buffer);

	cout << " Please Input the Purchase Record's Key(1~127) : ";

	string input;
	int input_key;
	cin >> input;

	input_key=atoi(input.c_str());

	if(input_key<1 && input_key>127){
		cout <<" Wrong Key!"<<endl;
		cout << " Press any button to return to Record Search" << endl;
		cout << ">> ";
		_getch();
		return;
	}

	Purchase result;

	PurchaseFile.Open("fileOfPurchase.dat", ios::in);

	//const int BTreeSize = 4;
	//BTree <char> bt(BTreeSize);
	//bt.Open("fileOfPurchase.ind",ios::in);
	int recaddr = bt.Search(input_key);
	if (recaddr == -1) {
		cout << "There is Not Correct Purchase ID" << endl;
	}
	else {
		PurchaseFile.Read(result, recaddr);

		cout << result;
	}
	cout << " Press any button to return to Record Search" << endl;
	cout << ">> ";
	_getch();

	//bt.Close();
	PurchaseFile.Close();

	return;
}

void PurchaseSearch(string user_id) {
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Purchase> PurchaseFile(buffer);

	system("cls");

	cout << " -My Purchase List-------------" << endl;
	Purchase result;

	PurchaseFile.Open("fileOfPurchase.dat", ios::in);

	int datacount = PMwithMember[user_id].size();
	if (datacount == 0) {
		cout << "There is Not Correct Member ID" << endl;
	}
	else {
		for (int i = 0; i < datacount; i++) {
			PurchaseFile.Read(result, PMwithMember[user_id][i]);

			cout << result;
		}
	}
	cout << " Press any button to return to Record Search" << endl;
	cout << ">> ";
	_getch();

	PurchaseFile.Close();

	return;

}