#include <iostream>
#include <vector>
#include <map>
#include <time.h>

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
public:
	Item(string title, double price) : title_(title), price_(price) {};
	string description() override { return title_;  }
	double price() override { return price_; }
private:
	string title_;
	double price_;
};

class ProductDecorator : public Product
{
public:
	ProductDecorator(Product* product) : product_(product) {};
	string description() override { return product_->description(); }
	double price() override { return product_->price(); }
protected:
	Product* product_;
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
public:
	Accessory(Product* product, string title, double price) : ProductDecorator(product), title_(title), price_(price){};
	string description() override { return product_->description() + ", " + title_; }
	double price() override { return product_->price() + price_; }
private:
	string title_;
	double price_;
};

/*

Creates the pontypridd branch and iterates through the items map

	Branch* Pontypridd = BranchFactory::createBranch("Pontypridd");
	map<string, double>::iterator it;

	// Iterate using iterator in for loop
	for (const auto& element : Pontypridd->getStoreItems()) {
		string itemName = element.first;
		double itemPrice = element.second;


		cout << "Order" << endl;
		Product* item = new Item(itemName, itemPrice);
		cout << item->description() << " : " << item->price() << endl;

		Product* nextDay = new NextDayDelivery(item);
		cout << nextDay->description() << " : " << nextDay->price() << endl;

		delete nextDay;
	}
*/

int main()
{
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
}