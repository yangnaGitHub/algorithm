#include <iostream>
#include <cstring>
#include <stack>
/************************************************************
逆波蘭後綴表達式計算數字的運算（編譯原理）
我們看到的數學表達式是一般的中序表達式（中綴表達式）（請結合樹）
中綴表達式轉換成后綴后前綴表達式能有效地處理
*************************************************************/
using namespace std;
class Point{
    float first, second, third, four;
    stack<float> result;
    stack<float> sign;
    public:
    Point():first(0),second(0),third(0),four(0){};
    Point(float first, float second, float third, float four):first(first),second(second),third(third),four(four){};
    void SetInitNum();
    void GetResult();
    void AddSpace(float *Array, int Size);
    int MoveMethod(float *Array, int Size, int startone, int endone, int starttwo, int endtwo);
    void ShowArray(float *Array, int Size);
    void Calculate(float *Array, int Size);
    void BackUpArray(float *Array, float *BackUp, int Size);
};

void Point::SetInitNum(){
    cout << "Enter the Four Number > ";
    cin >> Point::first >> Point::second >> Point::third >> Point::four;
}
//+ - * /
void Point::GetResult(){
    float Array[10] = {0};
    float foursign[4] = {-1, -2, -3, -4};
    int xindex = 0, yindex = 0, zindex = 0;
    //初始化最初的表達式（沒有括號）
    for(xindex = 0; xindex < 4; xindex++){
        for(yindex = 0; yindex < 4; yindex++){
            for(zindex = 0; zindex < 4; zindex++){
                memset(Array, 0, 10 * sizeof(float));
                Array[0] = Point::first;
                Array[1] = foursign[xindex];
                Array[2] = Point::second;
                Array[3] = foursign[yindex];
                Array[4] = Point::third;
                Array[5] = foursign[zindex];
                Array[6] = Point::four;
                AddSpace(Array, 7);
            }
        }
    }
}
//添加括號并計算
void Point::AddSpace(float *Array, int Size){
    int NewSize = 0;
    float TempArray[10];
    BackUpArray(Array, TempArray, Size);
    //(x y) m n
    NewSize = MoveMethod(Array, Size, 0, 2, 3, 6);
    //ShowArray(Array,NewSize);
    Calculate(Array, NewSize);
    //(x y m) n
    BackUpArray(TempArray, Array, Size);
    NewSize = MoveMethod(Array, Size, 0, 4, 5, 6);
    //ShowArray(Array,NewSize);
    Calculate(Array, NewSize);
    //x (y m) n
    BackUpArray(TempArray, Array, Size);
    NewSize = MoveMethod(Array, Size, 2, 4, 5, 6);
    //ShowArray(Array,NewSize);
    Calculate(Array, NewSize);
    //x (y m n)
    BackUpArray(TempArray, Array, Size);
    NewSize = MoveMethod(Array, Size, 2, 6, 0, 0);
    //ShowArray(Array,NewSize);
    Calculate(Array, NewSize);
    //x y (m n)
    BackUpArray(TempArray, Array, Size);
    NewSize = MoveMethod(Array, Size, 4, 6, 0, 0);
    //ShowArray(Array,NewSize);
    Calculate(Array, NewSize);
}

int Point::MoveMethod(float *Array, int Size, int startone, int endone, int starttwo, int endtwo){
    if(0 != endtwo){
        while(starttwo <= endtwo){
            Array[endtwo + 2] = Array[endtwo];
            endtwo--;
        }
        Array[starttwo + 1] = -6;
    }else Array[Size + 1] = -6;
    if(0 != endone){
        while(startone <= endone){
            Array[endone + 1] = Array[endone];
            endone--;
        }
        Array[startone] = -5;
    }
    return Size + 2;
}
//打印
void Point::ShowArray(float *Array, int Size){
    int index = 0;
    float temp = 0;
    while(index < Size){
        temp = Array[index];
        if(0 > temp){
            if(-1 == temp)
                cout << "+";
            else if(-2 == temp)
                cout << "-";
            else if(-3 == temp)
                cout << "*";
            else if(-4 == temp)
                cout << "/";
            else if(-5 == temp)
                cout << "(";
            else if(-6 == temp)
                cout << ")";
            index++;
            continue;
        }
        cout << temp;
        index++;
    }
    cout << "\t";
}
//備份最初的數學表達式
void Point::BackUpArray(float *Array, float *BackUp, int Size){
    int index = 0;
    memset(BackUp, 0, 10 * sizeof(float));
    while(index < Size)
        BackUp[index] = Array[index++];
}
//中綴表達式變後綴表達式并計算
void Point::Calculate(float *Array, int Size){
    int index = 0, spaceflag = 0;
    float temp = 0, spacetemp = 0, before = 0, after = 0;
    //ShowArray(Array, Size);
    while(index < Size){
        temp = Array[index++];
        if(temp > 0)
            Point::result.push(temp);
        else{
            if((-1 == temp) || (-2 == temp)){
                while(!Point::sign.empty()){//+ -優先級比較低的問題
                    spacetemp = Point::sign.top();
                    Point::sign.pop();
                    if(-5 != spacetemp)
                        Point::result.push(spacetemp);
                    else{
                        spaceflag = 1;
                        break;
                    }
                }
                if(spaceflag){
                    Point::sign.push(-5);
                    spaceflag = 0;
                }
                Point::sign.push(temp);
            }else if(-6 == temp){//括號匹配的問題
                while(1){
                    spacetemp = Point::sign.top();
                    Point::sign.pop();
                    if(-5 == spacetemp)
                        break;
                    else Point::result.push(spacetemp);
                    if(Point::sign.empty()){
                        cout << "Error" << endl;
                        break;
                    }
                }
            }else if(-4 == temp){//解決多個除法的問題
                if(!Point::sign.empty()){
                    spacetemp = Point::sign.top();
                    if(-4 == spacetemp){
                        Point::result.push(spacetemp);
                        Point::sign.pop();
                    }
                }
                Point::sign.push(temp);
            }else Point::sign.push(temp);
        }
    }
    while(!Point::sign.empty()){
        spacetemp = Point::sign.top();
        Point::sign.pop();
        Point::result.push(spacetemp);
    }
    index = 0;
    while(!Point::result.empty()){
        Array[index++] = Point::result.top();
        Point:result.pop();
    }
    Size = index;
    while(0 < index){
        temp = Array[--index];
        if(temp > 0)
            Point::result.push(temp);
        else{
            after = Point::result.top();
            Point::result.pop();
            before = Point::result.top();
            Point::result.pop();
            if(-1 == temp)
                before = before + after;
            else if(-2 == temp)
                before = before - after;
            else if(-3 == temp)
                before = before * after;
            else if(-4 == temp)
                before = before / after;
            Point::result.push(before);
        }
    }
    temp = Point::result.top();
    Point::result.pop();
    if(24 == temp){
        ShowArray(Array, Size);
        cout << temp << endl;
    }
}

int main(void){
    Point My24Point(5, 5, 5, 5);
    My24Point.GetResult();
    return 0;
}
