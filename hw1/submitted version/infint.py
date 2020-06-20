import math
import sys, re

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

def find_number_of_digits (num):
	counter = 0
	while(num > 0):
		num = num // 10
		counter += 1
	return counter

def check_digit_length (first):
	num_to_check = str(first)
	if (len(num_to_check) >= 41):
		return False
	return True

def multiplication (first, second):

	bigger_digit = find_bigger_number(int(first), int(second))
	len_of_bigger_digit = find_number_of_digits(bigger_digit)

	smaller_digit = find_smaller_number(int(first), int(second))
	len_of_smaller_digit = find_number_of_digits(smaller_digit)

	first_list = list(map(int, str(bigger_digit)))
	second_list = list(map(int, str(smaller_digit)))

	if (bigger_digit == 0 | smaller_digit == 0):
		return 0

	if (bigger_digit == 1):
		return smaller_digit
	elif (smaller_digit == 1):
		return bigger_digit

	final_result = 0
	total_tenth_power = 1

	iteration_tenth_power = 1
	denominator_tenth_power = 1
	iteration_result = 0
	for i in reversed(range(0, len_of_smaller_digit)):
		for j in reversed(range(0, len_of_bigger_digit)):
			iteration_result = iteration_result + (first_list[j]* iteration_tenth_power * second_list[i])
			# print ("Multiplying " + str(first_list[j]*iteration_tenth_power) + " and " + str(second_list[i]))
			# print ("iteration_result = " + str(iteration_result) + "\n")
			iteration_tenth_power *= 10

		final_result += iteration_result * total_tenth_power
		# print ("final_result = " + str(final_result) + "\n")

		iteration_result = 0
		total_tenth_power *= 10
		iteration_tenth_power = 1

	return final_result

def addition (first, second):
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
		# print ("element_1 sum = " + str(sum_of_numbers) + ".\t Sum without carryover = " + str(sum_without_carryover) + ".\t Carry over = " + str(carry_over))
		# print ("element_1 iteration = " + str(i) + ".\t Tenth power = " + str(tenth_power) + "\n")


		# END FOR LOOP

	# print ("Final sum = " + str(sum_of_numbers))
	return sum_of_numbers

def evaluate(st):
	# Check for missing numbers inside the expression
	if (st.find('(,') != -1):
		return "invalid expression"
	if (st.find(',)') != -1):
		return "invalid expression"

	st = st.replace("multiply", "m")
	st = st.replace("add","a")
	st = st.replace("(", " ")
	st = st.replace(")", " ")
	st = st.replace(",", " ")

	stack = st.split()
	loop_debugging = True
	operations_debugging = True

	while (len(stack) != 1):
		tempstack = []
		for i in range(0,len(stack)-1):
			num1 = stack[i]

			if (check_digit_length(num1) == False):
				return "invalid expression"

			if (num1.isdigit() & stack[i+1].isdigit()):
				num2 = stack[i+1]
				if (check_digit_length(num2) == False):
					return "invalid expression"
				ops = stack[i-1]
				tempstack.pop()
				if (ops == 'a'):
					tempstack.append(str(addition(int(num1),int(num2))))
				elif (ops == 'm'):
					tempstack.append(str(multiplication(find_bigger_number(int(num1), int(num2)), find_smaller_number(int(num1), int(num2)))))
				
				for j in range(i+2,len(stack)):
					tempstack.append(str(stack[j]))
					# break
				break

			else:
				tempstack.append(num1)
				
		stack = tempstack
	return (tempstack[0])

filename = find_file_name(str(sys.argv),"input=", ";")
digitsPerNode = sys.argv[len(sys.argv)-1]

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
				print (str(line) + "=invalid expression")
				pass
			elif (secondnum == -999):
				line = line[:-1]
				print (str(line) + "=invalid expression")
				pass
			elif (line == "\n"):
				# Check for empty line
				pass
			elif (int(digitsPerNode[len(digitsPerNode)-1]) > 4):
				# digitsPerNode cannot be greater than 4
				line = line[:-1]
				print (str(line) + "=invalid expression")
				pass
			elif(is_balanced(original_string) == False):
				# If the brackets are not balanced
				line = line[:-1]
				print (str(line) + "=invalid expression")
			else:
				# The numbers are sent to the evaluate function
				bigger_digit = find_bigger_number(firstnum,secondnum)
				len_of_bigger_digit = len(str(bigger_digit))-1

				smaller_digit = find_smaller_number(firstnum,secondnum)
				len_of_smaller_digit = len(str(smaller_digit))-1

				first_list = list(map(int, str(bigger_digit)))
				second_list = list(map(int, str(smaller_digit)))

				summation = evaluate(original_string)
				line = line.replace(' ', '') 	# Remove spaces from the original line
				line = line[:-1]			# Remove new line from the end
				print (str(line) + "=" + str(summation))

		line = fp.readline()

# END