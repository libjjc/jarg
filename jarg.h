#ifndef _C_MAIN_ARGUMENT_PARSER_H
#define _C_MAIN_ARGUMENT_PARSER_H

#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>

using namespace std;

namespace jarg {

	template<typename T>struct default_value { const T value = T(); };
	template<>struct default_value<double> { const double value = 0.0; };
	template<>struct default_value<float> { const float value = 0.f; };
	template<>struct default_value<char> { const char value = '\0'; };
	template<>struct default_value<bool> { const bool value = false; };
	template<>struct default_value<int8_t> { const int value = 0; };
	template<>struct default_value<int16_t> { const int16_t value = 0; };
	template<>struct default_value<int32_t> { const int32_t value = 0; };
	template<>struct default_value<int64_t> { const int64_t value = 0; };
	template<>struct default_value<uint8_t> { const uint8_t value = 0; };
	template<>struct default_value<uint16_t> { const uint16_t value = 0; };
	template<>struct default_value<uint32_t> { const uint32_t value = 0; };
	template<>struct default_value<uint64_t> { const uint64_t value = 0; };
	template<>struct default_value<string> { const string value = ""; };

	template<typename T> T strto(const string& str) { return T(); }
	template<> double strto<double>(const string& str) { return atof(str.c_str()); }
	template<> float strto<float>(const string& str) { return static_cast<float>(atof(str.c_str())); }
	template<> int strto<int>(const string& str) { return atoi(str.c_str()); }
	template<> long strto<long>(const string& str) { return atol(str.c_str()); }
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
		t_bool,
		t_char,
		t_int8,
		t_int16,
		t_int32,
		t_int64,
		t_uint8,
		t_uint16,
		t_uint32,
		t_uint64,
		t_float,
		t_double,
		t_string,
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

	//template<valtype> struct realtype { typedef bool rtype; };
	//template<> struct realtype<valtype::t_bool> { typedef bool rtype; };
	//template<> struct realtype<valtype::t_char> { typedef char rtype; };
	//template<> struct realtype<valtype::t_int8> { typedef int8_t rtype; };
	//template<> struct realtype<valtype::t_int16> { typedef int16_t rtype; };
	//template<> struct realtype<valtype::t_int32> { typedef int32_t rtype; };
	//template<> struct realtype<valtype::t_int64> { typedef int64_t rtype; };
	//template<> struct realtype<valtype::t_uint8> { typedef uint8_t rtype; };
	//template<> struct realtype<valtype::t_uint16> { typedef uint16_t rtype; };
	//template<> struct realtype<valtype::t_uint32> { typedef uint32_t rtype; };
	//template<> struct realtype<valtype::t_uint64> { typedef uint64_t rtype; };

	template<typename T> T& valref(void* pt) {
		stringstream ss;
		ss << "type = " << typeid(t).name() << " is an invalid type." << std::endl;
		throw std::invalid_argument(ss.c_str());
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


	enum class argtype : int {
		key,
		flag,
		rest
	};

	typedef struct jargdata {
		jargdata() {
			//type = valtype::t_unkown;
			//pval = NULL;
			str = "";
			memset(&dv.buf[0], 0, 16);
		}
		//valtype type;
		string str;
		//void* pval;
		union {
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
		} dv;
	}jarg_t;

	class arg {
	public:
		arg();
		explicit arg(const string& name);
		arg(const arg& node);
		arg& operator=(const arg& node);
		~arg();
	public:
		const string& name()const;
		arg& name(const string& s);
		const string& sname()const;
		arg& sname(const string& s);
		const string& brief()const;
		arg& brief(const string& s);
		const string& origin()const;
		arg& origin(const string& s);

		template<typename T> retcode wait(T* t = NULL, T d = defaule_value<T>().value) {
			_value.type = typecode<T>::code;
			_value.pval = (void*)t;
			set<T>(d);
		}

		argtype type()const;
		arg& type(argtype opt);
		template<typename T> arg& dv(const T t) {
			stringstream ss;
			ss << "type = " << typeid(t).name() << " is an invalid type." << std::endl;
			throw std::invalid_argument(ss.c_str());
		}
		template<> arg& dv<char>(const char t) { _value.dv.ch = t; return *this; }
		template<> arg& dv<bool>(const bool t) { _value.dv.b = t; return *this; }
		template<> arg& dv<int8_t>(const int8_t t) { _value.dv.i8 = t; return *this; }
		template<> arg& dv<int16_t>(const int16_t t) { _value.dv.i16 = t; return *this; }
		template<> arg& dv<int32_t>(const int32_t t) { _value.dv.i32 = t; return *this; }
		template<> arg& dv<int64_t>(const int64_t t) { _value.dv.i64 = t; return *this; }
		template<> arg& dv<uint8_t>(const uint8_t t) { _value.dv.u8 = t; return *this; }
		template<> arg& dv<uint16_t>(const uint16_t t) { _value.dv.u16 = t; return *this; }
		template<> arg& dv<uint32_t>(const uint32_t t) { _value.dv.u32 = t; return *this; }
		template<> arg& dv<uint64_t>(const uint64_t t) { _value.dv.u64 = t; return *this; }
		template<> arg& dv<float>(const float t) { _value.dv.f = t; return *this; }
		template<> arg& dv<double>(const double t) { _value.dv.lf = t; return *this; }

		template<typename T> T dv()const {
			stringstream ss;
			ss << "type = " << typeid(t).name() << " is an invalid type." << std::endl;
			throw std::invalid_argument(ss.c_str());
		}
		template<> char dv<>()const { return _value.dv.ch; }
		template<> bool dv<>()const { return _value.dv.b; }
		template<> int8_t dv<>()const { return _value.dv.i8; }
		template<> int16_t dv<>()const { return _value.dv.i16; }
		template<> int32_t dv<>()const { return _value.dv.i32; }
		template<> int64_t dv<>()const { return _value.dv.i64; }
		template<> uint8_t dv<>()const { return _value.dv.u8; }
		template<> uint16_t dv<>()const { return _value.dv.u16; }
		template<> uint32_t dv<>()const { return _value.dv.u32; }
		template<> uint64_t dv<>()const { return _value.dv.u64; }
		template<> float dv<>()const { return _value.dv.f; }
		template<> double dv<>()const { return _value.dv.lf; }

	private:

		void init();

	protected:
		string _name;
		string _sname;
		string _origin;
		jarg_t _value;
		valtype _type;
		void* _wait;
		string _brief;
		argtype _argtype;
	};

	class jap {
	public:
		jap();
		~jap();
	protected:
		jap(const jap& rhs) {}
	public:
		arg& optional(const string& name);
		arg& required(const string& name);
		arg& rest(const string& name);
	public:

		arg& flag(const string& name);
		template<typename>
		arg& key(const string& name);
		template<typename T = string>
		arg& rest(const string& name, T* t);

	public:
		const string& selfpath()const;
		const string& brief()const;
		jap& brief(const string& s);
		const string& usage()const;
		jap& usage(const string& s);

	protected:
		retcode nameparse(int argc, char** argv, int * where);
		retcode snameparse(int argc, char** argv, int * where);
		retcode restparse(int argc, char** argv, int * where);
	public:
		retcode parse(int argc, char** argv);
		const string& help()const;

	private:
		typedef pair<valtype, void*> arg_t;
		string _selfpath;
		string _brief;
		string _usage;
		vector<string> _errors;
		vector<arg> _args;
		vector<arg> _rests;

		map<string, size_t> _idx;
		//map<string, arg_t> _wait;
	};

	template<typename T>
	arg& jap::key(const string& name) {
		jarnode node = jarnode(name).type(argtype::key);
		jardata data;
		data.value.type = typecode<T>::code;
		node.value(data);
		_args.push_back(arg(name).type(argtype::key));
		_idx[name] = _args.size() - 1;
		return _args.back();
	}

	template<typename T>
	arg& jap::required(const string& name, T* t) {
		_args.push_back(arg(name).option(var_opt::required));
		_wait[name] = arg_t(typecode<T>::code, (void*)t);
		_idx[name] = _args.size() - 1;
		return _args.back();
	}

	template<typename T>
	arg& jap::rest(const string& name, T* t) {
		_args.push_back(arg(name).option(var_opt::rest));
		_wait[name] = arg_t(typecode<T>::code, (void*)t);
		_idx[name] = _args.size() - 1;
		return _args.back();
	}


}

#endif//_C_MAIN_ARGUMENT_PARSER_H


