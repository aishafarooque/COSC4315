Aisha Farooque
PSID: 1809992
----------------------

Remove old tc#.out files:
clear
rm tc1.out tc2.out tc3.out tc4.out tc5.out

To run this file, to run the code on the Linux server, go to the file path and enter one of the following in the command line:
	python3 freqnumber.py "input=tc1.txt;k=3;output=freqnumber.txt" >> tc1.out
	python3 freqnumber.py "input=tc2.txt;k=3;output=freqnumber.txt" >> tc2.out
	python3 freqnumber.py "input=tc3.txt;k=3;output=freqnumber.txt" >> tc3.out
	python3 freqnumber.py "input=tc4.txt;k=3;output=freqnumber.txt" >> tc4.out
	python3 freqnumber.py "input=tc5.txt;k=3;output=freqnumber.txt" >> tc5.out
	python3 freqnumber.py "input=tc6.txt;k=3;output=freqnumber.txt" >> tc6.out
	python3 freqnumber.py "input=tc7.txt;k=3;output=freqnumber.txt" >> tc7.out
	python3 freqnumber.py "input=tc8.txt;k=3;output=freqnumber.txt" >> tc8.out
	python3 freqnumber.py "input=tc9.txt;k=3;output=freqnumber.txt" >> tc9.out
	python3 freqnumber.py "input=tc10.txt;k=3;output=freqnumber.txt" >> tc10.out

To view the output:
	cat tc1.out
	cat tc2.out
	cat tc3.out
	...

To compare the tc#.out and ans#.out files and see the final grade:
	bash compareRes.sh
	cat grade
----------------------

The code uses functional programming (recursion) and lists to calculate the frequency of integers and real numbers in a given file.
Lists have been used to keep track of the numbers inside the list and nested lists have been used to keep track of the number's
frequency. 