#include "settings.hpp"
#include "dict.hpp"
#include "token.hpp"
#include "stream.hpp"
#include "score.hpp"

#include "trainer.hpp"

class t_vocabulary_base {
protected:
	tm_token m_token;
	t_dicts m_dicts;
	t_string m_path;
	// trainer
	t_score score;

	tm_strings split_words()
	{
		tm_strings words;
		t_strings names = token_names(m_token);
		for (t_string name : names)
			words[name[0]].push_back(name);
		return words;
	}
public:
	void path(t_string new_path)
	{
		m_path = new_path;
	}

	t_string path()
	{
		return m_path;
	}

	void dicts(t_dicts new_dicts)
	{
		score.remove();
		m_dicts = new_dicts;
		score.add(m_dicts);
	}

	t_dicts dicts()
	{
		return m_dicts;
	}

	void tokens(tm_token token)
	{
		m_token = token;
	}

	tm_token tokens()
	{
		return m_token;
	}

	void add(t_dicts new_dicts)
	{
		for (t_dict d : new_dicts)
			if (!m_token.count(d.word)) {
				m_dicts.push_back(d);
				score.add(&m_dicts.back());
			}
	}

	void add(tm_token tokens)
	{
		for (ti_token t = tokens.begin(); t != tokens.end(); t++)
			m_token[t->first] += t->second;
	}

	void add(t_vocabulary_base voc)
	{
		add(voc.dicts());
		add(voc.tokens());
	}

	void print()
	{
		// 
	}

	void info()
	{
		cout << "path : " << m_path << "\n";
		cout << "count words : " << m_token.size() << "\n";
	}

	tm_token unique(tm_token tm)
	{
		tm_token utoken;
		for (ti_token t = tm.begin(); t != tm.end(); t++)
			if (m_token.count(t->first))
				m_token[t->first] += t->second;
			else
				utoken[t->first] = t->second;
		return utoken;
	}
};

class t_vocabulary_word : public t_vocabulary_base {
public:
	void word_remove(t_string word)
	{
		if (m_token.count(word)) {
			for (ti_dicts it = m_dicts.begin(); it != m_dicts.end(); it++)
				if (it->word == word) {
					score.remove(*it);
					m_dicts.erase(it);
					break;
				}
			m_token.erase(word);
		}
	}

	void word_info(t_string word)
	{
		if (!m_token.count(word))
			return;
		cout << word << " : " << m_token[word] << "\n";
		for (ti_dicts it = m_dicts.begin(); it != m_dicts.end(); it++)
			if (it->word == word) {
				cout << *it;
				return;
			}
	}

	void word_add(t_string word, t_string trans)
	{
		m_token[word]++;
		for (ti_dicts it = m_dicts.begin(); it != m_dicts.end(); it++)
			if (it->word == word) {
				if (!it->translation_find(trans))
					it->translation_add(trans);
				return;
			}
		t_dict d(word);
		d.translation_add(trans);
		m_dicts.push_back(d);
		score.add(&m_dicts.back());
	}
};

class t_vocabulary_train : public t_vocabulary_word {
	t_pool pool;
public:
	void train(t_count count, t_type_test t)
	{
		pool.test_type(t);
		pool.test(score.train(count));
	}

	void learn(t_count count, t_type_test t)
	{
		pool.test_type(t);
		pool.test(score.learn(count));
	}
};

class t_vocabulary : public t_vocabulary_train {
public:
	void load()
	{
		t_path path;
		t_strings names = path.names(m_path);
		for (t_string name : names) {
			t_string name_file = m_path + name;
			if (find_str(name, ext_dict)) {
				t_stream::read(name_file, m_dicts);
			} else if (find_str(name, ext_token)) {
				t_stream::read(name_file, m_token);
			}
		}
		score.add(m_dicts);
	}

	void save()
	{
		t_path path;
		t_strings names = path.names(m_path);

		// tokens
		t_tokens tokens = token_convert(m_token);
		t_stream::write(m_path + ext_token, tokens);

		// dicts
		tm_strings words = split_words();
		for (auto it = words.begin(); it != words.end(); it++)
			t_stream::write(m_path + it->first + ext_dict, it->second);
	}
};
