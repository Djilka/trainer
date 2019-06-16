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

	template <class t_type>
	void write(t_type &data)
	{
		fs.write((char*) &data, sizeof(t_type));
	}

	template <class t_type>
	void read(t_type &data)
	{
		fs.read((char*) &data, sizeof(t_type));
	}

	void read(char *data, size_t size)
	{
		fs.read(data, size);
	}

	void write(char *data, size_t size)
	{
		fs.write(data, size);
	}

	void pos(int delta)
	{
		fs.seekg(delta, fs.cur);
	}
};
