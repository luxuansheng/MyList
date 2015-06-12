
#include<iostream>
// when on dev,stdlib.h needn't be included.
#include<stdlib.h>
using namespace std;


template <class T> class MyList;
template <class T> ostream & operator<< (ostream &os ,const MyList<T> &obj);
template <class T> MyList<T> operator+(const MyList<T> &l1, const MyList<T> &l2);
template <class T> MyList<T> operator+(const MyList<T> &l1, const T &item);


template<class T>
class MyList{
    friend ostream& operator << <>(ostream & os, const MyList<T> & obj);
	friend MyList<T> operator + <>(const MyList<T> &l1,const MyList<T> &l2);
	friend MyList<T> operator + <>(const MyList<T> &l1, const T &item);
private:
	T *a;
	int size;
	int last;
	void double_space()
	{
        T *b;
        b = new T[2 * size];
        for(int i = 0;i < last;++i)
        {
            b[i] = a[i];
        }
        delete []a;
        a = new T[2 * size];
        for(int i = 0; i< last;++i)
        {
            a[i] = b[i];
        }
        delete [] b;
        size *= 2;
	};
public:
    MyList()
    {
    size = 20;
    last = 0;
    a = new T [size];
    };
    MyList(int num, const T &item);
	MyList(const MyList &l);
    MyList(T* arr, int len);

	void push(const T &item);
	T pop();
	void insert(int index, const T &item);
	void clean();
	int get_size();
	void erase(int start, int end);
	T get_item(int index);
	MyList get_item(int start, int end);
	int count(const T &item);
	void remove(const T&item);
	void reverse();
	void sort(bool less=true);

	MyList<T> &operator = (const MyList<T> &l);
	MyList<T> &operator += (const T &item);
	MyList<T> &operator += (const MyList<T> &l);
	T &operator [] (int index);

	~MyList(){delete [] a;}
};


//-----------------------------------------------------------------------------
template <class T>
MyList<T>::MyList(int num, const T &item)
{
    size = num * 2;
    last = num;
    a = new T[size];
    for(int i = 0;i < num;++i)
    {
        a[i] = num;
    }
};

//-----------------------------------------------------------------------------
template <class T>
MyList<T>::MyList(const MyList &l)
{
    size = l.size;
    a = new T[size];
    for ( int i = 0;i< size;++i)
    {
        a[i] = l.a[i];
    }
    last = size - 1;
};


//-----------------------------------------------------------------------------
//  create MyList by the elements of *arr from 0 to len.
template <class T>
MyList<T>::MyList(T* arr, int len)
{
    last = len - 1;
    size = len;
    for(int i = 0;i < size;++i)
    {
        a[i] = arr[i];
    }
};


//-----------------------------------------------------------------------------
//add item to the last position.
template <class T>
void MyList<T>::push(const T &item)
{
    if (last < size)
    {
        a[last] = item;
        ++ last;
    }
    else
    {
        double_space();
        a[last] = item;
        ++ last;
    }
};



//-----------------------------------------------------------------------------
//delete the last element and return it.
template <class T>
T MyList<T>::pop()
{
    try{
        if(last == 0) throw (0.0);
        T tmp  = a[last];
        a[last] = 0;
        --last;
        return tmp;}
    catch(double){
        cout << "Empty list!" << endl;exit(0);
        }
};



//-----------------------------------------------------------------------------
//insert item to the index position.
template <class T>
void MyList<T>::insert(int index, const T &item)
{
    try{
		if (index<0 || index>last) throw(0.0);
        last++;
        while (index >= size)
        {double_space();}
        for(int i = last;i >= index+1;--i){a[i] = a[i-1];}
        a[index] =item;}
    catch (double) {
		cout<<"Index out of range!"<<endl; exit(0);
		}
};


//-----------------------------------------------------------------------------
//clear.
template <class T>
void MyList<T>::clean()
{
    last = 0;
};



//-----------------------------------------------------------------------------
//return the number of elements.
template <class T>
int MyList<T>::get_size()
{
    return last;
};




//-----------------------------------------------------------------------------
//erase the start-th to end-th elements.If start > end,return empty.
template <class T>
void MyList<T>::erase(int start, int end)
{
    try{
		if (start+last<0 || start>=last || end+last<0 || end>=last) throw(0.0);
        if (start<0) start+=last;
		if (end<0) end+=last;
		if (start>end) {last=0;return ;}
		for (int i=end;i<last;++i) a[i-end+start]=a[i+1];
		last-=(end-start+1);}
    catch (double){
		cout<<"Index Overflow!"<<endl;exit(0);
		}
};



//-----------------------------------------------------------------------------
//return the index-th element.
template <class T>
T MyList<T>::get_item(int index)
{
    try{
		if (index<0||index>=size) throw(0.0);
        return a[index];}
    catch (double) {
		cout<<"Index out of range!"<<endl;exit(0);
		}
};



//-----------------------------------------------------------------------------
//return the elements from start to end.Negative numbers are accepted.
template <class T>
MyList<T> MyList<T>::get_item(int start, int end)
{
    if (start < 0)
    {start = last + start;}
    if (end < 0)
    {end = last + end;}
    try{
        if(start > last || end < 0) throw (0.0);
        MyList b;
        b.last = end-start+1;
        b.size = b.last + 1;
        delete []b.a;
        b.a = new T [last];
        for(int i = 0;i <= end -start;++i)
        {
            b.a[i] = a[start + i];
        }
        return b;}
    catch(double){cout << "Index out of range!" << endl;exit(0);}

};




//-----------------------------------------------------------------------------
//return the number of item in MyList.
template <class T>
int MyList<T>::count(const T &item)
{
    int num = 0;
    for(int i = 0;i < last;++i)
    {
        if (a[i] == item)
        {
            num ++;
        }
    }
    return num;
};

//-----------------------------------------------------------------------------
//delete the first element equivalent to item.
template <class T>
void MyList<T>::remove(const T &item)
{
    bool flag=true;
	int i;
	for (i=0;i<last;++i)
		if (a[i]==item){flag=false;break;}
	if (!flag){
		for (int j=i;j<last-1;++j)
			a[j]=a[j+1];
		--last;
	}
};



//-----------------------------------------------------------------------------
template <class T>
MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2)
{
    MyList<T> b;
    b.last = l1.last +l2.last;
    while(b.size < b.last)
    {
        b.double_space();
    }
    for(int i = 0; i < l1.last;++i)
    {
        b.a[i] = l1.a[i];
    }
    for(int i = l1.last;i < b.last;++i)
    {
        b.a[i] = l2.a[i-l1.last];
    }
    return b;
};

//-------------------------------------------------------------------------------
template <class T>
MyList<T> operator + (const MyList<T> &l1, const T &item)
{
    MyList<T> b;
    b.size = l1.size*2;
    b.last = l1.last+1;
    delete [] b.a;
    b.a = new T[b.size];
    for(int i = 0;i < b.last -1;++i)
    {
        b.a[i] = l1.a[i];
    }
    b.a[b.last-1] = item;
    return b;
};


//---------------------------------------------------------------------------------
template <class T>
MyList<T> &MyList<T>::operator = (const MyList<T> &l)
{
    size = l.size;
    last = l.last;
    delete []a;
    a= new T[size];
    for(int i = 0;i<l.last;++i)
    {
        a[i] = l.a[i];
    }
};


//-----------------------------------------------------------------------------
template <class T>
MyList<T> &MyList<T>::operator += (const T &item)
{
    *this = *this + item;
};


//-----------------------------------------------------------------------------
template <class T>
MyList<T> &MyList<T>::operator += (const MyList<T> &l)
{
    *this = *this +l;
};


//-----------------------------------------------------------------------------
template <class T>
T &MyList<T>::operator [](int index)
{
    try{
        if (index > last) throw (0.0);
        return a[index];}
    catch(double){cout << "Index out of range." << endl;exit(0);}
};



//-----------------------------------------------------------------------------
template <class T>
ostream &operator<<(ostream &os, const MyList<T> &obj)
{
    os << "[";
    for(int i = 0; i < obj.last-1;++i)
    {
        os << obj.a[i] << ", ";
    }
    cout << obj.a[obj.last-1] ;
    os <<"]";
};

//-----------------------------------------------------------------------------
template <class T>
void Qsort(T a[], int low, int high)
{
    if(low >= high) return;
    int first = low,last_ = high;
    int t1 = a[first];
    while(first < last_){
        while(first < last_ && a[last_] >= t1) --last_;
        a[first] = a[last_];
        while(first < last_ && a[first] <= t1) ++first;
        a[last_] = a[first];
    }
    a[first] = t1;
    Qsort(a,low, first-1);
    Qsort(a,first+1, high);
};
template <class T>
void MyList<T>::sort(bool less){
    Qsort(a,0,last-1);
    if (!less) this->reverse();};


//-----------------------------------------------------------------------------
//Make the elements reversed.
template <class T>
void MyList<T>:: reverse()
{
    T *b;
    b = new T [last+1];
    for(int i = 0;i < last;++i)
    {
        b[i] = a[last-i-1];
    }
    delete []a;
    a = new T [size];
    for(int i = 0;i <last;++i)
    {
        a[i] = b[i];
    }
    delete []b;
};



//-----------------------------------------------------------------------------


int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
    // a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = [] *Èôstart > end£¬·µ»Ø¿ÕÊý×é
	b = a.get_item(3, -1); // b = [1, 0, 12]
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 0, 12]
	b = a + a; // b = [15, 4, 0, 12, 15, 4, 0, 12]
	b.insert(3, 116); // b = [15, 4, 0, 116, 12, 15, 4, 0, 12]
	b.remove(4); // b = [15, 0, 116, ...]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;

	return 0;
}



