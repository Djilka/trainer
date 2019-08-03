#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

typedef string t_string;
typedef vector<t_string> t_strings;

struct t_token;
typedef unsigned char t_mean;
typedef unsigned int t_count;
typedef map<t_string, t_count> tm_token;
typedef tm_token::iterator ti_token;
typedef vector<t_token> t_tokens;

struct t_dict;
typedef vector<t_dict> t_dicts;
typedef t_dict *tp_dict;
typedef vector<tp_dict> tp_dicts;
typedef tp_dicts::iterator tpi_dicts;
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

inline bool find_str(t_string str, t_string sub)
{
	return str.find(sub) != t_string::npos;
}
