#include "print.hpp"

using namespace ftl;

int main (int argc, char const *argv[])
{
	auto str = format("A number: {0}, the same number: {0}, something else: {1}", 123, "hejsa");
	print("{0}\n", str);
	return 0;
}