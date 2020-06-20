----------------------------
Aisha Farooque
PSID: 1809992
----------------------------

The program will not compile and run if *.cpp is used in the command line as such:
g++ -std=c++11 *.cpp -o mypython

Instead, the proper command is: g++ -std=c++11 mypython.cpp -o mypython. 
This command is also stored inside compile_and_run.sh file.


----------------------------
To compile and calculate grade:
----------------------------
clear
g++ -std=c++11 mypython.cpp -o mypython
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
bash compareRes.sh
cat grade

----------------------------
To remove preexisting files:
----------------------------

clear
ls
rm tc1.out tc2.out tc3.out tc4.out tc5.out tc6.out tc7.out tc8.out tc9.out tc10.out tc11.out tc12.out
rm tc1.py tc2.py tc3.py tc4.py tc5.py tc6.py tc7.py tc8.py tc9.py tc10.py tc11.py 
rm ans1.out ans2.out ans3.out ans4.out ans5.out ans6.out ans7.out ans8.out ans9.out ans10.out ans11.out


----------------------------
To transfer files from local folder to the server:
----------------------------

scp tc1.py tc2.py tc3.py tc4.py tc5.py tc6.py tc7.py tc8.py tc9.py tc10.py tc11.py tc12.py cosc5256@program.cs.uh.edu:/home/y2020/spring/cs4315/1/cosc5256/hw4


scp mypython.cpp ifElseEvaluator.cpp variables.cpp functions.cpp helper.cpp structDefinition.cpp compareRes.sh compile_and_run.sh tc1.py tc2.py tc3.py tc4.py tc5.py tc6.py tc7.py tc8.py tc9.py tc10.py tc11.py tc12.py cosc5256@program.cs.uh.edu:/home/y2020/spring/cs4315/1/cosc5256/test


--END
----------------------------
