#include <ctime>

struct t_item {
	t_strings syn;
	t_strings tr;

	bool operator==(const t_item& val)
	{
		return syn == val.syn && tr == val.tr;
	}

	void print(ostream &stream)
	{
		stream << "item:\n";
		::print(stream, syn);
		::print(stream, tr);
		stream << "\n";
	}

	friend ostream& operator<<(ostream &stream, t_item item);
	friend istream& operator>>(istream &stream, t_item &item);
};

ostream& operator<<(ostream &stream, t_item item)
{
	stream << item.syn;
	stream << item.tr;
	return stream;
}

istream& operator>>(istream &stream, t_item &item)
{
	stream >> item.syn;
	stream >> item.tr;
	return stream;
}

struct t_dict {
	typedef vector<t_item> t_items;

	t_string word;
	t_string trans;
	t_string type;
	t_items items;
	t_count pass;
	t_count count;
	tm time_cur;

	t_dict()
	{
		time_t t = time(0);
		tm* p_time_curr = localtime(&t);

		pass = 0;
		count = 0;
		time_cur = (nullptr != p_time_curr)? *p_time_curr : tm();
	}

	void update(bool result)
	{
		count++;
		pass += result;
	}

	bool operator==(const t_dict& val)
	{
		bool fl = items.size() == val.items.size();
		for (int i = 0; fl && i < items.size(); i++)
			fl = items[i] == val.items[i];
		return word == val.word && fl;
	}

	void print(ostream &stream)
	{
		stream << "dict:\n";
		stream << "\tpass: " << (int)pass << "\n";
		stream << "\tcount: " << count << "\n";
		stream << "\tword: " << word << "\n";
		stream << "\ttrans: " << trans << "\n";
		stream << "\ttype: " << type << "\n";
		for (t_item item : items)
			item.print(stream);
		stream << "\n";
	}

	friend ostream& operator<<(ostream &stream, t_dict dict);
	friend istream& operator>>(istream &stream, t_dict &dict);
};

ostream& operator<<(ostream &stream, t_dict dict)
{
	stream << dict.pass;
	stream << dict.count;
	stream << dict.word;
	stream << dict.trans;
	stream << dict.type;
	stream << dict.items;
	return stream;
}

istream& operator>>(istream &stream, t_dict &dict)
{
	stream >> dict.pass;
	stream >> dict.count;
	stream >> dict.word;
	stream >> dict.trans;
	stream >> dict.type;
	stream >> dict.items;
	return stream;
}

template <>
void print<t_dict>(ostream &stream, vector<t_dict> v)
{
	stream << typeid(t_dict).name() << ": size = " << v.size() << "\n";
	for (t_dict t : v)
		t.print(stream);
	stream << "\n";
}
