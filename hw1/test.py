import sys, re
input_string = str(sys.argv)

if (input_string.find("digitsPerNode") != -1):
	print ("found")
else:
	print ("whoops not found")