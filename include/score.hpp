
class t_score {
	t_count s_min = 0, s_max = max_score;
	t_scores score;

	t_count check(t_dict *d)
	{
		if (d->pass == max_try && d->count == max_try)
			return s_bad;
		if (!d->count)
			return s_min;
		t_count s = d->pass * 100 / d->count;
		return s < s_min ? s_min : s > s_max ? s_max : s;
	}

	tp_dicts select_word(int &count, int index, tp_dicts &dicts)
	{
		int val = 0;
		t_set checked;

		for (tp_dict pd : score[index]) {
			if (!checked.count(pd->word)) {
				checked.insert(pd->word);

				cout << "word:\n";
				pd->print(cout);
				cout << "Do you like it?\n";
				cout << "1. yes\n";
				cout << "2. I know it\n";
				cout << "3. no\n";
				cin >> val;

				switch (val) {
				case 1:
					dicts.push_back(pd);
					count--;
					break;
				case 2:
					pd->count = max_try;
					pd->pass = max_try;
					break;
				}
				if (!count)
					break;
			}
		}
		return dicts;
	}
public:
	void add(t_dict *dict)
	{
		t_count s = check(dict);
		score[s].push_back(dict);
	}

	void add(t_dicts &dicts)
	{
		for (int i = 0; i < dicts.size(); i++)
			add(&dicts[i]);
	}

	void remove()
	{
		for (int i = s_min; i <= s_max; i++)
			score[i].clear();
	}

	void remove(t_dict d)
	{
		for (int i = s_min; i <= s_max; i++) {
			for (auto it = score[i].begin(); it != score[i].end(); it++)
				if (*(*it) == d)
					score[i].erase(it);
		}
	}

	void sort_score(tm_token token)
	{
		for (int i = s_min; i <= s_max; i++) {
			sort(score[i].begin(), score[i].end(),
				[&token](tp_dict i, tp_dict j)
				{
					return token[i->word] < token[j->word];
				});
		}
	}

	void update(tm_token token)
	{
		for (int i = s_min; i <= s_max; i++) {
			tpi_dicts it = score[i].begin();
			while (it != score[i].end()) {
				t_count s = check((*it));
				if (s == s_bad)
					it = score[i].erase(it);
				else if (s != i) {
					score[s].push_back(*it);
					it = score[i].erase(it);
				} else
					it++;
			}
		}
		sort_score(token);
	}

	tp_dicts train(int count)
	{
		tp_dicts dicts;
		for (int i = s_min + 1; i <= s_max && count; i++)
			select_word(count, i, dicts);
		return dicts;
	}

	tp_dicts learn(int count)
	{
		tp_dicts dicts;
		select_word(count, s_min, dicts);
		return dicts;
	}
};
