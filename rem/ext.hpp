#ifndef EXT_HPP
#define EXT_HPP

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

namespace sjtu {
    using string = std::string;
    using parameter = std::vector<string>;

    const string INVALID = "Invalid";
    const string GUEST   = "guest";
    
    void error() {
        std::cout << INVALID << std::endl;
        throw std::invalid_argument("");
    }
    
    void format_print(int x) {
        std::cout << x / 100 << '.';
        x %= 100;
        if (x == 0)
            std::cout << "00";
        else if (x <= 9)
            std::cout << "0" << x;
        else
            std::cout << x;
    }

    int to_int(const string &str) {
        std::istringstream os(str);
        double value;
        os >> value;
        return value;
    }

    int to_int_100(const string &str) {
        std::istringstream os(str);
        double value;
        os >> value;
        return round(value * 100);
    }

    parameter split(const string &str, char ch = ' ') {
        parameter retval;
        size_t i, last;
        bool flag = true;
        for (i = 0, last = 0; i < str.size(); ++i) {
            if (str[i] == '"')
                flag ^= 1;
            if (str[i] == ch && flag) {
                if (i - last > 0)
                    retval.push_back(str.substr(last, i - last));
                last = i + 1;
            }
        }
        if (i - last > 0)
            retval.push_back(str.substr(last, i - last));
        return retval;
    }

    bool format(const string &str, string &attr, string &content) {
        if (str.front() != '-')
            return false;
        for (size_t i = 5; i < str.size(); ++i)
            if (str[i] == '=') {
                attr = str.substr(1, i - 1);
                content = str.substr(i + 1, str.size() - i - 1);
                return true;
            }
        return false;
    }
} // namespace sjtu

#endif
