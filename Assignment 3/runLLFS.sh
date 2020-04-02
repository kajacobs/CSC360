cd disk
rm -f vdisk
cd ..
cd apps
make clean > /dev/null

make ./test > /dev/null
make ./format > /dev/null
make ./testlists > /dev/null
make ./testdir > /dev/null

./testdir
hexdump -C ../disk/vdisk
