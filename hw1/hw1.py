# Name: Aisha Farooque
# PSID: 1809992

import re, sys

# Code credit goes to cji from stackoverflow.com
def find_between( s, first, last ):
    try:
        start = s.index( first ) + len( first )
        end = s.index( last, start )
        if (s[start:end] == ""):
        	return -999
        return int(s[start:end])
    except ValueError:
        return 0

def is_balanced (str):
	counter = 0
	for c in str:
		if (c == '('):
			counter+=1
		if (c == ')'):
			counter-=1

	if (counter == 0):
		# The string is balanced
		return True
	else:
		# The string is unbalanced
		return False

def find_file_name( s, first, last ):
    try:
        start = s.index( first ) + len( first )
        end = s.index( last, start )
        return s[start:end]
    except ValueError:
        return -1

def find_bigger_number (first, second):
	if (first > second): return first
	else: return second

def find_smaller_number (first, second):
	if (first < second): return first
	else: return second

def check_digit_length (first):
	num_to_check = str(first)
	if (len(num_to_check) >= 40):
		return False
	return True

def addition (first, second, list_one, list_two):
	bigger_digit = find_bigger_number(first,second)
	len_of_bigger_digit = len(str(bigger_digit))-1

	smaller_digit = find_smaller_number(first,second)
	len_of_smaller_digit = len(str(smaller_digit))-1

	# Use of lists to handle exceptionally large numbers
	first_list = list(map(int, str(bigger_digit)))
	second_list = list(map(int, str(smaller_digit)))

	carry_over = 0
	sum_of_numbers = 0
	sum_without_carryover = 0		
	tenth_power = 10

	# Making the length of two lists even
	if (len_of_bigger_digit != len_of_smaller_digit):
		# print ("Fixing length of smaller digit")
		number_of_zeros = len_of_bigger_digit - len_of_smaller_digit
		for i in range(0, number_of_zeros):
			second_list.insert(0,0)
		len_of_smaller_digit = len_of_bigger_digit
		# print (second_list)


	# Iterative addition loop
	for i in reversed(range(0, len_of_smaller_digit+1)): 		# Starting from the last digit
		sum_without_carryover = first_list[i] + second_list[i] + carry_over		

		# Removing the first digit from a carried over sum
		if (i != 0):
			if (sum_without_carryover > 9):
				carry_over = 1
				sum_without_carryover -= 10
			else:
				carry_over = 0

		# Fixing the tenth power
		if (i == len_of_bigger_digit):		# If it is the last digit, then no tenth power is required
			sum_of_numbers += sum_without_carryover
		else:
			sum_of_numbers += sum_without_carryover * tenth_power
			tenth_power *= 10


		# print ("Addition of " + str(first_list[i]) + " + " + str(second_list[i]) + " = " + str(sum_without_carryover))
		# print ("Current sum = " + str(sum_of_numbers) + ".\t Sum without carryover = " + str(sum_without_carryover) + ".\t Carry over = " + str(carry_over))
		# print ("Current iteration = " + str(i) + ".\t Tenth power = " + str(tenth_power) + "\n")


		# END FOR LOOP

	# print ("Final sum = " + str(sum_of_numbers))
	return sum_of_numbers
 

filename = find_file_name(str(sys.argv),"input=", "']")
with open(filename) as fp:
	line = fp.readline()
	line = line.replace(' ', '')			# Clean the line and remove spaces
	cnt = 1

	# Iterative solution
	while line:
		if (line == "========================================="):
			pass
		else:
			if (line == "\n"):
				pass
			original_string = line

			firstnum = (find_between(original_string, "add(", ","))
			secondnum = (find_between(original_string, ",", ")"))

			if (firstnum == -999):
				# Means the number was not found
				line = line[:-1]			# Remove new line from the end
				print (str(line) + "=error")
				pass
			elif (secondnum == -999):
				line = line[:-1]
				print (str(line) + "=error")
				pass
			elif (line == "\n"):
				# Check for empty line
				pass
			elif (check_digit_length(firstnum) == False):
				# If digit length is more than 40 digits
				line = line[:-1]
				print (str(line) + "=error")
				pass
			elif (check_digit_length(secondnum) == False):
				# If digit length is more than 40 digits
				line = line[:-1]
				print (str(line) + "=error")
				pass
			else:
				# The numbers are sent to addition function
				bigger_digit = find_bigger_number(firstnum,secondnum)
				len_of_bigger_digit = len(str(bigger_digit))-1

				smaller_digit = find_smaller_number(firstnum,secondnum)
				len_of_smaller_digit = len(str(smaller_digit))-1

				first_list = list(map(int, str(bigger_digit)))
				second_list = list(map(int, str(smaller_digit)))

				summation = addition(firstnum,secondnum,first_list,second_list)
				line = line.replace(' ', '') 	# Remove spaces from the original line
				line = line[:-1]			# Remove new line from the end
				print (str(line) + "=" + str(summation))

		line = fp.readline()

# END