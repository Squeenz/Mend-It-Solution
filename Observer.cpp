#include "Observer.h"

//Private method which generates the random order id from the alphaNum array
string Order::generateID(const int len)
{
	static const char alphaNum[] =
		"0123456780"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	string tmp;
	tmp.reserve(len);

	for (int i = 0; i < len; i++)
	{
		tmp += alphaNum[rand() % (sizeof(alphaNum))];
	}

	return tmp;
}

//Order constructor, when the order is created it will display the information below
//to the user
Order::Order(string branch, string type, vector<pair<Product*, ProductDecorator*>> items) : branch_(branch), type_(type), items_(items)
{
	vector<string> state = { "Processing", "Confirmed"};
	string currentState = "";

	this->setID();
	this->getDate();

	for (int i = 0; i < state.size(); i++)
	{
		system("CLS");
		currentState = state[i];
		cout << "=================================" << endl;
		cout << "	ORDER DETAILS WITH TRACKING	  " << endl;
		cout << "=================================" << endl;
		cout << "ORDER ID : " << this->id_ << endl << endl;
		cout << "CURRENT ORDER STATUS : " << currentState << endl << endl;
		cout << "ORDER TYPE : " << this->type_ << endl << endl;
		cout << "BRANCH : " << this->branch_ << endl << endl;
		cout << "DELIVERY DATE : " << this->date_ << endl << endl;
		cout << "=================================" << endl;
		cout << "ORDER ITEMS" << endl;

		double total = 0;
		if (items.size() != 0)
		{
			for (int i = 0; i < items.size(); i++)
			{
				cout << " " << items[i].second->description() << endl;

				total = total + items[i].second->price();
			}
		}
		cout << endl;

		cout << "ORDER COST: $" << total << endl << endl;



		this->setStatus(currentState);
		this_thread::sleep_for(chrono::seconds(3));
	};

	cout << "Order Tracking" << endl;
	cout << "============================================================" << endl;

	cout << "[ ORDER ID: " << this->getID() << ", DATE: " << this->getDate() << ", STATUS: " << this->getStatus() << ", BRANCH: " << this->getBranch() << " ]" << endl;
	this_thread::sleep_for(chrono::seconds(3));

	this->setStatus("Sent");
	cout << "[ ORDER ID: " << this->getID() << ", DATE: " << this->getDate() << ", STATUS: " << this->getStatus() << ", BRANCH: " << this->getBranch() << " ]" << endl;
	this_thread::sleep_for(chrono::seconds(5));

	this->setStatus("Delivered");
	cout << "[ ORDER ID: " << this->getID() << ", DATE: " << this->getDate() << ", STATUS: " << this->getStatus() << ", BRANCH: " << this->getBranch() << " ]" << endl;
	this_thread::sleep_for(chrono::seconds(3));
}

string Order::getBranch()
{
	return this->branch_;
}

string Order::setID()
{
	return this->id_ = generateID(10);
}

string Order::getID()
{
	return this->id_;
}

string Order::getDate()
{
	time_t now = std::time(nullptr); // Get current system time
	tm tm = {}; // Initialize tm structure

	// Convert system time to local time and store in tm structure
	localtime_s(&tm, &now);

	ostringstream osDate;

	// Output formatted time string
	osDate << put_time(&tm, "%d-%m-%Y");

	this->date_ = osDate.str();

	return this->date_;
}

string Order::setStatus(string state)
{
	return this->status_ = state;
}

string Order::getStatus()
{
	return status_;
}

vector<pair<Product*, ProductDecorator*>> Order::getItems()
{
	return items_;
}

//Subject public methods
void Subject::Attach(Observer* observer) {
	observers_.push_back(observer);
}

void Subject::Detach(Observer* observer) {
	observers_.erase(remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

void Subject::Notify(const vector<Order>& orders) {
	for (auto observer : observers_) {
		observer->update(orders);
	}
}

//Order Tracker
OrderTracker::OrderTracker(const string& name) : name_(name) {}

void OrderTracker::update(const vector<Order>& orders) {
	cout << name_ << " order tracker received an update" << endl;
	cout << "============================================================" << endl;
	for (auto order : orders) {
		cout << "[ ORDER ID: " << order.getID() << ", DATE: " << order.getDate() << ", STATUS: " << order.getStatus() << ", BRANCH: " << order.getBranch() << " ]" << endl;
	}
}