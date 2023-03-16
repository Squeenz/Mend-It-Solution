#include "Factory.h"

//Allows you to save an order to the branch to keep it for exporting
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

//Allows you to add items to the branch
void Branch::addItemToBranch(string item, string price)
{
	vector<string> itemGroup = { item, price };
	branchItems.push_back(itemGroup);
}

//Allows you to add accesories to the branch
void Branch::addAccesoryToBranch(string item, string price)
{
	vector<string> itemGroup = { item, price };
	branchAccesories.push_back(itemGroup);
}

//Creates the json object which stores all of branches item data
void branchDataToJson(json& j, const Branch* b) {
	j = json{
		{"Branch", b->getName()},
		{"Items", b->getStoreItems()},
		{"Accessories", b->getStoreAccesories()},
	};
}

//Creates the json file the data for this is created from the branchDataToJson function
void Branch::createData(Branch* branch)
{
	json myJson;
	branchDataToJson(myJson, branch);
	ofstream outFile(branch->getName() + "_Items.json");
	outFile << myJson.dump(4) << std::endl;
	outFile.close();
}

void Branch::importData()
{
	ifstream f(this->getName() + "_Items.json", ifstream::in);

	json myJson; // create uninitialized json object

	f >> myJson; // initialize json object with what was read from file

	for (int i = 0; i < myJson["Items"].size(); i++)
	{
		this->addItemToBranch(myJson["Items"].at(i).at(0), myJson["Items"].at(i).at(1));
	}

	for (int i = 0; i < myJson["Accesories"].size(); i++)
	{
		this->addAccesoryToBranch(myJson["Accesories"].at(i).at(0), myJson["Accesories"].at(i).at(1));
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

