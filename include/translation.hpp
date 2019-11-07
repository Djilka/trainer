#include "web.hpp"
#include "tokenization.hpp"
#include "parser.hpp"

class t_translation {
	static t_string dir;
public:
	static
	void set_dir(t_string ndir)
	{
		dir = ndir;
	}

	static
	t_vocabulary translate(t_strings words)
	{
		return translate(token_words(words));
	}

	static
	t_vocabulary translate(tm_token tokens)
	{
		t_vocabulary voc;
		voc.path(dir);
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

	static
	t_vocabulary translate(t_string text)
	{
		t_tokenization tok(text);
		return translate(tok.tokens());
	}
};

t_string t_translation::dir = dir_tmp;
