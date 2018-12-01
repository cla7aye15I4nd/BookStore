#ifndef FINANCE_HPP
#define FINANCE_HPP

#include <algorithm>
namespace sjtu{
    using i64 = long long;
    void print(i64 x, FILE *fp) {
        for (int i = 0; i < 64; i += 8) 
            fputc(x >> i & 255, fp);
    }

    i64 input(FILE* fp) {
        i64 x = 0;
        for (int i = 0; i < 64; i += 8) 
            x |= (i64) fgetc(fp) << i;
        return x;
    }

    void create(const std::string file) {
        FILE *f = fopen(file.c_str(), "w");
        fclose(f);
    }
    
    class costSystem{
        static const int BLOCKSIZE = 2048;

        FILE *base;
        FILE *data;

        int p;
        i64 size;
        std::vector<i64> sum;
        
        int get_id(int size) {
            return size / BLOCKSIZE;
        }
        
        i64 get(int pos) {
            fseek(data, pos * 8, SEEK_SET);
            return input(data);
        }

        void write(int pos, i64 val) {
            fseek(data, pos * 8, SEEK_SET);
            print(val, data);
        }

        i64 calc(int id, int l, int r) {
            int lb = id * BLOCKSIZE, rb = lb + BLOCKSIZE - 1;
            if (l <= lb && rb <= r) return sum[id];
            else {
                i64 ret = 0;
                for (int i = std::max(l, lb); i <= std::min(r, rb); ++i)
                    ret += get(i);
                return ret;
            }
        }
        
    public:
        costSystem () = default;
        i64 count() { return size; }
        void init (const std::string file) {
            base = fopen((file + ".base.bin").c_str(), "r+");
            data = fopen((file + ".data.bin").c_str(), "r+");

            if (base == nullptr) {
                create(file + ".base.bin");
                create(file + ".data.bin");
                base = fopen((file + ".base.bin").c_str(), "r+");
                data = fopen((file + ".data.bin").c_str(), "r+");
                print(0LL, base);
                print(0LL, base);
            }

            rewind(base);
            size = input(base);
            sum.resize(size / BLOCKSIZE + 1);
            for (auto &v : sum)
                v = input(base);
        }
        virtual ~costSystem () {
            rewind(base);
            print(size, base);
            for (auto v : sum)
                print(v, base);
            fclose(base);
            fclose(data);
        }

        void append(i64 x) {
            write(++size, x);
            sum.back() += x;
            if (size % BLOCKSIZE == 0)
                sum.emplace_back(0);
        }

        i64 find(int time = -1) {
            if (time == -1) return std::accumulate(sum.begin(), sum.end(), 0LL);
            else {
                i64 ret = 0;
                int l = size - time + 1, r = size;
                for (int i = get_id(l); i <= get_id(r); ++i)
                    ret += calc(i, l, r);
                return ret;
            }
        }

        i64 getdata(int x) {
            return calc(get_id(x), x, x);
        }
    };
}

#endif
