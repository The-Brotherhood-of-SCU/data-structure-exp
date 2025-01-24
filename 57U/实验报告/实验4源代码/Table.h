//
// Created by Administrator on 2024/12/5.
//

#ifndef EXP4_TABLE_H
#define EXP4_TABLE_H

#include <random>
#include "graph.h"
#include <cstdlib>
using namespace std;

enum dayType{
    morning,afternoon,evening
};
struct Bundle{
    int day=0;
    dayType dayType{};
    int totalDuration{};
    vector<Node*> classes;
};
class SemesterTable{
public:
    SemesterTable()=default;
    //模拟川大课表，上午4，下午5，晚上3节课
    static vector<Bundle> put(vector<Node*> classes){
        //尽量不要早八，不要晚十
        //先尝试全部排在下午
        //5->2+3;6->3+3
        vector<Node*> v2;
        v2.reserve(classes.size());
        for(auto i:classes){
            v2.push_back(i);
            if(i->credit>=4){
                while (i->credit>=4){
                    i->credit=i->credit-2;
                    auto j=new Node(i->name,i->credit,i->credit,i->semester);
                    j->credit=2;
                    v2.push_back(j);
                }
            }
        }
        classes=v2;
        vector<Bundle> bundles;
        int limit=5;
        arrange:
        int day=0;
        for (size_t i = 0; i < classes.size(); ++i) {
            if (day == 5) {
                break;
            }

            if (classes[i] == nullptr) {
                continue;
            }
            day++;
            Bundle bundle;
            bundle.day=day*2%5;
            bundle.classes.push_back(classes[i]);
            int availableCourse = limit - classes[i]->credit;
            classes[i] = nullptr;

            for (size_t j = 0; j < classes.size(); ++j) {
                if (classes[j] == nullptr) {
                    continue;
                }
                bool isSame = false;
                for (auto& k : bundle.classes) {
                    if (k->name == classes[j]->name) {
                        isSame = true;
                        break;
                    }
                }
                if (isSame) {
                    continue;
                }
                if (classes[j]->credit <= availableCourse) {
                    bundle.classes.push_back(classes[j]);
                    availableCourse -= classes[j]->credit;
                    classes[j] = nullptr;
                }
            }
            bundle.totalDuration = limit - availableCourse;
            bundles.push_back(bundle);
        }

        if(isRest(classes)&& limit>=3){
            limit--;
            goto arrange;
        }
        if(bundles.size()>15){
            cout<<"can not arrange"<<endl;
        }
        //sort the bundles by its totalDuration
        auto cmp=[](const void* a,const void* b){
            int m=((Bundle*)a)->totalDuration;
            int n=((Bundle*)b)->totalDuration;
            if(m==n){
                return 0;
            }
            if(m<n){
                return 1;
            }
            return +1;
        };
        qsort(bundles.data(),bundles.size(),sizeof(Bundle),cmp);
        for(int i=0;i<3;i++){
            for(int j=0;j<5;j++){
                int index=5*i+j;
                if(index>=bundles.size()){
                    break;
                }
                dayType dayType;
                switch (i) {
                    case 0:
                        dayType=afternoon;
                        break;
                    case 1:
                        dayType=morning;
                        break;
                    case 2:
                        dayType=evening;
                        break;
                }
                bundles[index].dayType=dayType;
            }
        }
        return bundles;
    }
    static bool isRest(const vector<Node*>& table){
        for(auto& i:table){
            if(i!= nullptr){
                return true;
            }
        }
        return false;
    }


private:
};

class Table {
private:
vector<vector<Node*>> semesterClasses;
Graph graph;
public:
    vector<vector<Bundle>> arranged;
explicit Table(const string& filename):graph(filename){
    semesterClasses=graph.arrange();
    arranged=arrange();
}
void dispose(){
    graph.dispose();
}
vector<vector<Bundle>> arrange(){
    vector<vector<Bundle>> result;
    result.reserve(semesterClasses.size());
    for(const auto& i:semesterClasses){
        result.push_back(SemesterTable::put(i));
    }
    return result;
}
void print(){
    for (int i = 0; i < arranged.size(); ++i) {
        cout << "# " << i + 1 << " semester ----------------" << endl;
        for (int j = 0; j < arranged[i].size(); ++j) {
            //cout << " - " << j + 1 << " 节:";
            auto bundle=arranged[i][j];
            cout<<"周"<<bundle.day+1<<" "<<getDayType(bundle.dayType)<<" "<<bundle.totalDuration<<"节课:";
            for (int k = 0; k < bundle.classes.size(); ++k) {
                cout << bundle.classes[k]->name << "("<<bundle.classes[k]->credit<<") ";
            }
            cout << endl;
        }
    }
}
private:
    string getDayType(dayType dayType){
        switch (dayType) {
            case morning:
                return "早上";
            case afternoon:
                return "下午";
            case evening:
                return "晚上";
        }
    }

};


#endif //EXP4_TABLE_H