all: indexer testio

indexer : indexer.c
gcc -std=c99 indexer.c -o indexer -lm

testio: testio.c
gcc -std=gnu99 -o testio testio.c recordio.c -lm

clean:
rm -f indexer testio
