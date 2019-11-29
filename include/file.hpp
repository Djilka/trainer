#pragma once
#include <fstream>

class t_file_r {
protected:
	fstream fs;
	using t_len = streamsize;
	using t_mode = ios_base::openmode;
public:
	t_file_r(t_string nm, t_mode mode = fstream::in | std::ifstream::binary)
	{
		fs.open(nm, mode);
	}

	~t_file_r()
	{
		fs.close();
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
public:
	t_file_w(t_string nm) : t_file_r(nm, fstream::out | fstream::trunc) { }
};
