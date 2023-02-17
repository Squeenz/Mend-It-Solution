#include <iostream>
#include <vector>

using namespace std;

/*
Display and select a branch
2. Browse and order the main items
3. Browse and order the accessories
4. Cancel/Confirm the Order
5. Pay for the order
6. Track the order in real time (for both over the counter and online sales)
*/

/*
If no existing files are found create template files
branches.txt - holds all of the branches
items.txt - all items that are sold
orders.txt - all comfirmed and payed orders
tracking.txt - all tracking information of orders
*/

/*Patterns to use
 -	Factory Desing = Structure of the branches
 -	Decorator Desing = Implementation of additional accessories
 -	Observer Pattern = Real-time Tracking
*/

class Branch
{
public:
	virtual string getName() const = 0;
	virtual vector<string> getStoreItems() const = 0;
	virtual vector<string> getStoreAccesories() const = 0;
};

class Treforest : public Branch
{
public:
	string getName() const override
	{
		return "Treforest";
	};
	vector<string> getStoreItems() const override 
	{
		return { "hammer", "screwdriver", "wrench", "nail" };
	}
	vector<string> getStoreAccesories() const override {
		return { "gloves", "safety glasses", "mask" };
	}
};

class Pontypridd : public Branch
{
public:
	string getName() const override
	{
		return "Pontypridd";
	};
	vector<string> getStoreItems() const override 
	{
		return { "drill", "saw", "pliers", "bolt" };
	}
	vector<string> getStoreAccesories() const override {
		return { "tape measure", "level", "utility knife" };
	}
};

class Cardiff : public Branch
{
public:
	string getName() const override
	{
		return "Cardiff";
	}
	vector<string> getStoreItems() const override
	{
		return { "paint", "brush", "roller", "putty knife" };
	}
	vector<string> getStoreAccesories() const override {
		return { "sandpaper", "drop cloth", "painter's tape" };
	}
};

class BranchFactory
{
public:
	static Branch* createBranch(const string& branchName)
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
	}
};

/*
-----------------------------------------------------------------------
Create the pontypridd branch and print out the items that it holds
-----------------------------------------------------------------------
	Branch* Pontypridd = BranchFactory::createBranch("Pontypridd");
	cout << Pontypridd->getName() << endl;
	cout << "Pontypridd's Store Items: " << endl;
	for (int i = 0; i < Pontypridd->getStoreItems().size(); i++)
	{
		cout << Pontypridd->getStoreItems().at(i) << ", ";
	}

	cout << endl;
	cout << "Pontypridd's Store Accesories: " << endl;
	for (int i = 0; i < Pontypridd->getStoreAccesories().size(); i++)
	{
		cout << Pontypridd->getStoreAccesories().at(i) << ", ";
	}
*/

int main()
{

}