#include <iostream>
#include <string>
#include <memory>
#include <cstddef>

class VeryHeavyDatabase {
public:
    virtual std::string GetData(const std::string& key) {
        return "value";
    }

    virtual ~VeryHeavyDatabase() = default;
};

class OneShotDB : public VeryHeavyDatabase {
private:
    VeryHeavyDatabase* real_object_;
    std::size_t shots_;

public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, std::size_t shots = 1)
        : real_object_(real_object), shots_(shots) {}

    std::string GetData(const std::string& key) override {
        if (shots_ == 0) {
            return "error";
        }

        --shots_;
        return real_object_->GetData(key);
    }
};

int main() {
    auto real_db = VeryHeavyDatabase();
    auto limit_db = OneShotDB(std::addressof(real_db), 2);

    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;

    return 0;
}