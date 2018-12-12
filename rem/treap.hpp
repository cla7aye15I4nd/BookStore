#ifndef TREAP_HPP
#define TREAP_HPP

#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

template <typename DataType> class Treap {
public:
  std::default_random_engine randint;

  struct Node {
    int ch[2];
    int val;
    int key;
  };

  static const size_t node_size = sizeof(Node);

  using node = int;

  node newnode(int key) {
    int id;
    if (bin.empty()) {
      id = end;
      os.seekp(id * node_size);
      Node tmp = {-1, -1, (int)randint(), key};
      os.write(reinterpret_cast<char *>(&tmp), node_size);
      end++;
    } else {
      id = bin.back();
      bin.pop_back();
      os.seekp(id * node_size);
      Node tmp = {-1, -1, (int)randint(), key};
      os.write(reinterpret_cast<char *>(&tmp), node_size);
    }

    return id;
  }

  void write(int id, int pos, int val) {
    os.seekp(id * node_size + pos * sizeof(int));
    os.write(reinterpret_cast<char *>(&val), sizeof(int));
  }

  int read(int id, int pos) {
    int val;
    os.seekp(id * node_size + pos * sizeof(int));
    os.read(reinterpret_cast<char *>(&val), sizeof(int));
    return val;
  }

  void rotate(int id, int pos, int d) {
    node &&u = read(id, pos);
    node &&t = read(u, d ^ 1);
    write(u, d ^ 1, read(t, d));
    write(t, d, u);
    write(id, pos, t);
  }

  void insert(int id, int pos, const DataType &key, int key_id) {
    node &&u = read(id, pos);
    if (u == -1) {
      u = newnode(key_id);
      write(id, pos, u);
    } else {
      auto &&e = get(read(u, 3));
      int d = e < key;
      insert(u, d, key, key_id);
      if (read(read(u, d), 2) > read(u, 2))
        rotate(id, pos, d ^ 1);
    }
  }

  void erase(int id, int pos, const DataType &key) {
    node &&u = read(id, pos);
    if (u == -1)
      return;
    auto &&e = get(read(u, 3));
    if (e == key) {
      if (read(u, 0) == -1) {
        bin.push_back(u);
        write(id, pos, read(u, 1));
      } else if (read(u, 1) == -1) {
        bin.push_back(u);
        write(id, pos, read(u, 0));
      } else {
        int d = read(read(u, 0), 2) > read(read(u, 1), 2);
        rotate(id, pos, d);
        u = read(id, pos);
        erase(u, d, key);
      }
    } else
      erase(u, e < key, key);
  }

  int find(node u, const DataType &key) {
    if (u == -1)
      return -1;
    int &&id = read(u, 3);
    auto &&e = get(id);
    if (e == key)
      return id;
    return find(read(u, key > e), key);
  }

  void set(const std::string &file, auto _get) {
    get = _get;
    os.open(file);
    if (!os.is_open()) {
      os.open(file, std::ios::out);
      os.close();
      os.open(file);
      for (int i = 0, x = -1; i < 4; ++i) {
        os.write(reinterpret_cast<char *>(&x), sizeof(int));
      }
    }
    os.seekp(0, std::ios::end);
    end = os.tellp() / node_size;
  }

  void find(node u, const DataType &left, const DataType &right,
            std::vector<int> &vec) {
    Node t;
    if (u == -1)
      return;

    os.seekp(u * node_size);
    os.read(reinterpret_cast<char *>(&t), node_size);
    auto &&e = get(t.key);
    if (e < left)
      find(t.ch[1], left, right, vec);
    else if (e > right)
      find(t.ch[0], left, right, vec);
    else {
      find(t.ch[0], left, right, vec);
      vec.push_back(t.key);
      find(t.ch[1], left, right, vec);
    }
  }

  void find(node u, std::vector<int> &vec) {
    if (u == -1)
      return;
    Node t;
    os.seekp(u * node_size);
    os.read(reinterpret_cast<char *>(&t), node_size);

    find(t.ch[0], vec);
    vec.push_back(t.key);
    find(t.ch[1], vec);
  }

  Treap() {}

  virtual ~Treap() { os.close(); }

  int find(const DataType &key) { return find(read(0, 0), key); }
  void erase(int id) { erase(0, 0, get(id)); }
  void insert(int id) { insert(0, 0, get(id), id); }
  std::vector<int> find(const DataType &left, const DataType &right) {
    std::vector<int> vec;
    find(read(0, 0), left, right, vec);
    return vec;
  }
  std::vector<int> find() {
    std::vector<int> vec;
    find(read(0, 0), vec);
    return vec;
  }

private:
  int end;
  std::fstream os;
  std::vector<node> bin;
  std::function<DataType(int)> get;
};

#endif
