#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

enum t_type_test {
	tt_up, tt_down
};

using t_string = string;
using t_strings = vector<t_string>;
using tm_strings = map<char, t_strings>;

struct t_token;
using t_mean = unsigned char;
using t_count = unsigned int;
using tm_token = map<t_string, t_count>;
using ti_token = tm_token::iterator;
using t_tokens = vector<t_token>;

struct t_item;
using t_items = vector<t_item>;

struct t_dict;
using t_dicts = vector<t_dict>;
using ti_dicts = t_dicts::iterator;

typedef t_dict *tp_dict;
using tp_dicts = vector<tp_dict>;
using tpi_dicts = tp_dicts::iterator;

const t_count max_score = 100;
typedef tp_dicts t_scores[max_score + 1];

template <class T>
ostream& operator<<(ostream &stream, vector<T> v)
{
	stream << v.size();
	for (T t : v)
		stream << t;
	return stream;
}

template <class T>
istream& operator>>(istream &stream, vector<T> &v)
{
	T t;
	size_t size = 0;
	stream >> size;
	for (int i = 0; i < size; i++) {
		stream >> t;
		v.push_back(t);
	}
	return stream;
}

template <class T>
void print(ostream &stream, vector<T> v)
{
	stream << typeid(T).name() << ": size = " << v.size() << "\n";
	for (T t : v)
		stream << t << " ";
	stream << "\n";
}

template <class T1, class T2>
void print(ostream &stream, map<T1, T2> v)
{
	stream << "map\n";
	for (auto it : v)
		stream << it.first << " : " << it.second << "\n";
	stream << "\n";
}

inline bool find_str(t_string str, t_string sub)
{
	return str.find(sub) != t_string::npos;
}
