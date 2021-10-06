#include<iostream>
#include<bits/stdc++.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "log.h"
#include "MatrixScalerOperations.h"
#include "MatrixOperations.h"
using namespace std;

 
bool isNumber( string &s) {
  return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

void test(){
    cout<<"Exting...";
    initLogger( "mylogfile.log", ldebug);

    L_(linfo) << "infasdasdo";
    endLogger();
    exit(0);
}

int main(int argc, char **argv){
    deque<int> scalar;
    deque<MatrixScalerOperations> deq;
    deque<char> orderOfEntry;
    // test();
    bool isScalerPresent=false;
    int contEmptyLines=0;
    
    initLogger( "mylogfile.log", ldebug);
    
	while(1){
		string temp;
		getline(cin,temp);
        if(contEmptyLines>=2)   break;
		if(!temp.length()){
            L_(linfo) << "Empty Line Detected";
            contEmptyLines++;
            continue;
        }
        contEmptyLines=0;
        L_(linfo) << "String scanned == "<<temp;
        if(temp[0]=='#'){
            L_(linfo) << "This Line is a comment\n";
            continue;
        }
        if(isNumber(temp)){
            scalar.push_back(atoi(temp.c_str()));
            orderOfEntry.push_back('s');
            L_(linfo) << "This Line is a scalar\n";
            continue;
        }
        
        L_(linfo) << "Matrix Detected";

        stringstream ss(temp);
        int r,c;
        string substr;
        getline(ss, substr, ' ');
        r=atoi(substr.c_str());
        getline(ss, substr, ' ');
        c=atoi(substr.c_str());
        L_(linfo) << "row == "<<r<<" col == "<<c;
        L_(linfo) << "Matrix Scanned ";
        
        MatrixScalerOperations mat(r,c);
        mat.enter();
        // mat.print();
        deq.push_back(mat);
        orderOfEntry.push_back('m');
    }

    int c;
    opterr = 0; 
    deque<char> operations;
    while ((c = getopt (argc, argv, "asmdtx:")) != -1)
        switch (c)
        {
            case '?':
                if (optopt == 'c')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
            default:
                operations.push_back((char)(c));
        }
    if(!operations.size()){
        L_(linfo) << "Exiting Program due to lack of Operations provided";
        exit(3);
    }

    while(operations.size()){
        char operation=operations.front();
        operations.pop_front();
        L_(linfo) << "Current Operation == "<< operation;

        if(operation=='a'){
            if(orderOfEntry.size()<=1){
                L_(linfo) << "Exiting Program due to lack of objects";
                exit(3);
            }else{
                char entry1=orderOfEntry.front();
                orderOfEntry.pop_front();
            
                char entry2=orderOfEntry.front();
                orderOfEntry.pop_front();
                L_(linfo) << "Adding "<<entry1 <<" and "<<entry2;
                if(entry1=='m' && entry2=='m'){
                    if(deq.size()<=1){
                        L_(linfo) << "Exiting Program due to lack of matrices";
                        exit(3);
                    }
                    MatrixOperations op;
                    MatrixScalerOperations mat1=deq.front();
                    deq.pop_front();
                    MatrixScalerOperations mat2=deq.front();
                    deq.pop_front();

                    vector<vector<int>> res=op.addMatrices(mat1.mat,mat2.mat);
                    MatrixScalerOperations resMatrix(res.size(),res[0].size());
                    resMatrix.mat=res;
                    
                    deq.push_front(resMatrix);
                    orderOfEntry.push_front('m');
                }else if((entry1=='m' && entry2=='s') || (entry1=='s' && entry2=='m')){
                    if(deq.size()<1){  
                        L_(linfo) << "Exiting Program due to lack of matrices";
                        exit(3);                              
                    }
                    if(scalar.size()<1){
                        L_(linfo) << "Exiting Program due to lack of scalar values";
                        exit(3);
                    }
                    MatrixOperations op;
                    MatrixScalerOperations mat1=deq.front();

                    int sclr=scalar.front();
                    scalar.pop_front();

                    deq.pop_front();
                    mat1.AddScaler(sclr);
                    
                    deq.push_front(mat1);
                    orderOfEntry.push_front('m');
                }else if(entry1=='s' && entry2=='s'){
                    if(scalar.size()<=1){
                        L_(linfo) << "Exiting Program due to lack of scalar values";
                        exit(3);
                    }
                    int sclr1=scalar.front();
                    scalar.pop_front();
                    int sclr2=scalar.front();
                    scalar.pop_front();

                    scalar.push_front(sclr1+sclr2);
                    orderOfEntry.push_front('s');
                }
            }
        }
        else if(operation=='s'){
            if(orderOfEntry.size()<=1){
                L_(linfo) << "Exiting Program due to lack of objects";
                exit(3);
                // Log
            }else{
                char entry1=orderOfEntry.front();
                orderOfEntry.pop_front();
            
                char entry2=orderOfEntry.front();
                orderOfEntry.pop_front();
                L_(linfo) << "Substracting "<<entry1 <<" and "<<entry2;
                if(entry1=='m' && entry2=='m'){
                    if(deq.size()<=1){
                        L_(linfo) << "Exiting Program due to lack of matrices";
                        exit(3);
                    }
                    MatrixOperations op;
                    MatrixScalerOperations mat1=deq.front();
                    deq.pop_front();
                    MatrixScalerOperations mat2=deq.front();
                    deq.pop_front();

                    vector<vector<int>> res=op.subtractMatrices(mat1.mat,mat2.mat);
                    MatrixScalerOperations resMatrix(res.size(),res[0].size());
                    resMatrix.mat=res;
                    
                    deq.push_front(resMatrix);
                    orderOfEntry.push_front('m');
                }else if((entry1=='m' && entry2=='s') || (entry1=='s' && entry2=='m')){
                    if(deq.size()<1){
                        L_(linfo) << "Exiting Program due to lack of matrices";
                        exit(3);   
                    }
                    if(scalar.size()<1){
                        L_(linfo) << "Exiting Program due to lack of scalar values";
                        exit(3);
                    }
                    MatrixOperations op;
                    MatrixScalerOperations mat1=deq.front();

                    int sclr=scalar.front();
                    scalar.pop_front();

                    deq.pop_front();
                    mat1.subtractScaler(sclr);
                    
                    deq.push_front(mat1);
                    orderOfEntry.push_front('m');
                }else if(entry1=='s' && entry2=='s'){
                    if(scalar.size()<=1){
                        L_(linfo) << "Exiting Program due to lack of scalar values";
                        exit(3);
                    }
                    int sclr1=scalar.front();
                    scalar.pop_front();
                    int sclr2=scalar.front();
                    scalar.pop_front();

                    scalar.push_front(sclr1-sclr2);
                    orderOfEntry.push_front('s');
                }
            }
        }
        else if(operation=='m'){
            if(orderOfEntry.size()<=1){
                L_(linfo) << "Exiting Program due to lack of objects";
                exit(3);
            }else{
                char entry1=orderOfEntry.front();
                orderOfEntry.pop_front();
            
                char entry2=orderOfEntry.front();
                orderOfEntry.pop_front();

                
                if(entry1=='m' && entry2=='m'){
                    if(deq.size()<=1){
                        L_(linfo) << "Exiting Program due to lack of matrices";
                        exit(3);
                    }
                    MatrixOperations op;
                    MatrixScalerOperations mat1=deq.front();
                    deq.pop_front();
                    MatrixScalerOperations mat2=deq.front();
                    deq.pop_front();

                    vector<vector<int>> res=op.multiplyMatrices(mat1.mat,mat2.mat);
                    MatrixScalerOperations resMatrix(res.size(),res[0].size());
                    resMatrix.mat=res;
                    
                    deq.push_front(resMatrix);
                    orderOfEntry.push_front('m');

                }else if((entry1=='m' && entry2=='s') || (entry1=='s' && entry2=='m')){
                    if(deq.size()<1){
                        L_(linfo) << "Exiting Program due to lack of matrices";
                        exit(3);   
                    }
                    if(scalar.size()<1){
                        L_(linfo) << "Exiting Program due to lack of scalar values";
                        exit(3);
                    }
                    MatrixOperations op;
                    MatrixScalerOperations mat1=deq.front();

                    int sclr=scalar.front();
                    scalar.pop_front();

                    deq.pop_front();
                    mat1.multiplyScaler(sclr);
                    
                    deq.push_front(mat1);
                    orderOfEntry.push_front('m');
                }else if(entry1=='s' && entry2=='s'){
                    if(scalar.size()<=1){
                        L_(linfo) << "Exiting Program due to lack of scalar values";
                        exit(3);
                    }
                    int sclr1=scalar.front();
                    scalar.pop_front();
                    int sclr2=scalar.front();
                    scalar.pop_front();

                    scalar.push_front(sclr1*sclr2);
                    orderOfEntry.push_front('s');
                }
            }
        }
        else if(operation=='d'){
            if(orderOfEntry.size()<=1){
                L_(linfo) << "Exiting Program due to lack of objects";
                exit(3);
            }else{
                if(deq.size()<1){
                    L_(linfo) << "Exiting Program due to lack of matrices";
                    exit(3);
                }
                if(scalar.size()<1){
                    L_(linfo) << "Exiting Program due to lack of scalar values";
                    exit(3);
                }
                
                char entry1=orderOfEntry.front();
                orderOfEntry.pop_front();
            
                char entry2=orderOfEntry.front();
                orderOfEntry.pop_front();

                if(entry1=='m' && entry2=='s' || entry2=='m' && entry1=='s' ){
                    MatrixScalerOperations mat=deq.front();
                    deq.pop_front();

                    int sclr=scalar.front();
                    scalar.pop_front();
                    
                    mat.divisionScaler(sclr);
                    deq.push_front(mat);

                    orderOfEntry.push_front('m');
            
                }
            }
        }
        else if(operation=='t'){
            if(orderOfEntry.size()<1){
                L_(linfo) << "Exiting Program due to lack of objects";
                exit(3);
            }
            else if(deq.size()<1){
                L_(linfo) << "Exiting Program due to lack of matrices";
                exit(3);
            }
            else if(orderOfEntry.front()!='m'){
                L_(linfo) << "Exiting Program because the item in queue is not a matrix";
                exit(3);
            }
            else{
                MatrixScalerOperations mat=deq.front();
                deq.pop_front();
                MatrixOperations op;
                vector<vector<int>> res=op.transposeMatrix(mat.mat);
                MatrixScalerOperations ans(res.size(),res[0].size());
                ans.mat=res;
                deq.push_front(ans);
            }
        }
        else if(operation=='x'){
            if(deq.size()<1){
                L_(linfo) << "Exiting Program due to lack of matrices";
                exit(3);
            }
            else if(orderOfEntry.front()!='m'){
                L_(linfo) << "Exiting Program because the item in queue is not a matrix";
                exit(3);
            }
            else{
                MatrixScalerOperations mat=deq.front();
                deq.pop_front();
                MatrixOperations op;
                int x = op.determinantOfMatrix(mat.mat,mat.mat.size());
                scalar.push_front(x);
                orderOfEntry.pop_front();
                orderOfEntry.push_front('s');
            }
        }
    }
    L_(linfo)<<"Closing the Logger ...";
    endLogger();
    if(orderOfEntry.size()){
        if(orderOfEntry.front()=='m'){
            MatrixScalerOperations mat=deq.front();
            cout<<mat.row<<" "<<mat.col<<endl;
            mat.print();
            deq.pop_front();
        }else{
            cout<<scalar.front()<<endl;
        }
    }
    return 0;
}