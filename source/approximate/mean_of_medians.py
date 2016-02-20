# Accepts a filename containing numeric values in each line of which the statistics need to be calculated.
# Alternately as second argument, the bucket size can also be passed.
import sys
import numpy as np

fileName = sys.argv[1]
# find median of bucket splits of data
buckets = 5

if len(sys.argv) == 3:
    # Assuming the 2nd argument is the bucket size
    # if it exists
    buckets = int(sys.argv[2])

data = np.fromfile(fileName,sep="\n")
nmap = len(data) # Number of hashes used.
print("(mean of {} hashes) = {}".format(nmap,np.mean(data)))

# Finding mean of medians and vice-versa now
idxes = np.arange(nmap)
np.random.shuffle(idxes)
# numpy.array_split allows unequal splits of data
groups = np.array_split(idxes, buckets)

mean_of_medians = np.mean([np.median(data[group_idxs]) for group_idxs in groups])
median_of_means = np.median([np.mean(data[group_idxs]) for group_idxs in groups])
print("mean of medians (from {} buckets of data) : {}".format(buckets, mean_of_medians))
print("median of means (from {} buckets of data) : {}".format(buckets, median_of_means))
print("Standard Deviation : {}".format(np.std(data)))
