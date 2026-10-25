#include <iostream>
#include <string>
#include <algorithm>

class Text {
public:
    virtual void render(const std::string& text) {
        std::cout << text;
    }

    virtual ~Text() = default;
};

class Decorator : public Text {
protected:
    Text* text_;

public:
    explicit Decorator(Text* text) : text_(text) {}

    ~Decorator() override {
        delete text_;
    }
};

class Paragraph : public Decorator {
public:
    using Decorator::Decorator;

    void render(const std::string& text) override {
        std::cout << "<p>";
        text_->render(text);
        std::cout << "</p>";
    }
};

class Reversed : public Decorator {
public:
    using Decorator::Decorator;

    void render(const std::string& text) override {
        std::string reversed_text = text;
        std::reverse(reversed_text.begin(), reversed_text.end());
        text_->render(reversed_text);
    }
};

class Link : public Decorator {
public:
    using Decorator::Decorator;

    void render(const std::string& url, const std::string& text) {
        std::cout << "<a href=" << url << ">";
        text_->render(text);
        std::cout << "</a>";
    }
};

int main() {
    auto text_block = new Paragraph(new Text());
    text_block->render("Hello world");
    std::cout << '\n';
    delete text_block;

    auto reversed_block = new Reversed(new Text());
    reversed_block->render("Hello world");
    std::cout << '\n';
    delete reversed_block;

    auto link_block = new Link(new Text());
    link_block->render("netology.ru", "Hello world");
    std::cout << '\n';
    delete link_block;

    return 0;
}