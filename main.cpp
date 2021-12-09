#include "parser.hpp"

using namespace std;

void run(istream& input, ostream& output){
    string s = "";
    float x = 0;
    getline(input, s);
    input >> x;
    Parser parser(s);
    auto f = parser.make_f();
    output << f->calculate(x);
    return;
}

int main(int argc, char* argv[])
{
	// // f = 24 - (30 - x)
	// auto a = std::make_unique<Scalar>(24);
	// auto b = std::make_unique<Scalar>(30);
	// auto x = std::make_unique<X>();

	// auto brackets = std::make_unique<SubtractionOperator>(std::move(b), std::move(x));
	// SubtractionOperator f{std::move(a), std::move(brackets)};

	// std::cout << f.calculate(5.f) << std::endl;

	run(cin, cout);
	return 0;
}