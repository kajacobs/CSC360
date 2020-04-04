cd disk
rm -f vdisk
cd ..
cd apps
make clean > /dev/null

make ./test > /dev/null
make ./format > /dev/null
make ./testlists > /dev/null
make ./testdir > /dev/null
make ./testfiles > /dev/null
make ./addfile > /dev/null
make ./removefile > /dev/null
make ./testargs > /dev/null

# For testing add and remove files
#./addfile
#hexdump -C ../disk/vdisk
#./removefile
#hexdump -C ../disk/vdisk

./testargs
