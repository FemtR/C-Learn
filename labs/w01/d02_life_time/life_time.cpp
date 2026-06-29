#include <iostream>
#include <string>
#include <utility>

class Tracer {
public:
    explicit Tracer(std::string name) : name_(std::move(name)) {
        std::cout << "construct: " << name_ << '\n';
    }

    ~Tracer() {
        std::cout << "destruct: " << name_ << '\n';
    }

private:
    std::string name_;
};

void LocalObject() {
    Tracer a("local_a");
    Tracer b("local_b");
}

void NestedScope() {
    Tracer a("nested_scope_a");
    {
        Tracer b("nested_scope_b");
        Tracer c("nested_scope_c");
    }
    Tracer d("nested_scope_d");
}

void HeapObject() {
    Tracer* p = new Tracer("heap object");
    delete p;
}

void StaticObject() {
    static Tracer s("static object");
}

int main() {
    LocalObject();
    NestedScope();
    HeapObject();
    StaticObject();
    StaticObject();
    return 0;
}
