#include "file.hpp"

class t_tokenization : public t_file {
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
	t_tokenization(t_string name) : t_file(name) { }

	tm_token tokens()
	{
		tm_token m_token;
		for (t_string word = get_word(); word.size(); word = get_word())
			m_token[word]++;
		return m_token;
	}
};
