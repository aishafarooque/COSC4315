Name: Aisha Farooque
PSID: 1809992
--------

How to run the code:
To run the code on the Linux server, go to the file path and enter one of the following in the command line:

	python3 infint.py "input=tc1.txt;" >> tc1.out
	python3 infint.py "input=tc2.txt;" >> tc2.out
	python3 infint.py "input=tc3.txt;" >> tc3.out
	python3 infint.py "input=tc4.txt;" >> tc4.out
	python3 infint.py "input=tc5.txt;" >> tc5.out
	python3 infint.py "input=tc6.txt;" >> tc6.out
	python3 infint.py "input=tc7.txt;" >> tc7.out
	python3 infint.py "input=tc8.txt;" >> tc8.out
	python3 infint.py "input=tc9.txt;" >> tc9.out
	python3 infint.py "input=tc10.txt;" >> tc10.out

To view the output:
	cat tc1.out
	cat tc2.out
	cat tc3.out
	...

To compare the tc#.out and ans#.out files and see the final grade:
	bash compareRes.sh
	cat grade

Explanation for the algorithm: 

	-- This is an iterative solution. I have used loops and two stacks to perform the operations -- 

	Python's built in additional and multiplication operators can only handle digits that are less than or equal to 40 digits. My algorithm can perform calculations on "infinite" digit length numbers by using Python's list data structures. The program first reads each line one at a time and stores them into integers bigger_digit and smaller_digit. The integers from these variables are then seperated by each digit into first and second list.

	Then, before sending the numbers to the respective function, we check for missing numbers, empty lines, and numbers that are equal to or more than 40 digits.

	After passing these checks, the numbers are sent to the addition and multiplication function, respectively, where they are added without using the built-in sum function. I have made my own addition algorithm. 

	Before re-testing the program, make sure to clear the previous tc#.out files as the new result will only to added to the old file. 

-------- 
