#ifndef EXT_HPP
#define EXT_HPP

#include <string>
#include <vector>

namespace sjtu{
    using string = std::string;
    using parameter = std::vector<string>;

    int to_int(const string& str) {
        int r = 0;
        for (auto c : str)
            r = r * 10 + c - '0';
        return r;
    }
    
    parameter split(const string& str, char ch = ' ') {
        parameter retval;
        size_t i, last;
        for (i = 0, last = 0; i < str.size(); ++i) {
            if (str[i] == ch) {
                retval.push_back(str.substr(last, i - last));
                last = i + 1;
            }
        }
        retval.push_back(str.substr(last, i - last));
        return retval;
    }
}

#endif
