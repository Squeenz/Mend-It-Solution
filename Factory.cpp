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

void Branch::setStoreItems(const string& item, const string& price)
{
	vector<string> tmpItem = { item, price };
	branchItems.push_back(tmpItem);
}

void Branch::setStoreAccesories(const string& item, const string& price)
{
	vector<string> tmpItem = { item, price };
	branchAccesories.push_back(tmpItem);
}

void branchDataToJson(json& j, const Branch* b) {
	j = json{
		{"Branch", b->getName()},
		{"Items", b->getStoreItems()},
		{"Accessories", b->getStoreAccesories()},
	};
}

void branchDataFromJson(const json& j, Branch* b) {
	// Use the at() function to retrieve values from the JSON object and pass them to setStoreItems() and setStoreAccessories().
	// If the JSON object contains multiple items or accessories, you may need to use a loop to iterate over them.
	b->setStoreItems(j.at("Items").at(0).at(0).get<string>(), j.at("Items").at(0).at(1).get<string>());
	//b->setStoreAccesories(j.at("Accessories").at(0).at(0).get<string>(), j.at("Accessories").at(0).at(1).get<string>());
}

void Branch::createData(Branch* branch)
{
	// create JSON object
	json myJson;
	branchDataToJson(myJson, branch);
	ofstream outFile(branch->getName() + "_Items.json");
	outFile << myJson.dump(4) << std::endl;
	outFile.close();
}

void Branch::importData(Branch* branch)
{
	ifstream f(branch->getName() + "_Items.json", ifstream::in);

	json myJson; // create uninitialized json object

	f >> myJson; // initialize json object with what was read from file

	//std::cout << myJson << std::endl; // prints json object to screen

	cout << myJson["Accesories"];
	cout << myJson["Accesories"].size() << endl;
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

