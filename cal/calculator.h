#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED
#include<map>
#include<string>
using namespace std ;
class calculator{
	protected:
		calculator * leftchild ;
		calculator * rightchild ;
	public:
		calculator():leftchild(NULL) , rightchild(NULL){};
		virtual ~calculator(){}  ;
		virtual void print(){} ;
		virtual int isNumber(){} ;
		virtual float getNum(){} ;
		virtual char getopr(){} ;
        virtual int getlevel(){} ;
};
class number : public calculator{
	private:
		float numbers ;
	public:
		number(float num):numbers(num){
		}
		number(const number &rhs){
			operator=(rhs) ;
		}
        number& operator=(const number &rhs){//number newnum;nuenum = rhs ;
			if(this != &rhs){
				numbers = rhs.numbers ;
			}
			return *this ;
		}
		void print(){
            cout << numbers << " ";
		}
		int isNumber(){
            return 1 ;
		}
		float getNum(){
            return numbers ;
		}
		char getopr(){
            return 0 ;
		}
		int getlevel(){
            return 0 ;
		}
};
class opr : public calculator {
	public:
		char op ;
		int level ;
		opr(char opt , int lv):op(opt) , level(lv){}
		opr(const opr &rhs){
			operator=(rhs);
		}
		const opr& operator=(const opr &rhs){
			if(this != &rhs){
				op = rhs.op ;
			}
			return *this ;
		}
		void print(){
		cout << op << " " ;
		}
		int isNumber(){
            return 0 ;
		}
		char getopr(){
            return op ;
		}
		int getlevel(){
            return level ;
		}
		float getNum(){
            return 0 ;
		}
};


#endif // CALCULATOR_H_INCLUDED
