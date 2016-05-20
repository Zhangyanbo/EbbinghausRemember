#include <ostream>
#include <iostream>

#include "csv.h"
#include "timeDataBase.h"

void work(timeData &td);
inline bool CtrlZ(std::string &item)
{
	return item == "[-]";
}

void work(timeData &td)
{
	std::string control;
	std::string temps;
	const std::string input = "\t>> ";

	std::cout << input;
	std::cin >> control;

	while (control != "quite")
	{
		if (control == "adds")
		{
			std::cout << "name" << input;

			std::string name;
			std::cin >> name;

			if (CtrlZ(name)) {
				control = " ";
				continue;
			}

			std::cout << "dt" << input;
			long dt;
			std::cin >> dt;

			td.addWorkShift(name, dt);
		}

		if (control == "add")
		{
			std::cout << "Add" << input;
			std::cin >> temps;
			if (CtrlZ(temps)) {
				control = " ";
				continue;
			}

			td.addWork(temps);
		}

		if (control == "print")
		{
			std::cout << "Print" << input << std::endl;
			td.print(std::cout);
		}

		if (control == "save")
		{
			td.save();
		}

		if (control == "select")
		{
			time_t t1;
			time_t t2;

			std::cout << "t1" << input;
			std::cin >> t1;
			std::cout << "t2" << input;
			std::cin >> t2;

			td.Select(t1, t2, std::cout);
		}

		if (control == "delete")
		{
			std::string delete_name;

			std::cout << "name" << input;
			std::cin >> delete_name;
			if (CtrlZ(delete_name)) {
				control = " ";
				continue;
			}

			td.delete_name(delete_name);
		}

		if (control == "todo" || control == "Todo" || control == "TODO")
		{
			td.getToday(std::cout);
		}

		if (control == "todos" || control == "Todos" || control == "TODOS")
		{
			int dt;
			std::cout << "shift" << input;
			std::cin >> dt;
			td.getTodayShift(std::cout, dt);
		}

		if (control == "renew")
		{
			std::string name;
			std::cout << "name" << input;
			std::cin >> name;
			if (CtrlZ(name)) {
				control = " ";
				continue;
			}

			if (td.renew(name) == -1)
			{
				std::cout << "Cannot find this name \"" << name << "\"" << std::endl;
			}

		}

		std::cout << input;
		std::cin >> control;
	}
}

int main()
{
	//std::cout << "Hello world" << std::endl;

	/////////////////////////

	timeData td;

	td.start();
	td.back();

	//td.print(std::cout);

	work(td);

	return 0;
}