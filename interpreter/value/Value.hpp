#ifndef VALUE_H
#define VALUE_H

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

protected:
    explicit Value(Value::Type type, int line) : type_(type), line_(line) {}
    Value::Type type_;
    int line_;

};

#endif