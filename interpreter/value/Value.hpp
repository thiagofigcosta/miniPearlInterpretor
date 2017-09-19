#ifndef VALUE_H
#define VALUE_H

class SyntacticalAnalysis;

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

protected:
    explicit Value(Value::Type type, int line) : type_(type), line_(line) {}

private:
   Value::Type type_;
   int line_;

};

#endif
