from matplotlib import pyplot as plt

from matplotlib import style
import numpy as np

style.use('ggplot')

# cpu.txt is the input file containing x,y coordinates for which we want to plot the graph
y,x = np.loadtxt('cpu.txt', 
					unpack=True,
					delimiter = '\t')

plt.plot(x,y)

plt.title('CPU usage vs time')
plt.xlabel('Time')
plt.ylabel('CPU usage')

plt.show()