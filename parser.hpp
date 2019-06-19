#include "html_file.hpp"
#include "html2node.hpp"

class t_parser
{
	t_html_file *html_file = nullptr;

	void title(t_dict &dict, t_node node)
	{
		dict.word = node.msg;
		for (int i = 0; i < node.child.size(); i++) {
			if (node.child[i].is_class("dictionary-transcription"))
				dict.trans = node.child[i].msg;
			if (node.child[i].is_class("dictionary-pos"))
				dict.type = node.child[i].msg;
		}
	}

	t_strings synonym(t_node node)
	{
		t_strings syn;
		for (int i = 0; i < node.child.size(); i++) 
			syn.push_back(node.child[i].msg);
		return syn;
	}

	t_strings translate(t_node node)
	{
		t_strings transl;
		for (int i = 0; i < node.child.size(); i++) {
			if (node.child[i].is_class("dictionary-meaning"))
				transl.push_back(node.child[i].msg);
		}
		return transl;
	}

	t_item meaning(t_node node)
	{
		t_item item;
		for (int i = 0; i < node.child.size(); i++) {
			if (node.child[i].is_class("dictionary-meanings-value"))
				item.tr = translate(node.child[i]);
			if (node.child[i].is_class("dictionary-meanings-trs"))
				item.syn = synonym(node.child[i]);
		}
		return item;
	}	

	void meanings(t_dict &dict, t_node node)
	{
		for (int i = 0; i < node.child.size(); i++) {
			if (node.child[i].is_class("dictionary-meanings-item"))
				dict.items.push_back(meaning(node.child[i]));
		}
	}

	t_dict nodes(t_node node)
	{
		t_dict dict;
		if (node.is_class("dictionary-item")) {
			for (int i = 0; i < node.child.size(); i++) {
				if (node.child[i].is_class("dictionary-title"))
					title(dict, node.child[i]);
				if (node.child[i].is_class("dictionary-meanings"))
					meanings(dict, node.child[i]);
			}
		}
		
		return dict;
	}

public:
	t_parser(t_string nm)
	{
		html_file = new t_html_file(nm);
	}

	~t_parser()
	{
		delete html_file;
	}

	t_dicts dict()
	{
		t_dicts d;

		html_file->skip("<body");
		html_file->skip("class=\"dictionary-list");
		html_file->skip("class=\"tab-list");

		if (nullptr != html_file && html_file->is_OK()) {
			t_html2node node(html_file);
			for (; node.load("dictionary-item");) {
				t_dict dh = nodes(node.get());
				dh.print();
				d.push_back(dh);
			}
		}

		return d;
	}
};

