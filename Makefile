
all:
	cmake -S. -Bbuild && \
	cd build && \
	cmake --build .

test: all
	cd build && \
	ctest

clean:
	rm -rf build
	rm -rf include/json.lex.h
	rm -rf include/json.tab.h
	rm -rf src/json.lex.cc
	rm -rf src/json.tab.cc
