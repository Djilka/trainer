#include "file.hpp"

class t_tokenization : public t_file {
	typedef vector<t_token> tv_token;

	tm_token m_token;

private:
	t_string get_word()
	{
		t_string word;

		char c;
		for (read(c); is_OK(); read(c)) {
			if ('A' <= c && c <= 'Z')
				c = 'a' + 'A' - c;
			if ('a' <= c && c <= 'z') {
				word += c;
			} else {
				if (!word.size())
					continue;
				if ('-') {
					read(c);
					if (is_OK() && c == '\n')
						continue;
					else {
						pos(-1);
						break;
					}
				}
				break;
			}
		}

		return word;
	}
public:
	t_tokenization(t_string name) : t_file(name)
	{
		for (t_string word = get_word(); word.size(); word = get_word())
			m_token[word]++;
	}

// TODO : does it need?
	tv_token vtoken()
	{
		tv_token v_token;
		tm_token::iterator it = m_token.begin();
		for (t_token token; it != m_token.end(); it++) {
			token.word = it->first;
			token.count = it->second;
			v_token.push_back(token);
		}

		return v_token;
	}

	tm_token mtoken()
	{
		return m_token;
	}
};
