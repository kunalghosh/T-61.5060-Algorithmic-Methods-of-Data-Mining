import sys

uniques = {}
F0 = 0
F2 = 0
for a in sys.stdin:
    try:
        uniques[a] += 1
    except KeyError,e:
        uniques[a] = 1
        F0 += 1

for a,v in uniques.iteritems():
    F2 = F2 + v**2

print("F0 = {} \nF2 = {}".format(F0,F2))

