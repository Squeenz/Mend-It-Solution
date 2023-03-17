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
	vector<vector<string>> defaultItems;
	vector<vector<string>> defaultAccesories;
	vector<vector<string>> branchItems;
	vector<vector<string>> branchAccesories;
	vector<Order> onlineOrders;
	vector<Order> instoreOrders;
public:
	virtual string getName() const = 0;
	virtual vector<vector<string>> getStoreItems() const = 0;
	virtual vector<vector<string>> getStoreAccesories() const = 0;
	virtual vector<vector<string>> getDefaultStoreItems() const = 0;
	virtual vector<vector<string>> getDefaultStoreAccesories() const = 0;
	virtual vector<Order> getBranchOnlineOrders() const = 0;
	virtual vector<Order> getBranchInstoreOrders() const = 0;
	void exportOrders(json& j, const Branch* b);
	void addItemToBranch(string item, string price);
	void addAccesoryToBranch(string item, string price);
	void createData(Branch* branch);
	void importData();
	void saveOrderToBranch(Order order, string type);
};


class Treforest : public Branch
{
private:
	vector<vector<string>> const defaultItems = { { "hammer", "100" }, { "screwdriver", "50" }, { "wrench", "30" }, { "nail", "1" } };
	vector<vector<string>> const defaultAccesories = { {"gloves", "5"}, {"safety glasses", "10"}, {"mask", "15"} };
public:
	string getName() const override;
	vector<vector<string>> getStoreItems() const override;
	vector<vector<string>> getStoreAccesories() const override;
	vector<vector<string>> getDefaultStoreItems() const override;
	vector<vector<string>> getDefaultStoreAccesories() const override;
	vector<Order> getBranchOnlineOrders() const override;
	vector<Order> getBranchInstoreOrders() const override;
};

class Pontypridd : public Branch
{
private:
	vector<vector<string>> const defaultItems = { {"drill", "100"}, {"saw", "50"}, {"pliers", "30"}, {"bolt", "1"} };
	vector<vector<string>> const defaultAccesories = { {"tape measure", "5"}, {"level", "10"}, {"utility knife", "15"} };
public:
	string getName() const override;
	vector<vector<string>> getStoreItems() const override;
	vector<vector<string>> getStoreAccesories() const override;
	vector<vector<string>> getDefaultStoreItems() const override;
	vector<vector<string>> getDefaultStoreAccesories() const override;
	vector<Order> getBranchOnlineOrders() const override;
	vector<Order> getBranchInstoreOrders() const override;
};

class Cardiff : public Branch
{
private:
	vector<vector<string>> const defaultItems = { {"paint", "100"}, {"brush", "50"}, {"roller", "30"}, {"putty knife", "1"} };
	vector<vector<string>> const defaultAccesories = { {"sandpaper", "5"}, {"drop cloth", "10"}, {"painter's tape", "15"} };
public:
	string getName() const override;
	vector<vector<string>> getStoreItems() const override;
	vector<vector<string>> getStoreAccesories() const override;
	vector<vector<string>> getDefaultStoreItems() const override;
	vector<vector<string>> getDefaultStoreAccesories() const override;
	vector<Order> getBranchOnlineOrders() const override;
	vector<Order> getBranchInstoreOrders() const override;
};

class BranchFactory
{
public:
	static Branch* createBranch(const string& branchName);
};

#endif //FACTORY_H



