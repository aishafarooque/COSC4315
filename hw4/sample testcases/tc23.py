# File: functional.py
# Content: test source code
def add(x,y):
	z=x+y
	return z

def multiply(x,y):
	z=x*y
	return z

def multefficient(x,y):
	if x!=0:
		if y!=0:
			z=x*y
		return z
	return 0

def dup(x):
	z=2*x
	return z

def divide(a,b):
	if b!=0:
		c=a/b
		return c
	else:
		return -1	

x1=add(multiply(1,3),multiply(4,6))
y1=1
x2=multiply(add(y1,y1),add(2,2))
x3=dup(x1)
x4 =x1 + x2
y=divide(5,2)
print("x1=",x1)
print("x2=",x2)
print("x3=",x3)
print("x4=",x4)
print("y=",y)
