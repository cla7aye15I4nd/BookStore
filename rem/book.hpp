#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include <vector>
#include <cstdio>
#include "database.hpp"
#include "treap.hpp"

namespace sjtu{
    struct book{
        using string = std::string;
    
        string ISBN;
        string name;
        string author;

        long long price, count;
        std::vector<string> keyword;

        static const int BOOKSIZE = 200;
        static char outbuf[BOOKSIZE];

        string combineName() const{ return name + ISBN; }
        string combineAuthor() const{ return author + ISBN; }
        string combineKeyword(int x) const{ return keyword[x] + ISBN; }
        string combinePrice() const{ return std::to_string(price) + ISBN; }

        friend std::ostream& operator<< (std::ostream& os, const book& u) {
            int last = 0;
            last = sprintf(outbuf, "%s %s %s %lld %lld %lu",
                           u.ISBN.c_str(), u.name.c_str(), u.author.c_str(), u.price, u.count, u.keyword.size());
            for (auto &s : u.keyword)
                last += sprintf(outbuf + last, " %s", s.c_str());
            for (int i = last; i < BOOKSIZE - 1; ++i)
                outbuf[i] = ' ';
            outbuf[BOOKSIZE - 1] = '\n';
            os << outbuf;
            return os;
        }

        friend std::istream& operator<< (std::istream& is, book& u) {
            int count = 0;
            is >> u.ISBN >> u.name >> u.author >> u.price >> u.count >> count;
            u.keyword.resize(count);
            for (auto &s : u.keyword)
                is >> s;
            return is;
        }
    };

    class bookSystem : private DataBase<book, book::BOOKSIZE>{
    public:
        bookSystem () : DataBase<book, book::BOOKSIZE>("book.bin") {
            isbn.set("isbn.bin", [&](int x) { return get(x).ISBN; });
            name.set("name.bin", [&](int x) { return get(x).combineName(); });
            author.set("author.bin", [&](int x) { return get(x).combineAuthor(); });
            keyword.set("keyword.bin", [&](int x) { return get(x / 100).combineKeyword(x % 100); });
            price.set("price.bin", [&](int x) { return get(x).combinePrice(); });
        }

        void select(std::string isbn) {
            int id = isbn.find(isbn);
            if (id == -1) error();
            else bk = get(id);
        }

        bool check(const std::string &para,
                   const std::string &tag) {
            return para.size() >= tag.size() && para.substr(0, tag.size()) == tag;
        }

        void modifyISBN() {
            
        }
        
        void modify(std::string para) {
            if (check(para, "-ISBN=")) modifyISBN();
        }
    
    private:
        Treap<std::string> isbn, name, author, keyword, price;
        book bk;
    };

}
#endif
