CXX      = g++-16
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
PROBLEMS = a b c d e f g

.PHONY: help new build run

help:
	@echo "Usage:"
	@echo "  make new   CONTEST=abc400        Create contest directory (a.cpp - g.cpp)"
	@echo "  make build FILE=abc/abc400/a     Compile"
	@echo "  make run   FILE=abc/abc400/a     Compile & run"

new:
	@test -n "$(CONTEST)" || (echo "Usage: make new CONTEST=abc400"; exit 1)
	@mkdir -p abc/$(CONTEST)
	@for p in $(PROBLEMS); do cp template.cpp abc/$(CONTEST)/$$p.cpp; done
	@echo "Created abc/$(CONTEST)/"

build:
	@test -n "$(FILE)" || (echo "Usage: make build FILE=abc/abc400/a"; exit 1)
	$(CXX) $(CXXFLAGS) -o $(FILE) $(FILE).cpp

run: build
	./$(FILE)
