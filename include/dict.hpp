
struct t_item {
	t_strings syn;
	t_strings tr;

	bool tr_find(t_string word)
	{
		for (t_string t : tr)
			if (t == word)
				return true;
		return false;
	}

	void tr_add(t_string word)
	{
		tr.push_back(word);
	}

	bool operator==(const t_item& val)
	{
		return syn == val.syn && tr == val.tr;
	}

	void print(ostream &stream)
	{
		stream << "synonym:\n";
		::print(stream, syn);
		stream << "translation:\n";
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
	t_string word;
	t_string trans;
	t_string type;
	t_items items;
	// t_count pass;
	t_mean pass;
	t_count count;
	tm time_cur;

	t_dict()
	{
		init();
	}

	t_dict(t_string w)
	{
		init();
		word = w;
	}

	void init()
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

	bool translation_find(t_string tr)
	{
		for (t_item it : items)
			if (it.tr_find(tr))
				return true;
		return false;
	}

	void translation_add(t_string tr)
	{
		t_item it;
		it.tr_add(tr);
		items.push_back(it);
	}

	bool check(t_string str, t_type_test t)
	{
		switch (t) {
			case tt_down: {
				bool is_right = false;
				for (int i = 0; !is_right && i < items.size(); i++)
					for (int j = 0; j < items[i].tr.size(); j++)
						is_right = str == items[i].tr[i];
				return is_right;
			}
			case tt_up:
				return str == word;
			default:
				return false;
		};
	}

	t_string get(t_type_test t)
	{
		switch (t) {
			case tt_down:
				return word;
			case tt_up: {
				t_string res;
				for (int i = 0; i < items.size(); i++) {
					for (int j = 0; j < items[i].tr.size(); j++)
						res += items[i].tr[j] + "; ";
					res += "\n";
				}
				return res;
			}
			default:
				return t_string();
		};
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
	stream << dict.pass << "\n";
	stream << dict.count << "\n";
	stream << dict.time_cur << "\n";
	str_write(stream, dict.word);
	str_write(stream, dict.trans);
	str_write(stream, dict.type);
	stream << dict.items << "\n";
	return stream;
}

istream& operator>>(istream &stream, t_dict &dict)
{
	stream >> dict.pass;
	stream >> dict.count;
	stream >> dict.time_cur;
	str_read(stream, dict.word);
	str_read(stream, dict.trans);
	str_read(stream, dict.type);
	stream >> dict.items;
	return stream;
}
