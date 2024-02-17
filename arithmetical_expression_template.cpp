

#include"head.h"
extern int extern_value_1;
extern int common_value_1;
extern void next_fun_1(double result,DataManager*data_manager);
template<int i>
void arithmetical_expression_caculate_entry(int result_id,DataManager*data_manager){
    if constexpr(i==0){
        //common_value_1=result_id;
        next_fun_1(0,data_manager);
    }
}
template<Operator op>
void arithmetical_expression_caculate(double result,DataManager*data_manager) {
    double value =data_manager->get_value(extern_value_1);
    if constexpr(op==Operator::ADD){
       __attribute__((musttail)) return next_fun_1(result+value,data_manager);
    }
    if constexpr(op==Operator::SUB){
       __attribute__((musttail)) return next_fun_1(result-value,data_manager);
    }
    if constexpr(op==Operator::MULTI){
        __attribute__((musttail)) return next_fun_1(result*value,data_manager);
    }
    if constexpr(op==Operator::DIVED){
        if (value == 0) {
            result=0;
          __attribute__((musttail))  return next_fun_1(result,data_manager); 
        }
        else {
          __attribute__((musttail))  return next_fun_1(result/value,data_manager); 
        }
        
    }
}

template<int i>
void arithmetical_expression_caculate_end(double result,DataManager*data_manager) {
    if(i==0){
        if(result<1){
            result=1;
        }
        data_manager->set_value(extern_value_1, result);    
    }
   
}
template
void arithmetical_expression_caculate_entry<0>(int result_id,DataManager*data_manager);
template
void arithmetical_expression_caculate<Operator::ADD>(double result,DataManager*data_manager) ;

template
void arithmetical_expression_caculate<Operator::SUB>(double result,DataManager*data_manager) ;

template
void arithmetical_expression_caculate<Operator::MULTI>(double result,DataManager*data_manager) ;

template
void arithmetical_expression_caculate<Operator::DIVED>(double result,DataManager*data_manager) ;

template
void arithmetical_expression_caculate_end<0>(double result,DataManager*data_manager);