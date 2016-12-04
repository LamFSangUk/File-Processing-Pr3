#include "RecordUpdate.h"
#include "RecordSearch.h"
#include "purchasesystem.h"

void RecordUpdate() {
	while (1) {
		system("cls");

		cout << " -Record-Update----------------" << endl;
		cout << " 1. Member Records Update" << endl;
		cout << " 2. Stock Records Update" << endl;
		cout << " 3. Purchase Records Update" << endl;
		cout << " 4. Exit to AdminMode" << endl;
		cout << " ------------------------------" << endl;
		cout << ">> ";

		int mode;
		cin >> mode;

		switch (mode) {
		case 1:
			MemberUpdate();
			break;
		case 2:
			StockUpdate();
			break;
		case 3:
			PurchaseUpdate();
			break;
		case 4: return;
		default: 
			cin.clear();
			break;

		}


	}
	return;
}
void MemberUpdate() {
	DelimFieldBuffer buf ('|', STDMAXBUF);
	TextIndexedFile<Member> StdIdxedFile(buf, LENID,10000);
	StdIdxedFile.Open ("fileOfMember");

	cout << " Please Input your Member ID to Update: ";

	string input;
	cin >> input;

	int delSize = 0;
	int find_flag=-1;

	Member m;
	m=MemberSearch(input,&find_flag);
	if (find_flag==-1) {
		cout << " There is Not Correct Member ID" << endl;
	}
	else {
		cout << endl << " Which Field do you want to Update, Press the Number "<<endl;
		cout << " (1) Name\n (2) Phone Number\n (3) Address\n (4) Birthday\n (5) E-mail (6) PW" << endl;

		cout << ">> ";
		int fieldnum;
		cin >> fieldnum;
		cin.ignore();

		string change;
		cout << " Input the Data : ";
		getline(cin, change);

		Member temp;
		int recaddr;
		int delSize;

		//MemberFile.Open("fileOfMember.dat", ios::in|ios::out);
		StdIdxedFile.Read((char*)input.c_str(),temp);

		switch (fieldnum) {
		case 1: temp.setName(change); break;
		case 2: temp.setPhonenum(change); break;
		case 3: temp.setAddress(change); break;
		case 4:	temp.setBirthday(change); break;
		case 5: temp.setEmail(change); break;
		case 6: temp.setPw(change); break;
		default: break;
		}
		//MemberFile.Close();

		//MemberFile.Open("fileOfMember.dat", ios::out);
		//delSize = MemberFile.Delete(idx);
		//recaddr = MemberFile.Append(temp);
		//Membermap[input] = recaddr;
		StdIdxedFile.Update((char*)input.c_str(),temp,&delSize);
		cout << " [UPDATE SUCCESS!]" << endl;
		//MemberFile.Close();
	}

	//TODO:cascasding
	cout << " Press any button to return to Record Update" << endl;
	cout << ">> ";
	_getch();

	TotalMemberDelSize += delSize;
	
	StdIdxedFile.Close();

	return;
}

void MemberUpdate(string user_id) {
	DelimFieldBuffer buf ('|', STDMAXBUF);
	TextIndexedFile<Member> StdIdxedFile(buf, LENID,10000);
	StdIdxedFile.Open ("fileOfMember");

	int delSize = 0;
	int find_flag=-1;

	Member m;
	m=MemberSearch(user_id,&find_flag);
	if (find_flag==-1) {
		cout << " There is Not Correct Member ID" << endl;
	}
	else {
		cout << endl << " Which Field do you want to Update, Press the Number "<<endl;
		cout << " (1) Name\n (2) Phone Number\n (3) Address\n (4) Birthday\n (5) E-mail (6) PW" << endl;

		cout << ">> ";
		int fieldnum;
		cin >> fieldnum;
		cin.ignore();

		string change;
		cout << " Input the Data : ";
		getline(cin, change);

		Member temp;
		int recaddr;
		int delSize;

		//MemberFile.Open("fileOfMember.dat", ios::in|ios::out);
		StdIdxedFile.Read((char*)user_id.c_str(),temp);

		switch (fieldnum) {
		case 1: temp.setName(change); break;
		case 2: temp.setPhonenum(change); break;
		case 3: temp.setAddress(change); break;
		case 4:	temp.setBirthday(change); break;
		case 5: temp.setEmail(change); break;
		case 6: temp.setPw(change); break;
		default: break;
		}
		//MemberFile.Close();

		//MemberFile.Open("fileOfMember.dat", ios::out);
		//delSize = MemberFile.Delete(idx);
		//recaddr = MemberFile.Append(temp);
		//Membermap[input] = recaddr;
		StdIdxedFile.Update((char*)user_id.c_str(),temp,&delSize);
		cout << " [UPDATE SUCCESS!]" << endl;
		//MemberFile.Close();
	}

	//TODO:cascasding

	TotalMemberDelSize += delSize;
	
	StdIdxedFile.Close();

	return;
}

void StockUpdate() {
	DelimFieldBuffer buf ('|', STDMAXBUF);
	TextIndexedFile<Stock> StdIdxedFile(buf, LENID,10000);
	StdIdxedFile.Open ("fileOfStock");

	cout << " Please Input your Member ID to Update: ";

	string input;
	cin >> input;

	int delSize = 0;
	//int idx = Stockmap[input];
	int find_flag=-1;

	Stock s;
	s=StockSearch(input,&find_flag);
	if (find_flag == -1) {
		cout << " There is Not Correct Stock ID" << endl;
	}
	else {
		cout << endl << " Which Field do you want to Update, Press the Number " << endl;
		cout << " (1) Category\n (2) Material\n (3) Price\n (4) Stock\n (5) Washing Info\n (6) Size" << endl;

		cout << ">> ";
		int fieldnum;
		cin >> fieldnum;
		cin.ignore();

		string change;
		cout << " Input the Data : ";
		getline(cin, change);

		Stock temp;
		int recaddr;
		int delSize;

		//StockFile.Open("fileOfStock.dat", ios::in|ios::out);
		//StockFile.Read(temp, idx);
		StdIdxedFile.Read((char*)input.c_str(),temp);

		switch (fieldnum) {
		case 1: temp.setCategory(change); break;
		case 2: temp.setMaterial(change); break;
		case 3: temp.setPrice(change); break;
		case 4:	temp.setStock(change); break;
		case 5: temp.setWashingInfo(change); break;
		case 6: temp.setSize(change); break;
		default: break;
		}
		//StockFile.Close();

		//MemberFile.Open("fileOfStock.dat", ios::out);
		//delSize = StockFile.Delete(idx);
		//cout << delSize;
		//recaddr = StockFile.Append(temp);
		//Stockmap[input] = recaddr;
		StdIdxedFile.Update((char*)input.c_str(),temp,&delSize);
		cout << " [UPDATE SUCCESS!]" << endl;
		
	}

	//TODO:cascasding
	cout << " Press any button to return to Record Update" << endl;
	cout << ">> ";
	_getch();

	TotalStockDelSize += delSize;

	StdIdxedFile.Close();

	return;
}

void PurchaseUpdate() {
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Purchase> PurchaseFile(buffer);

	cout << " Please Input your Purchase ID to Update: ";

	string input;
	cin >> input;

	int delSize = 0;
	int key = Purchasemap[input];
	if (key == 0) {
		cout << " There is Not Correct Purchase ID" << endl;
	}
	else {
		cout << endl << " Which Field do you want to Update, Press the Number " << endl;
		cout << " (1) Stock ID\n (2) Member ID\n (3) Quantity" << endl;

		cout << ">> ";
		int fieldnum;
		cin >> fieldnum;
		cin.ignore();

		string change;
		cout << " Input the Data : ";
		getline(cin, change);

		Purchase temp;
		int recaddr;

		PurchaseFile.Open("fileOfPurchase.dat", ios::in|ios::out);
		recaddr=bt.Search(key);
		PurchaseFile.Read(temp, recaddr);

		int errflag = 0;

		int find_flag=-1;

		switch (fieldnum) {
		case 1: 
			StockSearch(change,&find_flag);
			if(find_flag>=0) {
				for(int i=0;i<PMwithStock[temp.getStockId()].size();i++){
					if(PMwithStock[temp.getStockId()][i]==key) {
						PMwithStock[temp.getStockId()].erase(PMwithStock[temp.getStockId()].begin()+i);
						break;
					}
				}
				temp.setStockId(change);
			}
			else {
				cout << " No Stock that has the name '" << change + "'" << endl;
				errflag = 1;
			}

			break;
		case 2: 
			MemberSearch(change,&find_flag);
			if (find_flag>=0){
				for(int i=0;i<PMwithMember[temp.getMemberId()].size();i++){
					if(PMwithMember[temp.getMemberId()][i]==key) {
						PMwithMember[temp.getMemberId()].erase(PMwithMember[temp.getMemberId()].begin()+i);
						break;
					}
				}
				temp.setMemberId(change);
			}
			else {
				cout << " No Member that has the name '" << change + "'" << endl;
				errflag = 1;
			}

			break;
		case 3: temp.setQuantity(change); break;
		default: break;
		}
		//PurchaseFile.Close();

		//MemberFile.Open("fileOfMember.dat", ios::out);
		if (errflag == 0) {
			delSize = PurchaseFile.Delete(recaddr);
			recaddr = PurchaseFile.Append(temp);
			bt.Remove(key);
			bt.Insert(key,recaddr);
			Purchasemap[input] = key;
			if(fieldnum==1) PMwithStock[temp.getStockId()].push_back(key);
			else if(fieldnum==2) PMwithMember[temp.getMemberId()].push_back(key);
			cout << " [UPDATE SUCCESS!]" << endl;

			TotalPurchaseDelSize += delSize;
		}
		PurchaseFile.Close();
	}

	//TODO:cascasding
	cout << " Press any button to return to Record Update" << endl;
	cout << ">> ";
	_getch();

	return;
}

void PurchaseUpdate(string user_id) {
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Purchase> PurchaseFile(buffer);

	cout << " Please Input your Purchase ID to Update: ";

	string input;
	cin >> input;

	int delSize = 0;
	int idx = Purchasemap[input];
	if (idx == 0) {
		cout << " There is Not Correct Purchase ID" << endl;
	}
	else {
		Purchase temp;

		PurchaseFile.Open("fileOfPurchase.dat", ios::in|ios::out);
		PurchaseFile.Read(temp, idx);

		if(user_id==temp.getMemberId()){

			cout << endl << " Which Field do you want to Update, Press the Number " << endl;
			cout << " (1) Stock ID\n (2) Quantity" << endl;

			cout << ">> ";
			int fieldnum;
			cin >> fieldnum;
			cin.ignore();

			string change;
			cout << " Input the Data : ";
			getline(cin, change);

			int recaddr;
			int errflag = 0;
			int find_flag=-1;

			switch (fieldnum) {
			case 1: 
				StockSearch(change,&find_flag);
				if(find_flag>=0) {
					for(int i=0;i<PMwithStock[temp.getStockId()].size();i++){
						if(PMwithStock[temp.getStockId()][i]==idx) {
							PMwithStock[temp.getStockId()].erase(PMwithStock[temp.getStockId()].begin()+i);
							break;
						}
					}
					temp.setStockId(change); 
				}
				else {
					cout << " No Stock that has the name '" << change + "'" << endl;
					errflag = 1;
				}

				break;
			case 2: temp.setQuantity(change); break;
			default: break;
			}

			//MemberFile.Open("fileOfMember.dat", ios::out);
			if (errflag == 0) {
				delSize = PurchaseFile.Delete(idx);
				recaddr = PurchaseFile.Append(temp);
				Purchasemap[input] = recaddr;
				if(fieldnum==1) PMwithStock[temp.getStockId()].push_back(recaddr);
				cout << " [UPDATE SUCCESS!]" << endl;

				TotalPurchaseDelSize += delSize;
			}
		
		}
		else
			cout << " Invalid Access!" << endl;

		PurchaseFile.Close();
	}

	//TODO:cascasding
	cout << " Press any button to return to Record Update" << endl;
	cout << ">> ";
	_getch();

	return;
}