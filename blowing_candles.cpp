/*
 *  _     _               _                                   _ _           
 * | |__ | | _____      _(_)_ __   __ _    ___ __ _ _ __   __| | | ___  ___ 
 * | '_ \| |/ _ \ \ /\ / / | '_ \ / _` |  / __/ _` | '_ \ / _` | |/ _ \/ __|
 * | |_) | | (_) \ V  V /| | | | | (_| | | (_| (_| | | | | (_| | |  __/\__ \
 * |_.__/|_|\___/ \_/\_/ |_|_| |_|\__, |  \___\__,_|_| |_|\__,_|_|\___||___/
 *                                |___/                                     
 *
 */

#include <bits/stdc++.h>

typedef long long LL;


namespace geo {
    struct point {
        LL x,y;
        point() : x{0LL}, y{0LL} { }
        point(LL x, LL y) : x{x}, y{y} { }

        bool operator<(const geo::point &other) const {
            return x == other.x ? y < other.y : x < other.x;
        }

        friend std::ostream &operator<<(std::ostream &os, const geo::point &p) {
            return os << '(' << p.x << ',' << p.y << ')';
        }
        
        static double dist(const geo::point &p1, const geo::point &p2) {
            return std::hypot(p1.x-p2.x, p1.y-p2.y);
        }
    };

    struct line {
        double a,b,c; // ax + bx = c
        line() : a{0.0}, b{0.0}, c{0.0} { }
        line(double a, double b, double c) : a{a}, b{b}, c{c} { }
        line(const geo::point &p1, const geo::point &p2) {
            if (p1.x == p2.x) {
                a = 1.0; b = 0.0, c = static_cast<double>(-p1.x);
            } else {
                a = -static_cast<double>(p1.y - p2.y) / (p1.x - p2.x);
                b = 1.0;
                c = -static_cast<double>(a * p1.x) - p1.y;
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const geo::line &l) {
            return os << '(' << l.a << "x + " << l.b << "y = " << l.c  << ')';
        }
    };

    struct vector {
        LL x,y,z;
        vector() : x{0LL}, y{0LL}, z{0LL} { }
        vector(LL x, LL y) : x{x}, y{y}, z{0LL} { }
        vector(LL x, LL y, LL z) : x{x}, y{y}, z{z} { }
        vector(const geo::point &p1, const geo::point &p2) : x{p2.x-p1.x}, y{p2.y-p1.y}, z{0LL} { }

        double magnitude() const {
            return std::hypot(x,y,z);
        }

        // a * b
        static LL dot(const geo::vector &a, const geo::vector &b) {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }

        // a x b
        static geo::vector cross(const geo::vector &a, const geo::vector &b) {
            return geo::vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
        }

        friend std::ostream &operator<<(std::ostream &os, const geo::vector &v) {
            return os << '<' << v.x << ',' << v.y << ',' << v.z << '>';
        }
    };

    inline double distToLine(const geo::point &p, const geo::point &a, const geo::point &b) {
        geo::vector ap(a,p), ab(a,b);
        double u = static_cast<double>(geo::vector::dot(ap, ab)) / (ab.x*ab.x + ab.y*ab.y + ab.z*ab.z);
        double cx = a.x + ab.x*u;
        double cy = a.y + ab.y*u;
        return std::hypot(cx - p.x, cy - p.y);
    }
};


int main() {

    LL N,R; scanf("%lld %lld", &N, &R);
    std::vector<geo::point> pts(N);
    for (int i = 0; i < N; ++i) {
        scanf("%lld %lld", &pts[i].x, &pts[i].y);
    }

    std::sort(std::begin(pts), std::end(pts));

    std::vector<geo::point> lower_hull;
    for (const geo::point &p : pts) {
        while (static_cast<int>(lower_hull.size()) >= 2) {
            geo::point &a = lower_hull[static_cast<int>(lower_hull.size()) - 2];
            geo::point &b = lower_hull[static_cast<int>(lower_hull.size()) - 1];
            geo::point c = p;
            
            geo::vector v1(a,b);
            geo::vector v2(b,c);

            if (geo::vector::cross(v1,v2).z > 0) { break; }

            lower_hull.pop_back();
        }

        lower_hull.push_back(p);
    }

    std::vector<geo::point> upper_hull;
    for (const geo::point &p : pts) {
        while (static_cast<int>(upper_hull.size()) >= 2) {
            geo::point &a = upper_hull[static_cast<int>(upper_hull.size()) - 2];
            geo::point &b = upper_hull[static_cast<int>(upper_hull.size()) - 1];
            geo::point c = p;
            
            geo::vector v1(a,b);
            geo::vector v2(b,c);

            if (geo::vector::cross(v1,v2).z < 0) { break; }

            upper_hull.pop_back();
        }

        upper_hull.push_back(p);
    }


    std::vector<geo::point> convex_hull(static_cast<int>(lower_hull.size()) + static_cast<int>(upper_hull.size()) - 2);
    int j = 0;
    for (int i = 0; i < static_cast<int>(lower_hull.size()); ++i) { convex_hull[j++] = lower_hull[i]; }
    for (int i = static_cast<int>(upper_hull.size())-2; i > 0; --i) { convex_hull[j++] = upper_hull[i]; }

    if (static_cast<int>(convex_hull.size()) <= 2) {
        printf("0\n");
        return 0;
    }

    j = 1;
    double min_width = std::numeric_limits<double>::max();
    for (int i = 0; i < static_cast<int>(convex_hull.size()); ++i) {
        geo::point &a = convex_hull[i];
        geo::point &b = convex_hull[(i+1)%static_cast<int>(convex_hull.size())];
        geo::vector v(b,a);

        while (true) {
            geo::point &c = convex_hull[j%static_cast<int>(convex_hull.size())];
            geo::point &d = convex_hull[(j+1)%static_cast<int>(convex_hull.size())];
            
            geo::vector _v(c,d);
            if (geo::vector::cross(_v, v).z < 0) {
                break;
            }
            ++j;
        }

        min_width = std::min(min_width, geo::distToLine(convex_hull[j%static_cast<int>(convex_hull.size())], a, b));
    }

    printf("%.9lf\n", min_width);

    return 0;
}
