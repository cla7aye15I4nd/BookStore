#ifndef TREAP_HPP
#define TREAP_HPP

#include <random>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <functional>

template<typename DataType>
class Treap{
public:
    static const int MEMORY_SIZE = 5000000;
    
    std::default_random_engine randint;
    static int readint(std::istream& os) {
        int x;
        os >> x;
        return x;
    }
    
    struct Node{
        Node *ch[2];
        int val;
        int key;
    };

    using node = Node*;
    
    node newnode(int key) {
        top->ch[0] = top->ch[1] = nullptr;
        top->key = key;
        top->val = randint();
        return top++;
    }
    
    void rotate(node &u, int d) {
        node t = u->ch[d ^ 1];
        u->ch[d ^ 1] = t->ch[d];
        t->ch[d] = u;
        u = t;
    }

    void insert(node &u, int key) {
        if (u == nullptr) u = newnode(key);
        else {
            int d = get(u->key) < get(key);
            insert(u->ch[d], key);
            if (u->ch[d]->val > u->val)
                rotate(u, d ^ 1);
        }
    }

    void erase(node &u, int key) {
        if (u == nullptr) return;
        if (get(u->key) == get(key)) {
            if (u->ch[0] == nullptr) u = u->ch[1];
            else if (u->ch[1] == nullptr) u = u->ch[0];
            else {
                int d = u->ch[0]->val > u->ch[1]->val;
                rotate(u, d);
                erase(u->ch[d], key);
            }
        }else
            erase(u->ch[get(u->key) < get(key)], key);
    }

    int find(node u, const DataType &key) {
        if (u == nullptr) return -1;
        if (get(u->key) == key) return u->key;
        return find(u -> ch[get(u->key) > key], key);
    }
    
    void set(const std::string &file, auto _get) {
        get = _get;
        std::ifstream is(file);
        if (is.is_open()) {
            top = readint(is) + memory_pool;
            for (node ptr = memory_pool; ptr != top; ++ptr) {
                int x;

                x = readint(is); ptr->ch[0] = x != -1? x + memory_pool: nullptr;
                x = readint(is); ptr->ch[1] = x != -1? x + memory_pool: nullptr;
                is >> ptr->val >> ptr->key;
            }
            root = readint(is) + memory_pool;
            is.close();
        }
        os.open(file);
    }

    void find(node u, const DataType& left, const DataType& right, std::vector<int> &vec) {
        if (u == nullptr) return;
        DataType e = get(u->key);
        if (e < left) find (u->ch[1], left, right, vec);
        else if (e > right) find (u->ch[0], left, right, vec);
        else {
            find (u->ch[0], left, right, vec);
            vec.push_back(u->key);
            find (u->ch[1], left, right, vec);
        }
    }
    
    Treap () {
        memory_pool = new Node [MEMORY_SIZE];
        top = memory_pool;
        root = nullptr;
    }
    
    virtual ~Treap () {
        os << top - memory_pool << std::endl;
        for (node ptr = memory_pool; ptr != top; ++ptr) {
            os << (ptr->ch[0] ? ptr->ch[0] - memory_pool: -1) << ' '
               << (ptr->ch[1] ? ptr->ch[1] - memory_pool: -1) << ' '
               << ptr->val << ' '
               << ptr->key << std::endl;
        }
        os << root - memory_pool;
        os.close();
        delete [] memory_pool;
    }

    int find(const DataType& key) { return find(root, key); }
    void erase(int id) { erase(root, id); }
    void insert(int id) { insert(root, id); }
    std::vector<int> find(const DataType& left,
                          const DataType& right) {
        std::vector<int> vec;
        find(root, left, right, vec);
        return vec;
    }
    
private:
    node memory_pool, top, root;
    std::ofstream os;
    std::function<DataType(int)> get;
};

#endif
