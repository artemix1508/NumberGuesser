BOREDOS_SDK ?= $(abspath build/sdk)
DESTDIR ?= $(abspath build/bin)

CC = x86_64-elf-gcc
CFLAGS = -O2 -m64 -march=x86-64 -fno-stack-protector -fno-stack-check -fno-lto -fno-pie -ffreestanding -nostdlib -static -no-pie
INCLUDES = -I$(BOREDOS_SDK)/include

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=obj/%.o)
BINARY = number-guesser.elf

all: $(BINARY)

$(BOREDOS_SDK)/lib/libc.a:
	@printf "Standalone build detected. Fetching C SDK (libc)...\n"
	@git clone https://github.com/boredos/libc.git build/libc-sdk
	@$(MAKE) -C build/libc-sdk SDK_DIR=$(BOREDOS_SDK) install
	@rm -rf build/libc-sdk

obj/%.o: src/%.c | $(BOREDOS_SDK)/lib/libc.a
	@mkdir -p obj
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BINARY): $(OBJECTS)
	x86_64-elf-ld -m elf_x86_64 -nostdlib -static -no-pie -Ttext=0x40000000 \
		--no-dynamic-linker -z text -z max-page-size=0x1000 -e _start \
		-L$(BOREDOS_SDK)/lib $(BOREDOS_SDK)/lib/crt0.o $(OBJECTS) -lc -o $@

install: $(BINARY)
	mkdir -p $(DESTDIR)/bin
	cp $(BINARY) $(DESTDIR)/bin/

clean:
	rm -rf obj $(BINARY) build