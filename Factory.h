#pragma once
#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <string>
#include <fstream>
#include "Observer.h"
#include "Json.h"

using namespace std;
using json = nlohmann::json;

class Branch
{
protected:
	vector<vector<string>> branchItems;
	vector<vector<string>> branchAccesories;
	vector<Order> onlineOrders;
	vector<Order> instoreOrders;
public:
	virtual string getName() const = 0;
	virtual vector<vector<string>> getStoreItems() const = 0;
	virtual vector<vector<string>> getStoreAccesories() const = 0;
	vector<Order> getBranchOrders(string type);
	void addItemToBranch(string item, string price);
	void addAccesoryToBranch(string item, string price);
	void createData(Branch* branch);
	void importData();
	void exportData(Order* orders);
	void saveOrderToBranch(Order order, string type);
};


class Treforest : public Branch
{
public:
	string getName() const override;
	vector<vector<string>> getStoreItems() const override;
	vector<vector<string>> getStoreAccesories() const override;
};

class Pontypridd : public Branch
{
public:
	string getName() const override;
	vector<vector<string>> getStoreItems() const override;
	vector<vector<string>> getStoreAccesories() const override;
};

class Cardiff : public Branch
{
public:
	string getName() const override;
	vector<vector<string>> getStoreItems() const override;
	vector<vector<string>> getStoreAccesories() const override;
};

class BranchFactory
{
public:
	static Branch* createBranch(const string& branchName);
};

#endif //FACTORY_H



