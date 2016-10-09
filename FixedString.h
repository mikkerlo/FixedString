#include <vector>

class FixedString {
 public:
    FixedString(const char* str) {
        while (*str != '\0') {
            data_.push_back(*str);
        }
        data_.push_back(*str);
    }

 private:
    std::vector<char> data_;
};
