
# Specify the target
all:	lin_p1

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
lin_p1: submission.o submission.o
	g++  submission.o -o submission

# Specify how the object files should be created from source files
submission.o:	submission.cpp
	g++ -c submission.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o submission