struct t_token {
	t_string word;
	t_count	count = 0;

	bool operator==(const t_token& val)
	{
		return word == val.word;
	}

	bool operator>(const t_token &v)
	{
		return count > v.count;
	}

	void print(ostream &stream)
	{
		stream << "token:\n";
		stream << word  << " : " << count << "\n";
	}

	friend ostream& operator<<(ostream &stream, t_token token);
	friend istream& operator>>(istream &stream, t_token &token);
};

ostream& operator<<(ostream &stream, t_token token)
{
	stream << token.word;
	stream << token.count;
	return stream;
}

istream& operator>>(istream &stream, t_token &token)
{
	stream >> token.word;
	stream >> token.count;
	return stream;
}

template <>
void print<t_token>(ostream &stream, vector<t_token> v)
{
	stream << typeid(t_token).name() << ": size = " << v.size() << "\n";
	for (t_token t : v)
		t.print(stream);
	stream << "\n";
}

t_tokens token_convert(tm_token tokens)
{
	t_tokens c_tokens;
	for (tm_token::iterator t = tokens.begin(); t != tokens.end(); t++)
		c_tokens.push_back({.word = t->first, .count = t->second});
	return c_tokens;
}

tm_token token_convert(t_tokens tokens)
{
	tm_token c_tokens;
	for (t_token t : tokens)
		c_tokens[t.word] = t.count;
	return c_tokens;
}

t_strings token_names(tm_token tokens)
{
	t_strings names;
	for (tm_token::iterator t = tokens.begin(); t != tokens.end(); t++)
		names.push_back(t->first);
	return names;
}
