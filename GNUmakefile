#CXX		= clang
CXXFLAGS       += -I. -O3 -g
all:		heapwrap_test

heapwrap_test:	heapwrap_test.C
	$(CXX) $(CXXFLAGS) -o $@ $^

test:		all FORCE
	./heapwrap_test

FORCE:
