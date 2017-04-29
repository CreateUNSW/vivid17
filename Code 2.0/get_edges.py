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

# for crystal in crystals:
#   print(crystal)
  
edges = []
for i in range(0,len(crystals)+1):
  edges.append([-1])

visited = []
for i in range(1,len(crystals)+1):
  for vertex in crystals[i-1]:
    if vertex not in visited:
      visited.append(vertex)
      neighbor  = [i]
      for j in range(i+1, len(crystals) + 1):
        if vertex in crystals[j - 1]:
          neighbor.append(j)
      
      while(len(neighbor) > 0):
        x = neighbor.pop(0)
        for y in neighbor:
          if(y not in edges[x]):
            edges[x].insert(0,y);
          if(x not in edges[y]):
            edges[y].insert(0,x);
          
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