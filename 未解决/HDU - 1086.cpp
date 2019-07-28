#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <math.h>
#define PI 3.141592653589
#define MAXN 110
using namespace std;
//基本定义
const double eps = 1e-10;
struct Point
{
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) {}
};
/*struct Polygon
{
	int v;
	Point* polygon = new Point[v];
};*/
typedef Point Vector;
Vector operator+(Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator-(Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator*(Vector A, double p) { return Vector(A.x * p, A.y * p); }
Vector operator/(Vector A, double p) { return Vector(A.x / p, A.y / p); }
bool operator<(const Point& a, const Point& b) { return a.x < b.y || (a.x == b.x && a.y < b.y); }
int dcmp(double x) { if (fabs(x) < eps)return 0; else return x < 0 ? -1 : 1; }
bool operator==(const Point& a, const Point& b) { return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0; }

double Dot(Vector A, Vector B) { return A.x * B.x + A.y * B.y; } //点积
double Length(Vector A) { return sqrt(Dot(A, A)); } //向量的长度
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); } //两向量夹角

double Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; } //差积
double Area2(Point A, Point B, Point C) { return Cross(B - A, C - A); } //三角形的有向面积

Vector Rotate(Vector A, double rad) { return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad)); } //逆时针旋转rad角
Vector Normal(Vector A) { double L = Length(A); return Vector(-A.y / L, A.x / L); } //计算函数向量的单位法线 调用前应保证A不是零向量

Point GetLineIntersection(Point P, Vector v, Point Q, Vector w)
{ //求两条直线的交点 调用前应保证唯一的交点存在 且Cross(v,w)不为零
	Vector u = P - Q;
	double t = Cross(w, u) / Cross(v, w);
	//printf("%lf,%lf\n", Cross(w, u), Cross(v, w));
	return P + v * t;
}
double DistanceToLine(Point P, Point A, Point B)
{//计算点到直线的距离
	Vector v1 = B - A;
	Vector v2 = P - A;
	return fabs(Cross(v1, v2)) / Length(v1);
}
double DistanceToSegment(Point P, Point A, Point B)
{//计算点到线段的距离
	if (A == B)return Length(P - A);
	Vector v1 = B - A;
	Vector v2 = P - A;
	Vector v3 = P - B;

	if (dcmp(Dot(v1, v2)) < 0)return Length(v2);
	else if (dcmp(Dot(v1, v3)) > 0)return Length(v3);
	else return fabs(Cross(v1, v2)) / Length(v1);
}
Point GetLineProjection(Point P, Point A, Point B)
{//一个点在直线上的投影点
	Vector v = B - A;
	return A + v * (Dot(v, P - A), Dot(v, v));
}
bool OnSegment(Point p, Point a1, Point a2)
{
	//printf("%d %d\n", dcmp(Cross(a1 - p, a2 - p)), dcmp(Dot(a1 - p, a2 - p)));
	return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) <= 0;
	//叉积为零代表是这个点在这条直线上 而点积小于零的意思是这个点在中间 所以点就在线段上了
}
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2)
{//判断线段是否相交 不考虑到线段的端点
	double c1 = Cross(a2 - a1, b1 - a1);
	double c2 = Cross(a2 - a1, b2 - b1);
	double c3 = Cross(b2 - b1, a1 - b1);
	double c4 = Cross(b2 - b1, a2 - b1);

	return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
	//if (dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0)return true;//因为叉积是有方向的 所以他们的乘积为零就分别在两侧
	//if (OnSegment(b1, a1, a2))return true;
	//if (OnSegment(b2, a1, a2))return true;
	//if (OnSegment(a1, b1, b2))return true;
	//if (OnSegment(a2, b1, b2))return true;
	//if (a1 == b1 || a1 == b2 || a2 == b1 | a2 == b2)return true;
	//return false;
}

double ConvexPolygonArea(Point* p, int n)
{//多边形的有向面积
	double area = 0;

	for (int i = 1; i < n - 1; i++)area += Cross(p[i] - p[0], p[i + 1] - p[0]);
	return area / 2;
}
int isPointInPolygon(Point p, Point* poly, int n)
{//判断点是否在多边形以内
	int wn = 0;
	
	for (int i = 0; i < n; i++)
	{
		if (OnSegment(p, poly[i], poly[(i + 1) % n]))return -1;//在边界上
		int k = dcmp(Cross(poly[(i + 1) % n] - poly[i], p - poly[i]));
		int d1 = dcmp(poly[i].y - p.y);
		int d2 = dcmp(poly[(i + 1) % n].y - p.y);
		if (k > 0 && d1 <= 0 && d2 > 0)wn++;
		if (k < 0 && d2 <= 0 && d1 > 0)wn--;
	}
	if (wn != 0)return 1;//内部
	return 0;//外部
}
bool cmp_convexhull(const Point& x, const Point& y)
{
	if (dcmp(x.x - y.x) == -1)return true;
	else if (dcmp(x.x - y.x) == 0)
	{
		if (dcmp(x.y - y.y) == -1)return true;
		else return false;
	}
	else return false;
}
int ConvexHull(Point* p, int n, Point* ch)
{//凸包
	sort(p, p + n, cmp_convexhull);
	int m = 0;
	for (int i = 0; i < n; i++)
	{
		while (m > 1 && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0)m--;
		ch[m++] = p[i];
	}
	int k = m;

	for (int i = n - 2; i >= 0; i--)
	{
		while (m > k && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0)m--;
		ch[m++] = p[i];
	}
	if (n > 1)m--;
	return m;
}

//problem
struct Line
{
	Point a, b;
}line[MAXN];
int main(void)
{
	int N;

	while (scanf("%d", &N) != EOF && N)
	{
		int coun = 0;

		for (int i = 0; i < N; i++)scanf("%lf%lf%lf%lf", &line[i].a.x, &line[i].a.y, &line[i].b.x, &line[i].b.y);
		for (int i = 0; i < N; i++)
			for (int j = i + 1; j < N; j++)
				if (SegmentProperIntersection(line[i].a, line[i].b, line[j].a, line[j].b))coun++;

		printf("%d\n", coun);
	}

	return 0;
}