#include <string>
#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
#define MIN_TABLE_SIZE 10
#include <istream>
using namespace std;


enum EntryType {Legitimate, Empty, Deleted};
struct HashNode
{
    string element;
    int searchKey;
    int situation;
    enum EntryType info;
};

struct HashTable
{
    int tableSize;
    HashNode *table;
    
};

bool isPrime (int n)
{
    if (n == 2 || n == 3)
        return true;
    if (n == 1 || n % 2 == 0)
        return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;
    return true;
}

int nextPrime(int n)
{
    if (n <= 0)
        n == 3;
    if (n % 2 == 0)
        n++;
    for (; !isPrime( n ); n += 2);
    return n;
}

int HashingFunc(int key, int size, HashTable *table)
{	
	size = table->tableSize;
	int pos;
	for(int i = 0; i<size;i++){
	
		if(table->table[pos].element != "NULL"){
			if(pos>size){
				size = size*2;
			}
			pos = key%size;
			pos = (pos+i^2)%size;
		}
		else
			pos = key%size;
}
   return pos;
}

HashTable *initializeTable(int tableSize)
{
    HashTable *table;
    if (tableSize < MIN_TABLE_SIZE)
    {
        cout<<"Your table size is too small for hashing"<<endl;
        return NULL;
    }
    table = new HashTable;
    if (table == NULL)
    {
        cout<<""<<endl;
        return NULL;
    }
    table->tableSize = nextPrime(tableSize);
    table->table = new HashNode [table->tableSize];
    if (table->table == NULL)
    {
        cout<<"Your table size is too small for hashing"<<endl;
        return NULL;
    }
    for (int i = 0; i < table->tableSize; i++)
    {
        table->table[i].info = Empty;
        table->table[i].element = "NULL";
        table->table[i].searchKey = 0;
        table->table[i].situation = -1;
        
    }
    return table;
}

void search(int key, HashTable *htable)
{	
	int size = htable->tableSize;
    int place = htable->table[key].searchKey;
    int i = 0;

			while(i<htable->tableSize){
				if(i == HashingFunc(htable->table[key].searchKey,htable->tableSize,htable) && htable->table[key].situation == 0){
					cout<< "Your item is in the "<< i+1 <<"th place in the table."<<endl;
					break;	
				}
				else if(HashingFunc(htable->table[key].searchKey,htable->tableSize,htable) != i && htable->table[key].situation == 1){
					cout<<"Item not found."<<endl;
					break;
				}
				else{
					i++;
					continue;
				}	
						
			 
		}	

}

void add(int key,string veggie, HashTable *htable)
{	
	
	int size = htable->tableSize;
    int pos = HashingFunc(key,size,htable);
    
   	htable->table[pos].info = Legitimate;
    htable->table[pos].element = veggie;
	htable->table[pos].searchKey = key;
	htable->table[pos].situation = 0;
	
}

HashTable *rehash(HashTable *htable)
{   
    string veggie;
    int key;
	
    HashNode *table = htable->table;
    htable->tableSize = htable->tableSize*2 ;
    for (int i = 0; i < htable->tableSize/2; i++)
    {	
    	HashingFunc(table[i].searchKey,htable->tableSize,htable);
    	add(table[i].searchKey,table[i].element,htable);
    }
    //free(table);
    return htable;
}

void remove(int key, HashTable *table){
	
	int sit = table->table[key].situation;
			if(sit == 0){
				table->table[key].situation = 1;
				cout<<"Succesfully deleted..."<<endl;
			}
			else if(sit ==1)
				cout<<"This data is already deleted!"<<endl;
			else
				cout<<"Your place is NULL or does not exist. Please try again..."<<endl;
	
}

void print(HashTable *table)
{	
	int size = table->tableSize;
	cout<<"Here is your table: "<<endl;
	
    for (int i = 0; i < size; i++)
    {
        int key = table->table[i].searchKey;
        string veggie = table->table[i].element;
        int sit = table->table[i].situation;

        	if(table->table[i].situation == -1){
        		cout<<i + 1<<" th element of table is : [NULL]"<<endl;
        	}
        	else if(table->table[i].situation == 1)
        		cout<<i + 1<<" th element of table is : [" <<key<<", "<<veggie<<", "<<1<<"]"<<endl;
        	else	
            	cout<<i + 1<<" th element of table is : [" <<key<<", "<<veggie<<", "<<table->table[i].situation<<"]"<<endl;
    }

}

int main()
{
    int number, tableSize, position, key, i = 1;
    int choice;
    string veggie;
    HashTable *table;
    while(1)
    {
	    cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
		cout<<"$$$$$$$$$$$$ MAKE YOUR CHOICE $$$$$$$$$$$$$$$$$$"<<endl;
		cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
		cout<<"$$$$$$$$$$$$ 1) Enter table size $$$$$$$$$$$$$$$"<<endl;
		cout<<"$$$$$$$$$$$$ 2) Add vegetable to table $$$$$$$$$"<<endl;
		cout<<"$$$$$$$$$$$$ 3) Remove vegetable from table $$$$"<<endl;
		cout<<"$$$$$$$$$$$$ 4) Print table $$$$$$$$$$$$$$$$$$$$"<<endl;
		cout<<"$$$$$$$$$$$$ 5) Find vegetable from table $$$$$$"<<endl;
		cout<<"$$$$$$$$$$$$ 6) Rehash your table $$$$$$$$$$$$$$"<<endl;
		cout<<"$$$$$$$$$$$$ 0) Exit! $$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
		cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
		cout<<endl;
		cout<<"Make your choice : ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Please enter your table size: ";
            cin>>tableSize;
            table = initializeTable(tableSize);
            cout<<"Your table size is: "<<nextPrime(tableSize)<<endl;
            break;
            
        case 2:
            
        	cout<<"Enter your key number: ";
        	cin>>number;
        	cout<<"Please enter your vegetable name: ";
        	cin>>veggie;
            add(number, veggie, table);
            cout<<"Addition completed!"<<endl;
            i++;
            break;
        
            
        case 3:
        	cout<<"Enter key for remove data: ";
        	cin>>position;
        	remove(position,table);
            break;
        case 4:
            print(table);
            break;
            
        case 5:
        	cout<<"Please enter key for search: ";
        	cin>>key;
        	search(key,table);
        	
            break;
            
        case 6:
        	cout<<"Table is succesfully rehashed..."<<endl;
            rehash(table);
            //table = rehash(table);
            //print(table);
            break;
            
        case 0:
        	cout<<"...GAME OVER...";
        	exit(1);
        	
        default:
           cout<<"\nYou are doing something wrong! Please try again.\n";
       }
    }
    cout<<"...GAME OVER...";
    return 0;
}
