#ifndef XS_UTILITY
#define XS_UTILITY 0
template <typename T1, typename T2>
struct pair {
	T1 first;
	T2 second;
};
#include <utility>
#include <string>
using std::string;
using std::to_string;
using std::wstring;
#include <iostream>
using std::cout;
#include <sstream>
#include <fstream>
#include <array>
using std::array;
#include <deque>
#include <bitset>
#include <tuple>
using std::tuple;
#include <typeinfo>
//#include <format>
#include <algorithm>
#include <execution>
#include <concepts>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <memory>
#include <iomanip>
using namespace std::string_literals;
template <class T> concept container_t = requires(T a) {
	{ a.begin() } -> std::convertible_to<typename T::iterator>;
	{ a.end() } -> std::convertible_to<typename T::iterator>;
};
#define hash_sign #
#define rep(i, count, num) for (decltype(count) i = 0; i < count; i += num)
#define once(v)   for (static boolean v = True; v; v = False)
#define Once(body) {static const auto& Once = [&]() { body; return nullptr; }(); }
#define pass {}
#define namestr(x) #x
#define newln std::cout<<'\n';
#define self (*this)
#define var auto&
#define let auto
#define ref &
#define elif else if
#define lambda [&]
#define fn auto
#define pub public:
#define priv private:
#define then {
#define end }
#define is ==
#define in :
#define global ::
#define set =
#define ret return
#define to ->
#define typeof decltype
#define null NULL
#define none NULL
#define None NULL
#define new_v(v) (new typeof(v)(v))
#define copyof(v) (*(new_v(v)))
#define self_t typeof(self)
#define echo std::cout<<
#define puts std::cout<<
#define if_else(condition,if,else) ((condition)?(if):(else))
#define when switch
#define alias using
#define del delete
#define op operator
#define True true
#define False false
#define temp template
#define comment(v)
#define $ /##/
//#define meta(m) static const auto& _meta = [&]() { m; return true; }();
#define clambda(fn_body,...) struct { fn operator()(__VA_ARGS__){fn_body;}}
#define dotspace(_name,body) struct { body } _name;
//#define def(func_name,...) hash_sign define func_name(__VA_ARGS__)
alias real = float;
#ifndef _XSLIB2_
alias boolean = bool;
#endif
alias bit = bool;
alias str = std::string;
alias wstr = std::wstring;
alias integer = int;
alias uint = unsigned int;
alias i8 = std::int8_t;
alias i16 = std::int16_t;
alias i32 = std::int32_t;
alias i64 = std::int64_t;
alias u8 = std::uint8_t;
alias u16 = std::uint16_t;
alias u32 = std::uint32_t;
alias u64 = std::uint64_t;
alias f32 = float;
alias f64 = double;
inline static const float& pi = 3.14159265359f;
temp <typename T> alias linked_list = std::list<T>;
temp <typename T> alias list = std::pmr::vector<T>;
#undef end
template <typename Key, typename Value>
struct dict_pair {
	Key key;
	Value value;
};
template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const dict_pair<Key, Value>& v) { return (os << v.key << ":" << v.value); };
template <typename Key, typename Value>
class _Dict : public list<dict_pair<Key, Value>> {
public:
	using Self_t = list<dict_pair<Key, Value>>;
	using Self_t::vector;
	using Self_t::vector::push_back;
	inline Value& push_back(const Key& key, const Value& value) {
		Self_t::push_back({ key,value });
		return Self_t::back().value;
	};
	inline auto find(const Key& key) { return std::find_if(Self_t::begin(), Self_t::end(), [&](const dict_pair<Key, Value>& i) -> bool { return i.key == key; }); };
	inline Value& operator[](const Key& key) { return find(key)->value; };
	inline void remove(const Key& key) { Self_t::erase(find(key)); };
};
template <typename T> std::ostream& operator<<(std::ostream& os, const ::list<T>& v) {
	const char& beg_char = '[', end_char = ']';
	if (not v.empty()) {
		const str& sep = ", ";
		os << beg_char;
		const auto& e = v.end() - 1;
		for (auto b = v.begin(); b != e; b++) os << *b << sep;
		os << *v.rbegin() << end_char;
	}
	else os << beg_char << ' ' << end_char;
	return os;
};
#define end }
temp <typename T> alias dict = _Dict<string, T>;
temp <typename Return_t, typename ...Args> alias func_ptr = Return_t(*)(Args...);
typedef void* ptr;
namespace std then
	inline int  atoi(boolean ref v) then ret v ? 1 : 0; end;
	inline real atof(boolean ref v) then ret v ? 1.f : 0.f; end;
	inline boolean atob(const str ref v) then ret (v is "1" or v is "true" or v is "True") ? True : False; end;
end;
temp <typename ...Args_t>
inline fn print(Args_t&&... args) then
	(std::cout << ... << args) << '\n';
end;
static const char alphabet[26]{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
static const char ALPHABET[26]{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
static inline auto randf() { return ((float)std::rand() / (float)RAND_MAX); };
#ifndef _XS_VEX2_
temp <typename T> T sto(const std::string&);
temp <> inline int sto<int>(const std::string& _str) { return std::stoi(_str); };
temp <> inline real sto<real>(const std::string& _str) { return std::stof(_str); };
temp <> inline double sto<double>(const std::string& _str) { return std::stod(_str); };
temp <> inline long double sto<long double>(const std::string& _str) { return std::stold(_str); };
temp <> inline unsigned sto<unsigned>(const std::string& _str) { return (unsigned)std::stoi(_str); };
temp <> inline long sto<long>(const std::string& _str) { return std::stol(_str); };
temp <> inline long long sto<long long>(const std::string& _str) { return std::stoll(_str); };
temp <> inline unsigned long long sto<unsigned long long>(const std::string& _str) { return std::stoull(_str); };
#endif
enum class _Color then
	Black = 0x0,
	DarkBlue = 0x1,
	DarkGreen = 0x2,
	DarkCyan = 0x3,
	DarkRed = 0x4,
	DarkMagenta = 0x5,
	DarkYellow = 0x6,
	Grey = 0x7,
	DarkGrey = 0x8,
	Blue = 0x9,
	Green = 0xA,
	Cyan = 0xB,
	Red = 0xC,
	Purple = 0xD,
	Yellow = 0xE,
	White = 0xF
end;
#endif
/*
temp <typename T> class smart : public std::unique_ptr<T> then
	priv alias base = std::unique_ptr<T>;
	pub alias base::unique_ptr;
	priv alias base::op =;
	pub smart() = default;
	pub smart(const smart<T>&) : ;
	pub smart(smart<T>&&) = default;
	pub inline smart(T v) : base::unique_ptr(std::make_unique(v)) pass;
	pub inline fn operator =(const smart<T>& v) then
		*self = *v;
		return self;
	end;
	//pub inline auto& operator =(T v) : base::unique_ptr(v) { return self; };
	pub inline op T() const { return *self; };
	pub inline op T*() const { return &*self; };
	pub inline op T*() { return &*self; };
end;
#define int smart<int>
*/