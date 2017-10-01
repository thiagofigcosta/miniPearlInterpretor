#ifndef VALUE_H
#define VALUE_H
#include <string>
class Value {
public:
    enum Type {
        String,
        Integer,
        List,
        Hash
    };

    virtual ~Value() {}

    Value::Type type() { return type_; }
    int line() const { return type_; }
    static bool cmp(Value *a, Value *b);
    static std::string to_string(int v);
    static int to_int(std::string v);
protected:
    explicit Value(Value::Type type, int line) : type_(type), line_(line) {}
    Value::Type type_;
    int line_;

};

#endif
