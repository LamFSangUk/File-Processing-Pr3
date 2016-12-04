#include "RecordInsert.h"
#include "RecordSearch.h"
#include "purchasesystem.h"

void RecordInsert() {
	while (1) {
		system("cls");

		cout << " -Record-Insert----------------" << endl;
		cout << " 1. Member Records Insert" << endl;
		cout << " 2. Stock Records Insert" << endl;
		cout << " 3. Purchase Records Insert" << endl;
		cout << " 4. Exit to AdminMode" << endl;
		cout << " ------------------------------" << endl;
		cout << ">> ";

		int mode;
		cin >> mode;
		cin.ignore();

		switch (mode) {
		case 1:
			MemberInsert();
			cout << " Press any button to return to AdminMode" << endl;
			cout << ">> ";
			_getch();
			return;
		case 2:
			StockInsert();
			cout << " Press any button to return to AdminMode" << endl;
			cout << ">> ";
			_getch();
			break;
		case 3:
			PurchaseInsert();
			break;
		case 4: return;
		default: 
			cin.clear();
			break;

		}


	}
	return;
}

void MemberInsert(){
	DelimFieldBuffer buf ('|', STDMAXBUF);
	TextIndexedFile<Member> StdIdxedFile(buf, LENID, 10000);
	StdIdxedFile.Open ("fileOfMember");

	cout << " Please Input Member ID : ";

	string input;
	cin >> input;
	cin.ignore();

	Member temp;
	int find_flag=-1;
	MemberSearch(input,&find_flag);

	if (find_flag==-1) {
		string pw, name, phonenum, addr, birth, email;
		cout << " PASSWORD : ";
		getline(cin, pw);
		cout << " Name : ";
		getline(cin,name);
		cout << " Phone Number : ";
		getline(cin, phonenum);
		cout << " Address : ";
		getline(cin, addr);
		cout << " Birthday : ";
		getline(cin, birth);
		cout << " Email : ";
		getline(cin, email);

		temp.setId(input);
		temp.setPw(pw);
		temp.setName(name);
		temp.setPhonenum(phonenum);
		temp.setAddress(addr);
		temp.setBirthday(birth);
		temp.setEmail(email);
		temp.setLevel("9");

		StdIdxedFile.Append (temp);
	}
	else {
		cout << " The Member ID exists already" << endl;
	}

	StdIdxedFile.Close ();

	return;
}

void StockInsert() {
	DelimFieldBuffer buf ('|', STDMAXBUF);
	TextIndexedFile<Stock> StdIdxedFile(buf, LENID, 10000);
	StdIdxedFile.Open ("fileOfStock");

	cout << " Please Input Stock ID : ";

	string input;
	cin >> input;
	cin.ignore();

	Stock temp;
	int find_flag=-1;

	StockSearch(input,&find_flag);

	if (find_flag==-1) {
		string category, material, price, stock, wash_info, size;
		cout << " Category : ";
		getline(cin, category);
		cout << " Material : ";
		getline(cin, material);
		cout << " Price : ";
		getline(cin, price);
		cout << " Stock : ";
		getline(cin, stock);
		cout << " Washing Info : ";
		getline(cin, wash_info);
		cout << " Size : ";
		getline(cin, size);

		temp.setId(input);
		temp.setCategory(category);
		temp.setMaterial(material);
		temp.setPrice(price);
		temp.setStock(stock);
		temp.setWashingInfo(wash_info);
		temp.setSize(size);

		StdIdxedFile.Append (temp);
	}
	else {
		cout << "The Stock ID exists already" << endl;
	}

	StdIdxedFile.Close ();

	return;
}

void PurchaseInsert(){
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Purchase> PurchaseFile(buffer);

	cout << " Please Input Purchase ID : ";

	string input;
	cin >> input;
	cin.ignore();

	Purchase temp;

	PurchaseFile.Open("fileOfPurchase.dat", ios::out);

	//const int BTreeSize = 4;
	//BTree <char> bt(BTreeSize);
	//bt.Open("fileOfPurchase.ind",ios::in|ios::out);

	int find = Purchasemap[input];
	if (find == 0) {
		/*prj3*/
		char key=0;
		for(int i=1;i<=127;i++){
			if(keymap[i]==false){
				key=i;
				break;
			}
		}

		if(key==0){
			cout << "There are No Empty Keys(1~127)" << endl;

			cout << " Press any button to return to Record Search" << endl;
			cout << ">> ";
			_getch();

			//bt.Close();
			PurchaseFile.Close();
			return ;
		}


		string stock_id,member_id,quantity;
		cout << " Stock ID : ";
		getline(cin, stock_id);
		cout << " Member ID : ";
		getline(cin, member_id);
		cout << " Quantity : ";
		getline(cin, quantity);

		temp.setPurchaseId(input);
		temp.setStockId(stock_id);
		temp.setMemberId(member_id);
		temp.setQuantity(quantity);

		int recaddr = PurchaseFile.Append(temp);
		Purchasemap[input] = key;
		num_purchase++;

		cout << "The New Key is "<<(int)key<<endl;
		bt.Insert(key,recaddr);
	}
	else {
		cout << "The Purchase ID exists already" << endl;
	}
	cout << " Press any button to return to Record Search" << endl;
	cout << ">> ";
	_getch();

	//bt.Close();
	PurchaseFile.Close();

	return;
}

void PurchaseInsert(string user_id){
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Purchase> PurchaseFile(buffer);

	cout << " Please Input Purchase ID : ";

	string input;
	cin >> input;
	cin.ignore();

	Purchase temp;

	PurchaseFile.Open("fileOfPurchase.dat", ios::out);

	int idx = Purchasemap[input];
	if (idx == 0) {
		string stock_id,quantity;
		cout << "Stock ID : ";
		getline(cin, stock_id);
		cout << " Quantity : ";
		getline(cin, quantity);

		temp.setPurchaseId(input);
		temp.setStockId(stock_id);
		temp.setMemberId(user_id);
		temp.setQuantity(quantity);

		int recaddr = PurchaseFile.Append(temp);
		Purchasemap[input] = recaddr;
		num_purchase++;
	}
	else {
		cout << "The Purchase ID exists already" << endl;
	}
	cout << " Press any button to return to Record Search" << endl;
	cout << ">> ";
	_getch();

	PurchaseFile.Close();

	return;
}