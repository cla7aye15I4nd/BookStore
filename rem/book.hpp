#ifndef BOOK_HPP
#define BOOK_HPP

#include <iostream>

namespace sjtu{
    using i64 = long long;
    
    struct book_t{
        string ISBN;
        string name;
        string author;
        string keyword;
        i64 price;
        int quantity;

        book_t () : price(0), quantity(0) {}
        
        void setISBN(const string& _ISBN) { ISBN = _ISBN; }
        void setName(const string& _name) { name = _name; }
        void setAuthor(const string& _author) { author = _author; }
        void setKeyWord(const string& _keyword) { ISBN = _keyword; }
        void setPrice(i64 _price) { price = _price; }
        bool buy(int q) {
            if (quantity < q)
                return false;
            quantity -= q;
            return true;
        }

        friend std::ostream& operator<< (std::ostream& os, const book_t& book) {
            os << book.ISBN << ' ' << book.name << ' ' << book.author << ' ' << book.keyword << ' ' << book.price << ' ' << book.quantity;
            return os;
        }

        friend std::istream& operator>> (std::istream& os, book_t& book) {
            os >> book.ISBN >> book.name >> book.author >> book.keyword >> book.price >> book.quantity;
            return os;
        }
    };

    class warehouse{
    private:
        string ISBN;
        naive_database<book_t> db;

    public:
        warehouse () : db("data/ISBN/") {}

        void select(const string& _ISBN) {
            ISBN = _ISBN;
            if (!db.exist(_ISBN))
                db.save(ISBN);
        }

        void import(int q, i64 tot_price) {
            book_t book;
            db.get(ISBN, book);
            book.quantity += q;
            db.save(ISBN, book);
        }
        
        void buy(const string& id, int q) {
            book_t book;
            if (db.get(id, book) && book.buy(q)) {
                db.save(id, book);
            } else
                error();
        }
    };
}

#endif
