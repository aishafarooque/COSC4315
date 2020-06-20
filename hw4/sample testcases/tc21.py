#hard program - if insisde else
def f1(a,b):
   if a>b:
      c=a-b
      return c
   else:
      if a==0:
         return b
      else:
         c=b-a
         return c

x=f1(3,4)
y=f1(0,6)
z=f1(8,1)

print("x=",x)
print("y=",y)
print("z=",z)
