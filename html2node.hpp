#include "node.hpp"

class t_html2node
{
	t_file_html *file_html = nullptr;
	t_node res;

	bool is_close(t_string str)
	{
		return str.find("</") == 0;
	}

	t_node into(t_data &d)
	{
		t_node node(d.str);
		for (; file_html->is_OK();) {
			d = file_html->read();
			if (d.msg)
				node.msg = d.str;
			else if (is_close(d.str))
				return node;
			else
				node.child.push_back(into(d));
		}
		return node;
	}
public:
	t_html2node(t_file_html *file)
	{
		file_html = file;
	}

	bool load(t_string name_class)
	{
		t_data d = file_html->read();
		bool is_load = d.find(name_class) != string::npos;
		if (is_load)
			res = into(d);
		return is_load && file_html->is_OK();
	}

	t_node get()
	{
		return res;
	}
};
