#hard program - if else+global var
def f1(a,b):
   if a>b:
      z=a-b
      return z
   else:
      z=a+b
      return z
  

x=f1(3,4)
y=f1(0,6)
z=x+y

print("x=",x)
print("y=",y)
print("z=",z)
