threads=4

all:
	mkdir -p build/
	cd build/ && \
		cmake .. && \
		make -j ${threads}

unicorn:
	mkdir -p src/unicorn/build/
	cd src/unicorn/build/ && \
		cmake .. && \
		make -j ${threads}

install-unicorn:
	cd src/unicorn/build/ && \
		make install && \
		ldconfig

uninstall-unicorn:
	cd src/unicorn/build/ && \
		make uninstall

install:
	cp build/binmulator /usr/bin/

uninstall:
	rm -f /usr/bin/binmulator

clean-unicorn:
	rm -rf src/unicorn/build/
