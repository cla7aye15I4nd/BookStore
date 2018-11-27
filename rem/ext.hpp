#ifndef EXT_HPP
#define EXT_HPP

#include <string>
#include <vector>
#include <sstream>

namespace sjtu{
    using string = std::string;
    using parameter = std::vector<string>;

    int to_int(const string& str) {
        std::istringstream os(str);
   	double value; os >> value;
        return value;
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

    bool format(const string& str, string& attr, string& content) {
        if (str.front() != '-') return false;
        for (size_t i = 5; i < str.size(); ++i)
            if (str[i] == '=') {
                attr = str.substr(1, i - 1);
                content = str.substr(i + 1, str.size() - i - 1);
                return true;
            }
        return false;
    }
}

#endif
