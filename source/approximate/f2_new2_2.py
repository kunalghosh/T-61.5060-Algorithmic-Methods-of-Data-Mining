from __future__ import print_function
import sys
import numpy as np
import cPickle as pkl
import pprint

RAND_NUMS = 100000000
def getEstimatedF2(counts, n):
    # Mean of all values.
    return np.mean(n*(2*np.asarray(counts) - 1))

# # def get_next_rand(rands):
#     retVal = -1
#     try:
#         retVal = rands.pop()
#         # retVal = rands[-1]
#         # rands = rands[:-1]
#     except IndexError as e:
#         rands.extend(np.random.rand(RAND_NUMS))
#         retVal = rands.pop()
#         # rands = np.random.rand(RAND_NUMS)
#         # retVal = rands[-1]
#         # rands = rands[:-1]
#     return retVal
def get_next_rand(rands):
    retVal = -1
    if len(rands) == 0:
        rands = np.random.rand(RAND_NUMS)
    retVal = rands[-1]
    rands = rands[:-1]
    return retVal, rands



# def get_rand_idxes(rand_idxes,low,high):
#     retVal = -1
#     try:
#         retVal = rand_idxes[(low,high)].pop()
#     except IndexError as e:
#         rand_idxes[(low,high)].extend(np.random.randint(low,high,RAND_NUMS))
#     except KeyError as e:
#         rand_idxes[(low,high)] = list(np.random.randint(low,high,RAND_NUMS))
#     finally:
#         retVal = rand_idxes[(low,high)].pop()
#     return retVal

# def get_rand_idxes(rand_idxes,low,high):
#     retVal = -1
#     try:
#         retVal = rand_idxes.pop()
#         # retVal = rand_idxes[-1]
#         # rand_idxes = rand_idxes[:-1]
#     except IndexError as e:
#         rand_idxes.extend(np.random.randint(low,high,RAND_NUMS))
#         rand_idxes.pop()
#         # rand_idxes = np.random.randint(low,high,RAND_NUMS)
#         # retVal = rand_idxes[-1]
#         # rand_idxes = rand_idxes[:-1]
#     return retVal
# def get_rand_idxes(rand_idxes,low,high):
#     retVal = -1
#     if len(rand_idxes) == 0:
#         rand_idxes = np.random.randint(low,high,RAND_NUMS)
#     retVal = rand_idxes[-1]
#     rand_idxes = rand_idxes[:-1]
#     return retVal, rand_idxes



if __name__ == "__main__":
    rands = []
    # rand_idxes = {}
    rand_idxes = [] 
    outputFile = "f2_values_new_2Jan_new.txt"
    dataPkl = 'data.pkl'
    S = 4100000
    # S = 200
    # S = 10

    if len(sys.argv) == 2:
	try:	
	    S = int(sys.argv[1])
	except ValueError as e:	
            outputFile = sys.argv[1]

    if len(sys.argv) == 3:
        S = int(sys.argv[1])
        outputFile = sys.argv[2]

    X_listIdx = {} # Stores {line : [Idx in X_xcount where line appears]} 
    X_xcount = [] # Stores [line,count] (lines can be duplicates) 
    n = -1
    counter = 0
    batch_updater = {}

    for line in sys.stdin:
        # print(len(rands), len(rand_idxes))
        n += 1
        # if n % RAND_NUMS == 0:
        #     print("{} Rows done.".format(n))
        if n < S: # pick the first S elements of the stream
            X_xcount.append([line, 1]) # line and its count
            if line in X_listIdx:
                X_listIdx[line].append(n) # store the index of the element
            else:
                X_listIdx[line] = [n]
        else:
            prob = (S*1.0)/n # probability of picking the n'th element
            # randVal,rands = get_next_rand(rands)
            # if len(rand_idxes) == 0:
            #    rand_idxes = np.random.randint(low,high,RAND_NUMS)
            try:
                randVal = rands[-1]
                rands = rands[:-1]
            except IndexError as e:
                rands = np.random.rand(RAND_NUMS)
                randVal = rands[-1]
                rands = rands[:-1]
 
            if  randVal < prob: # Very high probability of picking a line close whose index is to S
                #---
                # Remove an element
                #---
                # pick an index from X_xcount to remove ( equal probability of each element ) 

                # idx_to_del,rand_idxes = get_rand_idxes(rand_idxes,0,S)
                # if len(rand_idxes) == 0:
                #     rand_idxes = np.random.randint(low,high,RAND_NUMS)
                try:
                    idx_to_del = rand_idxes[-1]
                    rand_idxes = rand_idxes[:-1]
                except IndexError as e:
                    rand_idxes = np.random.randint(0,S,RAND_NUMS)
                    idx_to_del = rand_idxes[-1]
                    rand_idxes = rand_idxes[:-1]
  
                # while(True):
                #     # if X_listIdx[line_to_del] is empty delete it and continue
                #     try:
                #         line_to_del = X_listIdx.keys()[get_rand_idxes(rand_idxes,0,len(X_listIdx),S)]
                #         # list_idx = get_rand_idxes(rand_idxes,0,len(X_listIdx[line_to_del]))
                #         # try:
                #         #     X_listIdx[line_to_del][list_idx], X_listIdx[line_to_del][-1] = X_listIdx[line_to_del][-1], X_listIdx[line_to_del][list_idx]
                #         # except Exception as e:
                #         #     print(X_listIdx[line_to_del], list_idx)
                #         #     sys.exit(1)
                #         idx_to_del = X_listIdx[line_to_del].pop()
                #     except IndexError as e:
                #         X_listIdx.pop(line_to_del,None)
                #         continue
                #     else:
                #         break
                
                X_xcount[idx_to_del] = [line, 1]
                #if line in X_listIdx:
                #    X_listIdx[line].append(idx_to_del)
                #else:
                #    X_listIdx[line] = [idx_to_del]

            else:
                # The line was not picked.
                # Increment X_xcount[i][1] where X_xcount[i][0] == line
                # if line in X_listIdx: 
                #     idxes = X_listIdx[line]
                #     for idx in idxes:
                #         X_xcount[idx][1] += 1
                counter += 1
                if counter != 500:
                    if line in batch_updater:
                        batch_updater[line] += 1
                    else:
                        batch_updater[line] = 1
                else:
                    for idx,line in enumerate(X_xcount):
                        line_str = line[0]
                        if line_str in batch_updater:
                            X_xcount[idx][1] += batch_updater[line_str]
                    batch_updater = {}
                    counter = 0


	
    strs,counts = zip(*X_xcount)
    counts = np.asarray(counts)
    vals = (n+1) * (2*counts-1)
    np.savetxt(outputFile, vals, fmt="%d")
    # vals = []
    # for entry in X_xcount:
    #     val.append((n+1)*(2*entry[1]-1))

    # with open(outputFile,"w") as oFile:
    #     # print(val)
    #     # print(val, file=oFile)
    #     oFile.write("{}\n".format(val))

    # print("Estimated F2 {}".format(int(getEstimatedF2(zip(*X_xcount)[1], n+1))))
    print("{}".format(int(getEstimatedF2(zip(*X_xcount)[1], n+1))))

