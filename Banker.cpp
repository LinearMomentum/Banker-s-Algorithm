#include <iostream>
#include <vector>
using namespace std;
bool Banker(vector<vector<int>> request,int Available[]){
    bool done=true;
    do{
        done=true;
        bool remove=true;
        for(int i=0;i<request.size();i++){
            for(int j=1;j<request[i].size();j++){
                if(request[i][j]>Available[j-1])
                    remove=false;
            }
            if(remove){
                for(int j=1;j<request[i].size();j++){
                    Available[j-1]+=request[i][j];
                }
                request.erase(request.begin()+i);
                done=false;
                cout<<"remvoe\n";
            }
        }
    }while(!done);
    return request.empty();
}
int main(){
    int types;
    cin>>types;
    int Max[types];
    int Available[types];
    vector<vector<int>> processes; //int[0] is PID
    for(int i=0;i<types;i++){
        cin>>Max[i];
        Available[i]=Max[i];
    }
    vector<vector<int>> running;
    while(1){
        int PID;
        cin>>PID;
        string command;
        cin>>command;
        int request[types];
        if(command!="terminate"){
            for(int i=0;i<types;i++){
                cin>>request[i];
            }
            if(command=="new"){ //command new
                bool insert=true;
                for(int i=0;i<processes.size();i++){
                    if(processes.at(i)[0]==PID)
                        insert=false;
                }
                for(int i=0;i<types;i++){
                    if(Max[i]<request[i])
                        insert=false;
                }
                if(!insert)
                    cout<<"NOT OK"<<endl;
                else{
                    vector<int> process;
                    process.push_back(PID);
                    for(int i=0;i<types;i++)
                        process.push_back(request[i]);
                    processes.push_back(process);
                    cout<<"OK\n";
                }
            }
            else{ //command request;
                bool allow=true,exit=false;
                for(int i=0;i<processes.size();i++){
                    if(processes[i][0]==PID){
                        exit=true;
                        for(int j=0;j<types;j++){
                            if(request[j]>processes[i][j+1])   //need
                                allow=false;
                            if(request[j]>Available[j])//remain
                                allow=false;
                        }
                    }
                }
                if(allow) allow=Banker(running,Available);
                if(!exit) allow=false;
                if(!allow) cout<<"NOT OK"<<endl;
                else{ 
                    cout<<"OK\n";
                    vector<int> process;
                    process.push_back(PID);
                    for(int i=0;i<types;i++){
                        process.push_back(request[i]);
                        Available[i]-=request[i];
                        }
                    running.push_back(process);
                }
            }
        }
        else{   // command terminate
            bool ok=false;
            for(int i=0;i<running.size();i++){
                if(running.at(i)[0]==PID){
                    for(int j=0;j<types;j++){
                        Available[i]+=running.at(i)[j+1];
                    }
                    running.erase(running.begin()+i);
                    cout<<"OK\n";
                    ok=true;
                    break;
                }
            }
            if(!ok)
                cout<<"NOT OK"<<endl;
        }
    }
}