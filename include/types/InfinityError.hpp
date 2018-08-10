#include <stdexcept>

class InfinityError : public std::runtime_error {
public:
    explicit InfinityError(const std::string &what) :
        std::runtime_error(what) {
    }
    explicit InfinityError(const char* what) :
        std::runtime_error(what) {
    }
};