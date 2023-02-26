#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include <stdlib.h>
#include<limits>

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

//Factory Pattern - Line 30 to 108
class Branch
{
public:
	virtual string getName() const = 0;
	virtual map<string, double> getStoreItems() const = 0;
	virtual map<string, double> getStoreAccesories() const = 0;
	virtual ~Branch() {};
};

class Treforest : public Branch
{
private:
	map<string, double> branchItems = { {"hammer", 100}, {"screwdriver", 50}, {"wrench", 30}, {"nail", 1} };
	map<string, double> branchAccesories = { {"gloves", 5}, {"safety glasses", 10}, {"mask", 15} };
public:
	string getName() const override { return "Treforest"; }
	map<string, double> getStoreItems() const override { return branchItems; }
	map<string, double> getStoreAccesories() const override { return branchAccesories; }
	~Treforest() {};
};

class Pontypridd : public Branch
{
private:
	map<string, double> branchItems = { {"drill", 100}, {"saw", 50}, {"pliers", 30}, {"bolt", 1} };
	map<string, double> branchAccesories = { {"tape measure", 5}, {"level", 10}, {"utility knife", 15} };
public:
	string getName() const override { return "Pontypridd"; };
	map<string, double> getStoreItems() const override { return branchItems; }
	map<string, double> getStoreAccesories() const override { return branchAccesories; }
	~Pontypridd() {};
};

class Cardiff : public Branch
{
private:
	map<string, double> branchItems = { {"paint", 100}, {"brush", 50}, {"roller", 30}, {"putty knife", 1} };
	map<string, double> branchAccesories = { {"sandpaper", 5}, {"drop cloth", 10}, {"painter's tape", 15} };
public:
	string getName() const override{ return "Cardiff"; }
	map<string, double> getStoreItems() const override{ return branchItems; }
	map<string, double> getStoreAccesories() const override { return branchAccesories; }
	~Cardiff() {};
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

class Product
{
public:
	virtual string description() = 0;
	virtual double price() = 0;
};

class Item : public Product
{
private:
	string title_;
	double price_;
public:
	Item(string title, double price) : title_(title), price_(price) {};
	string description() override { return title_;  }
	double price() override { return price_; }
};

class ProductDecorator : public Product
{
protected:
	Product* product_;
public:
	ProductDecorator(Product* product) : product_(product) {};
	string description() override { return product_->description(); }
	double price() override { return product_->price(); }
};

//Add a check to only one can be selected as an option
class NextDayDelivery : public ProductDecorator
{
public:
	NextDayDelivery(Product* product) : ProductDecorator(product) {};
	string description() override { return product_->description() + ", Next Day Delivery"; }
	double price() override { return product_->price() + 15.50; }
};

class ExpressDelivery : public ProductDecorator
{
public:
	ExpressDelivery(Product* product) : ProductDecorator(product) {};
	string description() override { return product_->description() + ", Express Delivery"; }
	double price() override { return product_->price() + 5.50; }
};

class Accessory : public ProductDecorator
{
private:
	string title_;
	double price_;
public:
	Accessory(Product* product, string title, double price) : ProductDecorator(product), title_(title), price_(price){};
	string description() override { return product_->description() + ", " + title_; }
	double price() override { return product_->price() + price_; }
};

//Work in progress 
//Going to work on the interface for now then comeback to this.
class Observer
{
public:
	virtual void update() = 0;
};

class Subject
{
public:
	virtual void registerObserver() = 0;
	virtual void unregisterObserver() = 0;
	virtual void notifyObserver() = 0;
};

//re-code all of the shit code.
class Interface
{
private:
	vector<string> branches = { "Treforest", "Pontypridd", "Cardiff"};
	string currentBranch_;
	int choice_;
	bool end_ = false;
public:
	Interface()
	{
		//If the current branch is empty then display branches otherwise display the selected branch
		currentBranch_ = (currentBranch_ == "") ? currentBranch_ = "Branches" : currentBranch_ = currentBranch_;
		string whatToShow = "branches";

		while (end_ != true)
		{
			cout << "=================================" << endl;
			cout << " Mend It Solutions  ::  " << currentBranch_ << endl;
			cout << "=================================" << endl;
			
			this->display(whatToShow);

			cout << "=================================" << endl;
			cout << "Choose a branch (1-3): ";

			try {
				this->getInput();
				whatToShow = "items";
			}
			catch(const invalid_argument& error)
			{
				cout << error.what() << endl;
			}
			cout << "=================================" << endl;

			this->selectedOption(choice_);
			system("CLS");
		}

	}

	void display(string whatToShow)
	{
		if (whatToShow == "branches")
		{
			for (int i = 0; i < branches.size(); i++)
			{
				cout << i + 1 << " :: " << branches.at(i) << endl;
			}
		}
		else if (whatToShow == "items")
		{
			Branch* branch = BranchFactory::createBranch(currentBranch_);

			map<string, double>::iterator it;

			for (const auto& object : branch->getStoreItems())
			{
				string name = object.first;
				double price = object.second;

				cout << name << "  ::  " << price << endl;
			}
		}
	}

	int getInput()
	{
		cin >> choice_;
		if (choice_ > 3 || choice_ < 1)
		{
			throw invalid_argument("Incorrect number value, Try again");
		}
		//need to work on this thurwer to check if input is char etc..
		else if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max());
			throw invalid_argument("Incorrect data type value, Try again");
		}
		else
		{
			return choice_;
		}
	}
	//fix everything
	void selectedOption(int branchChoice)
	{
		currentBranch_ = branches.at(choice_-1);
		
		/*
		Branch* branch = BranchFactory::createBranch(currentBranch_);
		map<string, double>::iterator it;

		cout << "====================================" << endl;
		cout << currentBranch_ << "  ::  MAIN ITEMS" << endl;
		cout << "====================================" << endl;
		for ( const auto& object : branch->getStoreItems())
		{
			string name = object.first;
			double price = object.second;

			cout << name << "  ::  " << price << endl;
		}

		cout << "====================================" << endl;
		cout << currentBranch_ << "  ::  ACCESORIES" << endl;
		cout << "====================================" << endl;
		for (const auto& object : branch->getStoreAccesories())
		{
			string name = object.first;
			double price = object.second;

			cout << name << "  ::  " << price << endl;
		}

		//testing decorator pattern
		cout << "====================================" << endl;
		cout << currentBranch_ << "  ::  ORDER TEST" << endl;
		cout << "====================================" << endl;

		//item we want for the test
		string itemName = "hammer";
		double itemPrice = 0;
		
		for (const auto& object : branch->getStoreItems())
		{
			string name = object.first;
			double price = object.second;

			if (name == itemName)
			{
				itemPrice = price;
				break;
			}
		}

		Product* orderItem = new Item(itemName, itemPrice);

		//accesory user wants
		string accItemName = "gloves";
		double accItemPrice = 0;

		for (const auto& object : branch->getStoreAccesories())
		{
			string name = object.first;
			double price = object.second;

			if (name == accItemName)
			{
				accItemPrice = price;
				break;
			}
		}

		Product* accItem = new Accessory(orderItem, accItemName, accItemPrice);

		cout << accItem->description() << " :: " << accItem->price() << endl;

		string accItemName2 = "safety glasses";
		double accItemPrice2 = 0;

		for (const auto& object : branch->getStoreAccesories())
		{
			string name = object.first;
			double price = object.second;

			if (name == accItemName2)
			{
				accItemPrice2 = price;
				break;
			}
		}
		
		Product* accItem2 = new Accessory(accItem, accItemName2, accItemPrice2);
		cout << accItem2->description() << " :: " << accItem2->price() << endl;
		*/

		/*
		Product* orderItem = new Item(itemName, itemPrice);
		
		cout << "Normal Order of item: " << endl;
		cout << orderItem->description() << " :: " << orderItem->price() << endl;
		
		Product* orderWithNext = new NextDayDelivery(orderItem);
		cout << "Order with next day delivery: " << endl;
		cout << orderWithNext->description() << " :: " << orderWithNext->price() << endl;
		*/
	}
};

/*
	Branch* Pontypridd = BranchFactory::createBranch("Pontypridd");
	map<string, double>::iterator it;

	// Iterate using iterator in for loop
	for (const auto& element : Pontypridd->getStoreItems()) {
		string itemName = element.first;
		double itemPrice = element.second;

		cout << "Order" << endl;
		Product* item = new Item(itemName, itemPrice);

		//cout << item->description() << " : " << item->price() << endl;

		for (const auto& element : Pontypridd->getStoreAccesories())
		{
			string itemAccName = element.first;
			double itemAccPrice = element.second;

			Product* itemAcc = new Accessory(item, itemAccName, itemAccPrice);
			cout << itemAcc->description() << " : " << itemAcc->price() << endl;

			Product* nextDayDelivery = new NextDayDelivery(itemAcc);
			cout << nextDayDelivery->description() << " : " << nextDayDelivery->price() << endl;

			//delete itemAcc;
			delete nextDayDelivery;
		}
	}
*/

int main()
{
	Interface* menu = new Interface;

}