#pragma once
#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include "Product.h"
#include <iomanip>
#include <iostream>

using namespace std;

//set up the observer pattern
class Order
{
private:
	string id_;
	string date_;
	string status_;
	string type_;
	string branch_;
	vector<pair<Product*, Accessory*>> items_;
	string generateID(const int len);
public:
	Order(string branch, string type, vector<pair<Product*, Accessory*>> items);
	string getBranch();
	string setID();
	string getID();
	string getDate();
	string setStatus(string state);
	string getStatus();
	vector<pair<Product*, Accessory*>> getItems();
};

class Observer {
public:
	virtual void update(const vector<Order>& orders) = 0;
};

class Subject {
public:
	void Attach(Observer* observer);
	void Detach(Observer* observer);
	void Notify(const vector<Order>& orders);
private:
	vector<Observer*> observers_;
};

class OrderTracker : public Observer {
public:
	OrderTracker(const string& name);
	void update(const vector<Order>& orders) override;
private:
	string name_;
};

#endif //OBSERVER_H
