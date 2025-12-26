#include <iostream>
#include <iomanip>
#include "header.h"
using namespace std;

int main(){
    MenuItem menu[MAX_MENU];
    int menuSize = 0;

    if(!loadMenuFromFile("Menu.txt",menu,menuSize)){
        cout <<"Menu File not found!\n";
        return -1;
    }
    else{
        cout <<"File has Loaded correctly\n";
    }

    int table;
    while(true){
        cout << "\n---New Customer---\n";
        cout << "Enter Table No or(0 to exit): ";
        cin>>table;
        if(table==0)break;//stop program

        //step 2: show menu
    showMenuToUser(menu,menuSize);
      OrderLine order[MAX_ORDER_LINES];
      int countOrder = 0;

      if(!takeOrderFromUser(menu,menuSize ,order,countOrder)){
        cout<<"Input error!\n";
        break;
      }

    if(countOrder ==0){
        cout << "No items was ordered.\n";
        continue;
    }

    double total = calculateOrderPrice(menu,menuSize,order,countOrder);
    cout << "\n----------------------------------\n";
    cout << "Total Amount : RM "<<fixed << setprecision(2) << total <<"\n";
    cout << "\n----------------------------------\n";

    //Payment Selection 
    cout << "\nPlease Select a payment Method:\n";
    cout <<"1.Cash\n";
    cout <<"2.Card\n";
    cout<<"3.eWallet\n";

    int paymentChoice;
    while (true) {
        cout << "Enter Choice from (1 - 3) :";
        if (!(cin >> paymentChoice)) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Please enter a number.\n";
            continue;
        }
        if (paymentChoice >= 1 && paymentChoice <= 3) break;
        cout << "Invalid payment option pls try again\n";
    }

    string paymentMethod;
    double change =0.0;

    if(paymentChoice == 1){

        paymentMethod = "Cash";
        double amountPaid;

    while (true) {
        cout << "Enter Cash RM :";
        if (!(cin >> amountPaid)) {
            cin.clear();
            cin.ignore(998, '\n');
            cout << "Please Enter Valid Payment Amount.\n";
            continue;
        }

        if (amountPaid < total) {
            cout << "Amount is less than total (" << fixed << setprecision(2) << total << "). Please Try again.\n";
            continue; // ask again and again until full amount is received 
        }

        change = amountPaid - total;
        cout << "Payment successful! Change: RM " << fixed << setprecision(2) << change << "\n";
        break; // exit cash loop when valid payment received
    }
}
    else if(paymentChoice ==2){
        paymentMethod = "Card";
        cout <<"Processing card...\n";
        cout << "Payment SuccessFul\n";

    }
    else if(paymentChoice ==3){
        paymentMethod = "eWallet";
        cout <<"Processing eWallet...\n";
        cout << "Payment SuccessFul\n";
    }else{
        cout << "Invalid payment option pls try again\n";
        continue;
    }
    int orderId = generateUniqueOrderID();
    string outFile = "receipt.txt";
    saveReceipt(outFile, orderId, table, menu, menuSize, order, countOrder, total, paymentMethod, change);  
    cout << "Saved receipt for Order ID :" << orderId <<"\n";
    }
    cout << "Thank you!\n";
    cout << "Have a great Day\n";
    return 0;

}