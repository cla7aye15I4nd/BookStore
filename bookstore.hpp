#ifndef BOOKSTORE_HPP
#define BOOKSTORE_HPP

#include "ext.hpp"
#include "database.hpp"
#include "SHA256.hpp"
#include "user.hpp"
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
    };
    
    class bookstore{
    private:
        userSystem user;

    public:
        bookstore () {}

        bool runCommand(const string& command) {
            parameter para = split(command);

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
                }
            }

            return true;
        }

        void run() {
            std::string command;

            while (true) {
                std::cerr << user.username << '@';
                std::getline(std::cin, command);
                if (!runCommand(command))
                    return;
                std::cerr << std::endl;             
            }
        }
    };
}

#endif
