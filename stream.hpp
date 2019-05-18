#include "file.hpp"
#include "convert.hpp"

template <class t_data>
class t_stream {
	typedef vector<t_data> tv_data;
public:
	static
	tv_data read(t_string name)
	{
		tv_data d;
		
		t_file file(name);
		t_raw raw;
		for (file.read(raw.len); raw.len && file.is_OK(); file.read(raw.len)) {
			file.read(raw.ptr, raw.len);
			t_data data = t_convert<t_data>::convert(raw);
			d.push_back(data);
		}

		return d;
	}

	static
	void write(t_string name, tv_data d)
	{
		t_file file(name);
		for (int i = 0; i < d.size() && file.is_OK(); i++) {
			t_raw raw = t_convert<t_data>::convert(d[i]);
			file.write(raw.len);
			file.write(raw.ptr, raw.len);
		}
	}
};
