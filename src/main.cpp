// Copyright (C) 2016 Mars Saxman. All rights reserved.
// Permission is granted to use at your own risk and distribute this software
// in source and binary forms provided all source code distributions retain
// this paragraph and the above copyright notice. THIS SOFTWARE IS PROVIDED "AS
// IS" WITH NO EXPRESS OR IMPLIED WARRANTY.

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stack>

#include "lexer.h"
#include "parser.h"

using std::string;

struct readout: public ast::builder {
	virtual void emit(ast::type id, std::string text, location loc) override {
	}
	void print() {
	}
};

static int run(std::istream &i) {
	readout o;
	parser p(o);
	lexer l(p);
	char c;
	while (i.get(c)) {
		l.scan(c);
	}
	o.print();
	return 0;
}

int main(int argc, const char *argv[]) {
	if (argc <= 1 && isatty(fileno(stdin))) {
		std::cout << "$> ";
		for (std::string line; std::getline(std::cin, line);) {
			std::stringstream in(line);
			run(in);
			std::cout << std::endl << "$> ";
		}
		return EXIT_SUCCESS;
	}
	if (argc <= 1) {
		return run(std::cin);
	}
	for (int i = 1; i < argc; ++i) {
		std::ifstream file(argv[i]);
		int ret = run(file);
		if (ret) return ret;
	}
	return EXIT_SUCCESS;
}

