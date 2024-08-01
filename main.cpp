#include <bits/stdc++.h>
using namespace std;

class Int{
    /*
     * use vector
     * */

    vector<uint> val;

public:
    Int():val{0}{}
    explicit Int(uint x){
        while(x){
            val.emplace_back(x % 10);
            x /= 10;
        }
    }

    Int operator+(const Int& other) const {
        Int result;
        result.val.resize(1 + max(other.val.size(), val.size()));
        for(size_t i = 0; i < result.val.size() - 1; ++i){
            result[i + 1] = (result[i] + other[i] + (*this)[i]) / 10;
            result[i] = (result[i] + other[i] + (*this)[i]) % 10;
        }
        result.removeLeadingZeros();
        return result;
    }

    Int pow10(uint k){
        Int result;
        result.val.resize(k);
        for(auto &i : val){
            result.val.emplace_back(i);
        }
        return result;
    }

    string to_string() const{
        string s;
        s.reserve(val.size());
        for(auto &i : val){
            s.push_back((char)(i + '0'));
        }
        reverse(s.begin(), s.end());
        return s;
    }

private:
    void removeLeadingZeros(){
        while(!val.empty() && val.back() == 0){
            val.pop_back();
        }
    }

    uint operator[](uint i) const{
        return i < val.size() ? val[i] : 0;
    }

    uint& operator[](uint i){
        return val[i];
    }
};

template<std::size_t n>
class Integer{
    bitset<n> val;
    bool sign;

public:
    Integer() : val(0), sign(false){}
    explicit Integer(long x) : val(abs(x)), sign(abs(x) != abs(x)){}
    explicit Integer(string x){
        if(x.empty()){
            throw std::invalid_argument("Empty string!");
        }

        Integer<n> temp;

        sign = (x[0] == '-');
        if(x[0] == '+' || x[0] == '-'){
            x[0] = '0';
        }

        for(auto &i : x){
            temp = (temp * Integer<n>(10)) + Integer<n>(i - '0');
            if(i < '0' || '9' < i){
                throw invalid_argument("Error char in string!");
            }
        }

        temp.sign = sign;
        *this = temp;
    }

    Integer<n> operator+(const Integer<n>& other) const {
        if(sign == other.sign){
            Integer result;
            result.sign = sign;
            for(size_t i = 0; i < n - 1; ++i){
                result[i + 1] = (((short)val[i] + other[i] + result[i]) > 1);
                result[i] = val[i] ^ other[i] ^ result.val[i];
            }
            if((short)result[n - 1] + val[n - 1] + other[n - 1] > 1){
                throw out_of_range("The integer is too big!");
            }
            result[n - 1] = result[n - 1] + val[n - 1] + other[n - 1];
            return result;
        }

        if(sign) {
            return *this - (-other);
        }
        return other - (-*this);
    }

    Integer<n> operator-(const Integer<n>& other) const {
        if(sign == other.sign){
            if(*this == other){
                return Integer<n>{};
            }
            Integer<n> result;
            result.sign = (other > *this);
            const Integer<n>& larger = (result.sign ^ sign ^ 1) ? *this : other;
            const Integer<n>& smaller = (result.sign ^ sign ^ 1) ? other : *this;
            bool borrow = false;
            for(size_t i = 0; i < n; ++i){
                result[i] = larger[i] ^ smaller[i] ^ borrow;
                borrow = (smaller[i] + borrow > larger[i]);
            }
            return result;
        }
        return *this + (-other);
    }

    Integer<n> operator*(const Integer<n>& other) const {
        Integer<n> result;
        result.sign = (sign != other.sign);
        for(size_t i = 0; i < n; i++){
            if(other[i]){
                result = result + ((*this).pow2(i));
            }
        }
        return result;
    }

    Integer<n> operator/(const Integer<n>& other) const {
        if(other == Integer<n>{}){
            throw invalid_argument("Division by zero!");
        }else if(other == Integer<n>(1)){
            return *this;
        }
        Integer<n> l(0), r(*this);
        r.val >>= 1;
        while(r > l){ // avoid l <= r here
            Integer<n> mid = l + r;
            mid.val >>= 1;
            try{
                auto tem = other * mid;
                if(tem > *this){
                    r = mid - Integer(1);
                }else{
                    l = mid + Integer(1);
                }
            }catch(out_of_range){
                r = mid - Integer(1);
            }
        }

        // to avoid l <= r which cause check to l == r every time
        Integer<n> mid = l + r;
        mid.val >>= 1;
        try{
            auto tem = other * mid;
            if(tem > *this){
                r = mid - Integer(1);
            }else{
                l = mid + Integer(1);
            }
        }catch(out_of_range){
            r = mid - Integer(1);
        }

        r.sign = sign ^ other.sign;

        return r;
    }

    Integer<n> pow2(size_t k) const {
        if(k > n){
            throw out_of_range("The k is too big!");
        }
        Integer<n> result = *this;
        for(uint i = 0; i < k; ++i){
            if(result.val[n - i - 1] == true){
                throw out_of_range("The k is too big!");
            }
        }
        result.val <<= k;
        return result;
    }

    string to_string(){
        Int base(1), res;
        for(uint i = 0; i < n; i++){
            if(val[i]){
                res = res + base;
            }
            base = base + base;
        }
        string ret;
        if(sign){
            ret.push_back('-');
        }
        ret.append(res.to_string());
        return ret;
    }

    bool operator == (const Integer<n>& other) const {
        return val == other.val && sign == other.sign;
    }

    bool operator > (const Integer<n>& other) const {
        if(sign != other.sign){
            return other.sign;
        }

        for(int i = n - 1; i >= 0; --i){
            if(val[i] != other[i]){
                return val[i];
            }
        }

        return false;
    }

    Integer<n> operator-() const {
        Integer result = *this;
        result.sign = !sign;
        return result;
    }

private:
    bool operator[](size_t i) const{
        return val[i];
    }

    typename bitset<n>::reference operator[](size_t i) {
        return val[i];
    }
};

int main(){
    Integer<128> a("-123456789"), b("987654321");
    cout << (b/a).to_string();
}