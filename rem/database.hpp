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
    DataType get(int id) {
        os.seekg(id * size, std::ios::beg);
        DataType data;
        os >> data;
        return data;
    }

    DataBase() {}
    DataBase(const std::string &file) {
        os.open(file, std::ios::in | std::ios::out);
        if (!os.is_open()) {
            os.open(file, std::ios::out);
            os.close();
            os.open(file, std::ios::in | std::ios::out);
        }
    }
    virtual ~DataBase() { os.close(); }

private:
    std::fstream os;
};

#endif
