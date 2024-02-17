#include<fstream>
#include"elf.h"
#include<unordered_map>
#include<regex>
#include<list>
#include <sstream>
#include "head.h"
#include <cxxabi.h>

struct RelaData {
	uint8_t* byte_array;
	Elf64_Xword byte_length;

	Elf64_Sxword added;
	Elf64_Addr	offset;
	Elf64_Xword type;

	size_t data_offset;
	size_t patch_index;
	
	HOLE_TYPE hole_type;
	const char*sym_name;

	RelaData() :byte_array(nullptr), byte_length(0), added(0), offset(0), type(0), data_offset(0), patch_index(0){};
	RelaData(uint8_t* byte_array, Elf64_Xword byte_length, Elf64_Sxword added, Elf64_Addr	offset, Elf64_Xword type,size_t data_offset,size_t patch_index,HOLE_TYPE hole_type)
		:byte_array(byte_array), byte_length(byte_length), added(added), offset(offset), type(type), data_offset(data_offset), patch_index(patch_index),hole_type(hole_type) {};


	RelaData(uint8_t* byte_array, Elf64_Xword byte_length, Elf64_Sxword added, Elf64_Addr	offset, Elf64_Xword type,size_t data_offset,size_t patch_index,HOLE_TYPE hole_type,const char*sym_name)
		:byte_array(byte_array), byte_length(byte_length), added(added), offset(offset), type(type), data_offset(data_offset), patch_index(patch_index),hole_type(hole_type),sym_name(sym_name) {};



};
struct GenerateTemplateData
{
	uint8_t* code;
	Elf64_Xword code_length;
	int index;

	size_t const_data_size;
	std::list<RelaData> const_data_rela_data;

	size_t extern_data_size;
	std::list<RelaData> extern_data_rela_data;
};

std::string get_real_name(const char*fun_name){
    int status;
    size_t buffer_size = 1024;
    char buffer[buffer_size];
    char* result = abi::__cxa_demangle(fun_name, buffer, &buffer_size, &status);
    if(!result){
        return std::string(fun_name);
    }
    std::string r= std::string(result);
    return r;
}

int main(int argc, char* argv[]) {
    std::string file_name("arithmetical_expression_template");
    std::string prefix = std::string(file_name.c_str(),file_name.length()-9);
	std::ifstream input(file_name+".o", std::ios::binary);
	std::vector<char> vec{ std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>() };
	char* buff = vec.data();
	Elf64_Ehdr* ehdr = reinterpret_cast<Elf64_Ehdr*>(buff);
	Elf64_Shdr* shdr_array = reinterpret_cast<Elf64_Shdr*>(buff + ehdr->e_shoff);
	Elf64_Shdr* str_shdr = reinterpret_cast<Elf64_Shdr*>(shdr_array + ehdr->e_shstrndx);
	const char* str_table = reinterpret_cast<const char*>(buff + str_shdr->sh_offset);
	Elf64_Sym* sym_table = nullptr;
	std::unordered_map<std::string, GenerateTemplateData> name_to_data;
	std::cmatch m;
    std::regex template_regex{"(\\w*)<\\D*(\\d*)>"};
	std::regex param_regex("(\\w*\\D)(\\d*)$");
	size_t common_data_count=0;
	
	for (Elf64_Section i = 0; i < ehdr->e_shnum; i++)
	{
		Elf64_Shdr* shdr = shdr_array + i;
		if (shdr->sh_type == SHT_RELA) {
           
            const char*fun_name_start = strstr(str_table + shdr->sh_name,prefix.c_str());
            if(!fun_name_start){
                    continue;
            }
            while (*fun_name_start!='.')
            {
                fun_name_start--;
            }
            fun_name_start++;
            std::string real_name = get_real_name(fun_name_start);
            std::cout<<"fun name rela"<< real_name<<std::endl;
			if (std::regex_search(real_name.c_str(), m, template_regex)) {
                
				int index = atoi(m[2].str().c_str());
				std::string fun_name = m[1].str()+m[2].str();//后面m被重用了
				Elf64_Rela* rela_array = reinterpret_cast<Elf64_Rela*>(buff + shdr->sh_offset);
				auto it = name_to_data.find(fun_name);
				if (it == name_to_data.end()) {
					name_to_data[fun_name] = GenerateTemplateData();
				}
				GenerateTemplateData& temp = name_to_data[fun_name];
				for (Elf64_Xword i = 0; i < shdr->sh_size / shdr->sh_entsize; i++) {
					/*shdr->sh_link*/
					Elf64_Rela* rela = rela_array + i;
					Elf64_Xword sym_index = ELF64_R_SYM(rela->r_info);
					Elf64_Xword reloc_type = ELF64_R_TYPE(rela->r_info);
					Elf64_Shdr* link_sym_table = reinterpret_cast<Elf64_Shdr*>(shdr_array + shdr->sh_link);
 					Elf64_Sym* sym = reinterpret_cast<Elf64_Sym*>(buff + link_sym_table->sh_offset) + sym_index;

					if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL and ELF64_ST_TYPE(sym->st_info) == STT_SECTION)
					{
						Elf64_Shdr* rodata_shdr = shdr_array + sym->st_shndx;
						uint8_t* byte_array = reinterpret_cast<uint8_t*>(buff + rodata_shdr->sh_offset);
						//rodata_shdr->sh_addralign;
						temp.const_data_rela_data.push_back({
							byte_array + rela->r_addend,
							rodata_shdr->sh_entsize,
							rela->r_addend,
							rela->r_offset,
							reloc_type,
							temp.const_data_size,
							temp.const_data_rela_data.size(),
							HOLE_TYPE::CONST_DATA
							});
						temp.const_data_size += rodata_shdr->sh_entsize;
					}
					else {
						size_t offset=temp.extern_data_size;						
						std::regex_search(str_table + sym->st_name,m,param_regex);
						std::cout << " sym name " << str_table + sym->st_name<<"  "<<m[1].str() << std::endl;
						HOLE_TYPE hole_type;
						size_t index =atoi(m[2].str().c_str());
						if(strstr(m[1].str().c_str(),"extern_value")){
							hole_type = HOLE_TYPE::EXTERN_DATA;
							temp.extern_data_size += 8;	
						}else if (strstr(m[1].str().c_str(),"common_value"))
						{
							hole_type = HOLE_TYPE::COMMON_DATA;
							offset=(index-1)*8;
							if(index>common_data_count){
								common_data_count=index;
							}
						}else if(strstr(m[1].str().c_str(),"next_fun")){
							hole_type = HOLE_TYPE::NEXT_FUN; 
						}else{
							hole_type = HOLE_TYPE::EXTERN_FUN;
						}
						
						
						temp.extern_data_rela_data.push_back({
						0,
						8,
						rela->r_addend,
						rela->r_offset,
						reloc_type,
						offset,
						index,
						hole_type,
						str_table + sym->st_name
							});																		
					}
				}
			}
		}
		if (shdr->sh_type == SHT_PROGBITS) {
			if (shdr->sh_flags & SHF_EXECINSTR) {
				const char*fun_name_start = strstr(str_table + shdr->sh_name,prefix.c_str());
                if(!fun_name_start){
                    continue;
                }
                while (*fun_name_start!='.')
                {
                    fun_name_start--;
                }
                fun_name_start++;
                std::string real_name = get_real_name(fun_name_start);
                std::cout<<"fun name text"<< real_name<<std::endl;
				if (std::regex_search(real_name.c_str(), m, template_regex)) {
					uint8_t* code = reinterpret_cast<uint8_t*>(buff + shdr->sh_offset);
					Elf64_Xword code_length = shdr->sh_size;
					int index = atoi(m[2].str().c_str());
					std::string fun_name = m[1].str()+m[2].str();
					std::cout << fun_name << std::endl;
					auto it = name_to_data.find(fun_name);
					if (it == name_to_data.end()) {
						name_to_data[fun_name] = GenerateTemplateData();
					}
					GenerateTemplateData& temp = name_to_data[fun_name];
					temp.code = code;
					temp.code_length = code_length;
					temp.index = index;
				}


			}
		}

		if (shdr->sh_type == SHT_SYMTAB) {
			sym_table = reinterpret_cast<Elf64_Sym*>(buff + shdr->sh_offset);
			std::cout << "sym " << str_table + shdr->sh_name << "  " << i << std::endl;
		}
	}

	std::ofstream output(file_name+".h", std::ios::binary);
	output << "#include\"head.h\"" << std::endl;
	
	for (auto it = name_to_data.cbegin(); it != name_to_data.cend(); it++)
	{
		output << "uint8_t " << it->first << "_code[]{";
		for (int i = 0; i < it->second.code_length; i++)
		{
			output << "0x" << std::hex << (int)it->second.code[i] << ",";
		}
		output<<std::dec << "};" << std::endl;
		int hole_index = 0;
		std::ostringstream  const_data_os;
		std::ostringstream  all_holes_os;
		output << "HoleData " << it->first << "_hole[]{";
		for (std::list<RelaData>::const_iterator rela_iterator = it->second.const_data_rela_data.cbegin(); rela_iterator!= it->second.const_data_rela_data.cend(); rela_iterator++)
		{
			output<< "{" 
				<<"(HOLE_TYPE)"<< (int)HOLE_TYPE::CONST_DATA << ","
				<<rela_iterator->type << ","
				<< rela_iterator->added << ","
				<< rela_iterator->offset << ","
				<< rela_iterator->data_offset << ","
				<< rela_iterator->patch_index << "},";
			for (int i = 0; i < rela_iterator->byte_length; i++)
			{
				const_data_os << "0x" << std::hex << (int)rela_iterator->byte_array[i] << ",";
			}
			hole_index++;
		}
		
		for (std::list<RelaData>::const_iterator rela_iterator = it->second.extern_data_rela_data.cbegin(); rela_iterator!= it->second.extern_data_rela_data.cend(); rela_iterator++)
		{
			output << "{"
				<<"(HOLE_TYPE)"<<(int)rela_iterator->hole_type << ","
				<< rela_iterator->type << ","
				<< rela_iterator->added << ","
				<< rela_iterator->offset << ",";
			if(rela_iterator->hole_type==HOLE_TYPE::EXTERN_DATA){
				output<< it->second.const_data_size+ rela_iterator->data_offset << ",";
			}else if(rela_iterator->hole_type==HOLE_TYPE::EXTERN_FUN){
				output<< rela_iterator->data_offset << ",";
			}else{
				output<< rela_iterator->data_offset << ",";
			}
			output<< rela_iterator->patch_index << "},";
			//需要在运行时查找rela_iterator->sym_name的地址
			//可以使用 dl_iterate_phdr 方法
			//也可以使用&fun获取方法地址
			hole_index++;
		}
		output <<std::dec<< "};" << std::endl;
		output << "uint8_t " << it->first << "_const_data[]{" << const_data_os.str() << "};"<<std::endl;
		const_data_os.clear();
		output << "TemplateData " << it->first << "_template{";
		output << it->second.const_data_size << "," << it->first << "_const_data" << ",";
		output << it->second.extern_data_size << ",";
		output << it->first << "_hole, " << it->second.const_data_rela_data.size() + it->second.extern_data_rela_data.size()<<",";
		output << it->first << "_code," << it->second.code_length << "};" << std::endl;
	}
	output << "size_t "<<file_name<< "_common_data_size=" <<common_data_count*8<<";";


}