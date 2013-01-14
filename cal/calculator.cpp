#include<iostream>
#include<string>
#include<ctype.h>
#include<vector>
#include<stack>
#include<math.h>
#include<list>
#include"calculator.h"
#include"operators.h"
int procal(const string& , vector<calculator*>&);
using namespace std ;
float cclt(const string &) ;
int getNum(string , int , float &) ;
void init() ;
void printcal(list<calculator*>&) ;
void sufcal( vector<calculator*>& , list<calculator*>& ) ;
int main(){
    string str ;
    getline(cin , str);
    float num = 0 ;
    //int a = getNum(str , 0 , num) ;
    //cout << "a" << a << "num" << num << endl ;
    float answer = cclt(str);
    cout << answer << endl ;
    return 0 ;
}
void init(){
    fpmap['+'] = add ;
    fpmap['-'] = subtraction ;
    oplevel['+'] = 1 ;
    oplevel['-'] = 1 ;
    oplevel['*'] = 2 ;
    oplevel['/'] = 2 ;
    oplevel['('] = 3 ;
    oplevel[')'] = 3 ;

}
float cclt(const string &str){
    vector<calculator*> calt ;
    int rs = procal(str , calt) ;
    if(!rs){
        cout << "ererr" ;
    }
    list<calculator*> scal ;
    sufcal(calt , scal) ;
    printcal(scal) ;

    return 1 ;
}
void sufcal(vector<calculator*>& cal , list<calculator*>& scal){
    stack<calculator*> midopr ;
    calculator* mop ;
    for(int i = 0 ; i < cal.size() ; i++){
        if(cal[i]->isNumber()){
            scal.push_back(cal[i]) ;
        }else{
            if(midopr.empty()){
                midopr.push(cal[i]) ;
            }else{
                mop = midopr.top() ;
                if(cal[i]->getopr() == ')'){
                    while(mop->getopr() != '('){
                        scal.push_back(mop);
                        midopr.pop() ;
                        mop = midopr.top() ;
                    }
                    midopr.pop() ;
                }else{
                    if(mop->getlevel() <= oplevel[cal[i]->getopr()]){
                        midopr.push(cal[i]) ;
                    }else{
                        while(mop->getlevel() > oplevel[cal[i]->getopr()]){
                            scal.push_back(cal[i]) ;
                            midopr.pop() ;
                            mop = midopr.top() ;
                        }
                    }
                }
            }
        }
    }
    while(!midopr.empty()){
        mop = midopr.top() ;
        scal.push_back(mop) ;
        midopr.pop() ;
    }
}
int procal(const string& str, vector<calculator*>& cal){
    calculator* newcal , *numcal;
    float num ;
    int advance = 0 ;
    int jud = 0 ;
    for(int i = 0 ; i < str.size() ; i++){
        if(!isdigit(str[i])){
            switch(str[i]){
                case '(' : case ')':case '*' : case '/': case '+':
                    newcal = new opr(str[ i ] , oplevel[ str[ i ] ]) ;
                    cal.push_back(newcal) ;
                    jud = 0 ;
                    break ;
                case '-':
                    advance = getNum(str , i + 1 , num ) ;
                    i = i + advance ;
                    num *= -1 ;
                    newcal = new opr('+' , oplevel[ '+' ]) ;
                    numcal = new number(num) ;
                    if(jud == 0 ){
                        cal.push_back(numcal) ;
                    }
                    else {
                        cal.push_back(newcal) ;
                        cal.push_back(numcal) ;
                    }
                    break ;
                default :
                    return 0 ;
            }
        }else{
            advance = getNum(str , i , num);
            i = i + advance - 1 ;
            newcal = new number(num) ;
            cal.push_back(newcal) ;
            jud = 1 ;
        }
    }
    return 1 ;
}
void printcal(list<calculator*>& cal){
   for(list<calculator*>::iterator iter = cal.begin() ; iter != cal.end() ; iter++){
        (*iter)->print() ;
   }
}
int getNum(string str , int begin , float &number ){
    int advance = 0 ;
    int dot = 0 ;
    vector<int> amb ;
    number = 0 ;
    int advance1 ;
    for(int i = begin ; i < str.size() ; i++ ){
        if(isdigit(str[i])){
            amb.push_back(str[i] - '0') ;
            advance++ ;
        }
        else if(str[i] == '.'){
            dot = advance ;
            advance++ ;
        }
        else
        break ;
    }
    if(dot == 0 ){
        dot = advance ;
        advance1 = advance ;
    }else{
        advance1 = advance - 1 ;
    }
    for(int i = 0 ; i < advance1 ; i++){
        number += amb[i] * pow(10 , (dot - i - 1)) ;
    }
    return advance ;
}
