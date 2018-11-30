#ifndef EXT_HPP
#define EXT_HPP

#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <iostream>

namespace sjtu{
    using string = std::string;
    using parameter = std::vector<string>;

    void format_print(int x) {
        std::cout << x / 100 << '.';
        x %= 100;
        if (x == 0) std::cout << "00";
        else if (x <= 9) std::cout << "0" << x;
        else std::cout << x;
    }
    
    int to_int(const string& str) {
        std::istringstream os(str);
   	double value; os >> value;
        return value;
    }

    int to_int_100(const string& str) {
        std::istringstream os(str);
   	double value; os >> value;
        fprintf(stderr, "%.3f %d\n", value, int(value * 100)); 
        return round(value * 100);
    }
    
    parameter split(const string& str, char ch = ' ') {
        parameter retval;
        size_t i, last;
        for (i = 0, last = 0; i < str.size(); ++i) {
            if (str[i] == ch) {
                if (i - last > 0)
                    retval.push_back(str.substr(last, i - last));
                last = i + 1;
            }
        }
        if (i - last > 0)
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
