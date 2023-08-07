#include <vector>
#include <random>
#include <string>
#include <algorithm>

char randomChar() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis('a', 'z');
    return static_cast<char>(dis(gen));
}

std::string generatePangram(size_t length) {
    std::string pangram;
    for(char c = 'a'; c <= 'z'; ++c)
        pangram += c;
    std::random_shuffle(pangram.begin(), pangram.end());
    
    while (pangram.length() < length) {
        char ch = randomChar();
        if (std::rand() % 10 == 0) {
            const std::string punctuation = "!@#$%^&*()_-+={}[]|:;<>,.?/~";
            pangram += punctuation[std::rand() % punctuation.size()];
        } else if (std::rand() % 6 == 0) {
            pangram += ' ';
        } else {
            pangram += randomChar();
        }
    }
    
    return pangram;
}

void randomTestCase(int size, int count) {
    for (int i = 0; i < count; ++i) {
        std::string randomString = generatePangram(size);

        if (i % 2 == 1) {
            char removedChar = randomChar();
            randomString.erase(std::remove_if(randomString.begin(), randomString.end(), [removedChar](char c) { return c == removedChar; }), randomString.end());
        }

        for(auto &c : randomString)
            if (std::rand() % 3 == 0)
                c = toupper(c);

        Assert::That(is_pangram(randomString), Equals(i % 2 == 0));
    }
}

Describe(fixed_tests)
{
    It(test_pangrams)
    {
      std::vector<std::string> cases = {
            "The quick brown fox jumps over the lazy dog.",
            "Cwm fjord bank glyphs vext quiz",
            "Pack my box with five dozen liquor jugs.",
            "How quickly daft jumping zebras vex.",
            "ABCD45EFGH,IJK,LMNOPQR56STUVW3XYZ"
      };
      
      for (auto &p : cases)
        Assert::That(is_pangram(p), Equals(true));
    };
  
    It(test_non_pangrams)
    {
      std::vector<std::string> cases = {
            "This isn't a pangram!",
            "abcdefghijklm opqrstuvwxyz",
            "Aacdefghijklmnopqrstuvwxyz"
      };
      
      for (auto &p : cases)
          Assert::That(is_pangram(p), Equals(false));
    };
};

Describe(Random) {
    It(random_tests_small) {
        randomTestCase(100, 46);
    };

    It(random_tests_large) {
        randomTestCase(100, 100000);
    };

    It(random_tests_larger) {
        randomTestCase(50, 1000000);
    }
};
