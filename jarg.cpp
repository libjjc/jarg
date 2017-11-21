#include "jarg.h"
using namespace jarg;
arg::arg() {
	init();
}

arg::arg(const string& name) {
	init();
	_name = name;
}

arg::arg(const arg& node) {
	_name = node._name;
	_sname = node._sname;
	_value = node._value;
	_brief = node._brief;
	_type = node._type;
}

arg& arg::operator=(const arg& node) {
	_name = node._name;
	_sname = node._sname;
	_value = node._value;
	_brief = node._brief;
	_type = node._type;
	return *this;
}

arg::~arg() {

}

void arg::init() {
	_value = jargdata();
}

const string& arg::name()const {
	return _name;
}

arg& arg::name(const string& s) {
	_name = s;
	return *this;
}

const string& arg::sname()const {
	return _sname;
}

arg& arg::sname(const string& s) {
	_sname = s;
	return *this;
}

const string& arg::brief()const {
	return _brief;
}

arg& arg::brief(const string& s) {
	_brief = s;
	return *this;
}

argtype arg::type()const {
	return _type;
}

arg& arg::type(argtype opt) {
	_type = opt;
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

retcode jap::nameparse(int argc, char ** argv, int * where){

}

retcode jap::parse(int argc , char** argv) {
	retcode ret = retcode::r_ok;
	_selfpath = argv[0];
	set<size_t> spclst;
	size_t cntr = 0;
	for (int i = 1; i < argc; i++) {
		string s = argv[i];
		if (s.size() >= 2 && s.substr(0, 2) == "--") {
			if (_idx.end() == _idx.find(s.substr(2))) {
				stringstream ss;
				ss << "unkown parameter[" << s.substr(2) << "]";
				_errors.push_back(ss.str());
				return retcode::r_err;
			}
			size_t pos = s.find('=',2);
			if (string::npos == pos) {
				stringstream ss;
				ss << "incompleted parameter[" << argv[i] << "]";
				_errors.push_back(ss.str());
				return retcode::r_err;
			}
			string k = s.substr(2, pos - 2);
			string v = s.substr(pos + 1);
			size_t idx = _idx.at(k);
			if (idx >= _args.size()) {
				_errors.push_back("unkown error , parameter index out range");
				return retcode::r_err;
			}
			if (spclst.end() != spclst.find(idx)) {
				stringstream ss;
				ss << "the parameter[" << k << "] is defined , or same to ["
					<< _args[*spclst.find(idx)].name() << ","
					<< _args[*spclst.find(idx)].sname() << "]";
				_errors.push_back(ss.str());
				return retcode::r_err;
			}
			arg& node = _args[idx];
			spclst.insert(idx);
			if (var_opt::required == node.option()) {
				cntr++;
			}
			node.origin(v);
			continue;
		}
		if (s.size() >= 1 && s[0] == '-') {
			s = s.substr(1);
			if (s.empty()) {
				_errors.push_back("incompleted parameter '-' , missing name");
				return retcode::r_err;
			}
			if (s.size() == 1) {
				if (_idx.end() == _idx.find(s)) {
					arg& node = _args[_idx.at(s)];
					if( valtype::t_bool == node.value.type())
				}
			}
			continue;
		}

	}
	return ret;
}

const string& jap::help()const {
	return "";
}


