#include "stream.hpp"

class t_vocabulary_base {
protected:
	typedef vector<t_token> t_tokens;
	typedef vector<t_dict> t_dicts;

	t_tokens m_tokens;
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

	void tokens(t_tokens new_tokens)
	{
		m_tokens = new_tokens;
	}

	t_tokens tokens()
	{
		return m_tokens;
	}
};


class t_vocabulary : public t_vocabulary_base {
public:
	
	void load()
	{
		m_tokens = t_stream<t_token>::read(m_path);
		m_dicts = t_stream<t_dict>::read(m_path);
	}

	void save()
	{
		t_stream<t_token>::write(m_path, m_tokens);
		t_stream<t_dict>::write(m_path, m_dicts);
	}

};
