#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <fstream>
#include <cassert>

template <typename DataType, int size>
class DataBase{
public:
    int append(const DataType& data) {
        os.seekp(0, std::ios::end);
        os << data;
        //std::cerr << "###" << os.tellp() << std::endl;
        return os.tellp() / size - 1;
    }
    DataType get(int id) {
        //std::cerr << "$$";
        os.seekg(id * size, std::ios::beg);
        //std::cerr << "####" << os.tellp() << std::endl;
        DataType data;
        os >> data;
        //std::cerr << data << '\n';
        return data;
    }
    
    DataBase () {}
    DataBase (const std::string& file) {
        os.open(file, std::ios::in | std::ios::out);
        if (!os.is_open()) {
            os.open(file, std::ios::out);
            os.close();
            os.open(file, std::ios::in | std::ios::out);
        }
    }
    virtual ~DataBase () { os.close(); }

private:
    std::fstream os;
};

#endif
