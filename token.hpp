struct t_token {
	t_string word;
	t_count	count = 0;

	void print()
	{
		cout << word << ":" << count << '\n';
	}

	bool operator==(const t_token& val)
	{
		return word == val.word;
	}

	bool operator>(const t_token &v)
	{
		return count > v.count;
	}
};

t_strings token_names(tm_token tokens)
{
	t_strings names;
	for (tm_token::iterator it = tokens.begin(); it != tokens.end(); it++)
		names.push_back(it->first);
	return names;
}
