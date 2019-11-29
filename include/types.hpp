#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <ctime>

using namespace std;

enum t_type_test {
	tt_up, tt_down
};

using t_code = map<char, int>;

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
using tm_dicts = map<char, t_dicts>;

typedef t_dict *tp_dict;
using tp_dicts = vector<tp_dict>;
using tpi_dicts = tp_dicts::iterator;
using tmp_dicts = map<char, tp_dicts>;

const t_count max_score = 100;
typedef tp_dicts t_scores[max_score + 1];

template <class T>
ostream& operator<<(ostream &stream, vector<T> v)
{
	stream << v.size();
	for (T t : v) {
		stream << "\n" << t;
	}
	return stream;
}

template <class T>
istream& operator>>(istream &stream, vector<T> &v)
{
	size_t size = 0;
	stream >> size;
	for (int i = 0; i < size; i++) {
		T t;
		stream >> t;
		v.push_back(t);
	}
	return stream;
}

void str_write(ostream &stream, t_string v)
{
	stream << v.size() << "\n";
	stream << v << "\n";
}

void str_read(istream &stream, t_string &v)
{
	size_t len = 0;
	stream >> len;
	while (v.size() < len) {
		t_string tmp;
		stream >> tmp;
		v += v.size() ? " " + tmp : tmp;
	}
}

ostream& operator<<(ostream &stream, t_strings v)
{
	stream << v.size() << "\n";
	for (t_string t : v)
		str_write(stream, t);
	return stream;
}

istream& operator>>(istream &stream, t_strings &v)
{
	size_t size = 0;
	stream >> size;
	for (int i = 0; i < size; i++) {
		t_string t;
		str_read(stream, t);
		v.push_back(t);
	}
	return stream;
}

ostream& operator<<(ostream &stream, tm v)
{
	stream << v.tm_sec << " ";
	stream << v.tm_min << " ";
	stream << v.tm_hour << " ";
	stream << v.tm_mday << " ";
	stream << v.tm_mon << " ";
	stream << v.tm_year << " ";
	stream << v.tm_wday << " ";
	stream << v.tm_yday << " ";
	stream << v.tm_isdst;
	return stream;
}

istream& operator>>(istream &stream, tm &v)
{
	stream >> v.tm_sec;
	stream >> v.tm_min;
	stream >> v.tm_hour;
	stream >> v.tm_mday;
	stream >> v.tm_mon;
	stream >> v.tm_year;
	stream >> v.tm_wday;
	stream >> v.tm_yday;
	stream >> v.tm_isdst;
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
