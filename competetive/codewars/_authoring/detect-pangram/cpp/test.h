#include <vector>
#include <random>
#include <string>
#include <algorithm>

Describe(fixed_tests) {
    It(test_pangrams) {
      std::vector<std::string> cases = {
            "The quick brown fox jumps over the lazy dog.",
            "Cwm fjord bank glyphs vext quiz",
            "Pack my box with five dozen liquor jugs.",
            "How quickly daft jumping zebras vex.",
            "ABCD45EFGH,IJK,LMNOPQR56STUVW3XYZ"
      };
      
      for (auto &p : cases)
        Assert::That(is_pangram(p), Equals(true), [&]() { return "Incorrect answer for " + p; });
    };
  
    It(test_non_pangrams) {
      std::vector<std::string> cases = {
            "This isn't a pangram!",
            "abcdefghijklm opqrstuvwxyz",
            "Aacdefghijklmnopqrstuvwxyz",
            ""
      };
      
      for (auto &p : cases)
          Assert::That(is_pangram(p), Equals(false), [&]() { return "Incorrect answer for: " + p; });
    };
};

Describe(Random) {
private:
  std::string ascii;
  std::string filler = " 0123456789!,.-_";
  std::random_device seeder;
  std::mt19937 engine{ seeder() };
  std::uniform_int_distribution<int> rand_transform_val {0, 4};
  std::uniform_int_distribution<char> rand_letter { 'a', 'z' };
  std::uniform_int_distribution<int> rand_ascii_remove_count {1, 25};
  std::uniform_int_distribution<int> rand_small_test_size { 30, 50 };
  std::uniform_int_distribution<int> rand_large_test_size { 10000, 50000 };
  
  std::string generate_test(int length, bool valid) {
    std::string test_ascii = ascii;
    std::shuffle(test_ascii.begin(), test_ascii.end(), engine);
    
    if (!valid) {
      int chars_to_remove = rand_ascii_remove_count(engine);
      test_ascii.erase(0, chars_to_remove);
    }
    
    std::string test_string = test_ascii;
    test_string.resize(length);

    auto test_ascii_size = test_ascii.size();
    test_ascii += filler;
    std::uniform_int_distribution<size_t> rand_test_char_idx { 0, test_ascii.size() - 1 };
    std::generate(test_string.begin() + test_ascii_size, test_string.end(), [&]() { return test_ascii[rand_test_char_idx(engine)]; });
    
    std::transform(test_string.begin(), test_string.end(), test_string.begin(), [&](char c) -> char {
      if (rand_transform_val(engine) == 0)
        return std::toupper(c);
      return c;
    });
    
    std::shuffle(test_string.begin(), test_string.end(), engine);
    return test_string;
  }
public:
    void SetUp() {
      ascii.resize(26);
      std::iota(ascii.begin(), ascii.end(), 'a');
    };
  
    It(random_tests_small) {
      for(int i = 0; i < 25; ++i) {
        std::string test_string = generate_test(rand_small_test_size(engine), true);
        Assert::That(is_pangram(test_string), Equals(true), [&]() { return "Incorrect answer for " + test_string; });
      }
      for(int i = 0; i < 25; ++i) {
        std::string test_string = generate_test(rand_small_test_size(engine), false);
        Assert::That(is_pangram(test_string), Equals(false), [&]() { return "Incorrect answer for " + test_string; });
      }
    };

    It(random_tests_large) {
      for(int i = 0; i < 25; ++i) {
        Assert::That(is_pangram(generate_test(rand_large_test_size(engine), true)), Equals(true));
      }
      for(int i = 0; i < 25; ++i) {
        Assert::That(is_pangram(generate_test(rand_large_test_size(engine), false)), Equals(false));
      }
    };
};
