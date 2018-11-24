#ifndef STRING_HPP
#define STRING_HPP

#include <cstring>

namespace sjtu{
    template <int length>
    class cstring {
        char *s;

    public:
        cstring () : s(new char [length]) {}
        virtual ~cstring() {
            delete [] s;
        }

        char& operator [] (int x) { return s[x]; }
        const char& operator [] (int x) const{ return s[x]; }
        int size() const { return length; }
        
        bool operator < (const cstring& t) const{
            for (int i = 0; i < length; ++i)
                if (s[i] < t[i]) return true;
            return false;
        }

        void operator = (const cstring& t) {
            for (int i = 0; i < length; ++i)
                s[i] = t[i];
        }

        void operator = (char* t) const{
            int size = strlen(t);
            for (int i = 0; i < length; ++i)
                s[i] = i < size ? t[i]: 0;
        }
    };
};

#endif
