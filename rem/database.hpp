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
        
        void save(const string& key, const T& value = T()) const{
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

    class BlockList{
        const int DATALEN;
        const int BLOCKSZ;
    
        std::vector<int> next;
        std::vector<int> size;
        char *tmp;
        FILE *fp;

    public:
        BlockList () = default;
        BlockList (int _DATALEN, int _BLOCKSZ, std::string file)
            : DATALEN(_DATALEN), BLOCKSZ(_BLOCKSZ), tmp(new char [_DATALEN * _BLOCKSZ]),
              fp(fopen((file + ".bin").c_str(), "r+")) {}

        virtual ~BlockList() {
            delete [] tmp;
        }
    
        void split(int x) {
            next.emplace_back(next[x]);
            next[x] = next.size();
            size[x] = BLOCKSZ / 2;
            size.emplace_back(BLOCKSZ / 2);

            fseek(fp, DATALEN * BLOCKSZ * x + DATALEN * BLOCKSZ / 2, SEEK_SET);
            for (int i = 0; i < DATALEN * BLOCKSZ / 2; ++i)
                tmp[i] = fgetc(fp);
            fseek(fp, 0, SEEK_END);
            for (int i = 0; i < DATALEN * BLOCKSZ / 2; ++i)
                fputc(tmp[i], fp);
        }

        bool compare(char *a, char *b) {
            for (int i = 0; i < DATALEN; ++i)
                if (a[i] < b[i]) return true;
            return false;
        }

        void assign(char *a, char *b) {
            for (int i = 0; i < DATALEN; ++i)
                a[i] = b[i];
        }
    
        bool cmp(char *s, int id) {
            fseek(fp, DATALEN * BLOCKSZ * id + DATALEN * (BLOCKSZ - 1), SEEK_SET);
            for (int i = 0; i < DATALEN; ++i) tmp[i] = fgetc(fp);
            return compare(s, tmp);
        }

        void insert(char* s) {
            for (size_t i = 0; i < next.size(); ++i) {
                if (i + 1 == next.size() || cmp(s, i)) {
                    fseek(fp, DATALEN * BLOCKSZ, SEEK_SET);
                    for (int j = 0; j < DATALEN * BLOCKSZ; ++j) tmp[j] = fgetc(fp);
                    for (int j = size[i] * DATALEN; j; j -= DATALEN) {
                        if (compare(tmp + j - DATALEN, s)) {
                            assign(tmp + j, s);
                            break;
                        }else assign(tmp + j, tmp + j - DATALEN);
                    }
                    size[i]++;
                    if (size[i] == BLOCKSZ) split(i);
                    return;
                }
            }
        }
    };
}

#endif
