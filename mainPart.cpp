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
    polygon(int n); // DONE
    polygon( polygon&, int n); // DONE
    ~polygon(); // DONE
    polygon& operator=( polygon&); //DONE
    point& operator[] (int); // DONE
    friend ostream& operator<<(ostream&, const polygon&); // DONE
    polygon operator*(const polygon&);
    int len() {return N;} // DONE
};

polygon::polygon(int n) // class constr
{
    int x, y;
    N = n;
    if (N)
    {
        A = new point[N];
        for(int i = 0; i < N; i++){
            cin >> x >> y;
            A[i].x = x;
            A[i].y = y;
        }

        //for(int i = 0; i < N; i++)
            //cout << A[i].x << " " << A[i].y << endl;
    }
}
polygon::polygon(polygon& obj, int n) // copy constr
{
    N = n;
    if(N)
    {
        A = new point[N];
        for(int i = 0; i < N; i++){
            A[i].x = obj[i].x;
            A[i].y = obj[i].y;
        }
    }
}
polygon::~polygon() // DELETE POLYGON
{
    delete[] A;
}

point& polygon::operator[](int n) // [] check
{
    return A[n];
}
ostream& operator<<(ostream& os, polygon& obj) // cout and file data out
{
    point p;
    for (int i = 0; i < obj.len(); i++)
    {
        p = obj[i];
        os << p.x << " " << p.y << endl;
    }
}


polygon& polygon::operator=( polygon& obj) // = copy func
{
    if (this == &obj)
        return *this;

    // delete old data and copy new
    delete [] A;
    N = obj.len();

    if (N)
    {
        A = new point[N];
        for(int i = 0; i < N; i++)
        {
            A[i].x = obj[i].x;
            A[i].y = obj[i].y;
        }
    } else {A = NULL;}

    return *this;
}


int main()
{
    polygon obj = polygon(3);
    polygon obj1;
    obj1 = obj;

    cout << obj1;
}
