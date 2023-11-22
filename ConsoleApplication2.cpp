#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

struct Node
{
	int ID;
	string name;
	string author;
	int year;
	long long price;
	string type;
	Node* next;
};

struct LinkedList
{
	Node* head = NULL;
	Node* tail = NULL;
};

Node* createNode(string s)
{
	Node* newnode = new Node;
	if (newnode)
	{
		string token;
		stringstream ss(s);
		int cnt = 1;
		while (getline(ss, token, '-'))
		{
			if (cnt == 1)
			{
				newnode->ID = stoi(token);
			}
			else if (cnt == 2)
			{
				newnode->name = token;
			}
			else if (cnt == 3)
			{

				newnode->author = token;
			}
			else if (cnt == 4)
			{
				newnode->year = stoi(token);
			}
			else if (cnt == 5)
			{
				newnode->price = stoll(token);
			}
			else if (cnt == 6)
			{
				newnode->type = token;
			}
			cnt++;
		}
	}
	newnode->next = NULL;
	return newnode;
}
void addTail(LinkedList* list, string data)
{
	Node* newnode = createNode(data);
	if (list->head == NULL)
	{
		list->head = newnode;
		list->tail = list->head;
	}
	else
	{
		list->tail->next = newnode;
		list->tail = newnode;
	}
}

void readData(LinkedList*& list)
{
	cout << "Nhap du lieu sach\nGo Enter 2 lan de thoat\n";
	cout << "Nhap dinh dang \"id-ten sach-NXB-Nam XB-Gia-The loai\"\n";
	cout << "Vi du \"12-Mang May Tinh-DHQG-2019-120000-Giao trinh\"\n";
	string line;
	while (getline(cin, line))
	{
		if (line == "") break;
		addTail(list, line);
	}

}
void write(LinkedList* list)
{
	ofstream w("input.txt", ios::out);
	Node* p = list->head;
	while (p)
	{
		w << p->ID << "-" << p->name << "-" << p->author << "-" << p->year << "-" << p->price << endl;
		p = p->next;
	}
}
void deleteBook(LinkedList*& list)
{
	int ID;
	cout << "Nhap ID sach can xoa: ";
	cin >> ID;
	Node* p = list->head;
	if (p->ID == ID)
	{
		list->head = NULL;
		list->tail = NULL;
		return;
	}
	ofstream w("input.txt", ios::out);
	while (p)
	{
		if (p->next != NULL && p->next->ID == ID)
		{
			p->next = p->next->next;
			write(list);
			return;
		}
		else
			p = p->next;
	}

	cout << "Khong tim thay!\n";
}
void findID(LinkedList* list, int key)
{
	Node* p = list->head;
	while (p)
	{
		if (p->ID == key)
		{
			cout << p->ID << "-" << p->name << "-" << p->author << "-" << p->year << "-" << p->price << endl;
			return;
		}
		p = p->next;
	}
	cout << "Khong tim thay!\n";
}
#include<map>
void SORT(int*& a, int n)
{
	for (int i = 0;i < n;++i)
	{
		for (int j = i + 1;j < n;++j)
		{
			if (a[j] > a[i]) swap(a[i], a[j]);
		}
	}
}
void stat(LinkedList* list, map<string, int>& mp)
{
	Node* p = list->head;
 	while (p)
	{
		mp[p->type]++;
		p = p->next;
	}
	for (auto it = mp.rbegin();it != mp.rend();++it)
	{
		cout << it->first << ": " << it->second << endl;
	}
}
int main()
{
	LinkedList* list = new LinkedList;
	//nhap sach
	readData(list);
	write(list);
	//xoa sach
	deleteBook(list);
	//tim kiem
	cout << "Nhap ID sach can tim: ";
	int id;cin >> id;
	findID(list, id);
	map<string, int> mp;
	//Thong ke sach theo the loai
	cout << "Thong ke cac loai sach: \n";
	stat(list, mp);


	return 0;
}