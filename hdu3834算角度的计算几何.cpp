#include <iostream>
#include <cstdio>
#include <cmath>
const double eps=1e-12;
const double pi=acos(-1.0);
typedef long long ll;
using namespace std;

struct Point
{
    double x, y, r; 
    Point(){}
    Point(double _x, double _y, double _r){x=_x; y=_y; r=_r;}
    void read(){scanf("%lf%lf%lf", &x, &y, &r);}
    Point operator -(const Point &tp)const
    {
        return Point(x - tp.x, y - tp.y, r - tp.r);
    }
    Point operator +(const Point &tp)const
    {
        return Point(x + tp.x, y + tp.y, r + tp.r);
    }
    Point operator *(const double &k)const
    {
        return Point(x * k, y * k, r * k);
    }  
};
       
int T;
double r, dx, dy, s, t;
Point p1, p2;

double power(double x)
{
    return x * x;   
}

int cross(Point op, Point sp, Point ep)
{
    double ans = (sp.y - op.y) * (ep.x - op.x) - (ep.y - op.y) * (sp.x - op.x);
    if (ans > eps) return 1;
    return -1;
}
double angle(Point a, Point b)//ab�����н�,area=A*B*cos(ab)
{
    double area = a.x * b.x + a.y * b.y;//���
    double ablen = sqrt((a.x * a.x + a.y * a.y) * (b.x * b.x + b.y * b.y));
    return acos (area / ablen);
}      
int main()
{
    int i, j, dir;
    double r1, r2, a, b, c, t1;
    double ref, dis, dti, v, perti, left, pang, stand, vang, rate;
    long long lti;
    Point first;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lf%lf%lf", &p1.x, &p1.y, &r1);
        scanf("%lf%lf%lf", &p2.x, &p2.y, &r2);
        r = r1 - r2;
        scanf("%lf%lf%lf", &dx, &dy, &t);
        p2.x -= p1.x, p2.y -= p1.y;
        a = power(dx) + power(dy);
        b = 2.0 * (dx * p2.x + dy * p2.y);
        c = power(p2.x) + power(p2.y) - power(r); 
        t1 = 0.5 * (sqrt(power(b) - 4.0 * a * c) - b) / a; 
        if (t1 - t > eps)
        {
            Point now;
            now.x = p2.x + dx * t + p1.x;
            now.y = p2.y + dy * t + p1.y;
            printf("%.1lf %.1lf\n", now.x, now.y);   
        }
        else
        {
            Point zero(0, 0, 0);        //ԭ�� 
            first.x = p2.x + dx * t1;   //��һ����ײ�� 
            first.y = p2.y + dy * t1; 
            dir = cross(zero, first, p2);//����1����ʱ�� 
            ref = angle(p2 - first, zero - first);//�����
            dis = cos(ref) * r * 2.0;         //��λ���� 
            v = sqrt(power(dx) + power(dy));  //�ٶ� 
            t -= t1;                          //ʱ�� 
            dti = t * v / dis;                 //���� 
            lti = (long long) dti;              //�������� 
            perti = dis / v;                     //��λʱ�� 
            left = t - perti * lti;              //��ʣʱ�� 
            pang = (pi - 2 * ref) * lti;          //ת���ĽǶ� 
            stand = atan2(first.y, first.x);      //��һ����ײ��ĽǶ� 
            stand += pang * dir;                  //���һ����ײ��ĽǶ� 
            Point now(cos(stand) * r, sin(stand) * r, 0);//���һ����ײ�� 
            vang = stand + (pi - 2 * ref) * dir;         //��һ����ײ��ĽǶ�  
            Point next(cos(vang) * r, sin(vang) * r, 0);//��һ����ײ��
            rate = left / perti;                         //�յ���� 
            Point vec = next - now;
            now = now + (vec * rate);
            printf("%.1lf %.1lf\n", now.x + p1.x, now.y + p1.y);
        }
    }
    system("pause");
    return 0;
}

/*
double atan( 
   double x 
); //����x�ķ�����ֵ

double atan2( double y, double x );
 //����y/x�ķ�����ֵ
*/

