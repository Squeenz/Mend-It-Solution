#pragma once
#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <string>
#include "Observer.h"

using namespace std;

class Branch
{
private:
	vector<Order> onlineOrders = {};
	vector<Order> instoreOrders = {};
public:
	virtual string getName() const = 0;
	virtual vector<vector<string>> getStoreItems() const = 0;
	virtual vector<vector<string>> getStoreAccesories() const = 0;
	void saveOrderToBranch(Order order, string type);
	vector<Order> getBranchOrders(string type);
};

class Treforest : public Branch
{
private:
	vector<vector<string>> const branchItems = { { "hammer", "100" }, { "screwdriver", "50" }, { "wrench", "30" }, { "nail", "1" } };
	vector<vector<string>> const branchAccesories = { {"gloves", "5"}, {"safety glasses", "10"}, {"mask", "15"} };
public:
	string getName() const override;
	vector<vector<string>> getStoreItems() const override;
	vector<vector<string>> getStoreAccesories() const override;
};

class Pontypridd : public Branch
{
private:
	vector<vector<string>> const branchItems = { {"drill", "100"}, {"saw", "50"}, {"pliers", "30"}, {"bolt", "1"} };
	vector<vector<string>> const branchAccesories = { {"tape measure", "5"}, {"level", "10"}, {"utility knife", "15"} };
public:
	string getName() const override;
	vector<vector<string>> getStoreItems() const override;
	vector<vector<string>> getStoreAccesories() const override;
};

class Cardiff : public Branch
{
private:
	vector<vector<string>> const  branchItems = { {"paint", "100"}, {"brush", "50"}, {"roller", "30"}, {"putty knife", "1"} };
	vector<vector<string>> const  branchAccesories = { {"sandpaper", "5"}, {"drop cloth", "10"}, {"painter's tape", "15"} };
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



