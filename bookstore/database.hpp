#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

namespace sjtu{
    template <typename T>

    class naive_database{
        string dir;

    public:
        naive_database () {}
        naive_database (string _dir) : dir(_dir) {}
        
        void save(const string& key, const T& value) const{
            std::ofstream os(dir + key + ".bin");
            os << value;
            os.close();   
        }

        bool exist(const string& key) {
            std::ifstream os(dir + key + ".bin");
            return os.is_open();
        }

        bool get(const string& key, T& value) {
            std::ifstream os(dir + key + ".bin");
            if (!os.is_open())
                return false;
            os >> value;
            os.close();
            return true;
        }

        bool erase(const string& key) {
            std::ifstream os(dir + key + ".bin");
            if (!os.is_open())
                return false;
            os.close();
            remove((dir + key + ".bin").c_str());
            return true;
        }
    };

}

#endif
