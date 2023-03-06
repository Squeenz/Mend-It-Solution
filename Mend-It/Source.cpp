#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <limits>
#include <string>

using namespace std;

class Branch
{
public:
	virtual string getName() const = 0;
	virtual vector<vector<string>> getStoreItems() const = 0;
	virtual vector<vector<string>> getStoreAccesories() const = 0;
	virtual ~Branch() {};
};

class Treforest : public Branch
{
private:
	vector<vector<string>> const branchItems = { { "hammer", "100" }, { "screwdriver", "50" }, { "wrench", "30" }, { "nail", "1" } };
	vector<vector<string>> const branchAccesories = { {"gloves", "5"}, {"safety glasses", "10"}, {"mask", "15"} };
public:
	string getName() const override { return "Treforest"; }
	vector<vector<string>> getStoreItems() const override { return branchItems; }
	vector<vector<string>> getStoreAccesories() const override { return branchAccesories; }
	~Treforest() {};
};

class Pontypridd : public Branch
{
private:
	vector<vector<string>> const branchItems = { {"drill", "100"}, {"saw", "50"}, {"pliers", "30"}, {"bolt", "1"} };
	vector<vector<string>> const branchAccesories = { {"tape measure", "5"}, {"level", "10"}, {"utility knife", "15"}};
public:
	string getName() const override { return "Pontypridd"; };
	vector<vector<string>> getStoreItems() const override { return branchItems; }
	vector<vector<string>> getStoreAccesories() const override { return branchAccesories; }
	~Pontypridd() {};
};

class Cardiff : public Branch
{
private:
	vector<vector<string>> const  branchItems = { {"paint", "100"}, {"brush", "50"}, {"roller", "30"}, {"putty knife", "1"}};
	vector<vector<string>> const  branchAccesories = { {"sandpaper", "5"}, {"drop cloth", "10"}, {"painter's tape", "15"} };
public:
	string getName() const override { return "Cardiff"; }
	vector<vector<string>> getStoreItems() const override { return branchItems; }
	vector<vector<string>> getStoreAccesories() const override { return branchAccesories; }
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
	string description() override { return title_; }
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
	Accessory(Product* product, string title, double price) : ProductDecorator(product), title_(title), price_(price) {};
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
	vector<string> branches = { "Treforest", "Pontypridd", "Cardiff" };
	vector<pair<Product*, Accessory*>> basket;
	string whatToDisplay;
	string currentBranch_;
	Branch* selectedBranch;
	vector<vector<string>>branchItems;
	vector<vector<string>>branchAccesories;
	string currentAccesory;
	double currentAccesoryPrice;
	int amountOfOptions_;
	int choice_;
	string choiceStr_;
	int infoToShow;
	bool itemAdded;
	bool typeOfInput = true;
	bool done = false;
	bool end_ = false;
public:
	Interface()
	{
		whatToDisplay = "branches";

		while (end_ != true)
		{
			cout << "CHOICE: " << choice_ << endl;
			cout << "CHOICESTR: " << choiceStr_ << endl;

			//If the current branch is empty then display branches otherwise display the selected branch
			currentBranch_ = (currentBranch_ == "") ? "Branches" : currentBranch_;

			cout << "=================================" << endl;
			cout << " Mend It Solutions  ::  " << currentBranch_ << endl;
			cout << "=================================" << endl;

			display(whatToDisplay);

			cout << "===============[INPUT]==================" << endl;
			if (typeOfInput == true)
			{
				cout << "Choose an option (1-" << amountOfOptions_ << "): ";
			}
			else
			{
				cout << "Choose an option (y/n): ";
			} 

			
			if (whatToDisplay == "branches")
			{
				getInput(typeOfInput);
				currentBranch_ = branches.at(choice_ - 1);
				choice_ = 0;
				whatToDisplay = "branchOptions";
			}
			else if (whatToDisplay == "branchOptions")
			{
				getInput(typeOfInput);
			}
			else if (whatToDisplay == "items")
			{
				getInput(typeOfInput);
			}
			//else if (whatToDisplay == "remove item")
			//{
			//	getInput();
			//}
			//else if (whatToDisplay == "view basket")
			//{
			//	getInput();
			//}
			else if (whatToDisplay == "trackOrder")
			{
				getInput(typeOfInput);
			}

			selectedOption(whatToDisplay, choice_);

			system("CLS");
		}

	}

	void display(string whatToShow)
	{
		if (whatToShow == "branches")
		{
			amountOfOptions_ = branches.size();

			for (int i = 0; i < branches.size(); i++)
			{
				cout << "      " << i + 1 << " :: " << branches.at(i) << endl;
			}
		}
		else if (whatToShow == "branchOptions")
		{
			vector<string>options = { "Order Items", "Order Tracking", "Go Back"};

			amountOfOptions_ = options.size();

			for (int i = 0; i < options.size(); i++)
			{
				cout << "      " << i + 1 << " :: " << options.at(i) << endl;
			}

			infoToShow = 0;
		}
		else if (whatToShow == "items")
		{
			selectedBranch = BranchFactory::createBranch(currentBranch_);

			branchItems = selectedBranch->getStoreItems();
			branchAccesories = selectedBranch->getStoreAccesories();

			amountOfOptions_ = branchItems.size() + 3;

			for (int i = 0; i < branchItems.size(); i++)
			{
				cout << "      " << i + 1 << " :: ";

				for (int y = 0; y < branchItems[i].size(); y++)
				{
					cout << branchItems[i][y] << " $ ";
				}
				
				cout << endl;
			}

			cout << "      " << amountOfOptions_ - 2 << " :: " << "Remove Item" << endl;
			cout << "      " << amountOfOptions_ - 1 << " :: " << "Finish Order" << endl;
			cout << "      " << amountOfOptions_ << " :: " << "Go Back" << endl;
			cout << endl;
			information(infoToShow);
			shoppingBasket();
			cout << endl;
 		}
		else if (whatToShow == "trackOrder")
		{
			cout << "ORDER DETAILS			" << endl;
			cout << "=================================" << endl;
			cout << "ORDER ID : {000000000}" << endl;
			cout << "ORDER STATUS : {status}" << endl;
			cout << "DELIVERY DATE : {11/02/2023}" << endl;
			cout << "DELIVERY OPTION: {Delivery option} " << endl;
			cout << "ORDER COST: {Total cost}" << endl;
			cout << "=================================" << endl;
			cout << "	1 :: Go back" << endl;
			cout << endl;
		}
	}

	void information(int infoToShow)
	{
		cout << "==============[INFORMATION]===================" << endl;
		switch (infoToShow)
		{
		case 1:
			cout << "Would you like " << currentAccesory << " for $" << currentAccesoryPrice << " to be added to your order ? " << endl;
			typeOfInput = false;
			break;
		case 2:
			//fix this, make this happen after the y/n input also fix the y/n to normal input after it has been addded to the basket.
			cout << "Would you like this {delivery option} to be added to your order?" << endl;
			typeOfInput = false;
			break;
		case 3:
			cout << "Are you sure you want to leave because the items in the basket will be deleted" << endl;
			typeOfInput = false;
			break;
		case 4:
			cout << "Choose which item you want to remove by the number" << endl;
			typeOfInput = false;
			break;
		case 5:
			cout << "Please confirm you want to proceed with this order" << endl;
			cout << "You won't be able to change the order once it has proceeded" << endl;
			typeOfInput = false;
			break;
		default:
			cout << "To add an item to the basket, type the item's id" << endl;
			cout << "For example if you type 1 then the item labeled as id 1" << endl;
			cout << "Will be added to the basket." << endl;
			typeOfInput = true;
			break;
		}
	}

	void shoppingBasket()
	{
		if (itemAdded == true)
		{
			cout << endl;
			cout << "================[BASKET]=================" << endl;
			cout << "Basket = {";

			double total = 0;
			if (basket.size() != 0)
			{
				for (int i = 0; i < basket.size(); i++)
				{
					cout << " " << basket[i].second->description() << " ";

					total = total + basket[i].second->price();
				}
			}
			else
			{
				cout << " Empty ";
			}

			cout << "}" << endl;

			cout << "Basket Total = { $ " << total << " }" << endl;

			if (choiceStr_ == "y" && done == true || choiceStr_ == "n" && done == true)
			{
				choiceStr_ = "";
				typeOfInput = true;
			}
		}
	}

	void getInput(bool numberInput)
	{
		try
		{
			if (typeOfInput == true)
			{
				if ((cin >> choice_) && numberInput) // check if the input is a number
				{
					if (choice_ > amountOfOptions_ || choice_ < 1)
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the invalid input
						throw invalid_argument("Incorrect number value, Try again: ");
					}
				}
				else
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the invalid input
					throw invalid_argument("Incorrect data type value, Try again: ");
				}
			}
			else
			{
				if ((cin >> choiceStr_) && choiceStr_ == "y" || choiceStr_ == "n")
				{
					choiceStr_;
				}
				else
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the invalid input
					throw invalid_argument("Incorrect answer, Try again (y/n): ");
				}
			}
		}
		catch (const invalid_argument& error)
		{
			cout << error.what();
			if (whatToDisplay == "items")
			{
				getInput(typeOfInput);
			}
			else
			{
				getInput(true);
			}
		}
	}

	//fix everything
	void selectedOption(string whatIsDisplayed, int choice)
	{
		if (whatIsDisplayed == "branchOptions")
		{
			//activates multiple times which cause problems need to be fixed ASP!!!
			switch (choice)
			{
			case 1:
				whatToDisplay = (whatIsDisplayed == "branchOptions") ? "items" : "branches";
				break;
			case 2:
				whatToDisplay = "track order";
				break;
			case 3:
				whatToDisplay = "branches";
				currentBranch_ = "";
				break;
			}
		}
		else if (whatIsDisplayed == "items")
		{			
			/*loop through each item and give them an index so the program knows 
			which input corresponds to which index for example. Item 1 will be index 1 and it will return hammer.*/
			if (choice != 0)
			{
				for (int i = 0; i < this->branchItems.size() + 1; i++)
				{
					if (choice == i)
					{
						if (choice - 1 < branchAccesories.size()) {
							currentAccesory = this->branchAccesories[choice - 1][0];
							currentAccesoryPrice = stod(this->branchAccesories[choice - 1][1]);
						}

						Product* item = new Item(this->branchItems[choice - 1][0], stod(this->branchItems[choice - 1][1]));

						if (currentAccesory == "" && currentAccesoryPrice == 0)
						{
							Accessory* addAccesory = new Accessory(item, currentAccesory, currentAccesoryPrice);
							basket.push_back(make_pair(item, addAccesory));
							choice_ = 0;
						}
						else
						{
							infoToShow = 1;
						}

						if (choiceStr_ == "y")
						{
							Accessory* addAccesory = new Accessory(item, currentAccesory, currentAccesoryPrice);
							basket.push_back(make_pair(item, addAccesory));
							currentAccesory = "";
							currentAccesoryPrice = 0;
							infoToShow = 0;
							choice_ = 0;
							itemAdded = true;
						}
						else if (choiceStr_ == "n")
						{
							Accessory* emptyAccesory = new Accessory(item, "", 0);
							basket.push_back(make_pair(item, emptyAccesory));
							currentAccesory = "";
							currentAccesoryPrice = 0;
							infoToShow = 0;
							choice_ = 0;
							itemAdded = true;
						}

						done = true;
						break;
					}
				}
			}
			
			if (choice == amountOfOptions_ - 2)
			{
				//logic for removing an item from basket
			}
			
			if (choice == amountOfOptions_- 1)
			{
				//logic for finish order
				infoToShow = 5;
				whatToDisplay = "trackOrder";
			}

			//Go back to display the branch options when the last option is selected
			if (choice == amountOfOptions_)
			{
				if (choiceStr_ == "y")
				{
					selectedBranch = nullptr;
					//check to see if they want to leave because it will remove all items from the basket
					whatToDisplay = "branchOptions";
					basket.clear();
					typeOfInput = true;
					itemAdded = false;
				}
				if (choiceStr_ == "n")
				{
					infoToShow = 0;
				}
				else
				{
					infoToShow = 3;
				}
			}
		}
	}
};

int main()
{
	Interface* menu = new Interface;

}

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