Aisha Farooque
PSID: 1809992
----------------------------

To run the file:
clear
ls
rm tc1.out tc2.out tc3.out tc4.out tc5.out tc6.out tc7.out tc8.out
g++ -std=c++11 gettype.cpp -o gettype
./gettype file=tc1.py > tc1.out
./gettype file=tc2.py > tc2.out
./gettype file=tc3.py > tc3.out
./gettype file=tc4.py > tc4.out
./gettype file=tc5.py > tc5.out
./gettype file=tc6.py > tc6.out
./gettype file=tc7.py > tc7.out
./gettype file=tc8.py > tc8.out
bash compareRes.sh
cat grade

----------------------------
A vector has been used to keep track of data types. 

Number of bytes for each of the variables:
Size of char: 1 byte
Size of int: 4 bytes
Size of float: 4 bytes
Size of double: 8 bytes

