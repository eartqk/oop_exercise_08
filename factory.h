#pragma once

#include <memory>

#include "figures.h"

template <typename T>
class Factory
{
public:
	static std::shared_ptr<Figure> CreateFigure(int choice)
	{
		std::shared_ptr<Figure> figure;
		std::pair<T, T> center;
		T side;
		std::cout << "Enter the coordinates of the center and a side separated by a space: ";
		std::cin >> center.first >> center.second >> side;
		if (side <= 0) 
		{
			std::cerr << "The side of a geometric figure cannot be non-positive!\n";
			throw -1;
		}
		if (choice == 1)
		{
		    figure = std::make_shared<Octagon<T>>(side, center);
		}
		if (choice == 2)
		{
			figure = std::make_shared<Triangle<T>>(side, center);
		}
		if (choice == 3)
		{
			figure = std::make_shared<Square<T>>(side, center);
		}
		return figure;
	}
};