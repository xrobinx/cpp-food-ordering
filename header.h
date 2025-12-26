#ifndef FOOD_ORDERING_HEADER_H
#define FOOD_ORDERING_HEADER_H
#include <iostream>
using namespace std;
constexpr int MAX_MENU = 20;
constexpr int MAX_ORDER_LINES = 20;

struct MenuItem{
    int menuId{};
    std::string name;
    double price{};
    int qty{};
};

struct OrderLine {
    int OrderId{};
    int OrderQty{};
};


bool loadMenuFromFile(string FileName,MenuItem menu[],int&MenuSize);
void showMenuToUser(MenuItem menu[],int menuSize);
bool takeOrderFromUser(MenuItem menu[],int menuSize ,OrderLine order[],int& countOrder);
double calculateOrderPrice(MenuItem menu[],int menuSize,OrderLine order[],int countOrder);
void saveReceipt(string &outFile,int OrderID, int TableNumber,MenuItem menu[],int menuSize,OrderLine order[],int countOrder, double TotalAmount,const string&paymentMethod,double change);
int generateUniqueOrderID();

#endif