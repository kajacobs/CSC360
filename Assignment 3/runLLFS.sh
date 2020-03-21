cd apps
make clean > /dev/null

make ./test > /dev/null
make ./format > /dev/null

./format
hexdump -C ../disk/vdisk
