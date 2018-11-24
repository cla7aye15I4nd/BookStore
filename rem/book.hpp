#ifndef BOOK_HPP
#define BOOK_HPP

#include <iostream>
#include "string.hpp"

namespace sjtu{
    using i64 = long long;
    
    struct book {
        int id;
        cstring<20> ISBN;
        
    };
}

#endif
