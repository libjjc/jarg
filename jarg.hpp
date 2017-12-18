#ifndef _C_MAIN_ARGUMENT_PARSER_H
#define _C_MAIN_ARGUMENT_PARSER_H

#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>

using namespace std;

namespace jarg {
	/**
	 * default_value ,default value for types
	 */
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

	/**
	 * strto<T>(str),convert string to types
	 */
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

	/**
	 * return code , r_ok is success , r_err is error.
	 */
	enum class retcode :int {
		r_ok = 0,
		r_err = -1
	};

	/**
	 * enum for types,int ,char ,short ,long ,float,etc.
	 */
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

	/**
	 * template for typecode from types.
	 */
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

	/**
	 * argument type
	 * @key
	 *		key-value argument.eg. --config=/usr/local/app/app.cfg ,it must be pair
	 * @check
	 *		bool argument , it is true while this argument specialed.eg. tar -cvzf
	 * @special
	 *		it is required argument, it always be input argument , eg. cp [src] [dst]
	 * @rest
	 *		it is the last arguments, it is not used
	 */
	enum class argoption : int {
		key = 0,
		check = 1,
		special = 2,
		rest = 3
	};

	
	/**
	 * get real value from string with type,actualy strto<T>(str)
	 */
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
		class arg {
		public:
			arg(const string& name, const string& sname = "");
			arg(const arg& node);
			arg& operator=(const arg& node);
			~arg();
		public:
			friend class jap;
			/**
			 * get argument name
			 */
			const string& name()const;
			/**
			 * get argument short name
			 */
			const string& sname()const;
			/**
			 * get/set argument brief
			 */
			const string& brief()const;
			arg& brief(const string& s);
			/**
			 * get/set argument origin
			 */
			const string& origin()const;
			arg& origin(const string& s);
			/**
			 * wait value , it will assign value to this address while parsing this argument.
			 */
			template<typename T> arg& wait(T* t = NULL, T d = defaule_value<T>().value) {
				_type = static_cast<valtype>(typecode<T>::code);
				_wait = (void*)t;
				return *this;
			}
			/**
			 * get wait address
			 */
			void* wait()const;
		private:
			void init();
		private:
			valtype type()const;
			arg& type(valtype vt);
			argoption option()const;
			arg& option(argoption opt);
		protected:
			string _name;
			string _sname;
			string _origin;
			valtype _type;
			void* _wait;
			string _brief;
			argoption _option;
		};
	public:
		/**
		 * make a check-type argument
		 */
		arg& check(const string& name,const string& sname = "");
		/**
		 * make a key-type argument
		 */
		arg& key(const string& name,const string& sname = "");
		/**
		 * make a special-type argument
		 */
		arg& special(const string& name, const string& sname = "");
	public:
		/**
		 * get check-type argument value
		 */
		bool get(const string& key);
		/**
		 * get check/special argument value
		 */
		template<typename T>
		T get(const string& key, T v4none = default_value<T>().value);
		/**
		 * get rest arguments
		 */
		const vector<string>& rest()const { return _rest; }
		/**
		 * get rest arguments , convert rests into type
		 */
		template<typename T>
		vector<T> rest()const;
	public:
		/**
		 * get app path
		 */
		const string& selfpath()const;
		/**
		 * get/set app brief,it used for descript app
		 */
		const string& brief()const;
		jap& brief(const string& s);
		/**
		 * get/set app brief,it used for descript usage of app
		 */
		const string& usage()const;
		jap& usage(const string& s);

	protected:
		retcode nameparse(int argc, char** argv, int * where);
		retcode snameparse(int argc, char** argv, int * where);
		retcode keyparse(const string& key, const string& value);
	public:
		retcode parse(int argc, char** argv);
		const string man()const;
	private:
		typedef pair<valtype, void*> arg_t;
		string _name;
		string _selfpath;
		string _brief;
		string _usage;
		vector<arg> _args;
		vector<string> _rest;
		map<string, size_t> _idx;
		vector<size_t> _spcidx;
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

	template<typename T>
	inline vector<T> jap::rest()const {
		vector<T> result;
		for (auto r : _rest) {
			result.push_back(strto<T>(r));
		}
		return result;
	}

	jap::arg::arg(const string& name, const string& sname) {
		init();
		_name = name;
		_sname = sname;
		_brief = "";
		_wait = NULL;
		_type = valtype::t_unkown;
		_option = argoption::rest;
	}

	jap::arg::arg(const arg& node) {
		_name = node._name;
		_sname = node._sname;
		_brief = node._brief;
		_wait = node._wait;
		_type = node._type;
		_option = node._option;
	}

	jap::arg& jap::arg::operator=(const arg& node) {
		_name = node._name;
		_sname = node._sname;
		_brief = node._brief;
		_wait = node._wait;
		_type = node._type;
		_option = node._option;
		return *this;
	}

	jap::arg::~arg() {

	}

	void jap::arg::init() {
		_wait = NULL;
	}

	const string& jap::arg::name()const {
		return _name;
	}


	const string& jap::arg::sname()const {
		return _sname;
	}



	const string& jap::arg::brief()const {
		return _brief;
	}

	jap::arg& jap::arg::brief(const string& s) {
		_brief = s;
		return *this;
	}

	const string & jarg::jap::arg::origin() const {
		return _origin;
	}

	jap::arg & jarg::jap::arg::origin(const string & s) {
		_origin = s;
		get_real_value grv;
		grv(_origin, _type, _wait);
		return *this;
	}

	void * jarg::jap::arg::wait() const {
		return _wait;
	}

	argoption jap::arg::option()const {
		return _option;
	}

	jap::arg& jap::arg::option(argoption opt) {
		_option = opt;
		return *this;
	}

	valtype jarg::jap::arg::type()const {
		return _type;
	}

	jap::arg& jarg::jap::arg::type(valtype vt) {
		_type = vt;
		return *this;
	}

	jap::jap() {
	}

	jap::~jap() {
	}

	const string & jap::selfpath() const {
		return _selfpath;
	}

	const string& jap::brief()const {
		return _brief;
	}

	jap& jap::brief(const string& s) {
		_brief = s;
		return *this;
	}

	const string& jap::usage()const {
		return _usage;
	}

	jap& jap::usage(const string& s) {
		_usage = s;
		return *this;
	}
	jap::arg& jap::check(const string& name, const string& sname) {
		if (_idx.end() != _idx.find(name) || _idx.end() != _idx.find(sname)) {
			stringstream ss;
			ss << "parameter name=" << name << " , or sname=" << sname << " already defined before.";
			throw std::invalid_argument(ss.str().c_str());
		}
		arg a(name, sname);
		a.type(valtype::t_bool);
		a.option(argoption::check);
		_args.push_back(a);
		_idx[name] = _args.size() - 1;
		_idx[sname] = _args.size() - 1;
		return _args.back();
	}

	jap::arg& jap::key(const string& name, const string& sname) {
		if (_idx.end() != _idx.find(name) || _idx.end() != _idx.find(sname)) {
			stringstream ss;
			ss << "parameter name=" << name << " , or sname=" << sname << " already defined before.";
			throw std::invalid_argument(ss.str().c_str());
		}
		arg a(name, sname);
		a.option(argoption::key);
		_args.push_back(a);
		_idx[name] = _args.size() - 1;
		_idx[sname] = _args.size() - 1;
		return _args.back();
	}

	jap::arg& jap::special(const string& name, const string& sname) {
		if (_idx.end() != _idx.find(name) || _idx.end() != _idx.find(sname)) {
			stringstream ss;
			ss << "parameter name=" << name << " , or sname=" << sname << " already defined before.";
			throw std::invalid_argument(ss.str().c_str());
		}
		arg a(name, sname);
		a.option(argoption::special);
		_args.push_back(a);
		_spcidx.push_back(_args.size());
		return _args.back();
	}

	bool jarg::jap::get(const string & key) {
		if (_idx.end() == _idx.find(key)) {
			return false;
		}
		arg& a = _args[_idx.at(key)];
		if (a.origin() == "" || a.origin() == "false" || a.origin() == "0") {
			return false;
		}
		return true;
	}

	retcode jap::nameparse(int argc, char** argv, int* where) {
		if (*where >= argc) {
			std::cerr << "the \"where\"=" << where << " is over the lengeh of arguments." << std::endl;
			return retcode::r_err;
		}
		string s = argv[*where];
		s = s.substr(2);

		size_t i = s.find('=');
		string k = s;
		string v = "";
		if (string::npos != i) {
			k = s.substr(0, i);
			v = s.substr(i + 1);
		}

		if (_idx.end() == _idx.find(k)) {
			std::cerr << "unknown parameter [" << k << "]" << std::endl;
			return retcode::r_err;
		}
		return keyparse(k, v);
	}

	retcode jap::snameparse(int argc, char** argv, int* where) {
		if (*where >= argc) {
			std::cerr << "the \"where\"=" << where << " is over the lengeh of arguments." << std::endl;
			return retcode::r_err;
		}
		string s = argv[*where];
		s = s.substr(1);

		if (s.size() > 1) {
			retcode ret = retcode::r_ok;
			for (auto ch : s) {
				if (_idx.end() == _idx.find(string(1, ch))) {
					std::cerr << "unknown parameter [" << ch << "]" << std::endl;
					return retcode::r_err;
				}
				if (retcode::r_err == (ret = keyparse(string(1, ch), ""))) {
					std::cerr << "key parameter error while parsing charater:" << ch << std::endl;
					return ret;
				}
			}
		}
		else if (s.size() == 1) {
			if (_idx.end() == _idx.find(s)) {
				std::cerr << "unknown parameter [" << s << "]" << std::endl;
				return retcode::r_err;
			}
			jap::arg& a = _args[_idx.at(s)];
			string k = s;
			string v = "";
			if (a.option() == argoption::check) {
				v = "true";
			}
			else if ((*where) < argc - 1 && a.option() == argoption::key) {
				(*where)++;
				v = argv[*where];
			}
			return keyparse(k, v);
		}

		return retcode::r_err;
	}

	retcode jap::keyparse(const string& k, const string& v) {
		arg& a = _args[_idx.at(k)].origin(v);
		return retcode::r_ok;
	}

	retcode jap::parse(int argc, char** argv) {
		retcode ret = retcode::r_ok;
		_selfpath = argv[0];
		size_t pos = 0;
		while (string::npos != (pos = _selfpath.find('\\', pos))) {
			_selfpath[pos] = '/';
		}
		if (string::npos != pos) {
			_name = _selfpath.substr(pos + 1);
		}
		set<size_t> spclst;
		size_t cntr = 0;
		int i = 1;
		for (; i < argc; i++) {
			string a = argv[i];
			if (a.size() > 2 && a.substr(0, 2) == "--") {
				if (retcode::r_err == (ret = nameparse(argc, argv, &i))) {
					break;
				}
			}
			else if (a.size() > 1 && a[0] == '-') {
				if (retcode::r_err == (ret = snameparse(argc, argv, &i))) {
					break;
				}
			}
			else break;
			if (a == "--help" || "-h" == a) {
				std::cout << man() << std::endl;
				break;
			}
		}
		for (auto spc : _spcidx) {
			if (spc >= _args.size()) {
				ret = retcode::r_err;
				std::cerr << "error: special index over the size of arguments ,while index = " << spc << " size = " << _args.size() << std::endl;
				break;
			}
			arg& a = _args[spc];
			if (i >= argc) {
				ret = retcode::r_err;
				std::cerr << "invalid argument : missing special parameter [" << a.name() << "]" << std::endl;
				break;
			}
			a.origin(argv[i]);
			i++;
		}
		for (; i < argc; i++) {
			_rest.push_back(argv[i]);
		}
		return ret;
	}

	const string jap::man()const {
		stringstream ss;
		ss << _name << std::endl;
		if (_usage != "") {
			ss << "\tusage:" << std::endl << "\t\t" << _usage << std::endl;
		}
		if ("" != _brief) {
			ss << "\tbrief:" << std::endl << "\t\t" << _brief << std::endl;
		}
		for (auto a : _args) {
			ss << "\t--" << a.name();
			if (a.sname() != "") {
				ss << " , -" << a.sname();
				if ("" != a.brief()) {
					ss << std::endl << "\t\t" << a.brief() << std::endl;
				}
			}
		}
		return ss.str();
	}

	void * jarg::get_real_value::operator()(const string & s, valtype type, void * value) {
		if (NULL == value) {
			return value;
		}
		switch (type) {
		case valtype::t_bool:
			*(bool*)value = !s.empty();
			break;
		case valtype::t_char:
			*(char*)value = s.empty() ? '\0' : s[0];
			break;
		case valtype::t_int8:
			*(int8_t*)value = static_cast<int8_t>(atoi(s.c_str()));
			break;
		case valtype::t_int16:
			*(int16_t*)value = static_cast<int16_t>(atoi(s.c_str()));
			break;
		case valtype::t_int32:
			*(int32_t*)value = static_cast<int32_t>(atoi(s.c_str()));
			break;
		case valtype::t_int64:
			*(int64_t*)value = static_cast<int64_t>(atoi(s.c_str()));
			break;
		case valtype::t_uint8:
			*(uint8_t*)value = static_cast<uint8_t>(atoi(s.c_str()));
			break;
		case valtype::t_uint16:
			*(uint16_t*)value = static_cast<uint8_t>(atoi(s.c_str()));
			break;
		case valtype::t_uint32:
			*(uint32_t*)value = static_cast<uint8_t>(atoi(s.c_str()));
			break;
		case valtype::t_uint64:
			*(uint64_t*)value = static_cast<uint8_t>(atoi(s.c_str()));
			break;
		case valtype::t_float:
			*(float*)value = static_cast<float>(atof(s.c_str()));
			break;
		case valtype::t_double:
			*(double*)value = atof(s.c_str());
			break;
		case valtype::t_string:
			*(string*)value = s;
			break;
		default:
			break;
		}
		return value;
	}
}

#endif//_C_MAIN_ARGUMENT_PARSER_H


