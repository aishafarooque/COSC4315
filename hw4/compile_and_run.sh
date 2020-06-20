clear
rm mypython grade
g++ -std=c++11 mypython.cpp -o mypython
# rm tc1.out tc2.out tc3.out tc4.out tc5.out tc6.out tc7.out tc8.out tc9.out tc10.out tc11.out tc12.out
./mypython tc1.py > tc1.out
./mypython tc2.py > tc2.out
./mypython tc3.py > tc3.out
./mypython tc4.py > tc4.out
./mypython tc5.py > tc5.out
./mypython tc6.py > tc6.out
./mypython tc7.py > tc7.out
./mypython tc8.py > tc8.out
./mypython tc9.py > tc9.out
./mypython tc10.py > tc10.out
./mypython tc11.py > tc11.out 
./mypython tc12.py > tc12.out 
./mypython tc13.py > tc13.out 
./mypython tc14.py > tc14.out 
./mypython tc15.py > tc15.out 
./mypython tc16.py > tc16.out 
./mypython tc17.py > tc17.out 
./mypython tc18.py > tc18.out 
./mypython tc19.py > tc19.out 
./mypython tc20.py > tc20.out 
./mypython tc21.py > tc21.out 	
./mypython tc22.py > tc22.out 	
bash compareRes.sh
cat grade
cat tc7.out