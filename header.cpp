#include "header.h"
#include <iostream>
#include <fstream>//file handling 
#include <iomanip>//manipulate I/O - formatting


int orderCounter= 59;
int generateUniqueOrderID(){
    return orderCounter++;
}

//made it static so only header.cpp | Encapsulation
static bool parseLine(const string& line, MenuItem& m){
    // c = colon
    // s = semicolon
    // a = ampersand
    long long  c = line.find(',');
    long long  s = line.find(';');
    long long  a = line.find('&'); 

if ((c == -1) || (s == -1) || (a == -1)) {
    return false;
}
try{
    // Extracts menuId, name, price, and qty from the line;
    m.menuId = stoi(line.substr(0,c));
    m.name = line.substr(c+1,s-c-1);
    m.price = stod(line.substr(s+1,a-s-1));
    m.qty = stoi(line.substr(a+1));

}catch(...){
    return false;
}
return true;

}

bool loadMenuFromFile(string FileName,MenuItem menu[],int&MenuSize){
    ifstream in(FileName);
    if(in.fail()){    // simpler check for file open
        cout <<"File not found!" << endl;
        return false;
    } 

    string line;
    MenuItem m;
    int Size =0; //reset Menu Size

    while(getline(in,line) && Size < MAX_MENU){
        if(line.empty()) continue;
        if (parseLine(line,m)){
            menu[Size++] = m;
        }
    }
    MenuSize = Size;
    return  Size>0;
}

void showMenuToUser(MenuItem menu[],int menuSize){
    cout <<"\n Full Menu in Stock\n" << endl;
    cout << left << setw(5) << "ID" << setw(25) << "Item" <<right <<setw(8)
         <<"Price" << setw(10)<<"Quantity" <<"\n";
    cout << string(48,'-')<<"\n";
    
    for(int i = 0; i < menuSize; i++){
        if(menu[i].qty >0){
            cout << left << setw(5) << menu[i].menuId << setw(25) << menu[i].name 
            << right <<(setw(8)) << fixed << setprecision(2) << menu[i].price << setw(10)<<menu[i].qty <<"\n";
            
        }
    }
}

bool takeOrderFromUser(MenuItem menu[],int menuSize ,OrderLine order[],int& countOrder){
    
    while(true){
    int id;
    cout << "\nPlease Enter Menu ID or Press '0' to Finish :";
    if (!(cin >> id)) {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Please enter a number.\n";
    continue;              
    }
    if(id==0){break;}

    int idx = -1;
    for (int i =0;i<menuSize;i++){
        if(menu[i].menuId==id){
            idx = i; 
            break;
        }
    }
    
    if(idx==-1){
        cout << "Invalid ID.\n"<< endl;
        cout << "Enter a new ID" << endl;
        continue;
    }

    if(menu[idx].qty <=0){
        cout << "Out Of stock : " << menu[idx].name << "\n";
        continue;
    }


    while(true){
    int UserQty;
    cout << "Select From 1 to "<< menu[idx].qty <<"\n";
    cout << "Enter Quantity :";


    if(cin>>UserQty){
        if(UserQty>0 && UserQty<=menu[idx].qty ){
            //for Order limit checker
            if(countOrder>=MAX_ORDER_LINES){
                cout << "Sorry you have reached your order limit!\n";
                break;
            }
            order[countOrder].OrderId = id;
            order[countOrder].OrderQty = UserQty;
            countOrder++;

            menu[idx].qty -=UserQty;
            break;
        }else {
            cout << "Invalid Input!\n"; 
            cout <<"Please enter new Qty\n";
            cin.clear(); //To clear error flags
            cin.ignore(998,'\n'); // clear wrong input
            continue;
        }
    }else {
        cin.clear();               
        cin.ignore(998, '\n'); 
        cout << "Please enter a number.\n";
        continue;
    }

    }
 }
    return true;
 
}

//calculate total from order by matching menuId
double calculateOrderPrice(MenuItem menu[],int menuSize,OrderLine order[],int countOrder) {
                    
    double total = 0.0;
    for (int i = 0; i < countOrder; ++i) {

        for (int j = 0; j < menuSize; ++j) {

            if (menu[j].menuId == order[i].OrderId) {
                total += menu[j].price * order[i].OrderQty;
                break;
            }
        }
    }

    return total;
}

void saveReceipt(string &outFile,int OrderID, int TableNumber,MenuItem menu[],int menuSize,OrderLine order[],
                    int countOrder, double TotalAmount,const string&paymentMethod,double change){
        //add at the end without overwriting the data - ios::append
        ofstream out(outFile,ios::app);
        if(out.fail()){
            cout << "Faild to write to file!\n";
            return;
        }
        out << "Order ID: " <<OrderID <<"| Table:" <<TableNumber<<"\n";
         out<<"---------------------------------------------------------------\n";
        out << left << setw(5) << "ID" << setw(25) << "Item" <<right <<setw(10)
            <<"Quantity" << setw(10)<<"Price" << setw(12)<< "Line"<<"\n";
        
        //find menu info
        for(int i = 0;i<countOrder; ++i){
            for(int j =0;j<menuSize;++j)
            if(menu[j].menuId==order[i].OrderId){
                double lineTotal = menu[j].price *  order[i].OrderQty;
                out <<left<<setw(5)<<menu[j].menuId << setw(25) << menu[j].name <<right<<setw(10) << order[i].OrderQty <<setw(10) 
                    <<fixed<<setprecision(2)<<menu[j].price<<setw(12) << fixed<<setprecision(2) << lineTotal <<"\n";
                break;
            }
        }
        out <<"---------------------------------------------------------------\n";
        out <<"Total : RM "<<fixed << setprecision(2) << TotalAmount<<"\n";
        out<<"Payment Method: " << paymentMethod<<"\n";
        if(paymentMethod=="Cash"){
            out<<"Change: RM"<<fixed << setprecision(2)<<change<<"\n";
    }
    }




