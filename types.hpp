#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

// -------->	string
typedef string t_string;
inline bool find_str(t_string str, t_string sub)
{
	return str.find(sub) != t_string::npos;
}
// TODO remove all compare for string

template <class t_data>
class t_vector {
	typedef vector<t_data> tv_data;
public:
	tv_data data;

	bool operator==(const t_vector<t_data>& v)
	{
		bool fl = data.size() == v.data.size();
		for (int i = 0; fl && i < data.size(); i++)
			fl = data[i] == v.data[i];
		return fl;
	}

	void add(const t_vector<t_data>& v)
	{
		if (data.size()) {
			for (int i = 0; i < v.data.size(); i++)
				add(v.data[i]);
		} else
			data = v.data;
	}

	void add(const t_data& d)
	{
		bool fl = false;
		for (int i = 0; !fl && i < data.size(); i++)
			if (fl = data[i] == d)
				data[i].add(d);
		if (!fl)
			data.push_back(d);
	}

	void print(t_string temp = "")
	{
		cout << temp << typeid(data).name() << ": size = " << data.size() << "\n";
		for (int i = 0; i < data.size(); i++)
			data[i].print();
	}

	size_t size()
	{
		return data.size();
	}

// TODO make right sort
	void vsort()
	{
		sort(data.begin(), data.end(), t_data::cmp);
	}

	t_data& operator[](size_t n)
	{
		return data[n];
	}

// TODO is it needed?
	void push_back(t_data d)
	{
		data.push_back(d);
	}
// TODO add begin() end()
};

template <>
void t_vector<t_string>::print(t_string temp)
{
	cout << temp << typeid(data).name() << ": size = " << data.size() << "\n";
	for (int i = 0; i < data.size(); i++)
		cout << temp << "\t" << data[i] << "\n";
}

typedef t_vector<t_string> t_strings;
