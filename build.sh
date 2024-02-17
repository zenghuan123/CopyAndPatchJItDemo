clang++ -o3 -fno-pic -mcmodel=large -std=c++1z -c arithmetical_expression_template.cpp -o arithmetical_expression_template.o
objdump -d arithmetical_expression_template.o &>arithmetical_expression_template.s
objdump -r arithmetical_expression_template.o &>arithmetical_expression_template.r
clang++ -o3 generate_template.cpp -o generate_template
./generate_template
clang++ -o3 main.cpp -o main
