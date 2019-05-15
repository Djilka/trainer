typedef unsigned int t_count;

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

	static
	bool cmp(t_token v1, t_token v2)
	{
		return v1.count > v2.count;
	}
};
