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
private:
	vector<vector<string>> branchItems;
	vector<vector<string>> branchAccesories;
	vector<Order> onlineOrders;
	vector<Order> instoreOrders;
public:
	virtual string getName() const = 0;
	virtual vector<vector<string>> getStoreItems() const = 0;
	virtual vector<vector<string>> getStoreAccesories() const = 0;
	vector<Order> getBranchOrders(string type);
	void setStoreItems(const string& item, const string& price);
	void setStoreAccesories(const string& item, const string& price);
	void createData(Branch* branch);
	void importData(Branch* branch);
	void exportData(Order* orders);
	void saveOrderToBranch(Order order, string type);
};


class Treforest : public Branch
{
private:
	vector<vector<string>> branchItems = {};
	vector<vector<string>> branchAccesories = {};
	//vector<vector<string>> branchItems = { { "hammer", "100" }, { "screwdriver", "50" }, { "wrench", "30" }, { "nail", "1" } };
	//vector<vector<string>> branchAccesories = { {"gloves", "5"}, {"safety glasses", "10"}, {"mask", "15"} };
public:
	string getName() const override;
	vector<vector<string>> getStoreItems() const override;
	vector<vector<string>> getStoreAccesories() const override;
};

class Pontypridd : public Branch
{
private:
	vector<vector<string>> branchItems;
	vector<vector<string>> branchAccesories;
	//vector<vector<string>> branchItems = { {"drill", "100"}, {"saw", "50"}, {"pliers", "30"}, {"bolt", "1"} };
	//vector<vector<string>> branchAccesories = { {"tape measure", "5"}, {"level", "10"}, {"utility knife", "15"} };
public:
	string getName() const override;
	vector<vector<string>> getStoreItems() const override;
	vector<vector<string>> getStoreAccesories() const override;
};

class Cardiff : public Branch
{
private:
	vector<vector<string>> branchItems;
	vector<vector<string>> branchAccesories;
	//vector<vector<string>> branchItems = { {"paint", "100"}, {"brush", "50"}, {"roller", "30"}, {"putty knife", "1"} };
	//vector<vector<string>> branchAccesories = { {"sandpaper", "5"}, {"drop cloth", "10"}, {"painter's tape", "15"} };
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



