//
// Created by Administrator on 2024/12/5.
//

#include <utility>
#include <functional>
#include "vector"
#include "string"
#include "Utils.h"

#ifndef EXP4_GRAPH_H
#define EXP4_GRAPH_H
using namespace std;

class Node{
public:
    [[nodiscard]] Node* copy() const{
        auto o= new Node(name,index,credit,semester);
/*        Node* o= (Node*)malloc(sizeof(Node));
        if(o==nullptr){
            cout<<"malloc failed"<<endl;
            exit(1);
        }
        o->name=name;
        o->index=index;
        o->credit=credit;
        o->semester=semester;*/
        return o;
    }
    Node(string name,int index,int credit,int semester){
        this->semester=semester;
        this->name=std::move(name);
        this->index=index;
        this->credit=credit;
    }
    string name;
    int index;
    int credit;
    int semester=0;
};
class Edge {
public:
    Edge(Node *start, Node *end) : start(start), end(end) {}
    Node *start;
    Node *end;
};
class Graph {
public:

    explicit Graph(const string& content){
        auto lines=Utils::splitString(content);
        auto line0=lines[0];
        for(const auto& i:Utils::splitString(line0,' ')){
            classesPerSemesters.push_back(stoi(i));
        }
        nodes=vector<Node*>(lines.size());
        for(int lineIndex=1;lineIndex<lines.size();lineIndex++){
            auto parameters=Utils::splitString(lines[lineIndex],' ');
            auto index=stoi(parameters[0]);
            auto name=parameters[1];
            auto credit=stoi(parameters[2]);
            auto fixedSemester=stoi(parameters[3]);

            Node* node=new Node(name,index,credit,fixedSemester);
            if(fixedSemester!=0){
                fixedNodes.push_back(node);
            }else{
                nodes[index]=node;
            }
            //edge
            for(const auto& i:Utils::splitString(parameters[4],',')){
                int preClass=stoi(i);
                if(preClass==0){
                    continue;
                }
                Edge* edge=new Edge(nodes[preClass],node);
                edges.push_back(edge);
            }

        }
    }
    vector<int> classesPerSemesters;
    vector<Edge*> edges;
    vector<Node*> nodes;
    vector<Node*> fixedNodes;
    vector<vector<Node*>> arrange(){
        //get all path
        auto allPath=getAllPath();
        //cout<<"there are "<<allPath.size()<<" paths"<<endl;
        //take the first path
        auto path=allPath[0];
        int index=0;
        auto getOne=[&](){
            return path[index++];
        };

        vector<vector<Node*>> result;
        for(int semester=0;semester<classesPerSemesters.size();semester++){
            vector<Node*> semesterResult;
            int availableClasses=classesPerSemesters[semester];
            for(auto fixedNode:fixedNodes){
                if(fixedNode->semester==semester+1){
                    semesterResult.push_back({fixedNode});
                    availableClasses--;
                }
            }
            for(int i=0;i<availableClasses;i++){
                semesterResult.push_back(getOne());
            }
            result.push_back(semesterResult);
        }
        return result;
    }
    void dispose(){
        for(auto i:nodes){
            //delete i;
        }
        for(auto i:edges){
            delete i;
        }
        for(auto i:fixedNodes){
            //delete i;
        }
    }
private:
    using Recorder = function<void(vector<Node*>)>;
    using StopSignal = function<bool()>;
    [[nodiscard]] vector<vector<Node*>> getAllPath() const{
        vector<vector<Node*>> allResult;
        Recorder recorder=[&](const vector<Node*>& result) {
            allResult.push_back(result);
        };
        StopSignal stopSignal=[&]() {
            return allResult.size()>=1000;
        };
        getOne(nodes,edges,{},recorder,stopSignal);
        return allResult;
    }

    static void getOne(const vector<Node*>& nodes,
                       const vector<Edge*>& edges,
                       const vector<Node*>& result,
                       Recorder& recorder,
                       StopSignal& stopSignal
                       ){
        if(stopSignal()){
            return;
        }
        //find node that inDegree==0
        auto zeroInDegreeNode=findNodeZeroInDegree(nodes,edges);
        if(zeroInDegreeNode.empty()){
            recorder(result);
        }
        for(auto i:zeroInDegreeNode){
            auto result_copy=result;
            result_copy.push_back(i);

            auto node_copy=nodes;
            auto edges_copy=edges;
            //delete node
            deleteNode(i,node_copy);
            //delete out edge
            for(auto j:findOutEdge(i,edges_copy)){
                deleteEdge(j,edges_copy);
            }
            getOne(node_copy, edges_copy, result_copy, recorder,stopSignal);
        }

    }
    static vector<Edge*> findInEdge(Node* node,const vector<Edge*>& edges){
        vector<Edge*> result;
        for(auto i:edges){
            if(i==nullptr){
                continue;
            }
            if(i->end==node){
                result.push_back(i);
            }
        }
        return result;
    }
    static vector<Edge*> findOutEdge(Node* node,const vector<Edge*>& edges){
        vector<Edge*> result;
        for(auto i:edges){
            if(i==nullptr){
                continue;
            }
            if(i->start==node){
                result.push_back(i);
            }
        }
        return result;
    }
    static vector<Node*> findNodeZeroInDegree(const vector<Node*>& nodes,const vector<Edge*>& edges){
        vector<Node*> result;
        for(auto i:nodes){
            if(i==nullptr){
                continue;
            }
            if(findInEdge(i,edges).empty()){
                result.push_back(i);
            }
        }
        bool isEdgeRemain=false;
        for(auto i:edges){
            if(i!=nullptr){
                isEdgeRemain=true;
                break;
            }
        }
        if(result.empty()&& isEdgeRemain){
            cout<<"there is a circle"<<endl;
        }
        return result;
    }
    static void deleteNode(Node* node,vector<Node*>& nodes){
        nodes[node->index]=nullptr;
    }
    static void deleteEdge(Edge* edge,vector<Edge*>& edges){
        for(auto & i : edges){
            if(i==edge){
                i=nullptr;
                return;
            }
        }
    }
};


#endif //EXP4_GRAPH_H
