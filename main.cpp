
#include "head.h"
#include "arithmetical_expression_template.h"
DataManager::DataManager(int size):all_data(size) {
}
void DataManager::set(std::string name,int id,std::vector<int>&&need_update_list) {
    name_to_idx[name] = id;
    all_data[id] = Data(0);
    update_list = std::move(need_update_list);

}
void DataManager::set_value(std::string name, double value) {
    auto it = name_to_idx.find(name);
    if (it == name_to_idx.end()) {
        return;
    }
    all_data[it->second].value = value;
}
void DataManager::set_value(int idx, double value) {
    if (idx < 0) {
        return;
    }
    if (idx >= all_data.size())
    {
        return;
    }
    all_data[idx].value = value;
}
double DataManager::get_value(const std::string& name) {
    auto it = name_to_idx.find(name);
    if (it == name_to_idx.end()) {
        return 0;
    }
    return all_data[it->second].value;
}
double DataManager::get_value(int idx){
	if (idx < 0) {
		return 0;
	}
	if (idx >= all_data.size())
	{
		return 0;
	}
	return all_data[idx].value;
}

ArithmeticalExpression::ArithmeticalExpression(OperatorVector operators):operators(operators){
}

void ArithmeticalExpression::caculate(int result_id,DataManager*data_manager) {
	double result = 0;
	Operator op = Operator::ADD;
	for (int i = 0; i < operators.size();i++) {
		OperatorAndData data = operators[i];
		if (data.op == Operator::DATA)
		{
			double value =data_manager->get_value(data.id);
			switch (op)
			{
			case Operator::ADD:
				result += value;
				break;
			case Operator::SUB:
				result -= value;
				break;
			case Operator::MULTI:
				result *= value;
				break;
			case Operator::DIVED:
				if (value == 0) {
					result = 0;
				}
				else {
					result /= value;
				}
				break;
			default:
				break;
			}

		}
		else {
			op = data.op;
		}
	}
	data_manager->set_value(result_id, result);

}

void ArithmeticalExpression::caculate_all_in_one_function(int result_id,DataManager* data_manager) {
	//6 = (0 * 1 + 2) * 3 + 4 + 5
	double result = 0;
	Operator op = Operator::ADD;
	int i = 0;
	OperatorAndData data = operators[i];
	if (data.op == Operator::DATA)
	{
		double value = data_manager->get_value(data.id);
		switch (op)
		{
		case Operator::ADD:
			result += value;
			break;
		case Operator::SUB:
			result -= value;
			break;
		case Operator::MULTI:
			result *= value;
			break;
		case Operator::DIVED:
			if (value == 0) {
				result = 0;
			}
			else {
				result /= value;
			}
			break;
		default:
			break;
		}

	}
	else {
		op = data.op;
	}
	i++;
	data = operators[i];
	if (data.op == Operator::DATA)
	{
		double value = data_manager->get_value(data.id);
		switch (op)
		{
		case Operator::ADD:
			result += value;
			break;
		case Operator::SUB:
			result -= value;
			break;
		case Operator::MULTI:
			result *= value;
			break;
		case Operator::DIVED:
			if (value == 0) {
				result = 0;
			}
			else {
				result /= value;
			}
			break;
		default:
			break;
		}

	}
	else {
		op = data.op;
	}
	i++;
	data = operators[i];
	if (data.op == Operator::DATA)
	{
		double value = data_manager->get_value(data.id);
		switch (op)
		{
		case Operator::ADD:
			result += value;
			break;
		case Operator::SUB:
			result -= value;
			break;
		case Operator::MULTI:
			result *= value;
			break;
		case Operator::DIVED:
			if (value == 0) {
				result = 0;
			}
			else {
				result /= value;
			}
			break;
		default:
			break;
		}

	}
	else {
		op = data.op;
	}
	i++;
	data = operators[i];
	if (data.op == Operator::DATA)
	{
		double value = data_manager->get_value(data.id);
		switch (op)
		{
		case Operator::ADD:
			result += value;
			break;
		case Operator::SUB:
			result -= value;
			break;
		case Operator::MULTI:
			result *= value;
			break;
		case Operator::DIVED:
			if (value == 0) {
				result = 0;
			}
			else {
				result /= value;
			}
			break;
		default:
			break;
		}

	}
	else {
		op = data.op;
	}
	i++;
	data = operators[i];
	if (data.op == Operator::DATA)
	{
		double value = data_manager->get_value(data.id);
		switch (op)
		{
		case Operator::ADD:
			result += value;
			break;
		case Operator::SUB:
			result -= value;
			break;
		case Operator::MULTI:
			result *= value;
			break;
		case Operator::DIVED:
			if (value == 0) {
				result = 0;
			}
			else {
				result /= value;
			}
			break;
		default:
			break;
		}

	}
	else {
		op = data.op;
	}
	i++;
	data = operators[i];
	if (data.op == Operator::DATA)
	{
		double value = data_manager->get_value(data.id);
		switch (op)
		{
		case Operator::ADD:
			result += value;
			break;
		case Operator::SUB:
			result -= value;
			break;
		case Operator::MULTI:
			result *= value;
			break;
		case Operator::DIVED:
			if (value == 0) {
				result = 0;
			}
			else {
				result /= value;
			}
			break;
		default:
			break;
		}

	}
	else {
		op = data.op;
	}
	i++;
	data = operators[i];
	if (data.op == Operator::DATA)
	{
		double value = data_manager->get_value(data.id);
		switch (op)
		{
		case Operator::ADD:
			result += value;
			break;
		case Operator::SUB:
			result -= value;
			break;
		case Operator::MULTI:
			result *= value;
			break;
		case Operator::DIVED:
			if (value == 0) {
				result = 0;
			}
			else {
				result /= value;
			}
			break;
		default:
			break;
		}

	}
	else {
		op = data.op;
	}
	i++;
	data = operators[i];
	if (data.op == Operator::DATA)
	{
		double value = data_manager->get_value(data.id);
		switch (op)
		{
		case Operator::ADD:
			result += value;
			break;
		case Operator::SUB:
			result -= value;
			break;
		case Operator::MULTI:
			result *= value;
			break;
		case Operator::DIVED:
			if (value == 0) {
				result = 0;
			}
			else {
				result /= value;
			}
			break;
		default:
			break;
		}

	}
	else {
		op = data.op;
	}
	i++;
	data = operators[i];
	if (data.op == Operator::DATA)
	{
		double value = data_manager->get_value(data.id);
		switch (op)
		{
		case Operator::ADD:
			result += value;
			break;
		case Operator::SUB:
			result -= value;
			break;
		case Operator::MULTI:
			result *= value;
			break;
		case Operator::DIVED:
			if (value == 0) {
				result = 0;
			}
			else {
				result /= value;
			}
			break;
		default:
			break;
		}

	}
	else {
		op = data.op;
	}
	i++;
	data = operators[i];
	if (data.op == Operator::DATA)
	{
		double value = data_manager->get_value(data.id);
		switch (op)
		{
		case Operator::ADD:
			result += value;
			break;
		case Operator::SUB:
			result -= value;
			break;
		case Operator::MULTI:
			result *= value;
			break;
		case Operator::DIVED:
			if (value == 0) {
				result = 0;
			}
			else {
				result /= value;
			}
			break;
		default:
			break;
		}

	}
	else {
		op = data.op;
	}
	data_manager->set_value(result_id, result);

}
int result_id_param=0;
size_t ArithmeticalExpression::get_path_data(std::list<PatchData>& patch_datas){
	
	patch_datas.push_back({
		{0},
		&arithmetical_expression_caculate_entry0_template,
		arithmetical_expression_template_common_data_size
	});
	Operator op = Operator::ADD;
	for (int i = 0; i < operators.size();i++) {
		OperatorAndData data = operators[i];
		if (data.op == Operator::DATA)
		{
			switch (op)
			{
			case Operator::ADD:
				patch_datas.push_back({
						{*reinterpret_cast<uint64_t*>(&data.id)},
						&arithmetical_expression_caculate1_template
					});
				break;
			case Operator::SUB:
				patch_datas.push_back({
						{*reinterpret_cast<uint64_t*>(&data.id)},
						&arithmetical_expression_caculate2_template
					});
				break;
			case Operator::MULTI:
				patch_datas.push_back({
						{*reinterpret_cast<uint64_t*>(&data.id)},
						&arithmetical_expression_caculate3_template
					});
				break;
			case Operator::DIVED:
				patch_datas.push_back({
						{*reinterpret_cast<uint64_t*>(&data.id)},
						&arithmetical_expression_caculate4_template
				});
				break;
			default:
				break;
			}

		}
		else {
			op = data.op;
		}
	}

	patch_datas.push_back({
			{reinterpret_cast<uint64_t>(&result_id_param)},
			&arithmetical_expression_caculate_end0_template
	});
	size_t total_size=0;
	for(std::list<PatchData>::const_iterator it=patch_datas.cbegin();it!=patch_datas.cend();it++){
		total_size= total_size+ it->common_data_size+it->template_data->const_data_size+it->template_data->extern_data_size+it->template_data->code_size;
	}
	return total_size;
}

#include<sys/mman.h>
#include<fcntl.h>
uint8_t* new_code_block(int size) {
	return (uint8_t*)mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_POPULATE, -1, 0);
};

uint8_t* generate_code(std::list<PatchData>& patch_datas , int total_size) {
	uint8_t* code_block = new_code_block(total_size);
	uint8_t* now_offset = code_block;
	for (std::list<PatchData>::const_iterator it = patch_datas.cbegin(); it != patch_datas.cend(); it++) {
		const PatchData& patch_data = *it;
		uint8_t* now_data_offset = now_offset  +it->common_data_size;
		uint8_t* now_code_offset = now_data_offset+ it->template_data->const_data_size + it->template_data->extern_data_size;
		uint8_t* next_offset = now_code_offset + it->template_data->code_size;
		//std::cout<<std::hex<<"code start "<<(uint64_t)now_code_offset<<std::endl;
		
		memcpy(now_data_offset, it->template_data->const_data, it->template_data->const_data_size);
		memcpy(now_code_offset, it->template_data->code, it->template_data->code_size);

		for (int i = 0; i < it->template_data->hole_size; i++){
			HoleData* hole_it = it->template_data->all_holes + i;
			uint8_t* need_dest_value;
			if (hole_it->hole_type == HOLE_TYPE::NEXT_FUN) {
				auto next = std::next(it);
				need_dest_value = next_offset +next->common_data_size+ next->template_data->const_data_size + next->template_data->extern_data_size;
			}
			else if (hole_it->hole_type == HOLE_TYPE::CONST_DATA) {
				need_dest_value = now_data_offset + hole_it->data_offset;
			}
			else if (hole_it->hole_type == HOLE_TYPE::EXTERN_DATA) {
				auto next = std::next(it);
				if(next==patch_datas.cend()){
					need_dest_value=reinterpret_cast<uint8_t*>(it->extern_data_patch_values[hole_it->patch_index-1]);
				}
				else{
				need_dest_value = now_data_offset + it->template_data->const_data_size + hole_it->data_offset;
				*((uint64_t*)(need_dest_value)) = it->extern_data_patch_values[hole_it->patch_index-1];//可能得从0开始
				}
			}else if(hole_it->hole_type==HOLE_TYPE::EXTERN_FUN){
				
				auto next = std::next(it);
				if(next==patch_datas.cend()){
					uint64_t set_value_fun = get_fun_address<void (DataManager::*)(int,double)>(&DataManager::set_value);
					need_dest_value=(uint8_t*)set_value_fun;
				}else{
					uint64_t get_value_fun = get_fun_address<double (DataManager::*)(int)>(&DataManager::get_value);
					need_dest_value=(uint8_t*)get_value_fun;
				}
				// 做一下依赖方法的重定位
			}else if(hole_it->hole_type==HOLE_TYPE::COMMON_DATA){
				size_t pre_count= it->extern_data_patch_values[0];
				auto pre=it;
				uint8_t* common_data_offset = now_code_offset- pre->common_data_size- pre->template_data->const_data_size- pre->template_data->extern_data_size;
				while (pre_count)
				{
					pre= std::prev(pre);
					
					common_data_offset = common_data_offset- pre->common_data_size- pre->template_data->const_data_size- pre->template_data->extern_data_size-pre->template_data->code_size;
					pre_count--;
				}
				
				need_dest_value = common_data_offset + hole_it->data_offset;
			}
			else {
				//need_dest_value = (uint8_t*)(it->all_patch_values[hole_it->patch_index]);
				abort();
			}

			switch (hole_it->reloc_type)
			{
			case R_X86_64_64:
				*((uint64_t*)(now_code_offset + hole_it->offset)) = uint64_t(need_dest_value + hole_it->added);
				break;
			case R_X86_64_PC32:
				*((uint64_t*)(now_code_offset + hole_it->offset)) = uint64_t(need_dest_value  + hole_it->added-(now_code_offset + hole_it->offset));
				break;
			default:
				break;
			}
			now_offset= next_offset;
		}
		
	}
	return code_block;

}


/*




ATK = (EQUIP_ATK*EQUIP_DURABILITY+GEN_ATK)*ATK_BUFF_RATE +EXTRA_ATK+REDUCE_ATK
*/

int main(int argc, char* argv[]) {


	DataManager* data_manager = new DataManager(7);
	data_manager->set("EQUIP_ATK", 0,{6});
	data_manager->set("EQUIP_DURABILITY", 1, { 6 });
	data_manager->set("GEN_ATK", 2, { 6 });
	data_manager->set("ATK_BUFF_RATE", 3,{6});
	data_manager->set("EXTRA_ATK", 4, { 6 });
	data_manager->set("REDUCE_ATK", 5, { 6 });
	data_manager->set("ATK", 6,{});
	Expression* express= new ArithmeticalExpression({
		{Operator::DATA,0},
		{Operator::MULTI,0},
		{Operator::DATA,1},
		{Operator::ADD,0},
		{Operator::DATA,2},
		{Operator::MULTI,0},
		{Operator::DATA,3},
		{Operator::ADD,0},
		{Operator::DATA,4},
		{Operator::DATA,5}
		});
	data_manager->set_value(0, 2.0);
	data_manager->set_value(1, 9.0);
	data_manager->set_value(2, 4.0);
	data_manager->set_value(3, 1.5);
	data_manager->set_value(4, 2);
	data_manager->set_value(5, -3);
	std::list<PatchData> patch_datas;
	size_t total_size=0;
	total_size+=express->get_path_data(patch_datas);
	uint8_t*ptr= generate_code(patch_datas,total_size);
	// for(int i=0;i<total_size;i++){
	// 	std::cout<<"0x"<<std::hex<<(int)ptr[i]<<",";
	// }
	// std::cout<<std::endl;
	mprotect(ptr, total_size, PROT_READ | PROT_EXEC);
	void (*entry)(int,DataManager*)=reinterpret_cast<void (*)(int,DataManager*)>(ptr+ patch_datas.begin()->common_data_size+patch_datas.begin()->template_data->const_data_size+patch_datas.begin()->template_data->extern_data_size);
	entry(6,data_manager);
	// std::cout<<data_manager->get_value(6);

	// return 0;
	int count = 10000000;
	//6 = (0 * 1 + 2) * 3 + 4 + 5
	data_manager->set_value(6, 100);
	auto now =std::chrono::steady_clock::now();
	for (int i = 0; i < count; i++)
	{
		express->caculate(6, data_manager);
	}
		
	std::cout <<"caculate cost " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - now).count()<<"ms value is "<<data_manager->get_value(6) << std::endl;
	data_manager->set_value(6, 100);
	now = std::chrono::steady_clock::now();
	for (int i = 0; i < count; i++)
	{
		express->caculate_all_in_one_function(6, data_manager);
	}
	std::cout << "caculate_all_in_one_function cost "<< std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - now).count() <<"ms value is " << data_manager->get_value(6) << std::endl;

	data_manager->set_value(6, 100);
	now = std::chrono::steady_clock::now();
	for (int i = 0; i < count; i++)
	{
		result_id_param=6;
		entry(6, data_manager);
	}
	std::cout << "copy and patch jit cost "<< std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - now).count() <<"ms value is " << data_manager->get_value(6) << std::endl;
	return 0;
}