#!/usr/bin/env python3

import sys

if(len(sys.argv) < 2):
  print("requires atleast 1 arg...")
  sys.exit(1);

crystals = []

with open(sys.argv[1],'r') as f:
  crystal = []
  for line in f:
    line = line.strip()
    if(len(crystal) == 0):
      crystal.append(line)
    elif(crystal[0] == line):
      # end of crystal
      crystals.append(crystal)
      crystal = []
    else:
      crystal.append(line)
  

# crystals is a list of list of vertices
edges = []
for i in range(0,len(crystals)+1):
  edges.append([-1])

visited = []
for i in range(1,len(crystals)+1):
  for j in range(1,len(crystals)+1):
    if(i == j):
      continue
    numCommon = 0
    for v1 in crystals[i-1]:
      for v2 in crystals[j-1]:
        if(v1 == v2):
          numCommon += 1

    if(numCommon >= 2):
      if(i not in edges[j]):
        edges[j].insert(0,i);
      if(j not in edges[i]):
        edges[i].insert(0,j);
          
print("<><><>")
for i,neighbor in enumerate(edges):
  print("{} {}".format(i,neighbor))
  
output = str(edges).replace(']','}').replace('[','{')
print('output')
print(output)
if(len(sys.argv) >= 3):
  with open(sys.argv[2],'w') as f:
    f.write(output)
else:
  print("no third argument: not piping output to file")
