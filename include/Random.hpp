#include <stdlib.h>
#include <vector>

#define _XS_RANDOM_

#if defined(import_randall) or defined(import_rand_all) or defined(import_randAll)
#define import_randint
#define import_randbool
#define import_randchar
#define import_randletter
#define import_randsymbol
#define import_randfloat
#define import_randinrange
#define import_randrange
#define import_randchoice
#endif

struct {
#if !defined(Random_Capitalize)
	int randint(int begin, int end) { return (std::rand() % ((end > begin) ? (end - begin) : (begin - end))) + (end > begin) ? begin : end; };
	int randint(int end) { return std::rand() % end; };
	int randint() { return std::rand() % INT_MAX; };

	const bool randbool() { return std::rand() % 2 == 0 ? false : true; };

	const char randchar() { return char(std::rand() % 256 - 128); };
	const char randletter() { return char(randbool() ? randint(65, 91) : randint(97,123)); };
	const char randsymbol() { return char( randbool() ? randint(33, 48) : randbool() ? randint(58, 65) : randbool() ? randint(91, 97) : randint(123, 127) ); };

	float randfloat(int precision = 11) {
		float t = 0.f;
		for (int i = 0; i < precision; i++) {
			t += float(rand() % 10) / pow(10, i + 1);
		};
		return t;
	};

	int randinrange(int limit, int start = 0, int step = 1) {
		std::vector<int> l;
		for (int i = start; i < limit; i += step)
			l.push_back(i);
		return choice(l);
	};
	std::vector<int> randrange(int limit, int begin, int end) {
		std::vector<int> l;
		for (int i = 0; i < limit; i++)
			l.push_back(randint(begin, end));
		return l;
	};

	template <typename T>
	T choice(std::initializer_list<T> v) {
		std::vector<T> l = v;
		auto s = std::rand() % l.size();
		return l[s];
	};
	template <typename T>
	T choice(std::vector<T> v) {
		auto s = std::rand() % v.size();
		return v[s];
	};
#else
	int randInt(int begin, int end) { return (std::rand() % ((end > begin) ? (end - begin) : (begin - end))) + (end > begin) ? begin : end; };
	int randInt(int end) { return std::rand() % end; };
	int randInt() { return std::rand() % INT_MAX; };

	const bool randBool() { return std::rand() % 2 == 0 ? false : true; };

	const char randChar() { return char(std::rand() % 256 - 128); };
	const char randLetter() { return char(randBool() ? randInt(65, 91) : randInt(97, 123)); };
	const char randSymbol() { return char(randBool() ? randInt(33, 48) : randBool() ? randInt(58, 65) : randBool() ? randInt(91, 97) : randInt(123, 127)); };

	float randFloat(int precision = 11) {
		float t = 0.f;
		for (int i = 0; i < precision; i++) {
			t += float(rand() % 10) / pow(10, i+1);
		};
		return t;
	};

	int randInRange(int limit, int start = 0, int step = 1) {
		std::vector<int> l;
		for (int i = start; i < limit; i += step)
			l.push_back(i);
		return choice(l);
	};
	std::vector<int> randRange(int limit, int begin, int end) {
		std::vector<int> l;
		for (int i = 0; i < limit; i++)
			l.push_back(randInt(begin, end));
		return l;
	};

	template <typename T>
	T choice(std::initializer_list<T> v) {
		std::vector<T> l = v;
		auto s = std::rand() % l.size();
		return l[s];
	};
	template <typename T>
	T choice(std::vector<T> v) {
		auto s = std::rand() % v.size();
		return v[s];
	};
#endif
} random;

#if defined(import_randint)
#if !defined(Random_Capitalize)
int randint(int begin, int end) { return (std::rand() % (end - begin)) + begin; };
int randint(int end) { return std::rand() % end; };
int randint() { return std::rand() % INT_MAX; };
#else
int randInt(int begin, int end) { return (std::rand() % (end - begin)) + begin; };
int randInt(int end) { return std::rand() % end; };
int randInt() { return std::rand() % INT_MAX; };
#endif
#endif

#if defined(import_randchoice) or defined(import_rand_choice) or defined(import_randChoice)
template <typename T>
T choice(std::initializer_list<T> v) {
	std::vector<T> l = v;
	auto s = std::rand() % l.size();
	return l[s];
};
template <typename T>
T choice(std::vector<T> v) {
	auto s = std::rand() % v.size();
	return v[s];
};
#endif

#if defined(import_randbool) or defined(import_rand_bool) or defined(import_randBool)
#if !defined(Random_Capitalize)
bool randbool() { return std::rand() % 2 == 0 ? false : true; };
#else
bool randBool() { return std::rand() % 2 == 0 ? false : true; };
#endif
#endif

#if defined(import_randchar) or defined(import_rand_char) or defined(import_randChar)
#if !defined(Random_Capitalize)
char randchar() { return char(std::rand() % 256 - 128); };
#else
char randChar() { return char(std::rand() % 256 - 128); };
#endif
#endif

#if defined(import_randletter) or defined(import_rand_letter) or defined(import_randLetter)
#if !defined(Random_Capitalize)
char randletter() { return char(random.randbool() ? random.randint(65, 91) : random.randint(97, 123)); };
#else
char randLetter() { return char(random.randBool() ? random.randInt(65, 91) : random.randInt(97, 123)); };
#endif
#endif

#if defined(import_randsymbol) or defined(import_rand_symbol) or defined(import_randSymbol)
#if !defined(Random_Capitalize)
char randsymbol() { return char(random.randbool() ? random.randint(33, 48) : random.randbool() ? random.randint(58, 65) : random.randbool() ? random.randint(91, 97) : random.randint(123, 127)); };
#else
char randSymbol() { return char(random.randBool() ? random.randInt(33, 48) : random.randBool() ? random.randInt(58, 65) : random.randBool() ? random.randInt(91, 97) : random.randInt(123, 127)); };
#endif
#endif

#if defined(import_randfloat) or defined(import_rand_float) or defined(import_randFloat)
#if !defined(Random_Capitalize)
float randfloat(int precision = 11) {
	float t = 0.f;
	for (int i = 0; i < precision; i++) {
		t += float(rand() % 10) / pow(10, i + 1);
	};
	return t;
};
#else
float randFloat(int precision = 11) {
	float t = 0.f;
	for (int i = 0; i < precision; i++) {
		t += float(rand() % 10) / pow(10, i + 1);
	};
	return t;
};
#endif
#endif

#if defined(import_randinrange) or defined(import_rand_in_range) or defined(import_randInRange)
#if !defined(Random_Capitalize)
int randinrange(int limit, int start = 0, int step = 1) {
	std::vector<int> l;
	for (int i = start; i < limit; i += step)
		l.push_back(i);
	return random.choice(l);
};
#else
int randInRange(int limit, int start = 0, int step = 1) {
	std::vector<int> l;
	for (int i = start; i < limit; i += step)
		l.push_back(i);
	return random.choice(l);
};
#endif
#endif

#if defined(import_randrange) or defined(import_rand_range) or defined(import_randRange)
#if !defined(Random_Capitalize)
std::vector<int> randrange(int limit, int begin, int end) {
	std::vector<int> l;
	for (int i = 0; i < limit; i++)
		l.push_back(random.randint(begin, end));
	return l;
};
#else
std::vector<int> randRange(int limit, int begin, int end) {
	std::vector<int> l;
	for (int i = 0; i < limit; i++)
		l.push_back(random.randInt(begin, end));
	return l;
};
#endif
#endif