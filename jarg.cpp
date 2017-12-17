#include "jarg.h"
#include <iostream>
using namespace jarg;
arg::arg(const string& name,const string& sname) {
	init();
	_name = name;
	_sname = sname;
	_brief = "";
	_wait = NULL;
	_type = valtype::t_unkown;
	_option = argoption::rest;
}

arg::arg(const arg& node) {
	_name = node._name;
	_sname = node._sname;
	_brief = node._brief;
	_wait = node._wait;
	_type = node._type;
	_option = node._option;
}

arg& arg::operator=(const arg& node) {
	_name = node._name;
	_sname = node._sname;
	_brief = node._brief;
	_wait = node._wait;
	_type = node._type;
	_option = node._option;
	return *this;
}

arg::~arg() {

}

void arg::init() {
	_wait = NULL;
}

const string& arg::name()const {
	return _name;
}


const string& arg::sname()const {
	return _sname;
}



const string& arg::brief()const {
	return _brief;
}

arg& arg::brief(const string& s) {
	_brief = s;
	return *this;
}

const string & jarg::arg::origin() const{
	return _origin;
}

arg & jarg::arg::origin(const string & s){
	_origin = s;
	get_real_value grv;
	grv(_origin, _type, _wait);
	return *this;
}

void * jarg::arg::wait() const{
	return _wait;
}

argoption arg::option()const {
	return _option;
}

arg& arg::option(argoption opt) {
	_option = opt;
	return *this;
}

valtype arg::type()const {
	return _type;
}

arg& arg::type(valtype vt) {
	_type = vt;
	return *this;
}


jap::jap() {

}

jap::~jap() {

}


const string & jap::selfpath() const{
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
arg& jap::check(const string& name, const string& sname) {
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

arg& jap::key(const string& name, const string& sname) {
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

arg& jap::rest(const string& name, const string& sname) {
	if (_idx.end() != _idx.find(name) || _idx.end() != _idx.find(sname)) {
		stringstream ss;
		ss << "parameter name=" << name << " , or sname=" << sname << " already defined before.";
		throw std::invalid_argument(ss.str().c_str());
	}
	arg a(name, sname);
	a.option(argoption::rest);
	_rest.push_back(a);
	return _args.back();
}

bool jarg::jap::get(const string & key){
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
	//_args[_idx.at(k)].origin(k);
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
				std::cerr << "key parameter error while parsing charater:"<<ch << std::endl;
				return ret;
			}
		}
	}
	else if(s.size() == 1){
		if (_idx.end() == _idx.find(s)) {
			std::cerr << "unknown parameter [" << s << "]" << std::endl;
			return retcode::r_err;
		}
		arg& a = _args[_idx.at(s)];
		string k = s;
		string v = "";
		if (a.option() == argoption::check) {
			v = "true";
		}
		else if ((*where) < argc-1 && a.option() == argoption::key) {
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

retcode jap::parse(int argc , char** argv) {
	retcode ret = retcode::r_ok;
	_selfpath = argv[0];
	_name = _selfpath.substr(_selfpath.find_last_of('\\')+1);
	set<size_t> spclst;
	size_t cntr = 0;
	
	for (int i = 1; i < argc; i++) {
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
		if (a == "--help" || "-h" == a) {
			std::cout << man() << std::endl;
			break;
		}
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
		}
		ss << std::endl << "\t\t" << a.brief() << std::endl;
	}
	return ss.str();
}

void * jarg::get_real_value::operator()(const string & s, valtype type, void * value){
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
