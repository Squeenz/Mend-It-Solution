#include <Windows.h>
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
void defaultBranchDataToJson(json& j, const Branch* b) {
	j = json{
		{"Branch", b->getName()},
		{"Items", b->getDefaultStoreItems()},
		{"Accessories", b->getDefaultStoreAccesories()},
	};
}

//Creates the json file, the data for this is created from the branchDataToJson function
void Branch::createData(Branch* branch)
{
	const int bufferSize = MAX_PATH; // maxium character lenght of a file path
	wchar_t buffer[bufferSize]; //array which is the size of the bufferSize(max_path)
	GetCurrentDirectory(bufferSize, buffer); //Get's the current directory path

	const wchar_t* dirName = L"BranchData";//The desired name of the new path
	const int pathLength = wcslen(buffer) + wcslen(dirName) + 2; // calculates the required length of the path, 2 for the '\\' and null terminator
	wchar_t* fullPath = new wchar_t[pathLength]; //dynamically allocates a new buffer of pathLength
	swprintf_s(fullPath, pathLength, L"%s\\%s", buffer, dirName); //function to format and store a string in the fullPath buffer.The format string L"%s\\%s" specifies that the string should start with the buffer string

	if (!CreateDirectory(fullPath, NULL)) {
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			//If it already exits just do nothing because the importing of data still
			//happens
		}
		else {
			//If the creation fails show the user the error
			cout << "Failed to create directory. Error: " << GetLastError() << endl;
		}
	}
	else {
		//If the folder directory doesn't exist create the different branches to generate
		//default items inplace for the user. If they do exits the other items will be used
		Branch* Treforest = BranchFactory::createBranch("Treforest");
		Branch* Pontypridd = BranchFactory::createBranch("Pontypridd");
		Branch* Cardiff = BranchFactory::createBranch("Cardiff");

		//Vector to simply store branches for later loop
		vector<Branch*> branches = { Treforest, Pontypridd, Cardiff };

		//create the json object
		json myJson;

		//Loop through each of of the branches and create the default data json files
		for (int i = 0; i < branches.size(); i++)
		{
			defaultBranchDataToJson(myJson, branches[i]);
			ofstream outFile("BranchData/" + branches[i]->getName() + "_Items.json");
			outFile << myJson.dump(4) << std::endl;
			outFile.close();
		}

		//Delete the pointers since they are no longer needed
		delete Treforest;
		delete Pontypridd;
		delete Cardiff;
	}

	//Delete the fullpath
	delete[] fullPath;
}

//Import data from the json files when called
void Branch::importData()
{
	//read the json file
	ifstream f("BranchData/"+ this->getName() + "_Items.json", ifstream::in);

	json myJson; // create uninitialized json object

	f >> myJson; // initialize json object with what was read from file

	//loop through the arrays in the json file and add each item to the branch
	for (int i = 0; i < myJson["Items"].size(); i++)
	{
		//add the item to the branch
		this->addItemToBranch(myJson["Items"].at(i).at(0), myJson["Items"].at(i).at(1));
	}

	//loop through the arrays in the json file and add each accesory to the branch
	for (int i = 0; i < myJson["Accessories"].size(); i++)
	{
		//add the accesory to the branch
		this->addAccesoryToBranch(myJson["Accessories"].at(i).at(0), myJson["Accessories"].at(i).at(1));
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
vector<vector<string>> Treforest::getDefaultStoreItems() const
{
	return defaultItems;
}
vector<vector<string>> Treforest::getDefaultStoreAccesories() const
{
	return defaultAccesories;
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
vector<vector<string>> Pontypridd::getDefaultStoreItems() const
{
	return defaultItems;
}
vector<vector<string>> Pontypridd::getDefaultStoreAccesories() const
{
	return defaultAccesories;
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
vector<vector<string>> Cardiff::getDefaultStoreItems() const
{
	return defaultItems;
}
vector<vector<string>> Cardiff::getDefaultStoreAccesories() const
{
	return defaultAccesories;
}


//Branch Factory, creates the different branch objects
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

