#include "iostream"
#include "Factory.h"
#include "Product.h"
#include "Observer.h"
#include "Interface.h"
#include "Windows.h"

using namespace std;

int main()
{
	//Create the interface which will display and link everything together
	MainInterface* ClientInterface = new MainInterface;
	delete ClientInterface;
	return 0;
}