#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <cassert>
#include <fstream>
#include <string>

template <typename DataType, int size> class DataBase {
public:
    int append(const DataType &data) {
        os.seekp(0, std::ios::end);
        os << data;
        return os.tellp() / size - 1;
    }
    void cover(const DataType &data, int id) {
        os.seekg(id * size, std::ios::beg);
        os << data;
    }
    DataType get(int id) {
        os.seekg(id * size, std::ios::beg);
        DataType data;
        os >> data;
        return data;
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
};

#endif
