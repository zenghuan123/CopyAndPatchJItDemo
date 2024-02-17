#ifndef HEAD_H
#define HEAD_H
#include<vector>
#include<tuple>
#include<unordered_map>
#include<chrono>
#include<iostream>
#include<list>
#include<elf.h>
#include<string.h>
enum class HOLE_TYPE
{
	NEXT_FUN = 0,
	CONST_DATA = 1,
	EXTERN_DATA = 2,
	COMMON_DATA = 3,
	EXTERN_FUN=4
};
struct HoleData {
	HOLE_TYPE hole_type;
	Elf64_Xword reloc_type;
	Elf64_Sxword added;
	Elf64_Addr	offset;

	size_t data_offset;
	size_t patch_index;
};


struct TemplateData {
	size_t const_data_size;
	uint8_t* const_data;
	size_t extern_data_size;
	HoleData* all_holes;
	size_t hole_size;
	uint8_t* code;
	size_t code_size;

};
struct PatchData
{
	std::vector<uint64_t> extern_data_patch_values;
	TemplateData* template_data;
	size_t common_data_size=0;
};


class Data {
public:
	Data() :value(0) {};
	Data(double value) :value(value) {};
	double value;
};
class DataManager {
private:
	std::unordered_map<std::string, int> name_to_idx;
	std::vector<Data> all_data;
	std::vector<int> update_list;
public:
	DataManager(int size);
	void set(std::string name,int id,std::vector<int>&&need_update_list);
	void set_value(std::string name, double value);
	void set_value(int idx, double value) ;
	double get_value(const std::string& name);
	double get_value(int idx);
	// inline double get_value(int idx){
	// 	return all_data[idx].value;
	// }

};

class Expression {
public:
	virtual void caculate(int result_id, DataManager* data_manager) =0;
	virtual void caculate_all_in_one_function(int result_id,DataManager* data_manage) = 0;
	virtual size_t get_path_data(std::list<PatchData>& patch_datas) =0;
};

enum class Operator {
	DATA,
	ADD,
	SUB,
	MULTI,
	DIVED
};
struct OperatorAndData
{
	Operator op;
	int id;
};
class ArithmeticalExpression:public Expression {
private:
	using OperatorVector = std::vector<OperatorAndData>;
	OperatorVector operators;
public:
ArithmeticalExpression(OperatorVector operators);
void caculate(int result_id,DataManager*data_manager)override;
void caculate_all_in_one_function(int result_id,DataManager* data_manager)override;
size_t get_path_data(std::list<PatchData>& patch_datas) override;
};
template<typename fun_type>
uint64_t get_fun_address(fun_type f){
	auto ptr=&f;
	return *static_cast<uint64_t*>(static_cast<void*>(static_cast<void**>(static_cast<void*>(ptr))));
}
#endif
