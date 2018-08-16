#include <iostream>
#include <cstdio>

using namespace std;

/*******************
3 3
0 1 1
0 2 3
1 2 1
0 2

3 3
1 2 1
1 3 2
2 3 4
3
¦}¬d¶°
********************/
int unionSearch(int root, int* roadSet){
    return (root == roadSet[root]) ? root : unionSearch(roadSet[root], roadSet);
}

int main(){
    int villageCounter = 0, roadCounter = 0;
    int maxRoad = 0, villageStart = 0, villageEnd = 0;

    while(1){
        cin >> villageCounter >> roadCounter;
        if(!villageCounter)
            break;
        int* roadSet = new int[villageCounter + 1];
        maxRoad = roadCounter - 1;
        for(int index = 1; index <= villageCounter; index++)
            roadSet[index] = index;
        while(roadCounter--){
            cin >> villageStart >> villageEnd;
            if(!villageStart || !villageEnd){
                maxRoad = -1;
                break;
            }
            villageStart = unionSearch(villageStart, roadSet);
            villageEnd = unionSearch(villageEnd, roadSet);
            if(villageStart != villageEnd){
                roadSet[villageStart] = villageEnd;
                maxRoad--;
            }
        }
        if(-1 == maxRoad)
            cout << "ERROR!" << endl;
        else cout << "minRoad >> " << maxRoad << endl;
        delete[] roadSet;
    }
}
