# include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

struct point {double x, y;};
struct line {double x1, y1, x2, y2;};

// Func declaration
bool cross(line&, line&, point&);


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
    polygon* operator*( polygon&);

    //new methods
    int len() {return N;} // DONE
    void setLines(); // make lines by points
    void showLines(); // show all lines
    bool isInTri(double, double); // Checking if a point lies in a triangle

    polygon(point*, int);
};

// Сonstructors
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

            //work with global
            /*ALL_DOTS[ALL_DOTS_LEN + i].x = x;
            ALL_DOTS[ALL_DOTS_LEN + i].y = y;*/
        }

        //for(int i = 0; i < N; i++)
            //cout << A[i].x << " " << A[i].y << endl;
    }

    //ALL_DOTS_LEN += N;
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
polygon::polygon(point ps[], int len) // - ???
{
    N = len;
    if(N)
    {
        A = new point[N];
        for(int i = 0; i < N; i++)
        {
            A[i].x = ps[i].x;
            A[i].y = ps[i].y;
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

polygon* polygon::operator*(polygon& obj) // Create new figure
{
    point* cr = new point[N + obj.len()]();
    int pos = 0;

    line l1, l2;
    double x, y;

    //check all lines
    for (int i = 0; i < N; i++)
    {
        l1 = L[i];
        for (int j = 0; j < obj.len(); j++)
        {
            l2 = obj.L[j];
            if (cross(l1, l2, cr[pos]))
            {
                pos++;
            }
        }
    }
    //cout << pos << endl;
    /*for (int i = 0; i < pos; i++)
        cout << cr[i].x << " " << cr[i].y << endl;*/

    // check all points
    for (int i = 0; i < N; i++)
    {
        //cout << "obj1: ";
        x = A[i].x; y = A[i].y;
        //cout << x << " " << y << " = " << obj.isInTri(x, y) << endl;
        if (obj.isInTri(x, y))
        {
            cr[pos].x = x;
            cr[pos].y = y;
            pos++;
        }
    }
    // ALL CR DOTS (= FIGURE!!!!
    for (int i = 0; i < obj.len(); i++)
    {
        //cout << "obj2: ";
        x = obj[i].x; y = obj[i].y;
        //cout << x << " " << y << " = " << isInTri(x, y) << endl;
        if (isInTri(x, y))
        {
            cr[pos].x = x;
            cr[pos].y = y;
            pos++;
        }
    }
    /*for (int i = 0; i < pos; i++)
        cout << cr[i].x << " " << cr[i].y << endl;
    for (int i = 0; i < pos; i++)
    {
        cout << "cr: ";
        x = cr[i].x; y = cr[i].y;
        cout << x << " " << y << " = " << (obj.isInTri(x, y) && isInTri(x, y)) << endl;
    }*/

    polygon* res = new polygon(cr, pos);
    delete[] cr;
    //cout << *res;
    return res;
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

bool cross(line& l1, line& l2, point& res) // intersection of two lines   DONE
{
    double n, nx, ny;
    double x1, y1, x2, y2;
    double x3, y3, x4, y4;
    bool t;

    x1 = l1.x1; y1 = l1.y1;
    x2 = l1.x2; y2 = l1.y2;

    x3 = l2.x1; y3 = l2.y1;
    x4 = l2.x2; y4 = l2.y2;

    if (y2 - y1 != 0)
    {
        float q = (x2 - x1) / (y1 - y2);
        float sn = (x3 - x4) + (y3 - y4) * q;

        if (!sn)
            return 0;

        float fn = (x3 - x1) + (y3 - y1) * q;
        n = fn / sn;
    }
    else
    {
        if (!(y3 - y4))
            return 0;

        n = (y3 - y1) / (y3 - y4);
    }
    nx = x3 + (x4 - x3) * n;
    ny = y3 + (y4 - y3) * n;

    t = ((x1 <= nx) && (nx <= x2)) || ((x2 <= nx) && (nx <= x1));
    t = t && ( ((x3 <= nx) && (nx <= x4)) || ((x4 <= nx) && (nx <= x3)) );
    t = t && ( ((y1 <= ny) && (ny <= y2)) || ((y2 <= ny) && (ny <= y1)) );
    t = t && ( ((y3 <= ny) && (ny <= y4)) || ((y4 <= ny) && (ny <= y3)) );

    if (t)
    {
        res.x = nx;
        res.y = ny;
        return true;
    }
    return false;
}
bool polygon::isInTri(double xx, double yy) //point belongs to triangle  DONE
{
    double x1, y1;
    double x2, y2;
    double x3, y3;

    double t1, t2, t3;

    point po;

    po = A[0]; x1 = po.x; y1 = po.y;
    po = A[1]; x2 = po.x; y2 = po.y;
    po = A[2]; x3 = po.x; y3 = po.y;

    t1 = (x1-xx)*(y2-y1) - (x2-x1)*(y1-yy); t1 = fabs(t1)!=0. ? t1/fabs(t1) : 1;
    t2 = (x2-xx)*(y3-y2) - (x3-x2)*(y2-yy); t2 = fabs(t2)!=0. ? t2/fabs(t2) : t1;
    t3 = (x3-xx)*(y1-y3) - (x1-x3)*(y3-yy); t3 = fabs(t3)!=0. ? t3/fabs(t3) : t2;
    //cout << "---\n" << t1 << " " << t2 << " " << t3 << "\n" << "---\n";
    if ( (t1 == t2) && (t2 == t3) )
        return true;
    return false;
}



int main()
{
    //polygon obj = polygon(3);
    //obj.setLines();
    //obj.showLines();

    /*point* p = new point[3];
    int l = 3;
    double x, y;

    for(int i = 0; i < l; i++){
        cin >> x >> y;
        p[i].x = x; p[i].y = y;
    }

    polygon o = polygon(p, l);
    cout << o;

    delete[] p;*/

    polygon obj1 = polygon(3);
    obj1.setLines();
    polygon obj2 = polygon(3);
    obj2.setLines();

    polygon* obj = obj1*obj2;
    cout << "Result:" << endl;
    cout << *obj;

    // work with file
    ofstream f;
    f.open("out.txt", ios_base::out);
    f.close();

    f.open("out.txt", ios_base::app);
    f << obj1;
    f << obj2;
    f << *obj;
    f.close();

    return 0;
}
