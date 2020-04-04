cd disk
rm -f vdisk
cd ..
cd apps
make clean > /dev/null

make ./test1 > /dev/null
make ./test2 > /dev/null
make ./test3 > /dev/null
make ./test4 > /dev/null
make ./test5 > /dev/null
make ./test6 > /dev/null
make ./test7 > /dev/null
make ./test8 > /dev/null
make ./test9 > /dev/null
make ./test10 > /dev/null

# Test 1: Initializes vdisk and closes the file system
echo ----------------Test 1: Initialize vdisk and close LLFS----------------------
./test1
hexdump -C ../disk/vdisk
hexdump ../disk/vdisk > init_hexdump.txt

# Test 2: Adds a single directory to the root directory, and then deletes it.
# compares the hexdump of test2 with test1
echo ----------------Test 2: Add a Single Directory to Root Directory------------
./test2
hexdump ../disk/vdisk > test_hexdump.txt
echo "Diffing the hexdumps of test1 and test2."
difftext=$(diff init_hexdump.txt test_hexdump.txt)
echo $difftext
[ -z $difftext ] && echo "No diff, successfully added and removed a single directory from root directory." 

# Test 3: Adds a single file to the root directory, and then deletes it.
# compares the hexdump of test3 with test1
echo ----------------Test 3: Add a Single File to Root Directory------------------
./test3
hexdump ../disk/vdisk > test_hexdump.txt
echo "Diffing the hexdumps of test1 and test3."
difftext=$(diff init_hexdump.txt test_hexdump.txt)
echo $difftext
[ -z $difftext ] && echo "No diff, successfully added and removed a single file from root directory." 

# Test 4: Creates multiple subdirectories and then deletes all of them except for the root diretory.
# compares the hexdump of test4 with test1
echo ----------------Test 4: Add Multiple Subdirectories-------------------------
./test4
hexdump ../disk/vdisk > test_hexdump.txt
echo "Diffing the hexdumps of test1 and test4."
difftext=$(diff init_hexdump.txt test_hexdump.txt)
echo $difftext
[ -z $difftext ] && echo "No diff, successfully added and removed multiple subdirectories." 

# Test 5: Creates 2 subdirectories and adds a file and then deletes the file and subdirectories.
# compares the hexdump of test5 with test1
echo ----------------Test 5: Add a  File To Directory------------------------------
./test5
hexdump ../disk/vdisk > test_hexdump.txt
echo "Diffing the hexdumps of test1 and test5."
difftext=$(diff init_hexdump.txt test_hexdump.txt)
echo $difftext
[ -z $difftext ] && echo "No diff, successfully added and removed a file within a subdirectory, and removed subdirectories."

# Test 6: Adds a large file to a subdirectory, and then deletes the file and subdirectories.
# compares the hexdump of test6 with test1
echo ----------------Test 6: Add a Large File--------------------------------------
./test6
hexdump ../disk/vdisk > test_hexdump.txt
echo "Diffing the hexdumps of test1 and test6."
difftext=$(diff init_hexdump.txt test_hexdump.txt)
echo $difftext
[ -z $difftext ] && echo "No diff, successfully added and removed a large file within a subdirectory, and removed subdirectories."

# Test 7: Read a file to a std.out, deletes file and directories after.
# compares the hexdump of test7 with test1
echo ----------------Test 7: Read a  File-------------------------------------------
./test7
hexdump ../disk/vdisk > test_hexdump.txt
echo ------------------------------------------------------
echo "Diffing the hexdumps of test1 and test7."
difftext=$(diff init_hexdump.txt test_hexdump.txt)
echo $difftext
[ -z $difftext ] && echo "No diff, successfully added and read a file to std.out, removed file subdirectories."

# Test 8: Read a large file to a std.out, deletes file and directories after.
# compares the hexdump of test8 with test1
# compares the hexdump of largefile.txt and outputfile.txt
echo ----------------Test 8: Read Large File--------------------------------------
./test8 > outputfile.txt
cat outputfile.txt
hexdump ../disk/vdisk > test_hexdump.txt
echo ------------------------------------------------------
echo "Diffing the hexdumps of test1 and test8."
difftext=$(diff init_hexdump.txt test_hexdump.txt)
echo $difftext
[ -z $difftext ] && echo "No diff, successfully added and read a large file to std.out, removed file subdirectories."
echo ------------------------------------------------------

echo "Diffing the hexdumps of the original largefile.txt and outputfile.txt."
diff=$(diff largefile.txt outputfile.txt)
echo $diff
[ -z $diff ] && echo "No diff, largefile.txt and outputfile.txt. Retrieved identical file from LLFS."

# Test 9: Adds multiple directories/subdirectories and multiple files within different subdirectories
# compares the hexdump of test9 with test1
echo ----------------Test 9: Make Multiple Subdirectories and Add Multiple Files----
./test9
hexdump ../disk/vdisk > test_hexdump.txt
echo "Diffing the hexdumps of test1 and test9."
difftext=$(diff init_hexdump.txt test_hexdump.txt)
echo $difftext
[ -z $difftext ] && echo "No diff, successfully added and removed multiple directories and files."

# Test 10: Try to delete non-empty directory
# compares the hexdump of test10 with test1
echo ----------------Test 10: Try to delete non-empty Directory---------------------
./test10


make clean > /dev/null
