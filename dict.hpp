#include <ctime>

typedef unsigned char t_mean;
typedef unsigned int t_count;

struct t_item {
	t_strings syn;
	t_strings tr;

	void print(t_strings data, t_string temp)
	{
		cout << temp << typeid(data).name() << ": size = " << data.size() << "\n";
		for (auto it : data)
			cout << temp << "\t" << it << "\n";
	}

	void print()
	{
		print(syn, "\t\t");
		print(tr, "\t\t");
	}

	bool operator==(const t_item& val)
	{
		return syn == val.syn && tr == val.tr;
	}
};

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

	void print()
	{
		cout << "print dict:\n";
		cout << "\tmean: " << (int)mean << "\n";
		cout << "\tcount: " << count << "\n";
		cout << "\tword: " << word << "\n";
		cout << "\ttrans: " << trans << "\n";
		cout << "\ttype: " << type << "\n";

		cout << typeid(items).name() << ": size = " << items.size() << "\n";
		for (auto it : items)
			it.print();
	}

	bool operator==(const t_dict& val)
	{
		bool fl = items.size() == val.items.size();
		for (int i = 0; fl && i < items.size(); i++)
			fl = items[i] == val.items[i];
		return word == val.word && fl;
	}
};
