#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class FixedString {
 public:
    using TContainer = std::vector<char>;

    FixedString(const char* someString = "") {
        const char* endString = someString;
        for (; *endString != '\0'; ++endString) {
        }
        data_ = TContainer(someString, endString + 1);
    }

    FixedString(const std::string& someString) :
            data_(someString.begin(), someString.end()) {
        data_.push_back('\0');
    }

    FixedString(const TContainer& someContainer) :
            data_(someContainer.begin(), someContainer.end()) {
        data_.push_back('\0');
    }

    const size_t size() const {
        return data_.size() - 1;
    }

    const bool empty() const {
        return size() == 0;
    }

    const char& operator[](const size_t &index) const {
        return data_[index];
    }

    char& operator[](size_t index) {
        return data_[index];
    }

    const char& at(size_t index) {
        if (index >= size()) {
            throw std::out_of_range("You try get access to " + std::to_string(index + 1) +
                                        " symbol, but string length is " + std::to_string(size()));
        }
        return data_[index];
    }

    const FixedString substr(size_t beginIndex, size_t length) const {
        return TContainer(data_.begin() + beginIndex, data_.begin() + length + beginIndex);
    }

    const FixedString substr(size_t beginIndex) const {
        return TContainer(data_.begin() + beginIndex, data_.end() - 1);
    }

    friend std::ostream& operator << (std::ostream &stream, const FixedString &object) {
        return stream << object.data_.data();
    }

    const TContainer::const_iterator begin() const {
        return data_.begin();
    }

    const TContainer::const_iterator end() const {
        return data_.end() - 1;
    }

    TContainer::iterator begin() {
        return data_.begin();
    }

    TContainer::iterator end() {
        return data_.end() - 1;
    }

    FixedString& operator += (const FixedString& rightString) {
        size_t oldLength = size();
        data_.resize(size() + rightString.size() + 1);
        std::copy(rightString.begin(), rightString.end(), begin() + oldLength);
        data_.back() = '\0';

        return *this;
    }

    friend const FixedString operator + (FixedString leftString,
                                            const FixedString &rightString) {
        return leftString += rightString;
    }

    friend const bool operator < (const FixedString &leftString,
                                    const FixedString& rightString) {
        return leftString.data_ < rightString.data_;
    }

    friend const bool operator == (const FixedString& leftString,
                                    const FixedString& rightString) {
        return leftString.data_ == rightString.data_;
    }

    friend const bool operator != (const FixedString& leftString,
                                    const FixedString& rightString) {
        return leftString.data_ != rightString.data_;
    }

    friend const bool operator >= (const FixedString& leftString,
                                    const FixedString& rightString) {
        return leftString.data_ >= rightString.data_;
    }

    friend const bool operator > (const FixedString& leftString,
                                    const FixedString& rightString) {
        return leftString.data_ > rightString.data_;
    }

    friend const bool operator <= (const FixedString& leftString,
                                    const FixedString& rightString) {
        return leftString.data_ > rightString.data_;
    }

    const char* c_str() const {
        return data_.data();
    }

 private:
    TContainer data_;
};
