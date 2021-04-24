# include <iostream>

using namespace std;

struct point {double x, y;};
struct line {double x1, y1, x2, y2;};

class polygon
{
private:
    point *A;
    line *L;
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

    //new methods
    int len() {return N;} // DONE
    void setLines(); // make lines by points
    void showLines(); // show all lines
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
    delete[] L;
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

//new methods
void polygon::setLines()
{
    L = new line[N];

    for (int i = 0; i < (N-1); i++)
    {
        L[i].x1 = A[i].x;
        L[i].y1 = A[i].y;

        L[i].x2 = A[i+1].x;
        L[i].y2 = A[i+1].y;
    }
    //last line
    L[N-1].x1 = A[N-1].x;
    L[N-1].y1 = A[N-1].y;
    L[N-1].x2 = A[0].x;
    L[N-1].y2 = A[0].y;
}
void polygon::showLines()
{
    for(int i = 0; i < N; i++)
        cout << "Line: " << L[i].x1 << ' ' << L[i].y1 << ' ' << L[i].x2 << ' ' << L[i].y2 << endl;
}


int main()
{
    polygon obj = polygon(3);
    obj.setLines();
    obj.showLines();
}
