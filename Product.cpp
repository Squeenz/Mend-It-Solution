#include "Product.h"

//Item class public methods
Item::Item(string title, double price) : title_(title), price_(price) {};
string Item::description()
{
	return title_;
}
double Item::price()
{
	return price_;
}

//Product decorator class public methods
ProductDecorator::ProductDecorator(Product* product) : product_(product) {};
string ProductDecorator::description()
{
	return product_->description();
}
double ProductDecorator::price()
{
	return product_->price();
}

//NextDayDelivery class public methods inherits from Product Decorator
NextDayDelivery::NextDayDelivery(Product* product) : ProductDecorator(product) {};
string NextDayDelivery::description()
{
	return product_->description() + ", Next Day Delivery";
}
double NextDayDelivery::price()
{
	return product_->price() + 15.50;
}

//ExpressDelivery class public methods inherits from Product Decorator
ExpressDelivery::ExpressDelivery(Product* product) : ProductDecorator(product) {};
string ExpressDelivery::description()
{
	return product_->description() + ", Express Delivery";
}
double ExpressDelivery::price()
{
	return product_->price() + 5.50;
}

//Accessory class public methods inherits from Product Decorator
Accessory::Accessory(Product* product, string title, double price) : ProductDecorator(product), title_(title), price_(price) {};
string Accessory::description()
{
	return product_->description() + ", " + title_;
}
double Accessory::price()
{
	return product_->price() + price_;
}