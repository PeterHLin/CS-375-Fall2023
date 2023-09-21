To run this program do the following:
1. Open terminal to program directory
2. Type "make" to compile
3. Type "./submission input.txt output.txt" to run the program
4. make sure input is a valid file and output is a valid file with a given input of integers
5. The output result will be in output.txt
6. Type "make clean" to remove all object files and the executable
 
My implemented program uses a binary search to find if the array has contains a difference
it first sorts the input array in accending order, and then it will loop through it finding
a difference between the first element and the second element until the end of the array.
It will use binary search to find if there is a difference that contains in the array. If so,
it will return true and return out the difference which will be outputted into the outpufile.
If not, it will return false and will create a 0 byte blank file to the outputfile name. 
My worst time complexity is O(n^2logn) because of the sorting algorithm and the binary search.
```