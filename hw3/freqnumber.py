import sys

def get_substring( s, first, last ):
    try:
        start = s.index( first ) + len( first )
        end = s.index( last, start )
        return s[start:end]
    except ValueError:
        return -1

def get_string_between_spaces(lists, line, index, number_of_elements, inserted):

	index = index + 1

	if (line == ""):
		return lists
	elif (line[index] == " "):
		lists.append(line[:index])
		line = line[index+1:]
		inserted += 1

		return get_string_between_spaces(lists, line, -1, number_of_elements, inserted)
	elif (number_of_elements != inserted):
		return get_string_between_spaces(lists, line, index, number_of_elements, inserted)

	return lists

def clean_list(lists, list_index, cleaned_list):
	# We have reached the end of the list
	list_index = list_index + 1

	if (list_index == len(lists)):
		return cleaned_list
	elif (lists[list_index].find(".") + 1 == len(lists[list_index])):
		# 7321. is not valid
		pass
	elif (lists[list_index].isnumeric()):
		cleaned_list.append(lists[list_index])
	else:
		try:
			float(lists[list_index])
			cleaned_list.append(lists[list_index])
		except ValueError:
			pass

	return clean_list(lists, list_index, cleaned_list)

def quick_sort(l):
	# Code credit to https://stackoverflow.com/questions/26858358/a-recursive-function-to-sort-a-list-of-ints
    if len(l) <= 1:
        return l
    else:
        return quick_sort([e for e in l[1:] if e >= l[0]]) + [l[0]] +\
            quick_sort([e for e in l[1:] if e < l[0]])

def get_max_frequency(lists, list_index, highest_frequency, highest_frequency_index):
	list_index = list_index + 1

	if (list_index == len(lists)):
		return highest_frequency_index

	if (lists[list_index][1] > highest_frequency):
		highest_frequency = lists[list_index][1]
		highest_frequency_index = list_index

	return get_max_frequency(lists, list_index, highest_frequency, highest_frequency_index)

def print_highest_frequencies(lists, k, previous_frequency, results):
	highest_frequency_index = get_max_frequency(lists, -1, -1, -1)

	if (k == 0):
		if (get_max_frequency(lists, -1, -1, -1) == previous_frequency):
			# print (lists[highest_frequency_index][0], lists[highest_frequency_index][1])
			results.insert(-1, str(lists[highest_frequency_index][0] + " " + str(lists[highest_frequency_index][1])))
		return results

	# print (lists[highest_frequency_index][0], lists[highest_frequency_index][1])

	results.append(lists[highest_frequency_index][0] + " " + str(lists[highest_frequency_index][1]))

	# print ('current frequency ', lists[highest_frequency_index][1], ' previous frequency ', previous_frequency)

	if (lists[highest_frequency_index][1] != previous_frequency):
		k -= 1
	
	previous_frequency = lists[highest_frequency_index][1]
	lists.remove(lists[highest_frequency_index])

	return print_highest_frequencies(lists, k, previous_frequency, results)

def sort_into_ints(lists, list_index, sorted_list):
	list_index = list_index + 1
	if (list_index == len(lists)):
		return sorted_list
	else:
		try:
			int(lists[list_index])
			sorted_list.append(int(lists[list_index]))
		except ValueError:
			pass
	return sort_into_ints(lists, list_index, sorted_list)

def sort_into_float(lists, list_index, sorted_list):
	list_index = list_index + 1
	if (list_index == len(lists)):
		return sorted_list
	else:
		if (lists[list_index].find(".") != -1):
			try:
				float(lists[list_index])
				sorted_list.append(float(lists[list_index]))
			except ValueError:
				pass
	return sort_into_float(lists, list_index, sorted_list)

def find_in_list(frequency_list, frequency_list_index, element_to_find):
	# [[1,2], [3,4]] => find_in_list(frequency_list, -1, 1) => 0
	frequency_list_index = frequency_list_index + 1

	# print (len(frequency_list))

	if (frequency_list_index == len(frequency_list)):
		return -99		# Element is not found inside the list

	if (frequency_list[frequency_list_index][0] == element_to_find):
		return frequency_list_index
	else:
		return find_in_list(frequency_list, frequency_list_index, element_to_find)

def count_frequencies(lists, list_index, freq_list):
	list_index = list_index + 1

	if (list_index == len(lists)):
		return freq_list

	if (list_index == 0):
		freq_list[0].append(lists[list_index])
		freq_list[0].append(1)
		return count_frequencies(lists, list_index, freq_list)

	index_in_list = find_in_list(freq_list, -1, lists[list_index])

	if (index_in_list != -99):
		freq_list[index_in_list][1] += 1
	else:
		freq_list.append([lists[list_index], 1])

	return count_frequencies(lists, list_index, freq_list)

def print_list(lists, list_index):
	list_index = list_index + 1
	if (list_index == len(lists)):
		return

	print (lists[list_index][0], lists[list_index][1])
	return print_list(lists, list_index)


def get_n_max(lists, k, results):
	highest_frequency_index = get_max_frequency(lists, -1, -1, -1)

	if (len(lists) <= 0):
		return results

	if (len(results) > 0):
		# print ('results end: ', results[-1])
		if (results[-1][1] != lists[highest_frequency_index][1]):
			k -= 1
			# print ('reducing k')

	if (k <= 0):
		return results

	

	# print ('highest_frequency: ', lists[highest_frequency_index])
	# print (results)


	results.append([(lists[highest_frequency_index][0]), (lists[highest_frequency_index][1])])
	lists.remove(lists[highest_frequency_index])

	return get_n_max(lists, k, results)


def swap(lists, list_index):
	list_index = list_index + 1

	if (len(lists) == 0):
		return []

	if (list_index == len(lists)-1):
		return lists

	first_element = lists[list_index]
	second_element = lists[list_index+1]
	if (first_element[1] == second_element[1]):
		if (first_element[0] > second_element[0]):
			lists[list_index], lists[list_index+1] = lists[list_index+1], lists[list_index]

	return swap(lists, list_index)

# sys.argv = "input=tc6.txt;k=-1;output=freqnumber.txt"
commandLine = str(sys.argv)+";"		# Add delimiter

inputFileName = get_substring(commandLine, "input=", ";")
if (inputFileName == ""):
	print("help: input file name not provided")
	sys.exit(0)

if (inputFileName == -1):
	print("help: input file name not provided")
	sys.exit(0)

k = int(get_substring(commandLine, "k=", ";"))

if (k <= 0):
	print("help: k <= 0")
	sys.exit(0)


outputFileName = get_substring(commandLine, "output=", ";")

lists = []

with open(inputFileName) as fp:
	line = fp.readline()

	while line:
		if (line == ""):
			pass
		line = line.rstrip()

		line = line + " "			# Add a space delimiter at the end, necessary 
		lists = get_string_between_spaces(lists, line, -1, line.count(" "), 0)
		
		line = fp.readline()

lists = clean_list(lists, -1, [])

if (len(lists) == 0):
	print("help: input file is empty")
	sys.exit(0)

# print (lists)
# print (sort_into_ints(lists, -1, []))

int_list = quick_sort(sort_into_ints(lists, -1, []))
float_list = quick_sort(sort_into_float(lists, -1, []))

int_list = count_frequencies(int_list, -1, [[]])
float_list = count_frequencies(float_list, -1, [[]])

# print (len(float_list))

# For tc4
if (k > len(int_list)):
	k_int = len(int_list)
else:
	k_int = k

if (k > len(float_list)):
	k_float = len(float_list)
else:
	k_float = k

# print ("integer:")
# print_list(print_highest_frequencies(int_list, k, -1, []), -1)
# print ("real:")
# print_list(print_highest_frequencies(float_list, k, -1, []), -1)

int_list = swap(get_n_max(int_list, k_int, []), -1)
float_list = swap(get_n_max(float_list, k_float, []), -1)

# print (float_list)

print ("integer:")
print_list(int_list, -1)
print ("real:")
print_list(float_list, -1)