#pragma once
#include <fstream>

enum t_mode_op {
	tmo_rd, tmo_wr
};

class t_file_r {
protected:
	fstream fs;
	typedef streamsize t_len;
	typedef ios_base::openmode t_mode;
	static const t_mode mode = fstream::in | fstream::out;

	t_mode_op mode_op;
public:
	t_file_r(t_string nm)
	{
		fs.open(nm, mode);
	}

	~t_file_r()
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

	template <class t_data>
	void write(t_data data)
	{
		fs << data;
	}

	template <class t_data>
	void read(t_data &data)
	{
		fs >> data;
	}

	void pos(int delta)
	{
		fs.seekg(delta, fs.cur);
	}
};

class t_file_w : public t_file_r {
	static const t_mode mode = fstream::in | fstream::out | fstream::trunc;
public:
	t_file_w(t_string nm) : t_file_r(nm) { }
};
