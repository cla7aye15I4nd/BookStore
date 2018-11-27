#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));
    fstream os;
    os.open("test.txt", ios::in | ios::out);
    //std::cerr << os.is_open() << '\n';
    int a;
    for (int i = 1; i < 10; ++i) {
        os.seekp(0, ios::end);
        for (int j = 1; j <= 5; ++j) {
            os << i;
        }
        os << '\n';
        os.seekg(6 * (rand() % i), ios::beg);
        os >> a;
        std::cerr << a << std::endl;
    }
    os.close();
    return 0;
}
