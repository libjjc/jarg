
#include <iostream>
#include "jarg.hpp"
int main(int argc, char** argv) {
	jarg::jap jap;
	bool btest;
	int i;
	float f;
	double lf;
	char ch;
	string s;
//	jap.check("test", "t").wait<bool>(&btest, true);
//	jap.key("int", "i").wait<int>(&i, 0);
//	jap.key("float", "f").wait<float>(&f, 0.f);
//	jap.key("str", "s").wait<string>(&s, "");
//	jap.key("char", "c").wait<char>(&ch, 'a');
//	jap.parse(argc, argv);
//	std::cout << (btest ? "true" : "false") << std::endl;
//	std::cout << "int i = " << i << std::endl;
//	std::cout << "float f = " << f << std::endl;
//	//std::cout << "double lf = " << lf << std::endl;
//	std::cout << "char ch = " << ch << std::endl;
//	std::cout << "string s = " << s << std::endl;

	jap.check("test", "t").brief("this is a simple test for bool variable");
	jap.key("int", "i").brief("this is a simple test for int variable,lalala,demaxiya,oh,oh,oh,this is yes ,that is no");
	jap.key("float", "f").brief("dididididididididdididididid.");
	jap.key("str", "s").brief();
	jap.key("char", "c").brief("");
	jap.parse(argc, argv);
	
	std::cout << (jap.get("t") ? "true" : "false" )<< std::endl;
	std::cout << (jap.get("test") ? "true" : "false" )<< std::endl;

	std::cout << jap.get<int>("i") << std::endl;
	std::cout << jap.get<int>("int") << std::endl;

	std::cout << jap.get<float>("float") << std::endl;
	std::cout << jap.get<float>("f") << std::endl;

	std::cout << jap.get<string>("s") << std::endl;
	std::cout << jap.get<string>("str") << std::endl;

	std::cout << jap.get<char>("c") << std::endl;
	std::cout << jap.get<char>("char") << std::endl;
	s = jap.man();
	std::cout << jap.man() << std::endl;
	std::cerr << "this is an error message!" << std::endl;
	std::cin >> s;
	return 0;
}