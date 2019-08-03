#include <cstring>
#include <assert.h>

#include "token.hpp"
#include "dict.hpp"

struct t_raw {
	size_t size = 1024;
	size_t len = 0;
	char ptr[1024];
};

class t_convert_base {
public:
	template <typename t_type>
	static
	void write(t_raw &raw, t_type val)
	{
		assert(raw.size - raw.len >= sizeof(t_type));
		memcpy(&raw.ptr[raw.len], &val, sizeof(t_type));
		raw.len += sizeof(t_type);
	}

	static
	void write(t_raw &raw, t_string val)
	{
		write(raw, val.size());
		assert(raw.size - raw.len >= val.size());
		memcpy(&raw.ptr[raw.len], val.data(), val.size());
		raw.len += val.size();
	}

	static
	void write(t_raw &raw, t_strings val)
	{
		write(raw, val.size());
		for (int i = 0; i < val.size(); i++)
			write(raw, val[i]);
	}
public:
	template <typename t_type>
	static
	void read(t_raw raw, t_type &val)
	{
		assert(raw.len >= sizeof(t_type));
		raw.len -= sizeof(t_type);
		memcpy(&val, &raw.ptr[raw.len], sizeof(t_type));
	}

	static
	void read(t_raw raw, t_string &val)
	{
		size_t size = 0;
		read(raw, size);
		assert(raw.len >= size);
		raw.len -= size;
		val = t_string(&raw.ptr[raw.len], size);
	}

	static
	void read(t_raw raw, t_strings &val)
	{
		size_t size = 0;
		read(raw, size);
		for (int i = 0; i < size; i++) {
			t_string str;
			read(raw, str);
			val.push_back(str);
		}
	}
};

template <class t_data>
class t_convert : public t_convert_base {
public:
	static
	t_data convert(t_raw raw)
	{
		return t_data();
	}

	static
	t_raw convert(t_data token)
	{
		return t_raw();
	}
};

template <>
class t_convert<t_token> : public t_convert_base {
public:
	static
	t_token convert(t_raw raw)
	{
		t_token token;
		read(raw, token.word);
		read(raw, token.count);
		return token;
	}

	static
	t_raw convert(t_token token)
	{
		t_raw raw;
		write(raw, token.word);
		write(raw, token.count);
		return raw;
	}
};

template <>
class t_convert<t_dict> : public t_convert_base {
public:
	static
	t_dict convert(t_raw raw)
	{
		t_dict dict;

		read(raw, dict.word);
		read(raw, dict.trans);
		read(raw, dict.type);
		read(raw, dict.pass);
		read(raw, dict.count);
		read(raw, dict.time_cur);
		// items
		size_t size = 0;
		read(raw, size);
		for(int i = 0; i < size; i++) {
			t_item item;
			read(raw, item.syn);
			read(raw, item.tr);
			dict.items.push_back(item);
		}
		
		return dict;
	}

	static
	t_raw convert(t_dict dict)
	{
		t_raw raw;

		write(raw, dict.word);
		write(raw, dict.trans);
		write(raw, dict.type);
		write(raw, dict.pass);
		write(raw, dict.count);
		write(raw, dict.time_cur);
		// items
		write(raw, dict.items.size());
		for(int i = 0; i < dict.items.size(); i++) {
			write(raw, dict.items[i].syn);
			write(raw, dict.items[i].tr);
		}

		return raw;
	}
};

