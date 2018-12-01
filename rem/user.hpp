#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include "SHA256.hpp"

namespace sjtu{
    struct user_t{
        int level;
        string username;
        string password;

        user_t () {}
        user_t (int _level, const string& _username, const string& _password = "")
            :level(_level), username(_username), password(sha256sum(_password)) {}

        friend std::ostream& operator<< (std::ostream& os, const user_t& user) {
            os << user.level << ' ' << user.username << ' ' << user.password;
            return os;
        }

        friend std::istream& operator>> (std::istream& os, user_t& user) {
            os >> user.level >> user.username >> user.password;
            return os;
        }
    };

    class userSystem{
    private:
        int _level;
        naive_database<user_t> db;
        
    public:
        string username;

        int level() const{ return _level; }
        
        userSystem () : db("user/"){
            _level = 7;
            username = "root";
            if (!db.exist(sha256sum("root"))) {
                db.save(sha256sum("root"), user_t(7, "root", "sjtu"));
            }
        }
        
        void login(const string& userid, const string& passwd = "") {
            user_t aim;
            if (db.get(sha256sum(userid), aim)) {
                if (aim.level >= _level && aim.password != sha256sum(passwd))
                    error();
                else {
                    _level = aim.level;
                    username = aim.username;
                }
            } else
                error();
        }

        void logout() {
            if (_level == 0) error();
            else {
                _level = 0;
                username = GUEST;
            }
        }

        void useradd(const string& userid, const user_t& aim) {
            if (_level < 3 || aim.level >= _level || db.exist(sha256sum(userid)))
                error();
            else db.save(sha256sum(userid), aim);
        }

        void signup(const string& userid, const string& passwd, const string& name) {
            if (db.exist(sha256sum(userid))) error();
            else db.save(sha256sum(userid), user_t(1, name, passwd));
        }
        
        void erase(const string& userid) {
            if (_level < 7 || !db.erase(sha256sum(userid)))
                error();
        }

        void modify(const string& userid, const string& pw0, const string& pw1 = "") {
            user_t aim;
            if (_level >= 1 && db.get(sha256sum(userid), aim)) {
                if (_level == 7) aim.password = sha256sum(pw0);
                else if (aim.password != sha256sum(pw0)) {
                    error();
                    return;
                } else
                    aim.password = sha256sum(pw1);
                db.save(sha256sum(userid), aim);
            } else
                error();
        }

        void addlog(const string& s) {
            db.append(username, s);
        }

        void report(const string& name) {
            std::cout << "username : " << name << std::endl;
            db.print(name);
        }

        void report() { report(username); }
        void all() {
            string path = "user/";
            DIR* pDir;
            struct dirent* ptr;

            struct stat s;
            lstat(path.c_str(), &s);
            
            string subFile;
            pDir = opendir(path.c_str());
            while((ptr = readdir(pDir)) != 0){
                subFile = ptr -> d_name;
                if(subFile == "." || subFile == "..")
                    continue;
                auto vs = split(subFile, '.');
                if (vs[1] == "log")
                    report(vs[0]);
            }
            closedir(pDir);
        }
    };
}

#endif
