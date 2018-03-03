#include <iostream>
#include <sstream>
#include <regex>

#include <parsit.hpp>

using namespace toast::parseit;

const std::string ignoreline = "<<";

int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
        return 1;
    }
//    std::string text = "Let me split    this into words\n 4.5 3,2434.234 fdhla dfs";
//    StringDelimitedBy<' '> text2 = {text};
//
//    // using wrapper around std::string
//    std::istringstream iss(text2);
//    std::vector<std::string> results((std::istream_iterator<StringDelimitedBy<' '>>(iss)),
//                                      std::istream_iterator<StringDelimitedBy<' '>>());
//    for(auto e: results)
//        std::cout << e << std::endl;
//
//    // using templated function - split
//    std::vector<std::string> words;
//    split<' '>(text, words);
//    std::copy(words.begin(), words.end(),
//              std::ostream_iterator<std::string>(std::cout, "\n"));
    
    // using regex
//    std::regex sep ("[ \t\n\r]+");
//    std::sregex_token_iterator tokens(text.cbegin(), text.cend(), sep, -1);
//    std::sregex_token_iterator end;
//    for(; tokens != end; ++tokens)
//        std::cout << *tokens << std::endl;
    
    static std::string cacheFile = getfilecontents(argv[1]);
    std::vector<std::string> lines;
    splitwithregex<'\n', '\r'>(cacheFile, lines);
    for(auto& line: lines){
        std::vector<std::string> keyword;
        splitwithregex<'\t', ' '>(line, keyword);
        if(!strncmp(keyword[0].c_str(), ignoreline.c_str(), ignoreline.size()))
            continue;
        std::copy(keyword.begin(), keyword.end(),
                  std::ostream_iterator<std::string>(std::cout, "\n"));
    }
    std::cout << std::endl;
    
    return 0;
}
