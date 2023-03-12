#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H

#include <vector>
#include <string>

using namespace std;

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
	Item(string title, double price);
	string description() override;
	double price() override;
};

class ProductDecorator : public Product
{
protected:
	Product* product_;
public:
	ProductDecorator(Product* product);
	string description() override;
	double price() override;
};

class NextDayDelivery : public ProductDecorator
{
public:
	NextDayDelivery(Product* product);
	string description() override;
	double price() override;
};

class ExpressDelivery : public ProductDecorator
{
public:
	ExpressDelivery(Product* product);
	string description() override;
	double price() override;
};

class Accessory : public ProductDecorator
{
private:
	string title_;
	double price_;
public:
	Accessory(Product* product, string title, double price);
	string description() override;
	double price() override;
};

#endif //PRODUCT_H
