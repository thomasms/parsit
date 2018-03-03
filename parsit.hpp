
#ifndef PARSEIT_HPP
#define PARSEIT_HPP

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <regex>
#include <fstream>
#include <streambuf>
#include <cerrno>

namespace toast {
    namespace parseit{
        
        // *** string splitters *** //
        // split using single delimiter and string wrapper
        template<char delimiter>
        struct StringDelimitedBy
        {
            std::string value;
            operator std::string () &&
            {
                return std::move(value);
            }
            operator std::string () const&
            {
                return value;
            }
        };
        template<char delimiter>
        std::istream& operator>>(std::istream& is, StringDelimitedBy<delimiter>& output)
        {
            std::getline(is, output.value, delimiter);
            return is;
        }

        // split using single delimiter
        template <char delimiter, class Container>
        void split(const std::string& str, Container& cont)
        {
            std::stringstream ss(str);
            std::string token;
            while (std::getline(ss, token, delimiter)) {
                cont.push_back(token);
            }
        }
        
        // Split using multiple delimiters using regex
        template <char... D, class Container>
        void splitwithregex(const std::string& str, Container& cont)
        {
            std::string pattern = "[]+";
            auto delimiters = {D...};
            std::for_each(delimiters.begin(),
                          delimiters.end(),
                          [&](char c){pattern.insert(1, 1, c);}
                          );
            std::regex sep (pattern);
            std::sregex_token_iterator tokens(str.cbegin(), str.cend(), sep, -1);
            std::sregex_token_iterator end;
            for(; tokens != end; ++tokens)
                cont.push_back(*tokens);
        }
        
        
        // *** cache file *** //
        std::string getfilecontents(const char *filename)
        {
            std::ifstream in(filename, std::ios::in | std::ios::binary);
            if (in)
            {
                return(std::string((std::istreambuf_iterator<char>(in)),
                                    std::istreambuf_iterator<char>()));
            }
            throw(errno);
        }
    }
}

#endif //PARSEIT_HPP
