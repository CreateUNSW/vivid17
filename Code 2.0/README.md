# Code the Second

## compiling main.cpp
 * just run `./compile_run`
 * Note this is not the file that is to be uploaded to the arduino

## generating edge configurations from grasshopper
* run the grasshopper script against the appropriate 3dm file
* there should be a large panel to the left (honestly don't remember where it is, but you can't miss it) labeled vertices
* right-click and copy the data into a text file (vertices.txt is an example of one such file)
* run the python script as `./get_edges.py input.txt output.txt` where *input.txt* is the data copied from grasshopper(e.g vertices.txt) and *output.txt* is the file to write the C++ matrix that can be copied to *main.cpp*
* alternatively you don't have to supply the second argument (*output.txt*) and it'll still display the correct configurations