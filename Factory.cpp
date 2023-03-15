#include "Factory.h"

void Branch::saveOrderToBranch(Order order, string type)
{
	if (type == "Online")
	{
		this->onlineOrders.push_back(order);
	}
	else if (type == "Instore")
	{
		this->instoreOrders.push_back(order);
	}
}

vector<Order> Branch::getBranchOrders(string type)
{
	if (type == "Online")
	{
		return this->onlineOrders;
	}
	else if (type == "Instore")
	{
		return this->instoreOrders;
	}
}

//Treforest Branch public methods
string Treforest::getName() const
{
	return "Treforest";
}
vector<vector<string>> Treforest::getStoreItems() const 
{ 
	return branchItems; 
}
vector<vector<string>> Treforest::getStoreAccesories() const 
{ 
	return branchAccesories; 
}

//Pontypridd Branch public methods
string Pontypridd::getName() const
{
	return "Pontypridd";
}
vector<vector<string>> Pontypridd::getStoreItems() const
{
	return branchItems;
}
vector<vector<string>> Pontypridd::getStoreAccesories() const
{
	return branchAccesories;
}

//Cardiff Branch public methods
string Cardiff::getName() const
{
	return "Cardiff";
}
vector<vector<string>> Cardiff::getStoreItems() const
{
	return branchItems;
}
vector<vector<string>> Cardiff::getStoreAccesories() const
{
	return branchAccesories;
}

//Branch Factory
Branch* BranchFactory::createBranch(const string& branchName)
{
	if (branchName == "Treforest")
	{
		return new Treforest();
	}
	else if (branchName == "Pontypridd")
	{
		return new Pontypridd();
	}
	else if (branchName == "Cardiff")
	{
		return new Cardiff();
	}
	else
	{
		return nullptr;
	}
};

