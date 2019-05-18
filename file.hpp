#pragma once
#include <fstream>

enum t_mode_op {
	tmo_rd, tmo_wr
};

class t_file
{
protected:
	fstream fs;
	typedef streamsize t_len;
	typedef ios_base::openmode t_mode;
	static const t_mode mode = fstream::in | fstream::out;

	t_mode_op mode_op;
public:
	t_file(t_string nm)
	{
		fs.open(nm, mode);
		if (!fs.is_open())
			fs.open(nm, mode | fstream::trunc);
	}

	~t_file()
	{
		fs.close();
	}

	void set_mode_op(t_mode_op m)
	{
		mode_op = m;
	}

	bool error()
	{
		return fs.good();
	}

	bool is_OK()
	{
		return fs.is_open() && fs.good() && !fs.eof();
	}

	void write(t_string &data)
	{
		size_t len = data.length();
		write(len);
		fs.write(data.c_str(), sizeof(char) * (len));
	}

	void read(t_string &data)
	{
		size_t len = 0;
		read(len);
		if (is_OK())
			for (int i = 0; i < len; i++)
				data += fs.get();
	}

	template <typename TYPE>
	void write(TYPE &data)
	{
		fs.write((char*) &data, sizeof(TYPE));
	}

	template <class TYPE>
	void read(TYPE &data)
	{
		fs.read((char*) &data, sizeof(TYPE));
	}

	t_string line()
	{
		t_string str;
		getline(fs, str);
		return str;
	}

	void line(t_string str)
	{
		fs.write(str.c_str(), str.length());
	}

	void read(char *data, size_t size)
	{
		fs.read(data, size);
	}

	void write(char *data, size_t size)
	{
		fs.write(data, size);
	}
};
