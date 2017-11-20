#include "jarg.h"

jargnode::jargnode() {
	init();
}

jargnode::jargnode(const string& name) {
	init();
	_name = name;
}

jargnode::jargnode(const jargnode& node) {
	_name = node._name;
	_sname = node._sname;
	_value = node._value;
	_brief = node._brief;
	_option = node._option;
}

jargnode& jargnode::operator=(const jargnode& node) {
	_name = node._name;
	_sname = node._sname;
	_value = node._value;
	_brief = node._brief;
	_option = node._option;
	return *this;
}

jargnode::~jargnode() {

}

void jargnode::init() {

}

const string& jargnode::name()const {
	return _name;
}

jargnode& jargnode::name(const string& s) {
	_name = s;
	return *this;
}

const string& jargnode::sname()const {
	return _sname;
}

jargnode& jargnode::sname(const string& s) {
	_sname = s;
	return *this;
}

const string& jargnode::brief()const {
	return _brief;
}

jargnode& jargnode::brief(const string& s) {
	_brief = s;
	return *this;
}

var_opt jargnode::option()const {
	return _option;
}

jargnode& jargnode::option(var_opt opt) {
	_option = opt;
	return *this;
}



jap::jap() {

}

jap::~jap() {

}

jargnode& jap::optional(const string& name) {
	_args.push_back(jargnode(name).option(var_opt::optional));
	_idx[name] = _args.size() - 1;
	return _args.back();
}

jargnode& jap::required(const string& name) {
	_args.push_back(jargnode(name).option(var_opt::required));
	_idx[name] = _args.size() - 1;
	return _args.back();
}

jargnode& jap::rest(const string& name) {
	_args.push_back(jargnode(name).option(var_opt::rest));
	_idx[name] = _args.size() - 1;
	return _args.back();
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

retcode jap::parse(int argc , char** argv) {
	retcode ret = retcode::r_ok;
	return ret;
}

const string& jap::help()const {

}


