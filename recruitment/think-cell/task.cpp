#include <iostream>
#include <random>
#include <ostream>

#include "interval-map.h"

class Value
{
    char a;
public:
    Value(char _a) { a = _a; }
    bool operator==(const Value &_val) const;
    bool operator==(const char &_val) const;
};

bool Value::operator==(const Value &_val) const
{
    return (a == _val.a);
}

bool Value::operator==(const char &_val) const
{
    return (a == _val);
}

class Key
{
    int a;
public:
    Key(int _a) { a = _a; }
    bool operator<(const Key &_key) const;
};

bool Key::operator<(const Key &_key) const
{
    return (a < _key.a);
}

void TestMapImpl(int test_c, int test_size, bool random_canon_check)
{
    std::cout << "NEW TEST" << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-test_size, test_size);

    
    interval_map<Key, Value> imap('A');

    std::vector<Value> manual;
    for (int i = 0; i < 6 * test_size; ++i)
        manual.push_back('A');

    for (int i = 0; i < test_c; ++i)
    {
        std::cout << "TEST INPUT " << i << ": " << std::endl;

        int l = dis(gen);
        int r = dis(gen);

        if (l > r)
        {
            std::swap(l, r);
        }

        char c = (char)(std::abs(dis(gen)) % 26 + 'A');

        std::cout << "\t" << l << " : " << r << " -- " << c << std::endl;

        for (int i = l; i < r; ++i)
            manual[i + (2 * test_size)] = c;
        imap.assign(Key(l), Key(r), Value(c));

        if (!random_canon_check || dis(gen) > 0)
        {
            if (!imap.check_canonicity())
            {
                std::cout << "ERROR: CANONICITY BROKEN!" << std::endl;
                return;
            }
        }

        for (int i = -test_size; i <= test_size; ++i)
        {
            Key k(i);
            if (!(imap[k] == manual[i + (2 * test_size)]))
            {
                return;
            }
        }
    }
}

int main()
{
    TestMapImpl(3000, 10000, false);
}