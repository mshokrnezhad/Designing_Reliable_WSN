import matplotlib.pyplot as plt 
  
f = open("xs.txt", 'r')
xs = f.readlines()
xs = [int(i) for i in xs]

f = open("ys.txt", 'r')
ys = f.readlines()
ys = [int(i) for i in ys]

f = open("rawx.txt", 'r')
xr = f.readlines()
xr = [float(i) for i in xr]

f = open("rawy.txt", 'r')
yr = f.readlines()
yr = [float(i) for i in yr]
  
# plotting points as a scatter plot 
plt.scatter(xs, ys, label= "sensor", color= "green", marker= "o", s=10) 
plt.scatter(xr, yr, label= "router", color= "blue", marker= "*", s=100) 
#plt.scatter(xrr, yrr, color= "blue", marker= "*", s=100) 
  
# x-axis label 
plt.xlabel('x - axis') 
# frequency label 
plt.ylabel('y - axis') 
# plot title 
plt.title('Under-Water Sensor Network + Reliable Routing Network') 
# showing legend 
plt.legend() 
  
# function to show the plot 
plt.show() 

