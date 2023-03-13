#include "Singleton.h"
#include "chrono"
#include "thread"

//Takes user input and check is the inpud is valid, depending on the bool isInputNumber
//It will run a different validation check. If isInputNumber true then it will check if the int input is
//valid in this case it will check if it's not over or under the numOfOptions.
//If isInputNumber is false then it will check if the string is y or n.
void InterfaceCore::getInputAndCheck(bool isInputNumber)
{
	cout << "===============[INPUT]==================" << endl;
	bool valid = false;

	while (!valid)
	{
		try
		{
			if (isInputNumber == true)
			{
				cout << "Choose an option (1-" << this->numOfOptions_ << "): ";

				if ((cin >> this->numChoice_) && isInputNumber) // check if the input is a number
				{
					if (this->numChoice_ > this->numOfOptions_ || this->numChoice_ < 1)
					{
						this->numChoice_ = 0;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the invalid input
						throw invalid_argument("Incorrect number value, Try again: ");
					}
					else
					{
						valid = true;
						this->numChoice_;
					}
				}
				else
				{
					this->numChoice_;
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
					valid = true;
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
			cout << error.what() << endl;
		}
	}
}

//Sets the numOfOptions to the paramater value
void InterfaceCore::setNumOfOptions(int numOfOptions)
{
	this->numOfOptions_ = numOfOptions;
}

//Resets the choice values to default which is 0 for int and "" for the string choice
void InterfaceCore::resetChoices()
{
	this->numChoice_ = 0;
	this->txtChoice_ = "";
}

//Returns the number of options
int InterfaceCore::getNumOfOptions()
{
	return numOfOptions_;
}

//Returns the number choice
int InterfaceCore::getNumChoice()
{
	return numChoice_;
}

//Returns string choice
string InterfaceCore::getTxtChoice()
{
	return txtChoice_;
}

//Returns the end bool
bool InterfaceCore::getEnd()
{
	return end_;
}

//Depending on the scenario it will return a different information message for the user
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
		cout << "Items that have been added together will be removed together" << endl << endl;
		break;
	case 10:
		cout << "Your basket is empty you can't remove any items" << endl << endl;
		break;
	default:
		cout << "To add an item to the basket, type the item's id" << endl;
		cout << "For example if you type 1 then the item labeled as id 1" << endl;
		cout << "Will be added to the basket." << endl << endl;
		break;
	}
}

//Displayes the items in the basket
void ShoppingBasket::display()
{
	if (show_ && basket_.size() != 0)
	{
		cout << endl;
		cout << "================[BASKET]=================" << endl;
		cout << "Basket = {";

		double total = 0;
		//if the basket size is not 0 then run the loop
		if (this->basket_.size() != 0)
		{
			//the loop iterates through the items in the basket and prints their name(description)
			//and inceremts the total value to the old total + new total
			//for example if there are two items one's price is 50
			//and the others is 100. During the first loop the total will be 50 then
			//on the second loop it would add the previous total and the current so the total would be 100 + 50 = 150
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

		//Show the user the total of the basket
		cout << "Basket Total = { $ " << total << " }" << endl;
	}
}

//Add the product and accesory to the basket's vector(list)
void ShoppingBasket::addItemToBasket(Product* product, Accessory* accesory)
{
	this->basket_.push_back(make_pair(product, accesory));
}

//Remove item from the basket
void ShoppingBasket::removeItemFromBasket(int choice)
{
	for (int i = 0; i < this->basket_.size(); i++)
	{
		if (choice - 1 == i)
		{
			this->basket_.erase(this->basket_.begin() + i);
			this->setShow(false);
		}
	}
}

//Set the show state of the basket
bool ShoppingBasket::setShow(bool state)
{
	return show_ = state;
}

//Clear all of the basket
void ShoppingBasket::clear()
{
	this->basket_.clear();
}

//Return the list of the items
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

//Just displays information at the top of the user interface
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
			delete selectedBranch_;
			break;
		}

		//Reset the user choices to prevent automatic selection when switches to other screen
		this->resetChoices();
	}
	else if (this->currentScreen_ == "BranchItems")
	{
		this->setNumOfOptions(selectedBranch_->getStoreItems().size() + 3);

		cout << this->getNumChoice() << endl;
		cout << this->getNumOfOptions() << endl;

		this->header(selectedBranch_->getName());

		this->branchItems(selectedBranch_, basket);

		basket->display();

		this->information(this->infoCase_);

		this->getInputAndCheck(this->typeOfInput_);

		if (this->getNumChoice() == this->getNumOfOptions())
		{
			this->infoCase_ = 6;
			this->typeOfInput_ = false;

			if (this->getTxtChoice() == "y")
			{
				this->currentScreen_ = "BranchOptions";
				this->infoCase_ = 0;
				this->typeOfInput_ = true;
				this->resetChoices();
				basket->clear();
			}
			else if (this->getTxtChoice() == "n")
			{
				this->infoCase_ = 0;
				this->typeOfInput_ = true;
				this->resetChoices();
			}
		}
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

void MainInterface::removeItem(ShoppingBasket* basket)
{
	system("CLS");
	this->header(this->selectedBranch_->getName());

	cout << "     ---------ITEMS---------" << endl;
	this->setNumOfOptions(basket->getItems().size() + 1);

	for (int i = 0; i < basket->getItems().size(); i++)
	{
		cout << "      " << i + 1 << " :: " << basket->getItems().at(i).second->description();
		cout << endl;
	}
	cout << endl;

	cout << "     ---------Options-------" << endl;
	cout << "      " << this->getNumOfOptions() << " :: " << "Go Back" << endl;

	this->infoCase_ = 9;
	this->information(this->infoCase_);
	this->typeOfInput_ = true;
	this->getInputAndCheck(this->typeOfInput_);
	basket->removeItemFromBasket(this->getNumChoice());
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
	string localScreen = "items";

	/*loop through each item and give them an index so the program knows
	which input corresponds to which index for example. Item 1 will be index 1 and it will return hammer.*/
	if (this->getNumChoice() != 0 && this->getNumChoice() <= this->getNumOfOptions() - 3)
	{
		int firstSelectedIndex = this->getNumChoice() - 1;

		Product* item = new Item(branchItems[firstSelectedIndex][0], stod(branchItems[firstSelectedIndex][1]));

		this->typeOfInput_ = false;
		this->infoCase_ = 3;

		if (this->getTxtChoice() == "y")
		{
			system("CLS");

			this->setNumOfOptions(branchAccesories.size());
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
				this->getInputAndCheck(this->typeOfInput_);

				if (this->getNumChoice() - 1 > this->getNumOfOptions() || this->getNumChoice() - 1 < 0)
				{
					this->getInputAndCheck(this->typeOfInput_);
				}
				else if (this->getNumChoice() - 1 <= this->getNumOfOptions())
				{
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
	else if (this->getNumChoice() == this->getNumOfOptions() - 2 && basket->getItems().size() != 0 )
	{
		bool goBack = false;

		while (!goBack)
		{	
			this->removeItem(basket);

			if (this->getNumChoice() == this->getNumOfOptions())
			{
				system("CLS");
				this->header(selectedBranch->getName());
				this->branchItems(selectedBranch, basket);
				this->typeOfInput_ = true;
				this->infoCase_ = 0;
				basket->setShow(true);
				this->resetChoices();
				goBack = true;
			}
		}
	}
	else if (this->getNumChoice() == this->getNumOfOptions() - 2 && basket->getItems().size() == 0)
	{
		this->infoCase_ = 10;
	}
}