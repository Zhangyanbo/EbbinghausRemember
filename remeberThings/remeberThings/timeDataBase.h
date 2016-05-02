#pragma once

#include "csv.h"
#include <ctime>
#include <sstream>
#include <array>

class timeData : public CSV
{
public:
	timeData() = default;
	timeData(std::string $path):
		CSV($path),
		tList(),
		nameList(),
		alive()
	{}

	void start(void);
	virtual void addWork(std::string);
	virtual void addWorkShift(std::string, long);

	void print(std::ostream &) const override;
	int write(mat_t &) override;
	void save(void);
	void delete_name(std::string);

	virtual void Select(time_t, time_t, std::ostream &) const;

	virtual void getToday(std::ostream &os);

	virtual void back() const;
protected:
	std::vector<time_t> tList;
	std::vector<std::string> nameList;
	
private:
	void addWork_do(std::string, time_t);
	void makeData(void);
	void getToday_do(std::ostream &os);


	std::vector<size_t> select_in(time_t, time_t) const;

	std::vector<bool> alive;

	//=======const datas
	const std::array<long, 6> dayshift = {0, 1, 2, 4, 7, 15};
};

inline void timeData::start()
{
	open('r', "tData.csv");
	read();
	close();

	makeData();
}

inline void timeData::addWork(std::string name)
{
	addWork_do(name, time(nullptr));
}

inline void timeData::addWorkShift(std::string name, long dt)
{
	addWork_do(name, time(nullptr) - dt * 86400);
}

inline void timeData::print(std::ostream &os) const
{
	os << "[Name, time]:" << std::endl;

	for (size_t i = 0; i < nameList.size(); ++i)
	{
		if (alive[i])
			os << nameList[i] << "\t" << tList[i] << std::endl;
	}

	os << "End of Data" << std::endl;
}

inline int timeData::write(mat_t& m)
{
	for (size_t i = 0; i < m.size(); ++i)
	{
		if (alive[i]) {
			for (size_t j = 0; j < m[i].size() - 1; ++j)
			{
				wfile << m[i][j] << ",";
			}
			wfile << m[i][m[i].size() - 1] << std::endl;
		}
	}

	return 0;
}

inline void timeData::save()
{
	open('w', "tData.csv");

	write(data);

	wfile.close();
	//close('w');
}

inline void timeData::delete_name(std::string de_str)
{
	for (size_t i = 0; i < nameList.size(); ++i)
	{
		if (nameList[i] == de_str)
			alive[i] = false;
	}
}

inline void timeData::Select(time_t t1, time_t t2, std::ostream& os) const
{
	auto sList = select_in(t1, t2);

	for (size_t i = 0; i < sList.size(); ++i)
	{
		os << "name:   " << nameList[sList[i]] << ",\t";
		os << "time:   " << tList[sList[i]] << std::endl;
	}
}

inline void timeData::getToday(std::ostream &os)
{
	getToday_do(os);
}

inline void timeData::back() const
{
	std::ofstream output_back;

	output_back.open("tData.bak");

	if (output_back.is_open())
	{
		for (size_t i = 0; i < data.size(); ++i)
		{
			if (alive[i]) {
				for (size_t j = 0; j < data[i].size() - 1; ++j)
				{
					output_back << data[i][j] << ",";
				}
				output_back << data[i][data[i].size() - 1] << std::endl;
			}
		}

		output_back.close();
	}else
	{
		std::cout << "Error : cannot open file `tData.bak`" << std::endl;
	}
}

inline void timeData::addWork_do(std::string name, time_t t)
{
	data.push_back({});
	alive.push_back(true);
	auto p = data.size() - 1;

	data[p].push_back(name);
	nameList.push_back(name);


	//char temp_index[200];
	//sprintf(temp_index, "%p", &t);
	//std::string temp_indexx;
	//temp_indexx = temp_index;

	std::stringstream ss;
	std::string temp_t_s;

	ss << t;
	ss >> temp_t_s;
	ss.clear();

	data[p].push_back(temp_t_s);
	tList.push_back(t);
}

inline void timeData::makeData()
{
	std::stringstream ss;
	time_t temp_t;

	for (size_t i = 0; i < data.size(); ++i)
	{
		alive.push_back(true);
		nameList.push_back(data[i][0]);

		//std::cout << "put data No." << i << std::endl;

		//std::cout << "Time = " << data[i][1] << std::endl;

		ss << data[i][1];
		ss >> temp_t;

		ss.clear();
		tList.push_back(temp_t);
	}
}

inline void timeData::getToday_do(std::ostream& os)
{
	long days;
	time_t today = time(nullptr);

	for (size_t i = 0; i < dayshift.size(); ++i)
	{
		for (size_t j = 0; j < nameList.size(); ++j)
		{
			days = today / 86400 - tList[j] / 86400;

			if (days == dayshift[i])
			{
				os << "dt = " << days << "\t : " << nameList[j] << std::endl;
			}
		}
	}
}

inline std::vector<size_t> timeData::select_in(time_t t1, time_t t2) const
{
	std::vector<size_t> temp = {};

	for (size_t i = 0; i < nameList.size(); ++i)
	{
		if (tList[i] <= t2 && tList[i] >= t1)
			temp.push_back(i);
	}

	return temp;
}
