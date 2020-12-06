#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int conJumps(char ins[], int currPtr, int registers[], char reg1[], char reg2[], char rOrL[]){
    int arg1 = reg1[0] - 97;
    int arg2 = reg2[0] - 97;
    if(strcmp(ins, "je") == 0){
        if(arg1 < 0 && arg2 < 0){
            if(atoi(reg1) == atoi(reg2)){
                return atoi(rOrL);
            }
        }else if(arg1 < 0){
            if(atoi(reg1) == registers[arg2]){
                return atoi(rOrL);
            }
        }else if(arg2 < 0){
            if(registers[arg1] == atoi(reg2)){
                return atoi(rOrL);
            }
        }else{
            if(registers[arg1] == registers[arg2]){
                return atoi(rOrL);
            }
        }
    }else if(strcmp(ins, "jne") == 0){
        if(arg1 < 0 && arg2 < 0){
            if(atoi(reg1) != atoi(reg2)){
                return atoi(rOrL);
            }
        }else if(arg1 < 0){
            if(atoi(reg1) != registers[arg2]){
                return atoi(rOrL);
            }
        }else if(arg2 < 0){
            if(registers[arg1] != atoi(reg2)){
                return atoi(rOrL);
            }
        }else{
            if(registers[arg1] != registers[arg2]){
                return atoi(rOrL);
            }
        }
    }else if(strcmp(ins, "jg") == 0){
      if(arg1 < 0 && arg2 < 0){
            if(atoi(reg1) > atoi(reg2)){
                return atoi(rOrL);
            }
        }else if(arg1 < 0){
            if(atoi(reg1) > registers[arg2]){
                return atoi(rOrL);
            }
        }else if(arg2 < 0){
            if(registers[arg1] > atoi(reg2)){
                return atoi(rOrL);
            }
        }else{
            if(registers[arg1] > registers[arg2]){
                return atoi(rOrL);
            }
        }  
    }else if(strcmp(ins, "jge") == 0){
        if(arg1 < 0 && arg2 < 0){
            if(atoi(reg1) >= atoi(reg2)){
                return atoi(rOrL);
            }
        }else if(arg1 < 0){
            if(atoi(reg1) >= registers[arg2]){
                return atoi(rOrL);
            }
        }else if(arg2 < 0){
            if(registers[arg1] >= atoi(reg2)){
                return atoi(rOrL);
            }
        }else{
            if(registers[arg1] >= registers[arg2]){
                return atoi(rOrL);
            }
        }
    }else if(strcmp(ins, "jl") == 0){
        if(arg1 < 0 && arg2 < 0){
            if(atoi(reg1) < atoi(reg2)){
                return atoi(rOrL);
            }
        }else if(arg1 < 0){
            if(atoi(reg1) < registers[arg2]){
                return atoi(rOrL);
            }
        }else if(arg2 < 0){
            if(registers[arg1] < atoi(reg2)){
                return atoi(rOrL);
            }
        }else{
            if(registers[arg1] < registers[arg2]){
                return atoi(rOrL);
            }
        }
    }else{
        if(arg1 < 0 && arg2 < 0){
            if(atoi(reg1) <= atoi(reg2)){
                return atoi(rOrL);
            }
        }else if(arg1 < 0){
            if(atoi(reg1) <= registers[arg2]){
                return atoi(rOrL);
            }
        }else if(arg2 < 0){
            if(registers[arg1] <= atoi(reg2)){
                return atoi(rOrL);
            }
        }else{
            if(registers[arg1] <= registers[arg2]){
                return atoi(rOrL);
            }
        }
    }
    return currPtr + 1;
}
int main(int argc, char* argv[]){
    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL){
        fclose(fp);
        return 0;
    }
    char instructions[100][40], curr[40];
    int registers[4], insptr = 0;
    for(;fgets(curr, 40, fp) != NULL; insptr++){
        strcpy(instructions[insptr], curr);
    }
    strcpy(instructions[insptr], "EOF");
    insptr = 0;
    while(strcmp(instructions[insptr], "EOF") != 0){
        char* currIns = instructions[insptr];
        char ins[6], regOrLine[20], reg1[20], reg2[20];
        int n = sscanf(currIns, "%s %s %s %s", ins, regOrLine, reg1, reg2);
        if(n == 2){
            int ind = regOrLine[0] - 97;
            if(strcmp(ins, "read") == 0){
                scanf("%d", &registers[ind]);
            }else if(strcmp(ins, "jmp") == 0){
                insptr = atoi(regOrLine);
                continue;
            }else{
                if(ind < 0){
                    printf("%d", atoi(regOrLine));
                }else{
                    printf("%d", registers[ind]);
                }
            }
            insptr++;
        }
        else if(n == 3){
            int src = regOrLine[0] - 97;
            int dest = reg1[0] - 97;
            if(strcmp(ins, "mov") == 0){ 
                if(src < 0){
                    registers[dest] = atoi(regOrLine);
                }else{
                    registers[dest] = registers[src];
                }
            }else if(strcmp(ins, "add") == 0){
                if(src < 0){
                    registers[dest] = registers[dest] + atoi(regOrLine);
                }else{
                    registers[dest] = registers[src] + registers[dest];
                }
            }else if(strcmp(ins, "sub") == 0){
                if(src < 0){
                    registers[dest] = registers[dest] - atoi(regOrLine);
                }else{
                    registers[dest] = registers[dest] - registers[src];
                }
            }else if(strcmp(ins, "mul") == 0){
                if(src < 0){
                    registers[dest] = registers[dest] * atoi(regOrLine);
                }else{
                    registers[dest] = registers[src] * registers[dest];
                }
            }else{
                if(src < 0){
                    registers[dest] = atoi(regOrLine) / registers[dest];
                }else{
                    registers[dest] = registers[src] / registers[dest];
                }
            }
            insptr++;
        }else if(n == 4){
            insptr = conJumps(ins, insptr, registers, reg1, reg2, regOrLine);
        }else{
            insptr++;
        }
    }
    return 0;
}