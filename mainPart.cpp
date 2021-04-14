# include <iostream>

using namespace std;

struct point {double x, y;};

class polygon
{
private:
    point *A;
    int N;
    // прочие скрытые переменные и функции
public:
    polygon(): N(0), A(NULL) {}; // DONE
    polygon(int n);
    polygon(const polygon&);
    ~polygon();
    polygon& operator=(const polygon&);
    point& operator[] (int);
    friend ostream& operator<<(ostream&, const polygon&);
    polygon operator*(const polygon&);
};
