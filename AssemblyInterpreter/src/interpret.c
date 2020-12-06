/* 
 * This is a custom assmembly code interpreter that
 * interprets and runs an assembly code up to 100 lines long
 * (Feature of more lines will possibly be coming in the future)
 * Made by Yug Patel for the Rutgers Course Computer Architecture(CS211) 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*This method evaluates a number that is used to determine 
 *what line the instruction pointer will jump to
 *@param ins - the string that contains the instruction
 *@param currPtr - the value of the current pointer
 *@param registers - the int array containing the values of each register
 *@param reg1 - a string containing a register or a constant
 *@param reg2 - a string containing a register or a constant
 *@param rOrL - the string containing where the pointer will jump to
 *@return - an int value that contains what instruction the pointer will jump to
 */

int conJumps(char ins[], int currPtr, int registers[], char reg1[], char reg2[], char rOrL[]){
    //This is used to determine whether reg1 and reg2 are registers or constants

    int arg1 = reg1[0] - 97; //arg1 is either a character from a,b,c,d or a number 
    int arg2 = reg2[0] - 97; //arg2 is either a character from a,b,c,d or a number

    //The condition check for "jump if reg1 equals reg2"
    if(strcmp(ins, "je") == 0){
        if(arg1 < 0 && arg2 < 0){ //if reg1 and reg2 are both constants
            if(atoi(reg1) == atoi(reg2)){ 
                return atoi(rOrL);
            }
        }else if(arg1 < 0){ //if only reg1 is a constant
            if(atoi(reg1) == registers[arg2]){
                return atoi(rOrL);
            }
        }else if(arg2 < 0){ //if only reg2 is a constant
            if(registers[arg1] == atoi(reg2)){
                return atoi(rOrL);
            }
        }else{ //if neither are constants
            if(registers[arg1] == registers[arg2]){
                return atoi(rOrL);
            }
        }

    //The condition check for "jump if reg1 not equal to reg2"
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

    //The condition check for "jump if reg1 is greater than reg2"
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

    //The condition check for "jump if reg1 is greater than or equal to reg2"  
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

    //The condition check for "jump if reg1 is less than reg2" 
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

    //The condition check for "jump if reg1 is less than or equal to reg2"
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

    //increment and return the instruction pointer if the condition isn't met
    return currPtr + 1;
}


//main method
int main(int argc, char* argv[]){
    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL){
        fclose(fp);
        return 0;
    }
    char instructions[100][40], curr[40];
    int registers[4], insptr = 0;
    
    /* Storing instruction pointers in an array
     * to better keep track of instructions
     * using an instruction pointer. 
     */
    for(;fgets(curr, 40, fp) != NULL; insptr++){
        strcpy(instructions[insptr], curr);
    }

    /* an "EOF" indicator put at the end
     * of the instructions array to mark
     * the end of file.
    */
    strcpy(instructions[insptr], "EOF");
    insptr = 0;
    
    //iterating through the instructions
    while(strcmp(instructions[insptr], "EOF") != 0){

        char* currIns = instructions[insptr];
        char ins[6], regOrLine[20], reg1[20], reg2[20];
        
        //n used to evaluate how many arguments are successfully passed
        int n = sscanf(currIns, "%s %s %s %s", ins, regOrLine, reg1, reg2);
        if(n == 2){

            int ind = regOrLine[0] - 97; //evaluates an index between 0-4 to store values into the registers array
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

            if(strcmp(ins, "mov") == 0){ //move function used to move values from src to destination 
                if(src < 0){
                    registers[dest] = atoi(regOrLine); //used to move a constant into a register
                }else{
                    registers[dest] = registers[src]; //used to move a register into a register
                }

            }else if(strcmp(ins, "add") == 0){ //add function to add the values of src and dest
                if(src < 0){
                    registers[dest] = registers[dest] + atoi(regOrLine);
                }else{
                    registers[dest] = registers[src] + registers[dest];
                }

            }else if(strcmp(ins, "sub") == 0){ //subtract function to subtract src from dest and store in dest
                if(src < 0){
                    registers[dest] = registers[dest] - atoi(regOrLine);
                }else{
                    registers[dest] = registers[dest] - registers[src];
                }

            }else if(strcmp(ins, "mul") == 0){ //multiply function to multiply src by dest and store in dest
                if(src < 0){
                    registers[dest] = registers[dest] * atoi(regOrLine);
                }else{
                    registers[dest] = registers[src] * registers[dest];
                }

            }else{ //divide function to do integer division of src/dest and store in dest
                if(src < 0){
                    registers[dest] = atoi(regOrLine) / registers[dest];
                }else{
                    registers[dest] = registers[src] / registers[dest]; 
                }
            }

            insptr++;
        }else if(n == 4){
	    //instruction pointer will hold the value returned from the method "conjumps"
            insptr = conJumps(ins, insptr, registers, reg1, reg2, regOrLine); 
        }else{
            insptr++;
        }

    }
    return 0;
}
