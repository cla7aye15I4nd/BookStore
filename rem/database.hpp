#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <fstream>

template <typename DataType, int size>
class DataBase{
public:
    void append(const DataType& data) {
        os.seekp(0, std::ios::end);
        os << data;
    }
    DataType get(int id) {
        os.seekp(id * size, std::ios::beg);
        DataType data;
        os << data;
        return data;
    }
    
    DataBase () {}
    DataBase (const std::string& file) {
        os.open(file, std::ios::in | std::ios::out);
    }
    virtual ~DataBase () { os.close(); }

private:
    std::fstream os;
};

#endif
