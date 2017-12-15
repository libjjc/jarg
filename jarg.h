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

	template<typename T> T inline strto(const string& str) { return T(); }
	template<> double inline strto<double>(const string& str) { return atof(str.c_str()); }
	template<> float inline strto<float>(const string& str) { return static_cast<float>(atof(str.c_str())); }
	template<> char inline strto<char>(const string& str) { return str.empty() ? '\0' : str[0]; }
	template<> int8_t inline strto<int8_t>(const string& str) { return  static_cast<int8_t>(atoi(str.c_str())); }
	template<> int16_t inline strto<int16_t>(const string& str) { return static_cast<int16_t>(atoi(str.c_str())); }
	template<> int32_t inline strto<int32_t>(const string& str) { return static_cast<int32_t>(atoi(str.c_str())); }
	template<> int64_t inline strto<int64_t>(const string& str) { return static_cast<int64_t>(atoi(str.c_str())); }
	template<> uint8_t inline strto<uint8_t>(const string& str) { return static_cast<uint8_t>(atoi(str.c_str())); }
	template<> uint16_t inline strto<uint16_t>(const string& str) { return static_cast<uint16_t>(atoi(str.c_str())); }
	template<> uint32_t inline strto<uint32_t>(const string& str) { return static_cast<uint32_t>(atoi(str.c_str())); }
	template<> uint64_t inline strto<uint64_t>(const string& str) { return static_cast<uint64_t>(atoi(str.c_str())); }
	template<> string inline strto<string>(const string& str) {return str;	}
	template<> bool inline strto<bool>(const string& str) {
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

	enum class argoption : int {
		key = 0,
		check = 1,
		rest = 2
	};



	class arg {
	public:
		//arg();
		arg(const string& name,const string& sname = "");
		arg(const arg& node);
		arg& operator=(const arg& node);
		~arg();
	public:
		const string& name()const;
		//arg& name(const string& s);
		const string& sname()const;
		//arg& sname(const string& s);
		const string& brief()const;
		arg& brief(const string& s);
		const string& origin()const;
		arg& origin(const string& s);

		template<typename T> arg& wait(T* t = NULL, T d = defaule_value<T>().value) {
			_type = static_cast<valtype>(typecode<T>::code);
			_wait = (void*)t;
			return *this;
		}
		void* wait()const;

		argoption option()const;
		arg& option(argoption opt);

		valtype type()const;
		arg& type(valtype vt);

	public:


	private:

		void init();

	protected:
		string _name;
		string _sname;
		string _origin;
		
		valtype _type;
		void* _wait;

		string _brief;
		argoption _option;
	};

	struct get_real_value {
		void* operator()(const string& s, valtype type, void* value);
	};

	class jap {
	public:
		jap();
		~jap();
	protected:
		jap(const jap& rhs) {}

	public:

		arg& check(const string& name,const string& sname = "");
		arg& key(const string& name,const string& sname = "");
		arg& rest(const string& name,const string& sname = "");

		bool get(const string& key);
		template<typename T>
		T get(const string& key, T v4none = default_value<T>().value);
		//template<typename T>
		//T rest(const string& key, T v4none);

	public:
		const string& selfpath()const;
		const string& brief()const;
		jap& brief(const string& s);
		const string& usage()const;
		jap& usage(const string& s);

	protected:
		retcode nameparse(int argc, char** argv, int * where);
		retcode snameparse(int argc, char** argv, int * where);
		retcode keyparse(const string& key, const string& value);
	public:
		retcode parse(int argc, char** argv);
		const string& man()const;
	private:
		typedef pair<valtype, void*> arg_t;

		string _selfpath;
		string _brief;
		string _usage;
		vector<arg> _args;
		vector<arg> _rest;

		map<string, size_t> _idx;
	};



	template<typename T>
	inline T jap::get(const string & skey, T v4none){
		if (_idx.end() == _idx.find(skey)) {
			return v4none;
		}
		arg& a = _args[_idx.at(skey)];
		if (a.origin() == "") {
			return v4none;
		}
		
		return strto<T>(a.origin());
	}

}

#endif//_C_MAIN_ARGUMENT_PARSER_H


