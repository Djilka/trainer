
class t_node {
	typedef vector<t_node> t_nodes;

	t_string get_class()
	{
		t_string tmp_class = "class=\"";
		size_t start = node.find(tmp_class);
		if (start != string::npos) {
			start += tmp_class.length();
			size_t end = node.find("\"", start);
			if (end != string::npos)
				return node.substr(start, end - start);
		}
		return "";
	}

	t_string get_nm()
	{
		t_string nm;
		for (int i = 1; i < node.length() && node[i] != ' ' && node[i] != '>'; i++)
			nm += node[i];
		return nm;
	}

public:
	t_string node;
	t_string nm;
	t_string msg;
	t_nodes  child;

	t_node() {}
	t_node(t_string str)
	{
		node = str;
		nm = get_nm();
	}

	void print()
	{
		cout << "node: " << node << "\n";
		cout << "nm: " << nm
			<< "; msg: " << msg << "\n\tchild:\n";
		for (int i = 0; i < child.size(); i++)
			cout << "\t\t" << child[i].nm << "\n";
		cout << "\n\n";
		for (int i = 0; i < child.size(); i++)
			child[i].print();
	}

	bool is_class(t_string name)
	{
		return get_class().find(name) == 0;
	}
};
