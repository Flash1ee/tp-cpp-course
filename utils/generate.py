import random
import sys
if len(sys.argv) != 2:
    exit(1)

n = 10**7
min = 0.1
max = 5
data = []
# id avg votes
for i in range(n):
    avg = round(random.uniform(min, max), 3)
    # if avg < 0.2: avg = 0
    votes = int(random.uniform(min, max**3))
    data.append(" ".join([str(j) for j in [i, votes, avg]]))

file = open(sys.argv[1], 'w')
file.write(str(n) + "\n")
for i in data:
    file.write(i+'\n')
file.close()
