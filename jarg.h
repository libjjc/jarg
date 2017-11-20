#ifndef _C_MAIN_ARGUMENT_PARSER_H
#define _C_MAIN_ARGUMENT_PARSER_H

#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

template<typename T>struct type_value { T value = T();};
template<>struct type_value<double> {double value = 0.0;};
template<>struct type_value<float> {float value = 0.f;};
template<>struct type_value<char> {char value = '\0';};
template<>struct type_value<bool> {bool value = false;};
template<>struct type_value<int> {int value = 0;};
template<>struct type_value<long> {long value = 0;};
template<>struct type_value<string> {string value = "";};

template<typename T> T strto(const string& str) {return T();}
template<> double strto<double>(const string& str) { return atof(str.c_str()); }
template<> float strto<float>(const string& str) {return static_cast<float>(atof(str.c_str()));}
template<> int strto<int>(const string& str) {return atoi(str.c_str());}
template<> long strto<long>(const string& str) {return atol(str.c_str());}
template<> bool strto<bool>(const string& str) { 
	return (str == "0" || str.empty() || str == "false") ? false : true; 
}

//template<typename T> string tostr<T>(T t) { stringstream ss; ss << t; return ss.str(); }


enum class retcode :int {
	r_ok = 0,
	r_err = -1	
};

enum class valtype : int {
	t_unkown = 0,
	t_bool ,
	t_char ,
	t_int8 ,
	t_int16 ,
	t_int32 ,
	t_int64 ,
	t_uint8 ,
	t_uint16 ,
	t_uint32 ,
	t_uint64 ,
	t_float ,
	t_double ,
	t_string , 
};

template<typename T>struct typecode { enum { code = valtype::t_unkown }; };
template<> struct typecode<bool> { enum { code = valtype::t_bool }; };
template<> struct typecode<char> { enum { code = valtype::t_char }; };
template<> struct typecode<int8_t> { enum { code = valtype::t_int8 }; };
template<> struct typecode<int16_t> { enum { code = valtype::t_int16 }; };
template<> struct typecode<int32_t> { enum { code = valtype::t_int32 }; };
template<> struct typecode<int64_t> { enum { code = valtype::t_int64 }; };
template<> struct typecode<uint8_t> { enum { code = valtype::t_uint8 }; };
template<> struct typecode<uint16_t> { enum { code = valtype::t_uint16 }; };
template<> struct typecode<uint32_t> { enum { code = valtype::t_uint32 }; };
template<> struct typecode<uint64_t> { enum { code = valtype::t_uint64 }; };
template<> struct typecode<float> { enum { code = valtype::t_float }; };
template<> struct typecode<double> { enum { code = valtype::t_double }; };
template<> struct typecode<string> { enum { code = valtype::t_string }; };


template<typename T> T& valref(void* pt) {
	stringstream ss;
	ss << "type = " << typeid(t).name() << " is an invalid type." << std::endl;
	throw std::invalid_argument(ss.c_str();
}

template<> bool& valref<bool>(void*pt) { return *((bool*)pt); }
template<> char& valref<char>(void*pt) { return *((char*)pt); }
template<> int8_t& valref<int8_t>(void*pt) { return *((int8_t*)pt); }
template<> int16_t& valref<int16_t>(void*pt) { return *((int16_t*)pt); }
template<> int32_t& valref<int32_t>(void*pt) { return *((int32_t*)pt); }
template<> int64_t& valref<int64_t>(void*pt) { return *((int64_t*)pt); }
template<> uint8_t& valref<uint8_t>(void*pt) { return *((uint8_t*)pt); }
template<> uint16_t& valref<uint16_t>(void*pt) { return *((uint16_t*)pt); }
template<> uint32_t& valref<uint32_t>(void*pt) { return *((uint32_t*)pt); }
template<> uint64_t& valref<uint64_t>(void*pt) { return *((uint64_t*)pt); }

enum class var_opt : int {
	optional,
	required,
	rest
};

typedef struct jargdata{
	valtype type;
	string str;
	union{
		char buf[16];
		bool b;
		char ch;
		int8_t i8;
		int16_t i16;
		int32_t i32;
		int64_t i64;
		uint8_t u8;
		uint16_t u16;
		uint32_t u32;
		uint64_t u64;
		float f;
		double lf;
	};
}jarg_t;

class jargnode {
public:
	jargnode();
	explicit jargnode(const string& name);
	jargnode(const jargnode& node);
	jargnode& operator=(const jargnode& node);
	~jargnode();
public:
	const string& name()const;
	jargnode& name(const string& s);
	const string& sname()const;
	jargnode& sname(const string& s);
	const string& brief()const;
	jargnode& brief(const string& s);
	var_opt option()const;
	jargnode& option(var_opt opt);
	template<typename T> jargnode& set(const T t){
		stringstream ss;
		ss << "type = " << typeid(t).name() << " is an invalid type." << std::endl;
		throw std::invalid_argument(ss.c_str();
	}
	template<> jargnode& set<char>(const char t) { _value.ch = t; return *this; }
	template<> jargnode& set<bool>(const bool t) { _value.b = t; return *this; }
	template<> jargnode& set<int8_t>(const int8_t t) { _value.i8 = t; return *this; }
	template<> jargnode& set<int16_t>(const int16_t t) { _value.i16 = t; return *this; }
	template<> jargnode& set<int32_t>(const int32_t t) { _value.i32 = t; return *this; }
	template<> jargnode& set<int64_t>(const int64_t t) { _value.i64 = t; return *this; }
	template<> jargnode& set<uint8_t>(const uint8_t t) { _value.u8 = t; return *this; }
	template<> jargnode& set<uint16_t>(const uint16_t t) { _value.u16 = t; return *this; }
	template<> jargnode& set<uint32_t>(const uint32_t t) { _value.u32 = t; return *this; }
	template<> jargnode& set<uint64_t>(const uint64_t t) { _value.u64 = t; return *this; }
	template<> jargnode& set<float>(const float t) { _value.f = t; return *this; }
	template<> jargnode& set<double>(const double t) { _value.lf = t; return *this; }

	template<typename T> T get()const {
		stringstream ss;
		ss << "type = " << typeid(t).name() << " is an invalid type." << std::endl;
		throw std::invalid_argument(ss.c_str();
	}
	template<> char get<>()const { return _value.ch; }
	template<> bool get<>()const { return _value.b; }
	template<> int8_t get<>()const { return _value.i8; }
	template<> int16_t get<>()const { return _value.i16; }
	template<> int32_t get<>()const { return _value.i32; }
	template<> int64_t get<>()const { return _value.i64; }
	template<> uint8_t get<>()const { return _value.u8; }
	template<> uint16_t get<>()const { return _value.u16; }
	template<> uint32_t get<>()const { return _value.u32; }
	template<> uint64_t get<>()const { return _value.u64; }
	template<> float get<>()const { return _value.f; }
	template<> double get<>()const { return _value.lf; }

private:

	void init();

protected:
	string _name;
	string _sname;
	jarg_t _value;
	string _brief;
	var_opt _option;
};

class jap {
public:
	jap();
	~jap();
protected:
	jap(const jap& rhs) {}
public:
	jargnode& optional(const string& name);
	jargnode& required(const string& name);
	jargnode& rest(const string& name);
public:
	template<typename T>
	jargnode& optional(const string& name, T* t);
	template<typename T>
	jargnode& required(const string& name, T* t);
	template<typename T>
	jargnode& rest(const string& name, T* t);

public:
	const string& selfpath()const;
	const string& brief()const;
	jap& brief(const string& s);
	const string& usage()const;
	jap& usage(const string& s);

public:
	retcode parse(int argc , char** argv);
	const string& help()const;
private:
	typedef pair<valtype, void*> arg_t;
	string _selfpath;
	string _brief;
	string _usage;
	vector<jargnode> _args;
	map<string, size_t> _idx;
	map<string, arg_t> _params;
};

template<typename T>
jargnode& optional(const string& name, T* t) {
	_args.push_back(jargnode(name).option(var_opt::));
	_args.push_back(arg_t(typecode<T>::code,(void*)t));
	_idx[name] = _args.size() - 1;
	return 
}

template<typename T>
jargnode& required(const string& name, T* t) {

}

template<typename T>
jargnode& rest(const string& name, T* t) {

}

#endif//_C_MAIN_ARGUMENT_PARSER_H


