#include "node.hpp"

class t_html2node {
	t_html_file *html_file = nullptr;
	t_node res;

	bool is_close(t_string str)
	{
		return str.find("</") == 0;
	}

	t_node into(t_data &d)
	{
		t_node node(d.str);
		for (; html_file->is_OK();) {
			d = html_file->read();
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
	t_html2node(t_html_file *file)
	{
		html_file = file;
	}

	bool load(t_string name_class)
	{
		t_data d = html_file->read();
		bool is_load = d.find(name_class) != string::npos;
		if (is_load)
			res = into(d);
		return is_load && html_file->is_OK();
	}

	t_node get()
	{
		return res;
	}
};
