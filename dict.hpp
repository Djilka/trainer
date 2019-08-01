#include <ctime>

struct t_item {
	t_strings syn;
	t_strings tr;

	bool operator==(const t_item& val)
	{
		return syn == val.syn && tr == val.tr;
	}

	friend ostream& operator<<(ostream &stream, t_item item);
	friend istream& operator>>(istream &stream, t_item item);
};

ostream& operator<<(ostream &stream, t_item item)
{
	stream << item.syn;
	stream << item.tr;
	return stream;
}

istream& operator>>(istream &stream, t_item item)
{
	t_string str;
	int count = 0;

	stream >> count;
	for (int i = 0; i < count; i++) {
		stream >> str;
		item.syn.push_back(str);
	}

	stream >> count;
	for (int i = 0; i < count; i++) {
		stream >> str;
		item.tr.push_back(str);
	}
	return stream;
}

struct t_dict {
	typedef vector<t_item> t_items;

	t_string word;
	t_string trans;
	t_string type;
	t_items items;
	t_mean mean;
	t_count count;
	tm time_cur;

	t_dict()
	{
		time_t t = time(0);
		tm* p_time_curr = localtime(&t);

		mean = 0;
		count = 0;
		time_cur = (nullptr != p_time_curr)? *p_time_curr : tm();
	}

	bool operator==(const t_dict& val)
	{
		bool fl = items.size() == val.items.size();
		for (int i = 0; fl && i < items.size(); i++)
			fl = items[i] == val.items[i];
		return word == val.word && fl;
	}

	friend ostream& operator<<(ostream &stream, t_dict dict);
	friend istream& operator>>(istream &stream, t_dict dict);
};

ostream& operator<<(ostream &stream, t_dict dict)
{
	stream << "dict:\n";
	stream << "\tmean: " << (int)dict.mean << "\n";
	stream << "\tcount: " << dict.count << "\n";
	stream << "\tword: " << dict.word << "\n";
	stream << "\ttrans: " << dict.trans << "\n";
	stream << "\ttype: " << dict.type << "\n";
	stream << typeid(dict.items).name() << ": size = " << dict.items.size() << "\n";
	for (t_item item : dict.items)
		stream << item << "\n";
	stream << "\n";

	return stream;
}

istream& operator>>(istream &stream, t_dict dict)
{
	stream >> dict.mean;
	stream >> dict.count;
	stream >> dict.word;
	stream >> dict.trans;
	stream >> dict.type;

	int count = 0;
	stream >> count;
	t_item item;
	for (int i = 0; i < count; i++) {
		stream >> item;
		dict.items.push_back(item);
	}
	return stream;
}
