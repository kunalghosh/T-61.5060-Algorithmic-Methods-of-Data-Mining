import string
import itertools
import sys


combos = 3
if len(sys.argv) == 2:
    combos = int(sys.argv[1])

for a in itertools.combinations(string.ascii_letters,combos):
    print "-".join(a)
