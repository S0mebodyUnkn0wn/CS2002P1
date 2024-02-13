# Makefile written with help of gnu make documentation and examples provided in it,
# Chapters referenced:
# https://www.gnu.org/software/make/manual/make.html#Directory-Search
# https://www.gnu.org/software/make/manual/make.html#Automatic-Variables
# https://www.gnu.org/software/make/manual/make.html#Pattern-Rules
# https://www.gnu.org/software/make/manual/make.html#Foreach-Function

# Tell make to search for .c and .h files in src
vpath %.h ./src
vpath %.c ./src

# Compilation output directory
output_dir = ./bin


# Rule for building the exec file.
# We know that all .o files will be in the $(output_dir) (since we put them there),
# so we append $(output_dir)/ to each requirement to tell clang where to find them.
ttable: main.o parsers.o stack.o printers.o
	clang $(foreach req, $+, $(output_dir)/$(req)) -o $@ -Wall -Wextra -g

# Pattern rule for building object files from source
%.o : %.c ./bin
	clang $< -o $(output_dir)/$@ -c -Wall -Wextra -g

# Create a bin directory, if it doesn't exist
./bin:
	mkdir bin

# Clean ./bin (Removes EVERYTHING in bin)
clean:
	rm -f $(output_dir)/* ttable
