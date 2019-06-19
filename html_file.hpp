#include "file.hpp"

class t_data
{
	bool is_start(char c)
	{
		return c == '<';
	}

	bool is_end(char c)
	{
		return c == '>';
	}

public:
	t_string str;
	bool msg;

	bool needed_back()
	{
		msg = !is_start(str[0]);
		if (msg) {
			str.pop_back();
			if (str.length() && str.back() == ' ')
				str.pop_back();
		}
		return msg;
	}

	bool complite()
	{
		return (is_start(str.back()) || is_end(str.back())) && str.length() > 1;
	}

	size_t size()
	{
		return str.length();
	}

	char back()
	{
		return size() ? str.back() : 0;
	}

	size_t find(t_string pattern)
	{
		return str.find(pattern);
	}
};


class t_html_file: public t_file
{
public:
	t_html_file(t_string nm): t_file(nm) {}

	t_data read()
	{
		t_data d;
		char c;
		while (is_OK() && !d.complite()) {
			fs.get(c);
			if (c == '\n' || c == '\t' || (d.size() == 0 && c == ' '))
				continue;
			if ((c == ' ' && d.back() != ' ') || c != ' ')
				d.str += c;
		}

		if (d.size() && d.needed_back())
			fs.seekp(-1, ios_base::cur);
		
		return d;
	}

	void skip(t_string pattern)
	{
		t_data d;
		do {
			d = read();
		} while (is_OK() && d.find(pattern) == string::npos);
	}
};
