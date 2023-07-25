#include <vector>
#include <random>

char randomChar() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis('a', 'z');
    return static_cast<char>(dis(gen));
}

std::string generatePangram() {
  std::string pangram;
  for(char c = 'a'; c <= 'z'; ++c)
    pangram += c;
  std::random_shuffle(pangram.begin(), pangram.end());
  
  while (pangram.length() < 46)
    pangram += randomChar();
  
  return pangram;
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
  
    It(random_tests) {
        for (int i = 0; i < 50; ++i) {
            std::string randomString = generatePangram();

            if (i % 2 == 1) {
                char removedChar = randomChar();
                randomString.erase(std::remove_if(randomString.begin(), randomString.end(), [removedChar](char c) { return c == removedChar; }), randomString.end());
            }

            Assert::That(is_pangram(randomString), Equals(i % 2 == 0));
        }
    }
};
