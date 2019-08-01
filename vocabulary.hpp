#include "stream.hpp"

class t_vocabulary_base {
protected:
	tm_token m_token;
	t_dicts m_dicts;
	t_string m_path;
public:
	void path(t_string new_path)
	{
		m_path = new_path;
	}

	t_string path()
	{
		return m_path;
	}

	void dicts(t_dicts new_dicts)
	{
		m_dicts = new_dicts;
	}

	t_dicts dicts()
	{
		return m_dicts;
	}

	void tokens(tm_token token)
	{
		m_token = token;
	}

	tm_token tokens()
	{
		return m_token;
	}

	void add(t_dicts new_dicts)
	{
		for (t_dict d : new_dicts)
			m_dicts.push_back(d);
	}

	void add(tm_token tokens)
	{
		for (tm_token::iterator t = tokens.begin(); t != tokens.end(); t++)
			m_token[t->first] += t->second;
	}
};


class t_vocabulary : public t_vocabulary_base {
public:
	
	void load()
	{
		m_token = token_convert(t_stream<t_token>::read(m_path));
		m_dicts = t_stream<t_dict>::read(m_path);
	}

	void save()
	{
		t_stream<t_token>::write(m_path, token_convert(m_token));
		t_stream<t_dict>::write(m_path, m_dicts);
	}

};
