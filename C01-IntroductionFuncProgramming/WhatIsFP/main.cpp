#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../../util/print.h"
/*
 * 1.12 A concrete example of imperative vs. declarative programming
 */
#define USE_FP

#ifndef USE_FP
// Cacluating the number of lines the imperative way
std::vector<int> count_lines_in_files(std::vector<std::string> const& files){
    std::vector<int> results;

    char c=0;
    for(auto const& file:files){
        int line_count =0;
        std::ifstream in(file);

        while(in.get(c)){
            if(c == '\n'){
                ++line_count;
            }
        }
        results.push_back(line_count);
    }
    return results;
}

#else

/*
 * With this solution, you're no longer concerned about exactly how the counting is
 * implemented; you are just declaring that you want to count the number of newlines
 * that appear in the give input stream. This is always the main idea when writing
 * programs in the functional style-- use abstractions that let you define the intent instead
 * of specifying how to do something-and is the aim of most techniques covered in this
 * book.
 */
int count_lines(std::string const& file){
    std::ifstream in(file);
    return std::count(std::istream_iterator<char>(in >> std::noskipws),
            std::istream_iterator<char>(),'\n');
}
#define USE_TRANSFORM
#ifndef USE_TRANSFORM
std::vector<int> count_lines_in_files(std::vector<std::string> const& files){

    std::vector<int>results;
    for(auto const& file: files){
        results.push_back(count_lines(file));
    }
    return results;
}

#else
std::vector<int> count_lines_in_files(std::vector<std::string>const &files){
    // Since we know the size of the resulting vector, we can
    // ppreallocate the needed number of elements
	std::vector<int> results(files.size());

    // Instead of using the raw for loop like in the count-lines-stdcout
    // we are using the std::transform algorithm to
    // convert the list of file names into a list of line counts
	std::transform(files.cbegin(),files.cend(),
					results.begin(),
					count_lines);
	return results;
}
#endif
#endif


int main()
{
    auto results = count_lines_in_files({"main.cpp","makefile"});
    for(auto const& res: results){
        println(res, " line(s)");
    }

    std::vector<int> v1{1,2,3,4,5};
    std::vector<int> v2{5,6,7,8};

    return 0;
}
