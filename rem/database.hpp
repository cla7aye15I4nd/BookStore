#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <cassert>
#include <fstream>
#include <string>
#include <unordered_map>

template <typename DataType, int size> class DataBase {
public:
  int append(const DataType &data) {
    os.seekp(0, std::ios::end);
    os << data;
    int id = os.tellp() / size - 1;
    map[id] = data;
    return id;
  }
  void cover(const DataType &data, int id) {
    map[id] = data;
    os.seekg(id * size, std::ios::beg);
    os << data;
  }
  const DataType &get(int id) {
    if (map.count(id))
      return map[id];
    else {
      os.seekg(id * size, std::ios::beg);
      DataType data;
      os >> data;
      return map[id] = data;
    }
  }

  DataBase() {}
  DataBase(const std::string &_file) {
    file = _file;
    os.open(file);
    if (!os.is_open()) {
      os.open(file, std::ios::out);
      os.close();
      os.open(file);
    }
  }
  virtual ~DataBase() { os.close(); }

private:
  std::string file;
  std::fstream os;
  std::unordered_map<int, DataType> map;
};

#endif
