class Bigint {
public:
        static const int BASE = 100000000, LEN = 8;
        bool negative;
        std::vector<int> a;
        Bigint& normalize();
public:
        Bigint(int x = 0);
        Bigint(const std::string& s);
        Bigint& operator = (const Bigint& x);
        Bigint& operator = (int x);
        Bigint& operator = (const std::string& s);
        const bool operator < (const Bigint& x) const;
        const bool operator > (const Bigint& x) const;
        const bool operator <= (const Bigint& x) const;
        const bool operator >= (const Bigint& x) const;
        const bool operator != (const Bigint& x) const;
        const bool operator == (const Bigint& x) const;
        Bigint operator -() const;
        Bigint& operator += (const Bigint& x);
        Bigint& operator -= (const Bigint& x);
        Bigint& operator *= (const Bigint& x);
        Bigint& operator /= (const Bigint& x);
        Bigint& operator %= (const Bigint& x);
        const Bigint operator + (const Bigint& x) const;
        const Bigint operator - (const Bigint& x) const;
        const Bigint operator * (const Bigint& x) const;
        const Bigint operator / (const Bigint& x) const;
        const Bigint operator % (const Bigint& x) const;
        friend std::pair<Bigint, Bigint> divmod(const Bigint& lhs, const Bigint& rhs);
        friend std::istream& operator >> (std::ostream& is, Bigint& x);
        friend std::ostream& operator << (std::ostream& os, const Bigint& x);
        friend const Bigint abs(Bigint x);
};
Bigint& Bigint::normalize() {
        int i = a.size()-1;
        while (i >= 0 && a[i] == 0) i --;
        a.resize(i + 1);
        if (a.size() == 0) negative = false;
        return *this;
}
Bigint::Bigint(int x) : negative(x < 0) {
        x = abs(x);
        for (; x > 0; x /= BASE) a.push_back(x % BASE);
}
Bigint::Bigint(const std::string& s): negative(false) {
        int p = 0;
        if (s[p] == '-') { p ++; negative = true; }
        else if (s[p] == '+') p ++;
        for (int i = s.size() - 1, v = BASE; i >= p; i --, v *= 10) {
                int x = s[i] - '0';
                if (x < 0 || 9 < x) {
                        std::cerr << "error: parse error:" << s << std::endl;
                        exit(1);
                } 
                if (v == BASE) {
                        v = 1;
                        a.push_back(x);
                } else {
                        a.back() += x * v;
                }
        }
        normalize();
}
Bigint& Bigint::operator = (const Bigint& x) {
        negative = x.negative;
        a = x.a;
        return *this;
}
Bigint& Bigint::operator = (int x) { return *this = Bigint(x); }
Bigint& Bigint::operator = (const std::string& s) { return *this = Bigint(s); }
const bool Bigint::operator < (const Bigint& x) const {
        if (negative != x.negative) return negative < x.negative;
        if (a.size() != x.a.size()) return (a.size() < x.a.size()) ^ negative;
        for(int i = a.size()-1; i >= 0; i --)
                if (a[i] != x.a[i]) return (a[i] < x.a[i]) ^ negative;
        return false;
}
const bool Bigint::operator > (const Bigint& x) const { return x < (*this); }
const bool Bigint::operator <= (const Bigint& x) const { return !(x < (*this)); }
const bool Bigint::operator >= (const Bigint& x) const { return !((*this) < x); }
const bool Bigint::operator != (const Bigint& x) const { return (*this) < x || x < (*this); }
const bool Bigint::operator == (const Bigint& x) const { return !((*this) < x || x < (*this)); }
Bigint Bigint::operator -() const {
        Bigint ret(*this);
        if (a.size()) ret.negative = !ret.negative;
        return ret;
}
Bigint& Bigint::operator += (const Bigint& x) {
        if (negative != x.negative) return *this -= -x;
        if (a.size() < x.a.size()) a.resize(x.a.size());
        int up = 0;
        for (int i = 0; i < a.size(); i ++) {
                a[i] += (i < x.a.size() ? x.a[i] : 0) + up;
                up = a[i] / BASE;
                a[i] %= BASE;
        }
        if (up) a.push_back(1);
        return *this;
}
Bigint& Bigint::operator -= (const Bigint& x) {
        if (negative != x.negative) return *this += -x;
        std::vector<int> b(x.a);
        if ((*this < x) ^ negative) {
                a.swap(b);
                negative = !negative;
        }
        for (int i = 0, up = 0; i < a.size(); i ++) {
                a[i] += BASE - (i < b.size() ? b[i] : 0) + up;
                up = a[i] / BASE - 1;
                a[i] %= BASE;
        }
        return this->normalize();
}
Bigint& Bigint::operator *= (const Bigint& x) {
        negative ^= x.negative;
        std::vector<int> c(a.size() * x.a.size() + 1);
        for (int i = 0; i < a.size(); i ++) {
                long long tmp = 0;
                for (int j = 0; j < x.a.size(); j ++) {
                        long long v = (long long)a[i] * x.a[j] + c[i+j] + tmp;
                        tmp = v / BASE;
                        c[i + j] = (int)(v % BASE);
                }
                if (tmp) c[i + x.a.size()] += (int)tmp;
        }
        a.swap(c);
        return this->normalize();
}
Bigint& Bigint::operator /= (const Bigint& x) {
        return *this = divmod(*this, x).first;
}
Bigint& Bigint::operator %= (const Bigint& x) {
        return *this = divmod(*this, x).second;
}
const Bigint Bigint::operator + (const Bigint& x) const {
        Bigint res(*this); return res += x;
}
const Bigint Bigint::operator - (const Bigint& x) const {
        Bigint res(*this); return res -= x;
}
const Bigint Bigint::operator * (const Bigint& x) const {
        Bigint res(*this); return res *= x;
}
const Bigint Bigint::operator / (const Bigint& x) const {
        Bigint res(*this); return res /= x;
}
const Bigint Bigint::operator % (const Bigint& x) const {
        Bigint res(*this); return res %= x;
}
std::pair<Bigint, Bigint> divmod(const Bigint& lhs, const Bigint& rhs) {
        if (!rhs.a.size()) {
                std::cerr<<"error: division by zero"<<std::endl;
                exit(1);
        }
        Bigint x(abs(rhs)), q, r;
        for (int i = lhs.a.size() - 1; i >= 0; i --) {
                r = r * Bigint::BASE + lhs.a[i];
                int head = 0, tail = Bigint::BASE;
                if (r >= x) {
                        while (head + 1 < tail) {
                                int mid = (head + tail) / 2;
                                if (x * Bigint(mid) > r) tail = mid;
                                else head = mid;
                        }
                        r -= x * head;
                }
                q.a.push_back(head);
        }
        reverse(q.a.begin(), q.a.end());
        bool neg = lhs.negative ^ lhs.negative;
        q.negative = neg;
        r.negative = neg;
        return std::make_pair(q.normalize(), r.normalize());
}
std::istream& operator >> (std::istream& is, Bigint& x) {
        std::string tmp;
        is >> tmp;
        x = Bigint(tmp);
        return is;
}
std::ostream& operator << (std::ostream& os, const Bigint& x) {
        if (x.negative) os << '-';
        if (!x.a.size()) os << 0;
        else os << x.a.back();
        for (int i = x.a.size()-2; i >= 0; i --) {
                os.width(Bigint::LEN);
                os.fill('0');
                os << x.a[i];
        }
        return os;
}
const Bigint abs(Bigint x) {
        x.negative = false;
        return x;
}
std::string str(Bigint x) {
        stringstream st;
        st << x;
        return st.str();
}
