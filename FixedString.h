#include <stdexcept>
#include <string>
#include <vector>

class FixedString {
 public:
    using TContainer = std::vector<char>;

    FixedString(const char* someString = "") {
        while (*someString != '\0') {
            data_.push_back(*someString);
            ++someString;
        }
        data_.push_back(*someString);
    }

    FixedString(const std::string& someString) {
        data_ = TContainer(someString.begin(), someString.end());
        data_.push_back('\0');
    }

    const size_t size() const {
        return data_.size() - 1;
    }

    const bool empty() const {
        return data_[0] == '\0';
    }

    const char& operator[](const size_t &index) const {
        return data_[index];
    }

    char& operator[](size_t index) {
        return data_[index];
    }

    const char& at(int index) {
        if (index < 0 || index >= size()) {
            throw std::out_of_range("You try get access to " + std::to_string(index + 1) +
                                        " symbol, but string length is " + std::to_string(size()));
        }
        return data_[index];
    }

 private:
    TContainer data_;
};
