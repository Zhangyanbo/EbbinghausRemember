#pragma once
#include <string>
#include <vector>
#include <fstream>

typedef std::vector<std::vector<std::string>> mat_t;

class CSV
{
public:
	CSV() = default;
	CSV(std::string $path) :
		path(path),
		data({})
	{}

	virtual int open(char, std::string);
	virtual int open(char, char *);
	virtual int open(char);

	virtual int close(char);
	virtual int close(void);

	virtual void read(std::string);
	virtual void read(void);

	virtual int write(mat_t &);
	virtual int write(void);

	virtual void print(std::ostream &) const;
private:
	void read_do(void);
	void pushin(char *, int);
	static std::string charPtrToString(char *[]);
protected:
	std::string path;
	std::ofstream wfile;
	std::ifstream rfile;
	mat_t data;
};

inline int CSV::open(char t, std::string str)
{
	path = str;
	//std::cout << "open::path = " << path << std::endl;

	if (t == 'w')
		wfile.open(path);

	if (t == 'r')
		rfile.open(path);

	return 0;
}

inline int CSV::open(char t, char* str)
{
	std::string temp_s = str;
	//std::cout << "string = " << temp_s << std::endl;
	return open(t, temp_s);
}

inline int CSV::open(char t)
{
	if(t == 'w')
		wfile.open(path);

	if (t == 'r')
		rfile.open(path);

	return 0;
}

inline int CSV::close(char t)
{
	if (t == 'r' && rfile.is_open())
		rfile.close();

	if (t == 'w' && wfile.is_open())
		rfile.close();

	return 0;
}

inline int CSV::close()
{
	close('r');
	close('w');

	return 0;
}

inline void CSV::read(std::string path)
{
	open('r', path);
	read();
}

inline void CSV::read()
{
	//std::ifstream file_in;
	auto is_open = false;


	read_do();


}

inline int CSV::write(mat_t& m)
{
	for (size_t i = 0; i < m.size(); ++i)
	{
		for (size_t j = 0; j < m[i].size() - 1; ++j)
		{
			wfile << m[i][j] << ",";
		}
		wfile << m[i][m[i].size() - 1] << std::endl;
	}

	return 0;
}

inline int CSV::write()
{
	return write(data);
}

inline void CSV::print(std::ostream& os) const
{
	os << ":::CSV Data:" << std::endl;

	for (size_t i = 0; i < data.size(); ++i)
	{
		for (size_t j = 0; j < data[i].size(); ++j)
		{
			os << data[i][j] << "\t";
		}
		os << std::endl;
	}

	os << ":::End of CSV" << std::endl;
}

inline void CSV::read_do()
{
	//std::ifstream file_in;
	std::vector<std::string> temp_strs;

	const int max_str_len = 1000;
	
	char strx[max_str_len];

	//file_in.open(path);

	while(!rfile.eof())
	{
		rfile.getline(strx, max_str_len);

		//std::cout << "get a line" << std::endl << strx << std::endl;

		pushin(strx, max_str_len);
	}

	//file_in.close();
}

inline void CSV::pushin(char* str, int maxlen)
{
	std::string tempstr = str;
	std::string temps = "";

	if (tempstr.size() == 0)
		return;

	long p = 0;
	data.push_back({});
	auto len = data.size();

	for (size_t i = 0; i < tempstr.size(); ++i)
	{
		if (tempstr[p] != ',')
		{
			temps.push_back(tempstr[p]);
		}
		else
		{
			data[len - 1].push_back(temps);
			temps.clear();
		}
		++p;
	}

	if (temps.size() > 0)
	{
		data[len - 1].push_back(temps);
		temps.clear();
	}
}

inline std::string CSV::charPtrToString(char* str[])
{
	std::string temp_str = "";
	long p = 0;

	while (str[p] != "\0")
	{
		temp_str.push_back(*str[p]);
		p++;
	}

	return temp_str;
}
