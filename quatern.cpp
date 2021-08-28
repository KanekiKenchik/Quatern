#include"quatern.h"

template<typename T>
T povor1(T p, T v, float phi)
{
    T res;
    float sum = 0;
    for (int i = 0; i < p.size(); i++)
        sum += p[i] * v[i];
    if (fabs(sum) < eps)
    {
        T tmp = {cos(phi), p[1] * sin(phi), p[2] * sin(phi), p[3] * sin(phi)};
        res = mult(tmp,v);
        res.erase(res.begin());
        return res;
    }
    else
    {
        res.clear();
        return res;
    }
}

template<typename T>
T povor2(T p, T v, float phi)
{
    T q, q1, res;
    float z = phi / 2;
    q = {cos(z),p[1] * sin(z),
         p[2] * sin(z),p[3] * sin(z)};
    q1 = {cos(z),p[1] * sin(z) * (-1),
         p[2] * sin(z) * (-1), p[3] * sin(z) * (-1)};
    res = mult(mult(q,v), q1);
    res.erase(res.begin());
    return res;
}

template<typename T>
pair<float, T> povor3(T p, T q, float phi1, float phi2)
{
    pair<float, T> res;
    T z, z2, q2, q1;
    float phi, z1, sum = 0;
    q2 = {cos(phi2/2),q[1]*sin(phi2/2),
         q[2]*sin(phi2/2),q[3]*sin(phi2/2)};
    q1 = {cos(phi1/2),p[1]*sin(phi1/2),
         p[2]*sin(phi1/2),p[3]*sin(phi1/2)};
    z = mult(q2,q1);
    for (int i = 1; i < 4; i++)
        sum += z[i] * z[i];
    z1 = sqrt(sum);
    if (z[0] > 0)
       phi = asin(z1) ;
    else
       phi = pi - asin(z1);
    z[0] = 0;
    z2 = multC(1/z1, z);

    if (fabs(sin(phi)) > eps)
    {
        res.first = 2*phi*180/pi;
        z2.erase(z2.begin());
        res.second = z2;
    }
    else
    {
        res.first = 0;
        p.erase(p.begin());
        res.second = p;
    }
    return res;
}

template<typename T>
pair<pair<float, T> , T>
povor4(T p, T q,
 float phi1, float phi2, T v)
{
    pair<float, T> z = povor3(p,q,phi1,phi2);
    pair<pair<float, T>, T> res;
    res.first = z;
    z.second = {0, z.second[0],z.second[1],z.second[2]};
    res.second = povor2(z.second,v,z.first * pi / 180);
    return res;
}

template<typename T>
T mult(T q1, T q2)
{
    T res = {q1[0]*q2[0]-q1[1]*q2[1]-q1[2]*q2[2]-q1[3]*q2[3],
                         q1[0]*q2[1]+q1[1]*q2[0]+q1[2]*q2[3]-q1[3]*q2[2],
                         q1[0]*q2[2]+q1[2]*q2[0]-q1[1]*q2[3]+q1[3]*q2[1],
                         q1[0]*q2[3]+q1[3]*q2[0]+q1[1]*q2[2]-q1[2]*q2[1]};
    return res;    
}

template<typename T>
T multC(float c, T quat)
{
    for (int i = 0; i < 4; i++)
        quat[i] *= c;
    return quat;    
}

template<typename T>
T summ(T quat1, T quat2)
{
    for (int i = 0; i < 4; i++)
        quat1[i] += quat2[i];
    return quat1;
}

vector<float> setQuat(string name = "")
{
    float a;
    vector<float> q;
    cout << "Введите кватернион " << name+": ";

    for (int i = 0; i < 4; i++)
    {
        cin >> a;
        q.push_back(a);
    }
    return q;
}

vector<float> setVect(string name = "")
{
    float a;
    vector<float> q;
    cout << "Введите вектор " << name+": ";
    q.push_back(0);

    for (int i = 1; i < 4; i++)
    {
        cin >> a;
        q.push_back(a);
    }
    return q;
}

template<typename T>
void output(T vect)
{
    for(auto &i : vect)
        cout << i << " ";
    cout << endl;
}

template<typename T>
int ifEqualVec(T vec1, T  vec2)
{
    for(int i; i<vec1.size(); i++)
        if (vec1[i]-eps>vec2[i] || vec1[i]+eps<vec2[i])
            return 0;
    return 1;
}

int ifEqualNum(float x, float y)
{
    float eps1=0.1;
    if (x-eps1>y || x+eps1<y)
         return 0;
    return 1;    
}

void test()
{
    vector<float> q,p,v, res1;
    pair<float, vector<float>> res2;
    pair<pair<float, vector<float>>, vector<float>> res3;
    float c, phi1, phi2;
    
    p={1,1,1,10}; 
    v={1,2,3,4};  
    res1={2,3,4,14};
    assert(summ(p,v)==res1);

    p={3,5,9,10}; 
    v={1,2,3,4};  
    res1={-74,17,18,19}; 
    assert(mult(p,v)==res1);

    c=10; 
    p={1,2,3,4};  
    res1={10,20,30,40}; 
    assert(multC(c,p)==res1);   

    //------------------------Тестирование povor1-------------------------
    p = {0,1,0,0}; q = {0,0,2,0}; phi1 = pi/2; res1 = {0,0,2};
    assert(ifEqualVec(res1, povor1(p,q,phi1)));

    //------------------------Тестирование povor2-------------------------
    p = {0,0,1,0}; q = {0,1,1,0}; phi1 = -pi/2; res1 = {0,1,1};
    assert(ifEqualVec(res1, povor2(p,q,phi1)));
    p = {0,float(1/sqrt(2)),float(1/sqrt(2)),0};
    q = {0,0,5,0}; phi1 = pi; res1 = {5,0,0};
    assert(ifEqualVec(res1, povor2(p,q,phi1)));
    
    //------------------------Тестирование povor3-------------------------
    p = {0,1,0,0}; q = {0,1,0,0}; phi1 = pi/8; phi2 = 7*pi/8;
    res2.first = 180; 
    res2.second = {1,0,0};
    assert(ifEqualVec(res2.second, povor3(p,q,phi1,phi2).second)
    && ifEqualNum(res2.first, povor3(p,q,phi1,phi2).first));
      
    //------------------------Тестирование povor4-------------------------
    p = {0,1,0,0}; q = {0,0,1,0}; v = {0,1,2,3};
    phi1 = pi/2; phi2 = pi/2;
    res3.first.first = 120; res3.first.second = {0.57735,0.57735,-0.57735};
    res3.second = {2,-3,-1};
    assert(ifEqualNum(res3.first.first, povor4(p,q,phi1,phi2,v).first.first) 
    && ifEqualVec(res3.first.second, povor4(p,q,phi1,phi2,v).first.second)
    && ifEqualVec(res3.second, povor4(p,q,phi1,phi2,v).second) );
    
    cout << "\nТестирование неуспешно...";
}