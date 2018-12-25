#ifndef NAIVE_DATABASE_HPP
#define NAIVE_DATABASE_HPP

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace sjtu {
template <typename T>

class naive_database {
  string dir;

public:
  naive_database() {}
  naive_database(string _dir) : dir(_dir) { mkdir(dir.c_str(), S_IRWXU); }

  void save(const string &key, const T &value = T()) const {
    std::ofstream os(dir + key + ".bin");
    os << value;
    os.close();
  }

  void append(const string &key, const string &val) const {
    std::fstream os(dir + key + ".log", std::ios::out | std::ios::app);
    os << val << std::endl;
    os.close();
  }

  void print(const string &name) {
    std::ifstream is(dir + name + ".log");
    string s;
    while (std::getline(is, s)) {
      auto v = split(s);
      std::cout << "\e[1;33m" << v[0] << "\033[0m";
      for (uint32_t i = 1; i < v.size(); ++i)
        std::cout << ' ' << v[i];
      std::cout << std::endl;
    }
    is.close();
  }

  bool exist(const string &key) {
    std::ifstream os(dir + key + ".bin");
    return os.is_open();
  }

  bool get(const string &key, T &value) {
    std::ifstream os(dir + key + ".bin");
    if (!os.is_open())
      return false;
    os >> value;
    os.close();
    return true;
  }

  bool erase(const string &key) {
    std::ifstream os(dir + key + ".bin");
    if (!os.is_open())
      return false;
    os.close();
    remove((dir + key + ".bin").c_str());
    return true;
  }
};
} // namespace sjtu

#endif
