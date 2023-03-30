
all:
	cmake -S. -Bbuild && \
	cd build && \
	cmake --build .

test: all
	cd build && \
	ctest

clean:
	rm -rf build