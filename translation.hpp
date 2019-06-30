#include "tokenization.hpp"
#include "web.hpp"
#include "parser.hpp"

class t_translation {
	typedef vector<t_dict> t_dicts;
	t_string text;
	t_string dir;
public:
	t_translation(t_string ntext)
	{
		text = ntext;
		dir = ntext;
	}

	t_vocabulary translate()
	{
		t_vocabulary voc;
		t_tokenization tok(text);
		
		// create dir
		voc.path(dir);
		tm_token tokens = tok.tokens();
		voc.tokens(tokens);
		t_strings words = token_names(tokens);

		// web
		t_web::load(dir, words);

		// parse
		for (t_string nm : words) {
			t_string path = dir + '/' + nm;
			t_parser parser(path);
			voc.add(parser.dict());
		}

		// clear dir

		return voc;
	}

};
