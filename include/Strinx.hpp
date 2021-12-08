#include <sstream>
#include <vector>

#define _XS_STRINX_
class strinx;
class strinx{
private:
	char* _str = new char[1]{'\0'};
	size_t _size = 0;
	size_t _it = 0;
	static std::string stx(float v) { std::stringstream ss; ss << v; return ss.str(); };
	static std::string stx(double v) { std::stringstream ss; ss << v; return ss.str(); };
	static std::string stx(int v) { return std::to_string(v); };
	std::vector<strinx> _split;
	bool _splt = false;
public:
	friend std::ostream& operator<<(std::ostream& os, const strinx& v);
	operator bool() const { return _size > 0 ? true : false; };
	bool operator!() const { return _size > 0 ? false : true; };
	operator int() const { return std::stoi(_str); };
	operator float() const { return std::stof(_str); };
	operator double() const { return std::stod(_str); };
	operator std::string() const { return std::string(_str); };
	operator char*() const { return _str; };
	char* data() const { return _str; };
	size_t size() const { return _size; };
	size_t lenght() const { return _size; };
	size_t len() const { return _size; };
	char& front() const { return _str[0]; };
	char& back() const { return _str[_size - 1]; };
	strinx first() const { return strinx(_str[0]); };
	strinx last() const { return strinx(_str[_size - 1]); };
	char& middle() const { return _str[_size / 2]; };
	const char* split_it = " \n\t";
	size_t& iterator() { return _it; };
	void reset() { _it = 0; };
	bool canmove() const { return _it >= _size ? false : true; };
	bool canmoveback() const { return _it == 0 ? false : true; };
	bool canmoveline() const {
		if (canmove()) {
			for (volatile size_t _i = _it; ; _i++) {
				if (_i >= _size)
					return false;
				if (_str[_i] == '\n' || _i == _size - 1)
					return true;
			};
		}
		else
			return false;
	}
	bool move() {
		if (_it < _size) {
			_it++;
			return true;
		}
		else
			_it = 0;
		return true;
	};
	bool moveback() {
		if (_it > -1) {
			_it--;
			return true;
		}
		else
			_it = _size - 1;
		return false;
	};
	bool move(size_t v) {
		if (_it < _size && _it + v < _size) {
			_it += v;
			return true;
		}
		else
			_it = _it + v - _size;
		return false;
	};
	bool moveback(size_t v) {
		if (_it > -1 && _it - v > -1) {
			_it -= v;
			return false;
		}
		else
			_it = _size - (_it + v - _size);
		return false;
	};
	/*bool moveline() {
		if (canmove()) {
			move();
			while (true) {
				if (_str[_it] == '\n')
					return true;
				if (!canmove())
					return false;
				_it++;
			};
		}
		else
			return false;
	}*/
	bool operator++() { return move(); };
	bool operator--() { return moveback(); };
	const char* c_str() const { return _str; };
	std::string str() const { return std::string(_str); };
	strinx() = default;
	strinx(const strinx&) = default;
	strinx(const char* v)	{ _str = _strdup(v); _size = strlen(_str); };
	strinx(char v)			{ _str = new char[2]{ v, '\0' }; _size = 1; };
	strinx(std::string& v)	{ _str = _strdup(v.c_str()); _size = v.size(); };
	strinx(int v)			{ _str = _strdup(stx(v).c_str()); _size = strlen(_str); };
	strinx(double v)		{ _str = _strdup(stx(v).c_str()); _size = strlen(_str); };
	strinx(float v)			{ _str = _strdup(stx(v).c_str()); _size = strlen(_str); };
	strinx(std::initializer_list<int> v) {
		strinx t;
		t += '{';
		t += ' ';
		for (const auto& i : v) {
			t += i;
			t += ',';
			t += ' ';
		};
		t = t(0, t.size() - 1);
		t += ' ';
		t += '}';
		*this = t;
	};
	strinx(std::initializer_list<const char*> v) {
		strinx t;
		t += '{';
		t += ' ';
		for (const auto& i : v) {
			t += i;
			t += ',';
			t += ' ';
		};
		t = t(0, t.size() - 1);
		t += ' ';
		t += '}';
		*this = t;
	};
	strinx(std::initializer_list<float> v) {
		strinx t;
		t += '{';
		t += ' ';
		for (const auto& i : v) {
			t += i;
			t += ',';
			t += ' ';
		};
		t = t(0, t.size() - 1);
		t += ' ';
		t += '}';
		*this = t;
	};
	char& operator[](const size_t& v) const { return _str[v]; };
	char& operator[](const int& v) const { return (v >= 0) ? _str[size_t(v)] : _str[_size - v]; };
	strinx operator[](std::initializer_list<size_t> v) {
		strinx t;
		for (const auto& i : v) if (i < _size) t += _str[i];
		return t;
	};
	strinx operator[](std::vector<size_t> v) {
		strinx t;
		for (const auto& i : v) if (i < _size) t += _str[i];
		return t;
	};
	strinx operator[](std::vector<int> v) {
		strinx t;
		for (const auto& i : v) if (i < _size) t += _str[i];
		return t;
	};
	strinx operator()() const { return *this; };
	strinx operator()(const size_t& v) const { return strinx(_str[v]); };
	strinx operator()(const size_t& begin, const size_t& end, const size_t& u = 1) const {
		strinx _t;
		if (begin < end)
			if (u == 1) {
				const size_t s = end - begin;
				char* c = new char[s + 1] {0};
				strncpy(c, &_str[begin], s);
				_t = (const char*)c;
			}
			else
				for (size_t i = begin; i < end; i += u)
					_t += _str[i];
		else if (begin == end)
			_t = _str[begin];
		else
			for (size_t i = begin; i > end; i-=u)
				_t += _str[i];
		return _t;
	};
	void print() const { std::cout << _str << '\n'; };
	void clear() { memset(_str, 0, _size); _size = 0; };
	void resize(const size_t& v, char c = ' ') {
		if (v < _size) {
			strinx _c = *this;
			*this = _c(0, v);
			_size = v;
		}
		else {
			strinx _c = *this;
			*this = _c(0, _size) + _c(_size, v);
			_size = v;
		};
	};
	void pop_last() { *this = _size > 0 ? this->operator()(0, _size - 1) : *this; };
	void pop_first() { *this = _size > 0 ? this->operator()(1, _size) : *this; };
	typedef std::vector<strinx> Split_t;
	Split_t& split() {
		if (!_splt) {
			strinx c = *this, s;
			while (c >> s)
				_split.push_back(s);
			_splt = true;
			return _split;
		}
		else
			return _split;
	};

	strinx random() const {
		strinx temp;
		size_t p;
		std::vector<size_t> ss;
		for (size_t i = 0; i < _size; i++) {
			p = rand() % _size;
		_r:;
			for (auto& j : ss)
				if (j == p) {
					p = rand() % _size;
					goto _r;
				};
			ss.push_back(p);
			temp += this->operator[](p);
		}
		return temp;
	};

	void format() {  };
	template <typename T, typename ...TAIL>
	strinx& format(const T& v, TAIL... tail) {
		strinx c = *this;
		c.reset();
		strinx s, t;
		while (c >> s) {
			if (s == "{}") {
				t += v;
				format(tail...);
			}
			else
				t += s;
			if (c.canmove())
				t += ' ';
		};
		_splt = false;
		*this = t;
		return *this;
	};

	strinx title() const {
		strinx c = *this, s, t;
		while (c >> s) {
			s.reset();
			s.up();
			t += s;
			if (c.canmove())
				t += ' ';
		};
		return t;
	};

	strinx reverse() const {
		strinx t;
		for (int i = this->size() - 1; i >= 0; i--)
			t += this->operator[](i);
		return t;
	};

	strinx strip() const {
		strinx c = *this, s, t;
		c >> s;
		c = c(c.iterator() - s.size(), c.size());
		c.reset();
		c = c.reverse();
		c >> s;
		t = c(c.iterator() - s.size(), c.size()).reverse();
		return t;
	};

	strinx capitalize() const {
		strinx c = *this;
		c.reset();
		c.up();
		return c;
	};

	strinx random_split() const { /*soon..*/ };

	std::vector<strinx> linesplit() const { /*soon..*/ };

	strinx sort() const { /*soon..*/ };

	void swap(const size_t& _first, const size_t& _second) {
		if (_first < _size and _second < _size) {
			const char ch1 = _str[_first], ch2 = _str[_second];
			_str[_first] = ch2;
			_str[_second] = ch1;
		};
	};

	void wrap(const size_t max, char ch = '\n') {
		/*if (_size > max) {
			strinx c = this->c_str(), t;
			c.print();
			char s;
			this->clear();
			while (c > s) {
				t += s;
				if (t.size() > max) {
					*this += t + ch;
					t.clear();
				};
			};
			*this += t;
		};*/
	};

	bool starts_with(char v) const {
		if (_size > 0)
			return _str[0] == v;
		else
			return false;
	};
	bool starts_with(const char* v) const {
		if (_size > strlen(v))
			return this->operator()(0, strlen(v)) == v;
		else if (_size == strlen(v))
			return *this == v;
		else
			return false;
	};
	bool starts_with(std::string v) const {
		if (_size > v.size())
			return this->operator()(0, v.size() - 1) == v;
		else if (_size == v.size())
			return *this == v;
		else
			return false;
	};
	bool starts_with(strinx v) const {
		if (_size > v.size())
			return this->operator()(0, v.size() - 1) == v;
		else if (_size == v.size())
			return *this == v;
		else
			return false;
	};
	bool starts_with(int v) const {
		if (_size > stx(v).size())
			return this->operator()(0, stx(v).size() - 1) == v;
		else if (_size == stx(v).size())
			return *this == v;
		else
			return false;
	};
	bool starts_with(float v) const {
		if (_size > stx(v).size())
			return this->operator()(0, stx(v).size() - 1) == v;
		else if (_size == stx(v).size())
			return *this == v;
		else
			return false;
	};

	bool ends_with(char v) const {
		if (_size > 0)
			return _str[_size-1] == v;
		else
			return false;
	};
	bool ends_with(const char* v) const {
		if (_size > strlen(v))
			return this->operator()(_size - strlen(v), _size) == v;
		else if (_size == strlen(v))
			return *this == v;
		else
			return false;
	};
	bool ends_with(std::string v) const {
		if (_size > v.size())
			return this->operator()(_size - v.size(), _size) == v;
		else if (_size == v.size())
			return *this == v;
		else
			return false;
	};
	bool ends_with(strinx v) const {
		if (_size > v.size())
			return this->operator()(_size - v.size(), _size) == v;
		else if (_size == v.size())
			return *this == v;
		else
			return false;
	};
	bool ends_with(int v) const {
		if (_size > stx(v).size())
			return this->operator()(_size - stx(v).size(), _size) == v;
		else if (_size == stx(v).size())
			return *this == v;
		else
			return false;
	};
	bool ends_with(float v) const {
		if (_size > stx(v).size())
			return this->operator()(_size - stx(v).size(), _size) == v;
		else if (_size == stx(v).size())
			return *this == v;
		else
			return false;
	};

	void operator=(char v)			{ _str = new char[2]{ v, '\0' }; _size = 1; _splt = false; };
	void operator=(const char* v)	{ _str = _strdup(v); _size = strlen(v); _splt = false; };
	void operator=(std::string v)	{ _str = _strdup(v.c_str()); _size = v.size(); _splt = false; };
	void operator=(int v)			{ _str = _strdup(stx(v).c_str()); _size = strlen(_str); _splt = false; };
	void operator=(float v)			{ _str = _strdup(stx(v).c_str()); _size = strlen(_str); _splt = false; };
	void operator=(std::initializer_list<int> v) { *this = strinx(v); _splt = false; };
	void operator=(std::initializer_list<float> v) { *this = strinx(v); _splt = false; };
	void operator=(std::initializer_list<const char*> v) { *this = strinx(v); _splt = false; };

	void operator+=(const char* v)	{
		if (_size == 0)
			_str = _strdup(v);
		else {
			const size_t s = _size + strlen(v);
			char* c = new char[s]{0};
			strncpy(c, (const char*)_str, _size);
			strcat(c, v);
			_str = c;
		};
		_size += strlen(v);
		_splt = false;
	};
	void operator+=(char v) {
		char* c = new char[2]{ v, '\0'};
		if (_size == 0)
			_str = c;
		else {
			char* c = new char[_size + 1]{ 0 };
			strncpy(c, (const char*)_str, _size);
			strcat(c, &v);
			_str = c;
		};
		_size++;
		_splt = false;
	};
	void operator+=(std::string v) {
		if (_size == 0)
			_str = _strdup(v.c_str());
		else {
			const size_t s = _size + v.size();
			char* c = new char[s] {0};
			strncpy(c, (const char*)_str, _size);
			strcat(c, v.c_str());
			_str = c;
		};
		_size += v.size();
		_splt = false;
	};
	void operator+=(strinx v) {
		if (_size == 0)
			_str = _strdup(v.c_str());
		else {
			const size_t s = _size + v.size();
			char* c = new char[s] {0};
			strncpy(c, (const char*)_str, _size);
			strcat(c, v.c_str());
			_str = c;
		};
		_size += v.size();
		_splt = false;
	};
	void operator+=(int v) {
		const std::string f = stx(v);
		if (_size == 0)
			_str = _strdup(f.c_str());
		else {
			const size_t s = _size + f.size();
			char* c = new char[s] {0};
			strncpy(c, (const char*)_str, _size);
			strcat(c, f.c_str());
			_str = c;
		};
		_size += f.size();
		_splt = false;
	};
	void operator+=(float v) {
		const std::string f = stx(v);
		if (_size == 0)
			_str = _strdup(f.c_str());
		else {
			const size_t s = _size + f.size();
			char* c = new char[s] {0};
			strncpy(c, (const char*)_str, _size);
			strcat(c, f.c_str());
			_str = c;
		};
		_size += f.size();
		_splt = false;
	};
	void operator+=(std::initializer_list<int> v) { *this += strinx(v); _splt = false; };
	void operator+=(std::initializer_list<float> v) { *this += strinx(v); _splt = false; };
	void operator+=(std::initializer_list<const char*> v) { *this += strinx(v); _splt = false; };

	strinx& operator<<(const char* v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(char v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(std::string v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(strinx v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(int v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(float v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(std::initializer_list<int> v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(std::initializer_list<float> v) { *this += ' '; *this += v; return *this; };
	strinx& operator<<(std::initializer_list<const char*> v) { *this += ' '; *this += v; return *this; };

	strinx& operator<(const char* v) { *this += v; return *this; };
	strinx& operator<(char v) { *this += v; return *this; };
	strinx& operator<(std::string v) { *this += v; return *this; };
	strinx& operator<(strinx v) { *this += v; return *this; };
	strinx& operator<(int v) { *this += v; return *this; };
	strinx& operator<(float v) { *this += v; return *this; };
	strinx& operator<(std::initializer_list<int> v) { *this += v; return *this; };
	strinx& operator<(std::initializer_list<float> v) { *this += v; return *this; };
	strinx& operator<(std::initializer_list<const char*> v) { *this += v; return *this; };

	bool operator==(char v) const {
		if (_size == 1 && _str[0] == v)
			return true;
		return false;
	};
	bool operator==(const char* v) const {
		if (_size == strlen(v)) {
			for (size_t i = 0; i < _size; i++)
				if (_str[i] == v[i]);
				else
					return false;
			return true;
		};
		return false;
	};
	bool operator==(std::string v) const {
		if (_size == v.size()) {
			for (size_t i = 0; i < _size; i++)
				if (_str[i] == v[i]);
				else
					return false;
			return true;
		};
		return false;
	}
	bool operator==(int v) const {
		if (_size == stx(v).size()) {
			size_t _c = 0;
			for (size_t i = 0; i < _size; i++)
				if (_str[i] == stx(v)[i])
					_c++;
				else
					return false;
			return true;
		};
		return false;
	}
	bool operator==(float v) const {
		if (_size == stx(v).size()) {
			size_t _c = 0;
			for (size_t i = 0; i < _size; i++)
				if (_str[i] == stx(v)[i])
					_c++;
				else
					return false;
			return true;
		};
		return false;
	}
	bool operator==(strinx v) const {
		if (_size == v.size()) {
			for (size_t i = 0; i < _size; i++)
				if (_str[i] == v[i]);
				else
					return false;
			return true;
		};
		return false;
	}

	bool operator!=(char v) const { return !(*this == v); };
	bool operator!=(const char* v) const { return !(*this == v); };
	bool operator!=(std::string v) const { return !(*this == v); };
	bool operator!=(int v) const { return !(*this == v); };
	bool operator!=(float v) const { return !(*this == v); };

	void operator-=(char v) { takeout(v); };
	void operator-=(const char* v) { takeout(v); };
	void operator-=(std::string v) { takeout(v); };
	void operator-=(strinx v) { takeout(v); };
	void operator-=(int v) { takeout(v); };
	void operator-=(float v) { takeout(v); };

	strinx operator-(char v) const { strinx _t = *this; _t.takeout(v); return _t; };
	strinx operator-(const char* v) const { strinx _t = *this; _t.takeout(v); false; return _t; };
	strinx operator-(std::string v) const { strinx _t = *this; _t.takeout(v); return _t; };
	strinx operator-(strinx v) const { strinx _t = *this; _t.takeout(v); return _t; };
	strinx operator-(int v) const { strinx _t = *this; _t.takeout(v); return _t; };
	strinx operator-(float v) const { strinx _t = *this; _t.takeout(v); return _t; };

	strinx operator+(char v) const { strinx _t = *this; _t += v; return _t; };
	strinx operator+(const char* v) const { strinx _t = *this; _t += v; return _t; };
	strinx operator+(std::string v) const { strinx _t = *this; _t += v; return _t; };
	strinx operator+(strinx v) const { strinx _t = *this; _t += v; return _t; };
	strinx operator+(int v) const { strinx _t = *this; _t += v; return _t; };
	strinx operator+(float v) const { strinx _t = *this; _t += v; return _t; };

	bool operator>>(strinx& v) {
		while (canmove()) {
			volatile bool _y = false;
			for (volatile size_t i = 0; i < strlen(split_it); i++)
				if (_str[_it] == split_it[i])
					_y = true;
			if (_y)
				move();
			else
				break;
		};
		if (canmove()) {
			v.clear();
			bool _y = false;
			for (; canmove(); move()) {
				for (volatile size_t i = 0; i < strlen(split_it); i++)
					if (_str[_it] == split_it[i]) {
						_y = true;
					};
				if (_y == false)
					v += _str[_it];
				else
					break;
			};
			return true;
		}
		else
			return false;
	};
	bool operator>>(std::string& v) {
		while (canmove()) {
			volatile bool _y = false;
			for (volatile size_t i = 0; i < strlen(split_it); i++)
				if (_str[_it] == split_it[i])
					_y = true;
			if (_y)
				move();
			else
				break;
		};
		if (canmove()) {
			v.clear();
			bool _y = false;
			for (; canmove(); move()) {
				for (volatile size_t i = 0; i < strlen(split_it); i++)
					if (_str[_it] == split_it[i]) {
						_y = true;
					};
				if (_y == false)
					v += _str[_it];
				else
					break;
			};
			return true;
		}
		else
			return false;
	};
	bool operator>>(const char*& v) {
		std::string  _v;
		while (canmove()) {
			volatile bool _y = false;
			for (volatile size_t i = 0; i < strlen(split_it); i++)
				if (_str[_it] == split_it[i])
					_y = true;
			if (_y)
				move();
			else
				break;
		};
		if (canmove()) {
			_v.clear();
			bool _y = false;
			for (; canmove(); move()) {
				for (volatile size_t i = 0; i < strlen(split_it); i++)
					if (_str[_it] == split_it[i]) {
						_y = true;
					};
				if (_y == false)
					_v += _str[_it];
				else
					break;
			};
			v = _v.c_str();
			return true;
		}
		else
			return false;
	};
	bool operator>(char& v) {
		if (canmove()) {
			v = _str[_it];
			return move();
		}
		else {
			return false;
		};
	};
	bool operator>(strinx& v) {
		if (canmove()) {
			v = _str[_it];
			return move();
		}
		else {
			return false;
		};
	};
	bool operator>(std::string& v) {
		if (canmove()) {
			v = _str[_it];
			return move();
		}
		else {
			return false;
		};
	};
	bool getline(strinx& v) {
		v.clear();
		if (canmoveline()) {
			for (; canmove(); move()) {
				if (_str[_it] != '\n')
					break;
			};
			for (; _str[_it] != '\n' && canmove(); move()) {
				v += _str[_it];
			};
			return true;
		}
		else
			return false;
	};
	bool getline(std::string& v) {
		v.clear();
		if (canmoveline()) {
			for (; canmove(); move()) {
				if (_str[_it] != '\n')
					break;
			};
			for (; _str[_it] != '\n' && canmove(); move()) {
				v += _str[_it];
			};
			return true;
		}
		else
			return false;
	};
	bool getline(const char*& v) {
		std::string _v;
		if (canmoveline()) {
			for (; canmove(); move()) {
				if (_str[_it] != '\n')
					break;
			};
			for (; _str[_it] != '\n' && canmove(); move()) {
				_v += _str[_it];
			};
			v = _v.c_str();
			return true;
		}
		else
			return false;
	};
	bool get(char& v) {
		if (canmove()) {
			v = _str[_it];
			return move();
		}
		else {
			return false;
		};
	};
	bool get(strinx& v) {
		if (canmove()) {
			v = _str[_it];
			return move();
		}
		else {
			return false;
		};
	};
	bool get(std::string& v) {
		if (canmove()) {
			v = _str[_it];
			return move();
		}
		else {
			return false;
		};
	};

	strinx operator*(size_t v) const {
		strinx _t;
		for (volatile size_t i = 0; i < v; i++)
			_t += *this;
		return _t;
	};
	void operator*=(size_t v) {
		const strinx _t = *this;
		this->clear();
		for (volatile size_t i = 0; i < v; i++)
			*this += _t;
		_splt = false;
	};
	strinx operator*(char v) const {
		strinx _t = *this, _j;
		for (size_t i = 0; i < _size * 2; i += 2) {
			_j[i] = _t[i / 2];
			_j[i + 1] = v;
		};
		return _j;
	};
	void operator*=(char v) {
		strinx _t = *this;
		this->resize(_size);
		for (size_t i = 0; i < _size * 2; i+=2) {
			_str[i] = _t[i/2];
			_str[i+1] = v;
		};
		_splt = false;
	};

	float to_float() const { return std::stof(_str); };
	int to_int() const { return std::stoi(_str); };
	double to_double() const { return std::stof(_str); };

	strinx upper() const {
		strinx _t = *this;
		for (size_t i = 0; i < _size; i++) {
			switch (_t[i]) {
			case 'a': _t[i] = 'A'; break;
			case 'b': _t[i] = 'B'; break;
			case 'c': _t[i] = 'C'; break;
			case 'd': _t[i] = 'D'; break;
			case 'e': _t[i] = 'E'; break;
			case 'f': _t[i] = 'F'; break;
			case 'g': _t[i] = 'G'; break;
			case 'h': _t[i] = 'H'; break;
			case 'i': _t[i] = 'I'; break;
			case 'j': _t[i] = 'J'; break;
			case 'k': _t[i] = 'K'; break;
			case 'l': _t[i] = 'L'; break;
			case 'm': _t[i] = 'M'; break;
			case 'n': _t[i] = 'N'; break;
			case 'o': _t[i] = 'O'; break;
			case 'p': _t[i] = 'P'; break;
			case 'r': _t[i] = 'R'; break;
			case 's': _t[i] = 'S'; break;
			case 't': _t[i] = 'T'; break;
			case 'q': _t[i] = 'Q'; break;
			case 'u': _t[i] = 'U'; break;
			case 'v': _t[i] = 'V'; break;
			case 'w': _t[i] = 'W'; break;
			case 'x': _t[i] = 'X'; break;
			case 'y': _t[i] = 'Y'; break;
			case 'z': _t[i] = 'Z'; break;
			}
		}
		return _t;
	};
	strinx lower() const {
		strinx _t = *this;
		for (size_t i = 0; i < _size; i++) {
			switch (_t[i]) {
			case 'A': _t[i] = 'a'; break;
			case 'B': _t[i] = 'b'; break;
			case 'C': _t[i] = 'c'; break;
			case 'D': _t[i] = 'd'; break;
			case 'E': _t[i] = 'e'; break;
			case 'F': _t[i] = 'f'; break;
			case 'G': _t[i] = 'g'; break;
			case 'H': _t[i] = 'h'; break;
			case 'I': _t[i] = 'i'; break;
			case 'J': _t[i] = 'j'; break;
			case 'K': _t[i] = 'k'; break;
			case 'L': _t[i] = 'l'; break;
			case 'M': _t[i] = 'm'; break;
			case 'N': _t[i] = 'n'; break;
			case 'O': _t[i] = 'o'; break;
			case 'P': _t[i] = 'p'; break;
			case 'R': _t[i] = 'r'; break;
			case 'S': _t[i] = 's'; break;
			case 'T': _t[i] = 't'; break;
			case 'Q': _t[i] = 'q'; break;
			case 'U': _t[i] = 'u'; break;
			case 'V': _t[i] = 'v'; break;
			case 'W': _t[i] = 'w'; break;
			case 'X': _t[i] = 'x'; break;
			case 'Y': _t[i] = 'y'; break;
			case 'Z': _t[i] = 'z'; break;
			}
		}
		return _t;
	};
	strinx numbers() const {
		strinx _t;
		for (size_t i = 0; i < _size; i++) {
			switch (_str[i]) {
			case '1': _t += '1'; break;
			case '2': _t += '2'; break;
			case '3': _t += '3'; break;
			case '4': _t += '4'; break;
			case '5': _t += '5'; break;
			case '6': _t += '6'; break;
			case '7': _t += '7'; break;
			case '8': _t += '8'; break;
			case '9': _t += '9'; break;
			case '0': _t += '0'; break;
			}
		}
		return _t;
	}

	bool up() {
		switch (_str[_it]) {
		case 'a': _str[_it] = 'A'; break;
		case 'b': _str[_it] = 'B'; break;
		case 'c': _str[_it] = 'C'; break;
		case 'd': _str[_it] = 'D'; break;
		case 'e': _str[_it] = 'E'; break;
		case 'f': _str[_it] = 'F'; break;
		case 'g': _str[_it] = 'G'; break;
		case 'h': _str[_it] = 'H'; break;
		case 'i': _str[_it] = 'I'; break;
		case 'j': _str[_it] = 'J'; break;
		case 'k': _str[_it] = 'K'; break;
		case 'l': _str[_it] = 'L'; break;
		case 'm': _str[_it] = 'M'; break;
		case 'n': _str[_it] = 'N'; break;
		case 'o': _str[_it] = 'O'; break;
		case 'p': _str[_it] = 'P'; break;
		case 'r': _str[_it] = 'R'; break;
		case 's': _str[_it] = 'S'; break;
		case 't': _str[_it] = 'T'; break;
		case 'q': _str[_it] = 'Q'; break;
		case 'u': _str[_it] = 'U'; break;
		case 'v': _str[_it] = 'V'; break;
		case 'w': _str[_it] = 'W'; break;
		case 'x': _str[_it] = 'X'; break;
		case 'y': _str[_it] = 'Y'; break;
		case 'z': _str[_it] = 'Z'; break;
		}
		_splt = false;
		return move();
	};
	bool low() {
		switch (_str[_it]) {
		case 'A': _str[_it] = 'a'; break;
		case 'B': _str[_it] = 'b'; break;
		case 'C': _str[_it] = 'c'; break;
		case 'D': _str[_it] = 'd'; break;
		case 'E': _str[_it] = 'e'; break;
		case 'F': _str[_it] = 'f'; break;
		case 'G': _str[_it] = 'g'; break;
		case 'H': _str[_it] = 'h'; break;
		case 'I': _str[_it] = 'i'; break;
		case 'J': _str[_it] = 'j'; break;
		case 'K': _str[_it] = 'k'; break;
		case 'L': _str[_it] = 'l'; break;
		case 'M': _str[_it] = 'm'; break;
		case 'N': _str[_it] = 'n'; break;
		case 'O': _str[_it] = 'o'; break;
		case 'P': _str[_it] = 'p'; break;
		case 'R': _str[_it] = 'r'; break;
		case 'S': _str[_it] = 's'; break;
		case 'T': _str[_it] = 't'; break;
		case 'Q': _str[_it] = 'q'; break;
		case 'U': _str[_it] = 'u'; break;
		case 'V': _str[_it] = 'v'; break;
		case 'W': _str[_it] = 'w'; break;
		case 'X': _str[_it] = 'x'; break;
		case 'Y': _str[_it] = 'y'; break;
		case 'Z': _str[_it] = 'z'; break;
		}
		_splt = false;
		return move();
	};
	bool up(size_t v) {
		if (v > _size)
			return false;
		else
			switch (_str[v]) {
			case 'a': _str[v] = 'A'; break;
			case 'b': _str[v] = 'B'; break;
			case 'c': _str[v] = 'C'; break;
			case 'd': _str[v] = 'D'; break;
			case 'e': _str[v] = 'E'; break;
			case 'f': _str[v] = 'F'; break;
			case 'g': _str[v] = 'G'; break;
			case 'h': _str[v] = 'H'; break;
			case 'i': _str[v] = 'I'; break;
			case 'j': _str[v] = 'J'; break;
			case 'k': _str[v] = 'K'; break;
			case 'l': _str[v] = 'L'; break;
			case 'm': _str[v] = 'M'; break;
			case 'n': _str[v] = 'N'; break;
			case 'o': _str[v] = 'O'; break;
			case 'p': _str[v] = 'P'; break;
			case 'r': _str[v] = 'R'; break;
			case 's': _str[v] = 'S'; break;
			case 't': _str[v] = 'T'; break;
			case 'q': _str[v] = 'Q'; break;
			case 'u': _str[v] = 'U'; break;
			case 'v': _str[v] = 'V'; break;
			case 'w': _str[v] = 'W'; break;
			case 'x': _str[v] = 'X'; break;
			case 'y': _str[v] = 'Y'; break;
			case 'z': _str[v] = 'Z'; break;
			default: return false;
			};
		_splt = false;
		return true;
	};
	bool low(size_t v) {
		if (v > _size)
			return false;
		else
			switch (_str[v]) {
			case 'A': _str[v] = 'a'; break;
			case 'B': _str[v] = 'b'; break;
			case 'C': _str[v] = 'c'; break;
			case 'D': _str[v] = 'd'; break;
			case 'E': _str[v] = 'e'; break;
			case 'F': _str[v] = 'f'; break;
			case 'G': _str[v] = 'g'; break;
			case 'H': _str[v] = 'h'; break;
			case 'I': _str[v] = 'i'; break;
			case 'J': _str[v] = 'j'; break;
			case 'K': _str[v] = 'k'; break;
			case 'L': _str[v] = 'l'; break;
			case 'M': _str[v] = 'm'; break;
			case 'N': _str[v] = 'n'; break;
			case 'O': _str[v] = 'o'; break;
			case 'P': _str[v] = 'p'; break;
			case 'R': _str[v] = 'r'; break;
			case 'S': _str[v] = 's'; break;
			case 'T': _str[v] = 't'; break;
			case 'Q': _str[v] = 'q'; break;
			case 'U': _str[v] = 'u'; break;
			case 'V': _str[v] = 'v'; break;
			case 'W': _str[v] = 'w'; break;
			case 'X': _str[v] = 'x'; break;
			case 'Y': _str[v] = 'y'; break;
			case 'Z': _str[v] = 'z'; break;
			default: return false;
			};
		_splt = false;
		return true;
	};
	void up(size_t begin, size_t end) {
		for (size_t i = begin; i < end && i < _size; i++) {
			switch (_str[i]) {
			case 'a': _str[i] = 'A'; break;
			case 'b': _str[i] = 'B'; break;
			case 'c': _str[i] = 'C'; break;
			case 'd': _str[i] = 'D'; break;
			case 'e': _str[i] = 'E'; break;
			case 'f': _str[i] = 'F'; break;
			case 'g': _str[i] = 'G'; break;
			case 'h': _str[i] = 'H'; break;
			case 'i': _str[i] = 'I'; break;
			case 'j': _str[i] = 'J'; break;
			case 'k': _str[i] = 'K'; break;
			case 'l': _str[i] = 'L'; break;
			case 'm': _str[i] = 'M'; break;
			case 'n': _str[i] = 'N'; break;
			case 'o': _str[i] = 'O'; break;
			case 'p': _str[i] = 'P'; break;
			case 'r': _str[i] = 'R'; break;
			case 's': _str[i] = 'S'; break;
			case 't': _str[i] = 'T'; break;
			case 'q': _str[i] = 'Q'; break;
			case 'u': _str[i] = 'U'; break;
			case 'v': _str[i] = 'V'; break;
			case 'w': _str[i] = 'W'; break;
			case 'x': _str[i] = 'X'; break;
			case 'y': _str[i] = 'Y'; break;
			case 'z': _str[i] = 'Z'; break;
			}
		}
		_splt = false;
	};
	void low(size_t begin, size_t end) {
		for (size_t i = begin; i < end && i < _size; i++) {
			switch (_str[i]) {
			case 'A': _str[i] = 'a'; break;
			case 'B': _str[i] = 'b'; break;
			case 'C': _str[i] = 'c'; break;
			case 'D': _str[i] = 'd'; break;
			case 'E': _str[i] = 'e'; break;
			case 'F': _str[i] = 'f'; break;
			case 'G': _str[i] = 'g'; break;
			case 'H': _str[i] = 'h'; break;
			case 'I': _str[i] = 'i'; break;
			case 'J': _str[i] = 'j'; break;
			case 'K': _str[i] = 'k'; break;
			case 'L': _str[i] = 'l'; break;
			case 'M': _str[i] = 'm'; break;
			case 'N': _str[i] = 'n'; break;
			case 'O': _str[i] = 'o'; break;
			case 'P': _str[i] = 'p'; break;
			case 'R': _str[i] = 'r'; break;
			case 'S': _str[i] = 's'; break;
			case 'T': _str[i] = 't'; break;
			case 'Q': _str[i] = 'q'; break;
			case 'U': _str[i] = 'u'; break;
			case 'V': _str[i] = 'v'; break;
			case 'W': _str[i] = 'w'; break;
			case 'X': _str[i] = 'x'; break;
			case 'Y': _str[i] = 'y'; break;
			case 'Z': _str[i] = 'z'; break;
			}
		}
		_splt = false;
	};

	void fill(char v) {
		char* c = new char[_size] { 0 };
		strncpy(c, (const char*)_str, _size);
		_str = c;
	};
	void fill(const char* v) {
		clear();
		for (size_t i = 0; i < _size; i++)
			*this += v;
	};
	void fill(std::string v) {
		clear();
		for (size_t i = 0; i < _size; i++)
			*this += v;
	};
	void fill(strinx v) {
		clear();
		for (size_t i = 0; i < _size; i++)
			*this += v;
	};
	void fill(int v) {
		clear();
		strinx q = v;
		for (size_t i = 0; i < _size; i++)
			*this += q;
	};
	void fill(float v) {
		clear();
		strinx q = v;
		for (size_t i = 0; i < _size; i++)
			*this += q;
	};

	strinx filter(char _find, char  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(char _find, const char* _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(char _find, std::string _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(char _find, strinx  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(char _find, int  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(char _find, float _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};

	strinx filter(const char* _find, char  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(const char* _find, const char* _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(const char* _find, std::string _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(const char* _find, strinx  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(const char* _find, int  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(const char* _find, float _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};

	strinx filter(std::string _find, char  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(std::string _find, const char*  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(std::string _find, std::string _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(std::string _find, strinx  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(std::string _find, int  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(std::string _find, float _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};

	strinx filter(strinx _find, char  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(strinx _find, const char* _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(strinx _find, std::string _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(strinx _find, strinx  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(strinx _find, int  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(strinx _find, float _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};

	strinx filter(int _find, char  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(int _find, const char* _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(int _find, std::string _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(int _find, strinx  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(int _find, int  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(int _find, float _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};

	strinx filter(float _find, char  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(float _find, const char* _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(float _find, std::string _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(float _find, strinx  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(float _find, int  _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};
	strinx filter(float _find, float _change) const {
		strinx c = *this;
		while (c.replace(_find, _change));
		return c;
	};

	void erase(char v) { while (takeout(v)); };
	void erase(const char* v) { while (takeout(v)); };
	void erase(std::string v) { while (takeout(v)); };
	void erase(strinx v) { while (takeout(v)); };
	void erase(int v) { while (takeout(v)); };
	void erase(float v) { while (takeout(v)); };

	bool check(char v) const {
		for (size_t i = 0; i < _size; i++) {
			if (v == _str[i]) {
				return true;
			};
		};
		return false;
	};
	bool check(const char* v) const {
		 size_t s = _size - strlen(v), sl = strlen(v);
		 for (size_t i = 0; i < s; i++)
			 if (this->operator()(i, i + sl) == v)
				 return true;
		return false;
	};
	bool check(std::string v) const {
		strinx _v = v;
		const size_t s = _size - v.size(), sl = v.size();
		for (size_t i = 0; i < s; i++) {
			if (_v == this->operator()(i, i + sl))
				return true;
		}
		return false;
	};
	bool check(strinx v) const {
		const size_t s = _size - v.size(), sl = v.size();
		for (size_t i = 0; i < s; i++) {
			if (v == this->operator()(i, i + sl))
				return true;
		}
		return false;
	};
	bool check(int v) const {
		strinx _v = v;
		const size_t s = _size - _v.size(), sl = _v.size();
		for (size_t i = 0; i < s; i++) {
			if (_v == this->operator()(i, i + sl))
				return true;
		}
		return false;
	};
	bool check(float v) const {
		strinx _v = v;
		const size_t s = _size - _v.size(), sl = _v.size();
		for (size_t i = 0; i < s; i++) {
			if (_v == this->operator()(i, i + sl))
				return true;
		}
		return false;
	};

	bool remove(size_t v) {
		if (v < _size) {
			*this = this->operator()(0, v) + this->operator()(v + 1, _size);
			return true;
		}
		else
			return false;
	};
	bool remove(size_t begin, size_t end) {
		if (end < _size and end > begin) {
			*this = this->operator()(0, begin) + this->operator()(begin + end, _size);
			return true;
		}
		else
			return false;
	};

	size_t index(char v) const {
		size_t _c = 0;
		for (size_t i = 0; i < _size; i++)
			if (v == _str[i])
				_c++;
		return _c;
	};
	size_t index(const char* v) const {
		size_t _c = 0;
		strinx _v = v;
		const size_t s = _size - strlen(v), sl = strlen(v);
		for (size_t i = 0; i < s; i++)
			if (_v == this->operator()(i, i + sl))
				_c++;
		return _c;
	};
	size_t index(std::string v) const {
		size_t _c = 0;
		strinx _v = v;
		const size_t s = _size - v.size(), sl = v.size();
		for (size_t i = 0; i < s; i++)
			if (_v == this->operator()(i, i + sl))
				_c++;
		return _c;
	};
	size_t index(strinx v) const {
		size_t _c = 0;
		const size_t s = _size - v.size(), sl = v.size();
		for (size_t i = 0; i < s; i++)
			if (v == this->operator()(i, i + sl))
				_c++;
		return _c;
	};
	size_t index(int v) const {
		size_t _c = 0;
		strinx _v = v;
		const size_t s = _size - _v.size(), sl = _v.size();
		for (size_t i = 0; i < s; i++)
			if (_v == this->operator()(i, i + sl))
				_c++;
		return _c;
	};
	size_t index(float v) const {
		size_t _c = 0;
		strinx _v = v;
		const size_t s = _size - _v.size(), sl = _v.size();
		for (size_t i = 0; i < s; i++)
			if (_v == this->operator()(i, i + sl))
				_c++;
		return _c;
	};

	size_t find(char v) const {
		size_t _c = _size;
		for (size_t i = 0; i < _size; i++) {
			if (v == _str[i]) {
				_c = i;
				break;
			};
		};
		return _c;
	};
	size_t find(const char* v) const {
		size_t _c = _size;
		const size_t s = _size - strlen(v), sl = strlen(v);
		for (size_t i = 0; i < s; i++) {
			if (this->operator()(i, i + sl) == v) {
				_c = i;
				break;
			};
		}
		return _c;
	};
	size_t find(std::string v) const {
		size_t _c = _size;
		const size_t s = _size - v.size(), sl = v.size();
		for (size_t i = 0; i < s; i++) {
			if (this->operator()(i, i + sl) == v) {
				_c = i;
				break;
			};
		}
		return _c;
	};
	size_t find(strinx v) const {
		size_t _c = _size;
		const size_t s = _size - v.size(), sl = v.size();
		for (size_t i = 0; i < s; i++) {
			if (this->operator()(i, i + sl) == v) {
				_c = i;
				break;
			};
		}
		return _c;
	};
	size_t find(int v) const {
		size_t _c = _size;
		strinx _v = v;
		const size_t s = _size - _v.size(), sl = _v.size();
		for (size_t i = 0; i < s; i++) {
			if (this->operator()(i, i + sl) == _v) {
				_c = i;
				break;
			};
		}
		return _c;
	};
	size_t find(float v) const {
		size_t _c = _size;
		strinx _v = v;
		const size_t s = _size - _v.size(), sl = _v.size();
		for (size_t i = 0; i < s; i++) {
			if (this->operator()(i, i + sl) == _v) {
				_c = i;
				break;
			};
		}
		return _c;
	};

	bool takeout(char v) {
		if (check(v)) {
			const size_t _f = find(v);
			strinx c = *this;
			*this = c(0, _f);
			*this += c(_f + 1, c.size());
			_splt = false;
			return true;
		}
		else
			return false;
	};
	bool takeout(const char* v) {
		if (check(v)) {
			const size_t _f = find(v), sl = strlen(v);
			strinx c = *this;
			*this = c(0, _f);
			*this += c(_f + sl, c.size());
			_splt = false;
			return true;
		}
		else
			return false;
	};
	bool takeout(std::string v) {
		if (check(v)) {
			const size_t _f = find(v), sl = v.size();
			strinx c = *this;
			*this = c(0, _f);
			*this += c(_f + sl, c.size());
			_splt = false;
			return true;
		}
		else
			return false;
	};
	bool takeout(strinx v) {
		if (check(v)) {
			const size_t _f = find(v), sl = v.size();
			strinx c = *this;
			*this = c(0, _f);
			*this += c(_f + sl, c.size());
			_splt = false;
			return true;
		}
		else
			return false;
	};
	bool takeout(int v) {
		if (check(v)) {
			const size_t _f = find(v), sl = stx(v).size();
			strinx c = *this;
			*this = c(0, _f);
			*this += c(_f + sl, c.size());
			_splt = false;
			return true;
		}
		else
			return false;
	};
	bool takeout(float v) {
		if (check(v)) {
			const size_t _f = find(v), sl = stx(v).size();
			strinx c = *this;
			*this = c(0, _f);
			*this += c(_f + sl, c.size());
			_splt = false;
			return true;
		}
		else
			return false;
	};

	void insert(char v) {
		strinx t = *this;
		*this = v;
		*this += t;
		_splt = false;
	}
	void insert(const char* v) {
		strinx t = *this;
		*this = v;
		*this += t;
		_splt = false;
	};
	void insert(std::string v) {
		strinx t = *this;
		*this = v;
		*this += t;
		_splt = false;
	};
	void insert(strinx v) {
		strinx t = *this;
		*this = v;
		*this += t;
		_splt = false;
	};
	void insert(int v) {
		strinx t = *this;
		*this = v;
		*this += t;
		_splt = false;
	};
	void insert(float v) {
		strinx t = *this;
		*this = v;
		*this += t;
		_splt = false;
	};

	void insert(size_t j, char v) {
		strinx t = *this;
		*this = t(0, j);
		*this += v;
		*this += t(j, t.size());
		_splt = false;
	};
	void insert(size_t j, const char* v) {
		strinx t = *this;
		*this = t(0, j);
		*this += v;
		*this += t(j, t.size());
		_splt = false;
	};
	void insert(size_t j, std::string v) {
		strinx t = *this;
		*this = t(0, j);
		*this += v;
		*this += t(j, t.size());
		_splt = false;
	};
	void insert(size_t j, strinx v) {
		strinx t = *this;
		*this = t(0, j);
		*this += v;
		*this += t(j, t.size());
		_splt = false;
	};
	void insert(size_t j, int v) {
		strinx t = *this;
		*this = t(0, j);
		*this += v;
		*this += t(j, t.size());
		_splt = false;
	};
	void insert(size_t j, float v) {
		strinx t = *this;
		*this = t(0, j);
		*this += v;
		*this += t(j, t.size());
		_splt = false;
	};

	bool replace(char v, char q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(const char* v, char q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(std::string v, char q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(strinx v, char q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(int v, char q)					{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(float v, char q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(char v, const char* q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(const char* v, const char* q)	{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(std::string v, const char* q)	{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(strinx v, const char* q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(int v, const char* q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(float v, const char* q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(char v, std::string q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(const char* v, std::string q)	{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(std::string v, std::string q)	{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(strinx v, std::string q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(int v, std::string q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(float v, std::string q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(char v, strinx q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(const char* v, strinx q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(std::string v, strinx q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(strinx v, strinx q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(int v, strinx q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(float v, strinx q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(char v, int q)					{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(const char* v, int q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(std::string v, int q)			{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(strinx v, int q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(int v, int q)					{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(float v, int q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(char v, float q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(const char* v, float q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(std::string v, float q)		{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(strinx v, float q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(int v, float q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
	bool replace(float v, float q)				{ if (check(v)) { const size_t f = find(v); this->takeout(v); this->insert(f, q); return true; } else return false; };
};
typedef strinx stx;
strinx operator""stx(const char* v, size_t) { return strinx(v); };
strinx operator""stx(unsigned long long v) { return strinx(int(v)); };
std::ostream& operator<<(std::ostream& os, const strinx& v) {
	os << v.c_str();
	return os;
};
std::vector<strinx> operator""split(const char* v, size_t) {
	strinx t = v, s;
	std::vector<strinx> m;
	while (t >> s)
		m.push_back(s);
	return m;
};