#pragma once
#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>
#include "Product.h"
#include "Factory.h"

using namespace std;

class InterfaceCore
{
private:
	int numOfOptions_ = 0;
	int numChoice_ = 0;
	string txtChoice_ = "";
	bool end_ = false;
public:
	void information(int scenario);
	void getInputAndCheck(bool isInputNumber);
	void setNumOfOptions(int numOfOptions);
	void resetChoices();
	int getNumOfOptions();
	int getNumChoice();
	string getTxtChoice();
	bool getEnd();
};

class ShoppingBasket
{
private:
	bool show_ = false;
	vector<pair<Product*, ProductDecorator*>> basket_;
public:
	void display();
	bool setShow(bool status);
	void addItemToBasket(Product* product, ProductDecorator* accessory);
	vector<pair<Product*, ProductDecorator*>> getItems();
	Product* getLastItem();
	void removeItemFromBasket(int choice);
	void clear();
	void creditCardInput();
	void otherPaymentInput();
	void payment(vector<string> options, string typeOfPayment);
	void orderBasketItems(Branch* selectedBranch);
};

class MainInterface : public InterfaceCore
{
private:
	const vector<string> allBranches = { "Treforest", "Pontypridd", "Cardiff" };
	Branch* selectedBranch_ = nullptr;
	string currentScreen_ = "Branches";
	int infoCase_ = 0;
	bool typeOfInput_ = true;
public:
	MainInterface();
	void display(ShoppingBasket* basket);
	void header(string branch);
	void branches();
	void branchOptions();
	void removeItem(ShoppingBasket* basket);
	void branchItems(ShoppingBasket* basket);
	void paymentAndOrder(ShoppingBasket* basket);
	void deliveryOptions(ShoppingBasket* basket);
	void orderTracking();
};

#endif //SINGLETON_H