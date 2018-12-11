#ifndef BOOKSTORE_HPP
#define BOOKSTORE_HPP

#include "rem/ext.hpp"
#include "rem/naive_database.hpp"
#include "rem/database.hpp"
#include "rem/SHA256.hpp"
#include "rem/user.hpp"
#include "rem/book.hpp"
#include "rem/finance.hpp"

#include <map>

namespace sjtu{
    static std::map<std::string, int> cmd = {
        {"exit", -1},
        {"su", 0},
        {"logout", 1},
        {"useradd", 2},
        {"register", 3},
        {"delete", 4},
        {"passwd", 5},
        {"select", 6},
        {"modify", 7},
        {"import", 8},
        {"show", 9},
        {"buy", 10},
        {"load", 11},
        {"report", 12},
        {"log", 13},
    };
    
    class bookstore{
    private:
        userSystem user;
        bookSystem book;
        costSystem in, out;
        
    public:
        bookstore () {
            in.init("in");
            out.init("out");
        }
        
        bool runCommand(const string& command, std::ifstream &is) {
            parameter para = split(command);

            bool flag = true;
            try {
                if (!cmd.count(para.front()))
                    error();
                else {
                    switch (cmd[para.front()]) {
                    case -1:
                        return false;
                    case 0:
                        if (para.size() < 2 || para.size() > 3) error();
                        else para.size() == 2 ? user.login(para[1]): user.login(para[1], para[2]);
                        break;
                    case 1:
                        if (para.size() != 1) error();
                        else user.logout();
                        break;
                    case 2:
                        if (para.size() != 5) error();
                        else user.useradd(para[1], user_t(to_int(para[3]), para[4], para[2]));
                        break;
                    case 3:
                        if (para.size() != 4) error();
                        else user.signup(para[1], para[2], para[3]);
                        break;
                    case 4:
                        if (para.size() != 2) error();
                        else user.erase(para[1]);
                        break;
                    case 5:
                        if (para.size() < 3 || para.size() > 4) error();
                        else para.size() == 3 ? user.modify(para[1], para[2]) : user.modify(para[1], para[2], para[3]);
                        break;
                    case 6:
                        if (para.size() != 2 || user.level() < 3) error();
                        else book.select(para[1]);
                        break;
                    case 7:
                        if (para.size() < 2 || user.level() < 1) error();
                        else {
                            para.erase(para.begin());
                            book.modify(para);
                        }
                        break;
                    case 8:
                        if (para.size() != 3 || user.level() < 3) error();
                        else {
                            book.import(to_int(para[1]), to_int_100(para[2]), in, out);
                        }
                        break;
                    case 9:
                        if (user.level() < 1) error();
                        else if (para.size() == 1) book.show();
                        else if (para[1] == "finance") {
                            if (para.size() > 3) error();
                            if (para.size() == 2) {
                                std::cout << "+ ";
                                format_print(in.find(-1));
                                std::cout << " - ";
                                format_print(out.find(-1));
                                std::cout << std::endl;
                            } else {
                                int t = to_int(para[2]);
                                std::cout << "+ ";
                                format_print(in.find(t));
                                std::cout << " - ";
                                format_print(out.find(t));
                                std::cout << std::endl;
                            }
                        }
                        else book.show(para[1]);
                        break;
                    case 10:
                        if (user.level() < 1 || para.size() != 3) error();
                        else {
                            book.buy(para[1], to_int(para[2]), in, out);
                        }
                        break;
                    case 11:
                        is.open(para[1]);
                        break;
                    case 12:
                        if (para.size() == 1) error();
                        else if (para[1] == "myself") {
                            if (user.level() >= 3) user.report();
                            else error();
                        } else if (para[1] == "employee") {
                            if (user.level() >= 7) user.all();
                            else error();
                        } else if (para[1] == "finance") {
                            for (int i = 0; i < in.count(); ++i) {
                                std::cout << " + "; format_print(in.getdata(i));
                                std::cout << " - "; format_print(out.getdata(i));
                                std::cout << std::endl;
                            }
                        } else error();
                        break;
                    case 13:
                        if (user.level() < 7) error();
                        else {
                            user.all();
                            std::cout << std::endl;
                            for (int i = 0; i < in.count(); ++i) {
                                std::cout << " + "; format_print(in.getdata(i));
                                std::cout << " - "; format_print(out.getdata(i));
                                std::cout << std::endl;
                            }
                        }
                        break;
                    default:
                        error();
                    }
                }
            } catch (...) { flag = false; }

            if (flag && user.level() >= 3) 
                user.addlog(command);

            return true;
        }

        void run() {
            std::string command;

            std::ifstream is;

            is.open("command.txt");
            while (true) {
#ifdef USER
                std::cerr << user.username << '@';
#endif
                if (is.is_open()) std::getline(is, command);
                else std::getline(std::cin, command);
                if (!runCommand(command, is))
                    return;
#ifdef USER
                std::cerr << std::endl;
#endif
                if (is.is_open() && is.eof()) is.close();
            }
        }
    };
}

#endif
