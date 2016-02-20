import sys
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as pl
# import pylab as pl

if len(sys.argv) != 2:
    print("Need a filename for the plot output. Exiting...")
else:
    outputFile = sys.argv[1]
    data = []
    for line in sys.stdin:
        data.append(line.strip())
    data=map(int, data)
    pl.hist(data,100)
    pl.savefig(outputFile)
    # pl.show()

