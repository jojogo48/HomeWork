llc  -relocation-model=pic --filetype=obj test.ll
gcc -o test test.o
