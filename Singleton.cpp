#include "Singleton.h"

void InterfaceCore::getInputAndCheck(bool isInputNumber)
{
	cout << "===============[INPUT]==================" << endl;
	try
	{
		if (isInputNumber == true)
		{
			cout << "Choose an option (1-" << this->numOfOptions_ << "): ";

			if ((cin >> numChoice_) && isInputNumber) // check if the input is a number
			{
				if (numChoice_ > numOfOptions_ || numChoice_ < 1)
				{
					numChoice_ = 0;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the invalid input
					throw invalid_argument("Incorrect number value, Try again: ");
				}
			}
			else
			{
				numChoice_;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the invalid input
				throw invalid_argument("Incorrect data type value, Try again: ");
			}
		}
		else
		{
			cout << "Choose an option (y/n): ";

			if ((cin >> txtChoice_) && txtChoice_ == "y" || txtChoice_ == "n")
			{
				txtChoice_;
			}
			else
			{
				txtChoice_ = "";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the invalid input
				throw invalid_argument("Incorrect answer, Try again (y/n): ");
			}
		}
	}
	catch (const invalid_argument& error)
	{
		cout << error.what();
	}
}

void InterfaceCore::setNumOfOptions(int numOfOptions)
{
	this->numOfOptions_ = numOfOptions;
}

void InterfaceCore::resetChoices()
{
	this->numChoice_ = 0;
	this->txtChoice_ = "";
}

int InterfaceCore::getNumOfOptions()
{
	return numOfOptions_;
}

int InterfaceCore::getNumChoice()
{
	return numChoice_;
}

string InterfaceCore::getTxtChoice()
{
	return txtChoice_;
}

bool InterfaceCore::getEnd()
{
	return end_;
}

void InterfaceCore::information(int scenario)
{
	cout << endl;
	cout << "==============[INFORMATION]=============" << endl;
	switch (scenario)
	{
	case 1:
		cout << "Type in the branch you want to select " << endl;
		cout <<  "and press the enter key" << endl << endl;
		break;
	case 2:
		cout << "Type in what you would like to do " << endl;
		cout << "and press the enter key" << endl << endl;
		break;
	case 3:
		cout << "Would you like to add an accesory to the main item? " << endl << endl;
		break;
	case 4:
		cout << "Which accesory would you like to add" << endl << endl;
		break;
	case 5:
		cout << "Would you like this " << " to be added to your order ? " << endl << endl;
		break;
	case 6:
		cout << "Are you sure you want to leave because the items in the basket will be deleted" << endl << endl;
		break;
	case 7:
		cout << "Choose which item you want to remove by the number" << endl << endl;;
		break;
	case 8:
		cout << "Please confirm you want to proceed with this order" << endl;
		cout << "You won't be able to change the order once it has proceeded" << endl << endl;
		break;
	case 9:
		cout << "Choose an item you want to remove from the basket" << endl;
		break;
	default:
		cout << "To add an item to the basket, type the item's id" << endl;
		cout << "For example if you type 1 then the item labeled as id 1" << endl;
		cout << "Will be added to the basket." << endl << endl;
		break;
	}
}

void ShoppingBasket::display()
{
	if (show_)
	{
		cout << endl;
		cout << "================[BASKET]=================" << endl;
		cout << "Basket = {";

		double total = 0;
		if (this->basket_.size() != 0)
		{
			for (int i = 0; i < this->basket_.size(); i++)
			{
				cout << " " << this->basket_[i].second->description() << " ";

				total = total + this->basket_[i].second->price();
			}
		}
		else
		{
			cout << " Empty ";
		}

		cout << "}" << endl;

		cout << "Basket Total = { $ " << total << " }" << endl;
	}
}

void ShoppingBasket::addItemToBasket(Product* product, Accessory* accesory)
{
	this->basket_.push_back(make_pair(product, accesory));
}

bool ShoppingBasket::setShow(bool state)
{
	return show_ = state;
}

vector<pair<Product*, Accessory*>> ShoppingBasket::getItems()
{
	return basket_;
}

MainInterface::MainInterface()
{
	//Create the shopping basket
	//Call it out side the loop so all of the items 
	//stay in the vector and don't get removed after each iteration of the loop
	ShoppingBasket* basket = new ShoppingBasket;

	//Loop the user interface until the end state is changed to true
	while (this->getEnd() != true)
	{
		//Call the display function which is resposible for user interface
		this->display(basket);
		//Clear the screen after each change
		system("CLS");
	}
}

void MainInterface::header(string branch)
{
	cout << "=================================" << endl;
	cout << " Mend It Solutions  :: " << branch << endl;
	cout << "=================================" << endl;
}

void MainInterface::display(ShoppingBasket* basket)
{
	//Shows the all of the branches and their values
	if (this->currentScreen_ == "Branches")
	{
		//Set the header to branches
		this->header("Branches");
		//Display all of the branches
		this->branches();
		//Call the information function to show {Case 1: Instructions}
		this->information(1);
		//Get the input from the user and only take int as input
		this->getInputAndCheck(true);
		//Create the branch using the factory desing pattern
		this->selectedBranch_ = BranchFactory::createBranch(allBranches[this->getNumChoice() - 1]);
		//Change the current screen to branch options
		this->currentScreen_ = "BranchOptions";
	}
	else if (this->currentScreen_ == "BranchOptions")
	{
		//Change the header to display the selected branch's name
		this->header(selectedBranch_->getName());
		//Show all of the posible things the user can do in each branch
		this->branchOptions();
		//Call the information function to show {Case 2: Instructions}
		this->information(2);
		//Get the input from the user and only take int as input
		this->getInputAndCheck(true);

		//Gets the value which is valid and depedning on the value
		//changes the current screen which changes what is being displayed.
		switch (this->getNumChoice())
		{
		case 1:
			//change the screen to branch items
			this->currentScreen_ = "BranchItems";
			break;
		case 2: 
			//chagne the screen to order tracking
			this->currentScreen_ = "OrderTracking";
			break;
		case 3: 
			//chagne the screen to branches
			this->currentScreen_ = "Branches";
			break;
		}

		//Reset the user choices to prevent automatic selection when switches to other screen
		this->resetChoices();
	}
	else if (this->currentScreen_ == "BranchItems")
	{
		this->header(selectedBranch_->getName());

		this->branchItems(selectedBranch_, basket);

		basket->display();

		this->information(this->infoCase_);

		this->getInputAndCheck(this->typeOfInput_);
	}

}

void MainInterface::branches()
{
	this->setNumOfOptions(allBranches.size());

	for (int i = 0; i < allBranches.size(); i++)
	{
		cout << "      " << i + 1 << " :: " << allBranches.at(i) << endl;
	}
}

void MainInterface::branchOptions()
{
	vector<string>options = { "Order Items", "Order Tracking", "Go Back" };

	this->setNumOfOptions(options.size());

	for (int i = 0; i < options.size(); i++)
	{
		cout << "      " << i + 1 << " :: " << options.at(i) << endl;
	}
}

void MainInterface::branchItems(Branch* selectedBranch, ShoppingBasket* basket)
{
	cout << "     ---------Items---------" << endl;
	//Get the selected branch items and accesories and turn it into private variables for this function
	vector<vector<string>> branchItems = selectedBranch->getStoreItems();
	vector<vector<string>> branchAccesories = selectedBranch->getStoreAccesories();

	//Set the amount of posssilbe choices
	this->setNumOfOptions(branchItems.size() + 3);

	//loop through all of the items in the branch items vector and display them to the user
	for (int i = 0; i < branchItems.size(); i++)
	{
		cout << "      " << i + 1 << " :: ";

		for (int y = 0; y < branchItems[i].size(); y++)
		{
			cout << branchItems[i][y];
			cout << " - ";
		}

		cout << endl;
	}
	cout << endl;

	//Extra options for the user this is included in set the amount of posssilbe choices
	cout << "     ---------Options-------" << endl;
	cout << "      " << this->getNumOfOptions() - 2 << " :: " << "Remove Item" << endl;
	cout << "      " << this->getNumOfOptions() - 1 << " :: " << "Finish Order" << endl;
	cout << "      " << this->getNumOfOptions() << " :: " << "Go Back" << endl;

	//set current accesory as empty
	string currentAccesory = "";
	double currentAccesoryPrice = 0;

	/*loop through each item and give them an index so the program knows
	which input corresponds to which index for example. Item 1 will be index 1 and it will return hammer.*/
	if (this->getNumChoice() != 0)
	{
		int firstSelectedIndex = this->getNumChoice() - 1;

		Product* item = new Item(branchItems[firstSelectedIndex][0], stod(branchItems[firstSelectedIndex][1]));

		this->typeOfInput_ = false;
		this->infoCase_ = 3;

		if(this->getTxtChoice() == "y")
		{
			system("CLS");

			this->typeOfInput_ = true;
			this->resetChoices();

			header(selectedBranch->getName());

			cout << "     ---------Items---------" << endl;
			for (int i = 0; i < branchAccesories.size(); i++)
			{
				cout << "      " << i + 1 << " :: ";

				for (int y = 0; y < branchAccesories[i].size(); y++)
				{
					cout << branchAccesories[i][y];
					cout << " - ";
				}

				cout << endl;
			}

			this->information(4);

			if (currentAccesory == "" && currentAccesoryPrice == 0)
			{
				this->getInputAndCheck(typeOfInput_);

				int secondSelectedIndex = this->getNumChoice() - 1;

				currentAccesory = branchAccesories[secondSelectedIndex][0];
				currentAccesoryPrice = stod(branchAccesories[secondSelectedIndex][1]);

				Accessory* accesory = new Accessory(item, currentAccesory, currentAccesoryPrice);

				basket->addItemToBasket(item, accesory);
				basket->setShow(true);
				this->infoCase_ = 0;
				this->typeOfInput_ = true;
				this->resetChoices();

				system("CLS");
				this->header(selectedBranch->getName());
				this->branchItems(selectedBranch, basket);
			}
		}
		else if (this->getTxtChoice() == "n")
		{
			Accessory* emptyAccesory = new Accessory(item, currentAccesory, currentAccesoryPrice);
			basket->addItemToBasket(item, emptyAccesory);
			basket->setShow(true);
			this->infoCase_ = 0;
			this->typeOfInput_ = true;
			this->resetChoices();
		}
	}
}