CC=gcc
FLAGCS=-Wall -g
SRC=lsR.c
OUT=lsR

target:
	$(CC) $(FLAGCS) -o $(OUT) $(SRC)

install: target
	mkdir -p ./bin
	mv ./lsR ./bin

clean:
	rm -rf ./*.o

distclean: clean
	rm -rf ./bin
