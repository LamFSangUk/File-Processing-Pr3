#include "purchasesystem.h"
#include "indfile.h"
#include "RecordSearch.h"
#include "RecordInsert.h"
#include "RecordDelete.h"
#include "RecordUpdate.h"

map<string,int> Purchasemap;
map<string, vector<int> > PMwithMember, PMwithStock;
int num_purchase=0;

int TotalMemberDelSize = 0;
int TotalStockDelSize = 0;
int TotalPurchaseDelSize = 0;

const int BTreeSize = 4;
BTree <char> bt(BTreeSize);
bool keymap[128];

void purchasesystem(){
	//Init screen

	string input_id,input_pw;
	int find_flag=-1;

	ifstream ifs;
	ifs.open("fileOfMember.ind");
	if ( !ifs.is_open() ) {
		DelimFieldBuffer buf ('|', STDMAXBUF);
		TextIndexedFile<Member> MemberIdxedFile(buf, LENID,10000);
		MemberIdxedFile.MakeIdxFile("fileOfMember");
	}

	ifs.close();
	ifs.open("fileOfStock.ind");
	if ( !ifs.is_open() ) {
		DelimFieldBuffer buf ('|', STDMAXBUF);
		TextIndexedFile<Stock> StockIdxedFile(buf, LENID,10000);
		StockIdxedFile.MakeIdxFile("fileOfStock");
	}
	ifs.close();

	/*pr3*/
	//ifs.open("fileOfPurchase.ind");
	//if(!ifs.is_open()){

	//Purchase data에 대한 새로운 Index File 생성.
	int result=0;

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Purchase> PurchaseFile(buffer);

	result = bt.Create("fileOfPurchase.ind", ios::in | ios::out | ios::trunc);
	if (!result) { cout << "Please delete fileOfPurchase.ind" << endl; return ; }
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);

	int key=1;//BTree를 위한 key, key의 범위는 1~127

	while (1) {		
		Purchase temp;
		int recaddr = PurchaseFile.Read(temp);
		if (recaddr == -1) break;

		Purchasemap[temp.getId()]=key;

		PMwithMember[temp.getMemberId()].push_back(key);
		PMwithStock[temp.getStockId()].push_back(key);
		num_purchase++;

		keymap[key]=true;
		bt.Insert(key, recaddr);
		key++;
	}
	//bt.Close();
	PurchaseFile.Close();
	//}
	//ifs.close();

	MemberFileCompaction();
	StockFileCompaction();
	//PurchaseFileCompaction();

	cout << " ID : ";
	cin >> input_id;
	cout << " PW : " ;
	cin >> input_pw;

	Member m;

	m=MemberSearch(input_id,&find_flag);

	if(find_flag>=0){
		printf("1");
		if(input_pw==m.getPw()){

			if(m.getLevel()=="1"){
				//Execute Admin mode
				AdminMode();
			}
			else if(m.getLevel()=="9"){
				//Execute General mode
				UserMode(input_id);
			}
			else{
				cout << "Invalid PassWord"<<endl;
			}
		}
	}
	else{
		cout << "Unknown Member"<<endl;
	}

	bt.Close();

	return;
}


void AdminMode(){
	while(1){
		system ("cls");

		cout << " -Admin Mode---------" << endl;
		cout << " 1. Records Search" << endl;
		cout << " 2. Records Insert" << endl;
		cout << " 3. Records Delete" << endl;
		cout << " 4. Records Update" << endl;
		cout << " 5. Exit" << endl;
		cout << " ------------------------------" << endl;

		cout << ">> ";

		int mode;
		cin >> mode;
		cin.ignore();

		switch (mode) {
		case 1: RecordSearch(); break;
		case 2: RecordInsert(); break;
		case 3: RecordDelete(); break;
		case 4: RecordUpdate();  break;
		case 5: 
			return;
		default: 
			cin.clear();

		}

		if(TotalMemberDelSize>1024)	MemberFileCompaction();
		if(TotalStockDelSize>1024) StockFileCompaction();
		//if (TotalPurchaseDelSize > 1024) PurchaseFileCompaction();
	}
}

void UserMode(string user_id){
	while(1){
		system ("cls");

		cout << " -User Mode---------" << endl;
		cout << " 1. My Info Admin" << endl;
		cout << " 2. Stock Search" << endl;
		//cout << " 3. Purchase" << endl;
		cout << " 4. Exit" << endl;
		cout << " ------------------------------" << endl;

		cout << ">> ";

		int mode;
		cin >> mode;
		cin.ignore();

		Stock s;
		int find_flag=-1;
		string input;

		switch (mode) {
		case 1: 
			MyInfoAdmin(user_id);
			break;
		case 2: 
			cout << " Please Input the Stock ID : ";

			cin >> input;

			s=StockSearch(input,&find_flag);

			if(find_flag>=0){//Find Success
				cout << s;
			}
			else{
				cout << " There is Not Correct Stock ID" << endl;
			}
			cout << " Press any button to return to UserMode" << endl;
			cout << ">> ";
			_getch();

			break;

			//case 3: PurchaseUser(user_id); break;
		case 4:
			return;
		default: 
			cin.clear();


		}
		if (TotalMemberDelSize>1024) MemberFileCompaction();
		if (TotalStockDelSize>1024) StockFileCompaction();
		//if (TotalPurchaseDelSize > 1024) PurchaseFileCompaction();
	}
}

void PurchaseUser(string user_id){
	while(1){
		system ("cls");

		cout << " -Purchase Mode---------" << endl;
		cout << " 1. New Purchase" << endl;
		cout << " 2. My Purchase Search" << endl;
		cout << " 3. My Purchase Update" << endl;
		cout << " 4. My Purchase Delete" << endl;
		cout << " 5. Exit" << endl;
		cout << " ------------------------------" << endl;

		cout << ">> ";

		int mode;
		cin >> mode;
		cin.ignore();

		switch (mode) {
		case 1: PurchaseInsert(user_id); break;
		case 2: PurchaseSearch(user_id); break;
		case 3: PurchaseUpdate(user_id); break;
		case 4: PurchaseDelete(user_id); break;
		case 5: return;
		}
	}
}

void MyInfoAdmin(string user_id){
	system ("cls");

	cout << " -My Info Admin---------" << endl;
	cout << " 1. Update My Info" << endl;
	cout << " 2. WithDraw" << endl;
	cout << " 3. Exit" << endl;
	cout << " ------------------------------" << endl;

	cout << ">> ";

	int mode;
	cin >> mode;
	cin.ignore();

	string ans;

	switch (mode) {
	case 1: MemberUpdate(user_id); 
		cout << " Press any button to return to UserMode" << endl;
		cout << ">> ";
		_getch();
		break;
	case 2: 
		cout <<"Are You Sure to Withdraw?(Y/N)" <<endl;
		cin >> ans;
		if(ans=="Y"){
			MemberDelete(user_id);
			exit(0);
		}
		break;
	case 3: 
	default:
		return;
	}
	return;
}

void MemberFileCompaction() {
	vector<Member> temp;

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Member> MemberFile(buffer);
	MemberFile.Open("fileOfMember.dat", ios::in);

	Member m;

	while (MemberFile.Read(m) != -1) {
		temp.push_back(m);
	}

	MemberFile.Close();

	TextIndexedFile<Member> MemberIdxedFile(buffer, LENID, 10000);
	MemberIdxedFile.Create("fileOfMember",ios::out|ios::trunc);

	for (int i = 0; i < temp.size(); i++) {
		m = temp[i];
		MemberIdxedFile.Append(m);
	}

	MemberIdxedFile.Close();
}

void StockFileCompaction() {
	vector<Stock> temp;

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Stock> StockFile(buffer);
	StockFile.Open("fileOfStock.dat", ios::in);

	Stock s;

	while (StockFile.Read(s) != -1) {
		temp.push_back(s);
	}

	StockFile.Close();

	TextIndexedFile<Stock> StockIdxedFile(buffer, LENID, 10000);
	StockIdxedFile.Create("fileOfStock", ios::out | ios::trunc);

	for (int i = 0; i < temp.size(); i++) {
		s = temp[i];
		StockIdxedFile.Append(s);
	}

	StockIdxedFile.Close();
}

void PurchaseFileCompaction() {
	vector<Purchase> temp;

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Purchase> PurchaseFile(buffer);
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);

	Purchase p;
	while (PurchaseFile.Read(p) != -1) {
		temp.push_back(p);
	}

	Purchasemap.clear();
	PMwithMember.clear();
	PMwithStock.clear();

	PurchaseFile.Close();

	PurchaseFile.Create("fileOfPurchase.dat", ios::out|ios::trunc);

	int recaddr;
	for (int i = 0; i < temp.size(); i++) {

		if ((recaddr = PurchaseFile.Write(temp[i])) == -1) {
			cout << "Write Error!" << endl;
		}
		else {
			Purchasemap.insert(make_pair(temp[i].getId(), recaddr));
			PMwithMember[temp[i].getMemberId()].push_back(recaddr);
			PMwithStock[temp[i].getStockId()].push_back(recaddr);
		}
	}

	PurchaseFile.Close();

	return;
}