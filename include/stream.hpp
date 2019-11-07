#include "file.hpp"

class t_stream {
public:
	template <class t_data>
	static
	void read(t_string name, t_data &d)
	{
		t_file_r file(name);
		file.read(d);
	}

	template <class t_data>
	static
	void write(t_string name, t_data d)
	{
		t_file_w file(name);
		file.write(d);
	}

	// vector
	template <class t_data>
	static
	void read(t_string name, vector<t_data> &d)
	{
		t_file_r file(name);
		while (file.is_OK()) {
			t_data tmp;
			file.read(tmp);
			d.push_back(tmp);
		}
	}

	template <class t_data>
	static
	void write(t_string name, vector<t_data> d)
	{
		t_file_w file(name);
		for (t_data data : d)
			if (file.is_OK())
				file.write(data);
	}

	// tm_token
	static
	void read(t_string name, tm_token &d)
	{
		t_file_r file(name);
		while (file.is_OK()) {
			t_token tmp;
			file.read(tmp);
			d[tmp.word] = tmp.count;
		}
	}

	static
	void write(t_string name, tm_token d)
	{
		t_file_w file(name);
		for (auto it = d.begin(); it != d.end(); it++) {
			t_token token(it->first, it->second);
			file.write(token);
		}
	}
};
