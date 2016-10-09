#include <algorithm>
#include <iostream>
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

    FixedString(const TContainer& someContainer) {
        data_ = TContainer(someContainer.begin(), someContainer.end());
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

    const FixedString substr(size_t beginIndex, size_t length) const {
        return TContainer(data_.begin() + beginIndex, data_.begin() + length + beginIndex);
    }

    const FixedString substr(size_t beginIndex) const {
        return TContainer(data_.begin() + beginIndex, data_.end() - 1);
    }

    friend std::ostream& operator << (std::ostream &stream, const FixedString &object) {
        stream << object.data_.data();
        return stream;
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
        leftString += rightString;
        return leftString;
    }

    friend const bool operator < (const FixedString &leftString,
                                    const FixedString& rightString) {
        size_t minLength = std::min(leftString.size(), rightString.size());
        size_t diffPos = 0;
        while (diffPos < minLength && leftString[diffPos] == rightString[diffPos]) {
            ++diffPos;
        }

        if (diffPos == minLength) {
            return leftString.size() < rightString.size();
        } else {
            return leftString[diffPos] > rightString[diffPos];
        }
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
        return !(leftString < rightString);
    }

    friend const bool operator > (const FixedString& leftString,
                                    const FixedString& rightString) {
        return !(leftString < rightString) && leftString != rightString;
    }

    friend const bool operator <= (const FixedString& leftString,
                                    const FixedString& rightString) {
        return (leftString < rightString) || leftString == rightString;
    }

    const char* c_str() const {
        return data_.data();
    }

 private:
    TContainer data_;
};
