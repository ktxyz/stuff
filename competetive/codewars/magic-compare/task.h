#include <iostream>

#ifdef LOCAL_TASK
    #define LOG(x) std::cout << x << std::endl
#else
    #define LOG(x)
#endif

template<class T>
class MagicCompare {
    T value_;
    bool expr_val_ = true;
public:
    MagicCompare() = default;
    MagicCompare(const MagicCompare<T>& other) : value_(other.value_), expr_val_(other.expr_val_) {
        LOG("Copy constructed with value: " << value_);
    }

    MagicCompare(T value) : value_(value) {
        LOG("Constructed with value: " << value_);
    }

    MagicCompare(T value, bool expr_val) : value_(value), expr_val_(expr_val) {
        LOG("Constructed with value: " << value_ << " and expression value: " << expr_val_);
    }

    bool GetExpr() const { return expr_val_; }
    void AndExpr(bool expr) {
        LOG("AndExpr called with: " << expr << ". Previous value was: " << expr_val_);
        expr_val_ = expr_val_ && expr;
    }
    T GetValue() const { return value_; }

    operator bool() const {
        return expr_val_;
    }

    operator T() const {
        return value_;
    }

    MagicCompare<T>& operator++() {
        ++value_;
        return *this;
    }

    MagicCompare<T>& operator--() {
        --value_;
        return *this;
    }

    MagicCompare<T>& operator+=(T rhs) {
        value_ += rhs;
        return *this;
    }

    MagicCompare<T>& operator-=(T rhs) {
        value_ -= rhs;
        return *this;
    }

    MagicCompare<T>& operator=(T rhs) {
        value_ = rhs;
        return *this;
    }

    MagicCompare<T> operator+(T rhs) {
        LOG("Addition called with value: " << rhs);
        MagicCompare<T> temp(rhs);
        temp.AndExpr(expr_val_ && value_ + rhs);
        return temp;
    }

    MagicCompare<T> operator-(T rhs) {
        LOG("Subtraction called with value: " << rhs);
        MagicCompare<T> temp(rhs);
        temp.AndExpr(expr_val_ && value_ - rhs);
        return temp;
    }

    MagicCompare<T> operator+(const MagicCompare<T>& rhs) {
        LOG("Addition called with value: " << rhs.GetValue());
        MagicCompare<T> temp = rhs;
        temp.AndExpr(expr_val_ && value_ + rhs.GetValue());
        return temp;
    }

    MagicCompare<T> operator-(const MagicCompare<T>& rhs) {
        LOG("Subtraction called with value: " << rhs.GetValue());
        MagicCompare<T> temp = rhs;
        temp.AndExpr(expr_val_ && value_ - rhs.GetValue());
        return temp;
    }

    MagicCompare<T> operator<(const MagicCompare<T>& rhs) {
        LOG("Less than comparison: " << value_ << " < " << rhs.GetValue());
        MagicCompare<T> temp = rhs;
        temp.AndExpr(expr_val_ && value_ < rhs.GetValue());
        return temp;
    }

    MagicCompare<T> operator>(const MagicCompare<T>& rhs) {
        LOG("Greater than comparison: " << value_ << " > " << rhs.GetValue());
        MagicCompare<T> temp = rhs;
        temp.AndExpr(expr_val_ && value_ > rhs.GetValue());
        return temp;
    }

    MagicCompare<T> operator<(T rhs) {
        LOG("Less than comparison: " << value_ << " < " << rhs);
        MagicCompare<T> temp(rhs);
        temp.AndExpr(expr_val_ && value_ < rhs);
        return temp;
    }

    MagicCompare<T> operator>(T rhs) {
        LOG("Greater than comparison: " << value_ << " > " << rhs);
        MagicCompare<T> temp(rhs);
        temp.AndExpr(expr_val_ && value_ > rhs);
        return temp;
    }

    MagicCompare<T> operator==(T rhs) {
        LOG("Equal comparison: " << value_ << " == " << rhs);
        MagicCompare<T> temp(rhs);
        temp.AndExpr(expr_val_ && value_ == rhs);
        return temp;
    }

    MagicCompare<T> operator!=(T rhs) {
        LOG("Not equal comparison: " << value_ << " != " << rhs);
        MagicCompare<T> temp(rhs);
        temp.AndExpr(expr_val_ && value_ != rhs);
        return temp;
    }

    MagicCompare<T> operator<=(const MagicCompare<T>& rhs) {
        LOG("Less than or equal comparison: " << value_ << " <= " << rhs.GetValue());
        MagicCompare<T> temp = rhs;
        temp.AndExpr(expr_val_ && value_ <= rhs.GetValue());
        return temp;
    }

    MagicCompare<T> operator>=(const MagicCompare<T>& rhs) {
        LOG("Greater than or equal comparison: " << value_ << " >= " << rhs.GetValue());
        MagicCompare<T> temp = rhs;
        temp.AndExpr(expr_val_ && value_ >= rhs.GetValue());
        return temp;
    }

    MagicCompare<T> operator<=(T rhs) {
        LOG("Less than or equal comparison: " << value_ << " <= " << rhs);
        MagicCompare<T> temp(rhs);
        temp.AndExpr(expr_val_ && value_ <= rhs);
        return temp;
    }

    MagicCompare<T> operator>=(T rhs) {
        LOG("Greater than or equal comparison: " << value_ << " >= " << rhs);
        MagicCompare<T> temp(rhs);
        temp.AndExpr(expr_val_ && value_ >= rhs);
        return temp;
    }

    MagicCompare<T> operator*(const MagicCompare<T>& other) const {
        return MagicCompare<T>(value_ * other.value_, this->GetExpr() && other.GetExpr());
    }

    friend MagicCompare<T> operator*(const T& lhs, const MagicCompare<T>& rhs) {
        return MagicCompare<T>(lhs * rhs.value_, rhs.GetExpr());
    }

    friend MagicCompare<T> operator*(const MagicCompare<T>& lhs, const T& rhs) {
        return MagicCompare<T>(lhs.value_ * rhs, lhs.GetExpr());
    }
};

template<class T>
MagicCompare<T> operator!=(T lhs, const MagicCompare<T>& rhs) {
    LOG("Global Not equal comparison: " << lhs << " != " << rhs.GetValue());
    MagicCompare<T> temp = rhs;
    temp.AndExpr(lhs != rhs.GetValue());
    return temp;
}

template<class T>
MagicCompare<T> operator==(T lhs, const MagicCompare<T>& rhs) {
    LOG("Global Equal comparison: " << lhs << " == " << rhs.GetValue());
    MagicCompare<T> temp = rhs;
    temp.AndExpr(lhs == rhs.GetValue());
    return temp;
}

template<class T>
MagicCompare<T> operator<(T lhs, const MagicCompare<T>& rhs) {
    LOG("Global Less than comparison: " << lhs << " < " << rhs.GetValue());
    MagicCompare<T> temp = rhs;
    temp.AndExpr(lhs < rhs.GetValue());
    return temp;
}

template<class T>
MagicCompare<T> operator>(T lhs, const MagicCompare<T>& rhs) {
    LOG("Global Greater than comparison: " << lhs << " > " << rhs.GetValue());
    MagicCompare<T> temp = rhs;
    temp.AndExpr(lhs > rhs.GetValue());
    return temp;
}

template<class T>
MagicCompare<T> operator!=(const MagicCompare<T>& lhs, T rhs) {
    LOG("Global Not equal comparison (reversed): " << lhs.GetValue() << " != " << rhs);
    MagicCompare<T> temp(rhs);
    temp.AndExpr(lhs.GetExpr() && lhs.GetValue() != rhs);
    return temp;
}

template<class T>
MagicCompare<T> operator==(const MagicCompare<T>& lhs, T rhs) {
    LOG("Global Equal comparison (reversed): " << lhs.GetValue() << " == " << rhs);
    MagicCompare<T> temp(rhs);
    temp.AndExpr(lhs.GetExpr() && lhs.GetValue() == rhs);
    return temp;
}

template<class T>
MagicCompare<T> operator<(const MagicCompare<T>& lhs, T rhs) {
    LOG("Global Less than comparison (reversed): " << lhs.GetValue() << " < " << rhs);
    MagicCompare<T> temp(rhs);
    temp.AndExpr(lhs.GetExpr() && lhs.GetValue() < rhs);
    return temp;
}

template<class T>
MagicCompare<T> operator>(const MagicCompare<T>& lhs, T rhs) {
    LOG("Global Greater than comparison (reversed): " << lhs.GetValue() << " > " << rhs);
    MagicCompare<T> temp(rhs);
    temp.AndExpr(lhs.GetExpr() && lhs.GetValue() > rhs);
    return temp;
}

template<class T>
MagicCompare<T> operator<=(T lhs, const MagicCompare<T>& rhs) {
    LOG("Global Less than or equal comparison: " << lhs << " <= " << rhs.GetValue());
    MagicCompare<T> temp = rhs;
    temp.AndExpr(lhs <= rhs.GetValue());
    return temp;
}

template<class T>
MagicCompare<T> operator>=(T lhs, const MagicCompare<T>& rhs) {
    LOG("Global Greater than or equal comparison: " << lhs << " >= " << rhs.GetValue());
    MagicCompare<T> temp = rhs;
    temp.AndExpr(lhs >= rhs.GetValue());
    return temp;
}

template<class T>
MagicCompare<T> operator<=(const MagicCompare<T>& lhs, T rhs) {
    LOG("Global Less than or equal comparison (reversed): " << lhs.GetValue() << " <= " << rhs);
    MagicCompare<T> temp(rhs);
    temp.AndExpr(lhs.GetExpr() && lhs.GetValue() <= rhs);
    return temp;
}

template<class T>
MagicCompare<T> operator>=(const MagicCompare<T>& lhs, T rhs) {
    LOG("Global Greater than or equal comparison (reversed): " << lhs.GetValue() << " >= " << rhs);
    MagicCompare<T> temp(rhs);
    temp.AndExpr(lhs.GetExpr() && lhs.GetValue() >= rhs);
    return temp;
}
