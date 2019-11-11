#include "file.hpp"

class t_tokenization : public t_file_r {
public:
	t_tokenization(t_string name) : t_file_r(name) { }

	tm_token tokens()
	{
		tm_token m_token;
		t_string word, tmp;
		while (is_OK()) {
			read(tmp);
			word.clear();
			for (char c : tmp) {
				if ('A' <= c && c <= 'Z')
					c = c - 'A' + 'a';
				if ('a' <= c && c <= 'z')
					word += c;
				else {
					m_token[word]++;
					word.clear();
				}
			}
			if (word.size())
				m_token[word]++;
		}
		return m_token;
	}
};
