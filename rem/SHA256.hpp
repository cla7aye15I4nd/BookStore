#ifndef SHA256_HPP
#define SHA256_HPP

#include <string>

namespace sjtu {
using byte_t = uint8_t;
using word_t = uint32_t;

static constexpr word_t H[] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19,
};

static constexpr word_t KEY[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};

inline word_t ch(word_t x, word_t y, word_t z) { return (x & y) ^ (~x & z); }
inline word_t maj(word_t x, word_t y, word_t z) {
  return (x & y) ^ (x & z) ^ (y & z);
}
inline word_t rotr(word_t x, std::size_t n) {
  return (x >> n) | (x << (32 - n));
}
inline word_t SIGMA0(word_t x) {
  return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}
inline word_t SIGMA1(word_t x) {
  return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}
inline word_t sigma0(word_t x) { return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3); }
inline word_t sigma1(word_t x) { return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10); }
inline byte_t hex(byte_t x) { return x < 10 ? x + 48 : x + 87; }

struct sha256_engine {
  word_t w[8], x[64];
  word_t a, b, c, d, e, f, g, h, t0, t1;

  void _sha256sum(word_t *unit) {
    for (int i = 0; i < 16; ++i)
      x[i] = unit[i];
    for (int i = 16; i < 64; ++i)
      x[i] = sigma1(x[i - 2]) + x[i - 7] + sigma0(x[i - 15]) + x[i - 16];

    for (int i = 0; i < 8; ++i)
      (&a)[i] = w[i];
    for (int i = 0; i < 64; ++i) {
      t0 = h + SIGMA1(e) + ch(e, f, g) + KEY[i] + x[i];
      t1 = SIGMA0(a) + maj(a, b, c);
      h = g;
      g = f;
      f = e;
      e = d + t0;
      d = c;
      c = b;
      b = a;
      a = t0 + t1;
    }

    for (int i = 0; i < 8; ++i)
      w[i] += (&a)[i];
  }

  std::string sha256sum(const std::string &message) {
    std::copy(H, H + 8, w);

    size_t length = (message.length() / 64 + 1) * 64;
    byte_t *tmp = new byte_t[length];

    std::fill(tmp, tmp + length, 0);
    for (size_t i = 0; i < message.length(); ++i)
      tmp[i] = message[i];
    tmp[message.length()] = 0x80;
    for (int i = 0; i < 8; ++i)
      tmp[length - i - 1] = 8 * message.length() >> i * 8;

    word_t *plain = (word_t *)tmp;
    for (size_t i = 0, j = 0; i < length; i += 4, ++j)
      plain[j] =
          (tmp[i] << 24) | (tmp[i + 1] << 16) | (tmp[i + 2] << 8) | tmp[i + 3];

    size_t pack_cnt = length >> 6;
    for (size_t i = 0; i < pack_cnt; ++i)
      _sha256sum(plain + i * 16);

    std::string code(64, 0);
    for (size_t i = 0; i < 8; ++i)
      for (size_t j = 0; j < 8; ++j)
        code[i << 3 | j] = hex((w[i] >> (32 - (j + 1) * 4)) & 15);

    delete[] tmp;
    return code;
  }
};

std::string sha256sum(const std::string &message) {
  return sha256_engine().sha256sum(message);
}
} // namespace sjtu

#endif
