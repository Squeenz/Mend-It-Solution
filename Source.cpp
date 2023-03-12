#include "iostream"
#include "sqlite3.h"
#include "Factory.h"
#include "Product.h"
#include "Observer.h"
#include "Singleton.h"
#include "sqlite3.h"
#include "stdio.h"


using namespace std;

//class Interface
//{
//private:
//	const vector<string> branches = { "Treforest", "Pontypridd", "Cardiff" };
//	vector<pair<Product*, Accessory*>> basket;
//	vector<Order> onlineOrders;
//	vector<Order> instoreOrders;
//	string whatToDisplay;
//	string currentBranch_;
//	Branch* selectedBranch;
//	vector<vector<string>>branchItems;
//	vector<vector<string>>branchAccesories;
//	string currentAccesory;
//	double currentAccesoryPrice;
//	int amountOfOptions_;
//	int choice_;
//	string choiceStr_;
//	int infoToShow;
//	bool typeOfInput = true;
//	bool showBasket = false;
//	bool done = false;
//	bool end_ = false;
//public:
//	Interface()
//	{
//		srand((unsigned)time(NULL) * 0);
//		whatToDisplay = "branches";
//
//		while (end_ != true)
//		{
//			If the current branch is empty then display branches otherwise display the selected branch
//			currentBranch_ = (currentBranch_ == "") ? "Branches" : currentBranch_;
//
//			cout << "=================================" << endl;
//			cout << " Mend It Solutions  ::  " << currentBranch_ << endl;
//			cout << "=================================" << endl;
//
//			display(whatToDisplay);
//
//			cout << "===============[INPUT]==================" << endl;
//			if (typeOfInput == true)
//			{
//				cout << "Choose an option (1-" << amountOfOptions_ << "): ";
//			}
//			else
//			{
//				cout << "Choose an option (y/n): ";
//			}
//
//			if (whatToDisplay == "branches")
//			{
//				getInput(typeOfInput);
//				currentBranch_ = branches.at(choice_ - 1);
//				choice_ = 0;
//				whatToDisplay = "branchOptions";
//			}
//			else if (whatToDisplay == "orderTracking")
//			{
//				getInput(typeOfInput);
//			}
//			else if (whatToDisplay == "branchOptions")
//			{
//				getInput(typeOfInput);
//			}
//			else if (whatToDisplay == "items")
//			{
//				getInput(typeOfInput);
//			}
//			else if (whatToDisplay == "removeItem")
//			{
//				getInput(typeOfInput);
//			}
//			else if (whatToDisplay == "order")
//			{
//				getInput(typeOfInput);
//			}
//
//			selectedOption(whatToDisplay, choice_);
//
//			system("CLS");
//		}
//
//	}
//
//	void display(string whatToShow)
//	{
//		if (whatToShow == "branches")
//		{
//			amountOfOptions_ = branches.size();
//
//			for (int i = 0; i < branches.size(); i++)
//			{
//				cout << "      " << i + 1 << " :: " << branches.at(i) << endl;
//			}
//		}
//		else if (whatToShow == "orderTracking")
//		{
//			amountOfOptions_ = 1;
//
//			for (int i = 0; i < branches.size(); i++)
//			{
//				if (currentBranch_ == branches[i])
//				{
//					OrderTracker tracker1(currentBranch_ + " Online");
//					Subject onlineOrderSub;
//					onlineOrderSub.Attach(&tracker1);
//					onlineOrderSub.Notify(onlineOrders);
//				}
//			}
//
//			/*
//			OrderTracker tracker1("Online");
//			Subject onlineOrderSub;
//			onlineOrderSub.Attach(&tracker1);
//			onlineOrderSub.Notify(onlineOrders);
//
//			cout << endl;
//
//			OrderTracker tracker2("Instore");
//			Subject instoreOrderSub;
//			instoreOrderSub.Attach(&tracker2);
//			instoreOrderSub.Notify(instoreOrders);
//			*/
//
//			cout << "1 :: Go back" << endl;
//		}
//		else if (whatToShow == "branchOptions")
//		{
//			vector<string>options = { "Order Items", "Order Tracking", "Go Back" };
//
//			amountOfOptions_ = options.size();
//
//			for (int i = 0; i < options.size(); i++)
//			{
//				cout << "      " << i + 1 << " :: " << options.at(i) << endl;
//			}
//
//			infoToShow = 0;
//		}
//		else if (whatToShow == "items")
//		{
//			cout << "     ---------ITEMS---------" << endl << endl;
//
//			selectedBranch = BranchFactory::createBranch(currentBranch_);
//
//			branchItems = selectedBranch->getStoreItems();
//			branchAccesories = selectedBranch->getStoreAccesories();
//
//			amountOfOptions_ = branchItems.size() + 3;
//
//			for (int i = 0; i < branchItems.size(); i++)
//			{
//				cout << "      " << i + 1 << " :: ";
//
//				for (int y = 0; y < branchItems[i].size(); y++)
//				{
//					cout << branchItems[i][y] << " $ ";
//				}
//
//				cout << endl;
//			}
//
//			cout << "      " << amountOfOptions_ - 2 << " :: " << "Remove Item" << endl;
//			cout << "      " << amountOfOptions_ - 1 << " :: " << "Finish Order" << endl;
//			cout << "      " << amountOfOptions_ << " :: " << "Go Back" << endl;
//			cout << endl;
//			information(infoToShow);
//			shoppingBasket(showBasket);
//			cout << endl;
//		}
//		else if (whatToShow == "order")
//		{
//			amountOfOptions_ = 1;
//			infoToShow = 0;
//
//			Order* onlineOrder = new Order(currentBranch_, "Online", basket);
//			onlineOrders.push_back(*onlineOrder);
//
//			cout << "	1 :: Go back" << endl;
//
//			choiceStr_ = "";
//			showBasket = false;
//			typeOfInput = true;
//			done = false;
//			basket.clear();
//		}
//		else if (whatToShow == "removeItem")
//		{
//			cout << "       ---------ITEMS---------" << endl << endl;
//			amountOfOptions_ = basket.size() + 1;
//
//			for (int i = 0; i < basket.size(); i++)
//			{
//				cout << "   " << i + 1 << " :: " << basket[i].second->description();
//				cout << endl;
//			}
//
//			cout << "   " << amountOfOptions_ << " :: Go Back" << endl;
//
//			cout << endl;
//			information(infoToShow);
//			cout << endl;
//		}
//	}
//
//	void information(int infoToShow)
//	{
//		cout << "==============[INFORMATION]===================" << endl;
//		switch (infoToShow)
//		{
//		case 1:
//			cout << "Would you like " << currentAccesory << " for $" << currentAccesoryPrice << " to be added to your order ? " << endl;
//			typeOfInput = false;
//			break;
//		case 2:
//			fix this, make this happen after the y/n input also fix the y/n to normal input after it has been addded to the basket.
//			cout << "Would you like this {delivery option} to be added to your order?" << endl;
//			typeOfInput = false;
//			break;
//		case 3:
//			cout << "Are you sure you want to leave because the items in the basket will be deleted" << endl;
//			typeOfInput = false;
//			break;
//		case 4:
//			cout << "Choose which item you want to remove by the number" << endl;
//			typeOfInput = false;
//			break;
//		case 5:
//			cout << "Please confirm you want to proceed with this order" << endl;
//			cout << "You won't be able to change the order once it has proceeded" << endl;
//			typeOfInput = false;
//			break;
//		case 6:
//			cout << "Choose an item you want to remove from the basket" << endl;
//			typeOfInput = true;
//			break;
//		default:
//			cout << "To add an item to the basket, type the item's id" << endl;
//			cout << "For example if you type 1 then the item labeled as id 1" << endl;
//			cout << "Will be added to the basket." << endl;
//			typeOfInput = true;
//			break;
//		}
//	}
//
//	void shoppingBasket(bool show)
//	{
//		if (show)
//		{
//			cout << endl;
//			cout << "================[BASKET]=================" << endl;
//			cout << "Basket = {";
//
//			double total = 0;
//			if (basket.size() != 0)
//			{
//				for (int i = 0; i < basket.size(); i++)
//				{
//					cout << " " << basket[i].second->description() << " ";
//
//					total = total + basket[i].second->price();
//				}
//			}
//			else
//			{
//				cout << " Empty ";
//			}
//
//			cout << "}" << endl;
//
//			cout << "Basket Total = { $ " << total << " }" << endl;
//
//			if (choiceStr_ == "y" && done == true || choiceStr_ == "n" && done == true)
//			{
//				choiceStr_ = "";
//				typeOfInput = true;
//			}
//		}
//	}
//
//	void getInput(bool numberInput)
//	{
//		try
//		{
//			if (typeOfInput == true)
//			{
//				if ((cin >> choice_) && numberInput) // check if the input is a number
//				{
//					if (choice_ > amountOfOptions_ || choice_ < 1)
//					{
//						cin.clear();
//						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the invalid input
//						throw invalid_argument("Incorrect number value, Try again: ");
//					}
//				}
//				else
//				{
//					cin.clear();
//					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the invalid input
//					throw invalid_argument("Incorrect data type value, Try again: ");
//				}
//			}
//			else
//			{
//				if ((cin >> choiceStr_) && choiceStr_ == "y" || choiceStr_ == "n")
//				{
//					choiceStr_;
//				}
//				else
//				{
//					cin.clear();
//					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the invalid input
//					throw invalid_argument("Incorrect answer, Try again (y/n): ");
//				}
//			}
//		}
//		catch (const invalid_argument& error)
//		{
//			cout << error.what();
//			if (whatToDisplay == "items")
//			{
//				getInput(typeOfInput);
//			}
//			else
//			{
//				getInput(true);
//			}
//		}
//	}
//
//	void resetItemState()
//	{
//		currentAccesory = "";
//		currentAccesoryPrice = 0;
//		infoToShow = 0;
//		choice_ = 0;
//	}
//
//	fix everything
//	void selectedOption(string whatIsDisplayed, int choice)
//	{
//		if (whatIsDisplayed == "branchOptions")
//		{
//			activates multiple times which cause problems need to be fixed ASP!!!
//			switch (choice)
//			{
//			case 1:
//				whatToDisplay = (whatIsDisplayed == "branchOptions") ? "items" : "branches";
//				break;
//			case 2:
//				whatToDisplay = "orderTracking";
//				break;
//			case 3:
//				whatToDisplay = "branches";
//				currentBranch_ = "";
//				break;
//			}
//		}
//		else if (whatIsDisplayed == "orderTracking")
//		{
//			amountOfOptions_ = 1;
//
//			user input logic behind tracking
//			if (choice == amountOfOptions_)
//			{
//				whatToDisplay = "branches";
//			}
//		}
//		else if (whatIsDisplayed == "items")
//		{
//			/*loop through each item and give them an index so the program knows
//			which input corresponds to which index for example. Item 1 will be index 1 and it will return hammer.*/
//			if (choice != 0)
//			{
//				for (int i = 0; i < this->branchItems.size() + 1; i++)
//				{
//					if (choice == i)
//					{
//						Product* item = new Item(this->branchItems[choice - 1][0], stod(this->branchItems[choice - 1][1]));
//
//						if (choice - 1 < branchAccesories.size()) {
//							currentAccesory = this->branchAccesories[choice - 1][0];
//							currentAccesoryPrice = stod(this->branchAccesories[choice - 1][1]);
//						}
//
//						if (currentAccesory == "" && currentAccesoryPrice == 0)
//						{
//							Accessory* addAccesory = new Accessory(item, currentAccesory, currentAccesoryPrice);
//							basket.push_back(make_pair(item, addAccesory));
//							choice_ = 0;
//						}
//						else
//						{
//							infoToShow = 1;
//						}
//
//						if (choiceStr_ == "y")
//						{
//							Accessory* addAccesory = new Accessory(item, currentAccesory, currentAccesoryPrice);
//							basket.push_back(make_pair(item, addAccesory));
//							resetItemState();
//							showBasket = true;
//						}
//						else if (choiceStr_ == "n")
//						{
//							Accessory* emptyAccesory = new Accessory(item, "", 0);
//							basket.push_back(make_pair(item, emptyAccesory));
//							resetItemState();
//							showBasket = true;
//						}
//
//						done = true;
//					}
//				}
//			}
//
//			if (choice == amountOfOptions_ - 2)
//			{
//				logic for removing an item from basket
//				whatToDisplay = "removeItem";
//				infoToShow = 6;
//			}
//
//			if (choice == amountOfOptions_ - 1)
//			{
//				logic for finish order
//				infoToShow = 5;
//				if (choiceStr_ == "y")
//				{
//					orders.push_back(basket);
//					whatToDisplay = "order";
//				}
//			}
//
//			Go back to display the branch options when the last option is selected
//			if (choice == amountOfOptions_)
//			{
//				if (choiceStr_ == "y")
//				{
//					selectedBranch = nullptr;
//					check to see if they want to leave because it will remove all items from the basket
//					whatToDisplay = "branchOptions";
//					basket.clear();
//					typeOfInput = true;
//					showBasket = false;
//					choiceStr_ = "";
//				}
//				else if (choiceStr_ == "n")
//				{
//					infoToShow = 0;
//				}
//				else
//				{
//					infoToShow = 3;
//				}
//			}
//		}
//		else if (whatIsDisplayed == "order")
//		{
//			if (choice == 1)
//			{
//				whatToDisplay = "items";
//			}
//		}
//		else if (whatIsDisplayed == "removeItem")
//		{
//			bool empty = false;
//
//			for (int i = 0; i < basket.size(); i++)
//			{
//				if (choice - 1 == i)
//				{
//					basket.erase(basket.begin() + i);
//					empty = true;
//				}
//			}
//
//			if (choice == amountOfOptions_)
//			{
//				whatToDisplay = "items";
//			}
//			else if (empty == true && basket.size() == 0)
//			{
//				whatToDisplay = "items";
//			}
//		}
//	}
//};
//*/

	//ShoppingBasket Basket;

	//Product* item = new Item("IPHONE xxs", 200);
	//Accessory* addAccesory = new Accessory(item, "earbuds", 25);

	//Basket.addItemToBasket(item, addAccesory);

	//Product* item2 = new Item("ssss", 10);
	//Accessory* addAccesory2 = new Accessory(item2, "ezzzzzds", 25);

	//Basket.addItemToBasket(item2, addAccesory2);

	//Basket.setShow(true);
	//Basket.display();
	//
	//vector<Order> onlineOrders;

	//Order* onlineOrder = new Order("Treforest", "Online", Basket.getItems());
	//onlineOrders.push_back(*onlineOrder);

	//Order* onlineOrder2 = new Order("Treforest", "Online", Basket.getItems());
	//onlineOrders.push_back(*onlineOrder2);

	//OrderTracker tracker1("Online");
	//Subject onlineOrderSub;
	//onlineOrderSub.Attach(&tracker1);
	//onlineOrderSub.Notify(onlineOrders);

	//int input;
	//cin >> input;

int main()
{
	//Interface* menu = new Interface;

	MainInterface* ClientInterface = new MainInterface;

	return 0;
}