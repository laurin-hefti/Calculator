//CALCULATOR

//imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stringlibary.c"

//macros
#define printerror printf("\nerror\n");
#define PRINTNEWLINE printf("\n");
#define nullptr 0x00

//Settings variables

//sets the testmode, the while loop will not be executet and all test will be automatilcy executet once
#define TESTMDOE 0

//prints all debug stuff
#define DEBUGPRINT 0

//macro functions how makes things easier
#define dprint(mes) if(DEBUGPRINT){printf(mes);PRINTNEWLINE}
#define printnum(num) printf("%d",num);PRINTNEWLINE

//just some notes for eventualy upgrading stuff
//#definde halbiere(wert) ((wert)/2)



String* getExecPeace(String* s, int num_of_controls){
    char* startc = "(";
    char* endc = ")";

    int num_s_c = 0;
    int num_e_c = 0;
    int index_last_start_c = -1;
    int index_last_end_c = -1; 
    int search_next_end_c = 0;
    int serach_next_start_c = 0;

    //old not working code but if the new code does not work we still have the pricipals of the foreign code
    /*
    for (int i = 0; i < s->len; i++){
        if (cmpCharSeq(s, i, startc, 1)){
            if (num_s_c >= num_of_controls)//must be bevore because whenn two start c is echeaved and we wath to have two start c then not decresas count of end c
            {
                num_e_c -= 1;
            }
            num_s_c += 1;
            index_last_start_c = i;
        }

        if (cmpCharSeq(s, i, endc, 1) && num_s_c >= num_of_controls){
            num_e_c += 1;
            if (num_e_c == num_of_controls){
                index_last_end_c = i;
                break;
            }
        }
    }

    if (num_of_controls > 1){
        index_last_start_c = searchReverseCharOffsetNum(s, startc, index_last_end_c, num_of_controls-num_s_c);//may just -1
    }
    */  

    for (int i = 0; i < s->len; i++){
        if (cmpCharSeq(s, i, endc, 1)){
            num_e_c += 1;
            search_next_end_c = 1;
            if (num_e_c == num_of_controls){
                index_last_end_c = i;
                break;
            }
        }
        if (cmpCharSeq(s, i, startc, 1) && search_next_end_c){
            num_e_c -= 1;
        }
    }

    for (int i = index_last_end_c-1; i >= 0; i--){
        if (cmpCharSeq(s, i, startc, 1)){
            num_s_c += 1;
            if (num_s_c == num_of_controls){
                index_last_start_c = i;
                break;
            }
        }
        if (cmpCharSeq(s, i, endc, 1)){
            num_s_c -= 1;
        }
    }

    if (index_last_start_c == -1 || index_last_end_c == -1){
        //printf("error not found exepeace\n");
        return fastInitStringfs(s);
    }

    String* inst = getCharSeqFromString(s, index_last_start_c, index_last_end_c);

    return inst;
}

String* translateToabstractSyntax(String* s){
    char* control[2] = {"(",")"};
    char* operators[6] = {"*","/","+","-","^","&"};
    char* numbers[11] = {"0","1","2","3","4","5","6","7","8","9","."};
    char* end_op_or_var[8] = {"*","/","+","-","^","&","(",")"};
    char* number = "n";
    char* variable = "v";

    String* abs_s = initString(); //abstract string
    
    for (int i = 0; i < s->len; i++){
        int set = 0; 
        for (int j = 0; j < 2; j++){
            if (cmpCharSeq(s, i, control[j], 1)){
                addStringwithOffset(abs_s, s, 1, i);
                set = 1;
                break;
            }
        }
        if (set == 0){
        for (int j = 0; j < 6; j++){
            if (cmpCharSeq(s, i, operators[j], 1)){
                addStringwithOffset(abs_s, s, 1, i);
                set = 1;
                break;
            }
        }
        }
        if (set == 0){
        for (int j = 0; j < 11; j++){
            if (cmpCharSeq(s, i, numbers[j], 1)){
                addChar(abs_s, number, 1);
                set = 1;
                break;
            }
        }
        if (set == 0){
            addChar(abs_s, variable, 1);
        }
        int found_end = 0;
        int const_i = i;
        for (int j = 1; j < s->len; j++){
            for (int k = 0; k < 8; k++){
                if (cmpCharSeq(s, const_i+j, end_op_or_var[k], 1)){
                    found_end = 1;
                    break;
                }
            }
            if (found_end){
                break;
            }else{
                i+=1;
            }
        }
        }
    }
    return abs_s;
}

String* abs_mVar(String* s){
    String* mVar_s = fastInitStringfs(s);
    while (getIndexofCharSeq(mVar_s, "(n*v)", 5) != -1){
        mVar_s = getreplaceChar(mVar_s, "(n*v)", 5, "mVar", 4);
    }
    return mVar_s;
}

String* abs_operator(String* s){
    char* op[4] = {"+", "-", "*", "/"};
    String* abs_o_s = fastInitStringfs(s);
    for (int i = 0; i < 4; i++){
        while (getIndexofCharSeq(abs_o_s, (char*) op[i], 1) != -1){
            abs_o_s = getreplaceChar(abs_o_s, (char*) op[i], 1, "o", 1);
        }
    }
    return abs_o_s;
}

int testIfInst(String* s){
    if (getIndexOfChar(s, "(",0) != -1 && getIndexOfChar(s, ")",0) != -1){
        return 1;
    } else {
        return 0;
    }
}

String* setControl(String* s){
    char* operators[] = {"*", "/", "+", "-"}; //controls the order
    char* controls[] = {"*", "/" , "+", "-", "(", ")"};

    //char* controls_up[] = {"*", "/" , "+", "-", ")"};//not in use
    //char* controls_down[] = {"*", "/" , "+", "-", "("};

    char* startc = "(";
    char* endc = ")";

    String* control_s = fastInitStringfs(s);

    for (int i = 0; i < 4; i++){
        int c_o = getIndexListofChar(control_s, operators[i])[0];

        int last_c = 0;
        for (int j = 0; j < c_o; j++){
            last_c = getIndexOfChar(control_s, operators[i], last_c);

            //finding border of operator
            
            //if it is -1 then we are at the border fo the string because it should givs a result
            int up_border = getIndexBorderofCharList(control_s, controls, 6, last_c);
            int down_border = getReverseIndexBorderofCharList(control_s, controls, 6, last_c);

            if (up_border == -1){
                up_border = control_s->len;
            }

            if (down_border == -1){
                down_border = -1;
            }

            if (cmpCharSeq(control_s,up_border,startc,1)){int count=0; while(1){if(cmpCharSeq(control_s, up_border, startc, 1)){count+=1;}
                                                                                if(cmpCharSeq(control_s, up_border, endc, 1)){count-=1;}
                                                                                if(count==0){break;}
                                                                                up_border+=1;}}
            if (cmpCharSeq(control_s,down_border,endc,1)){int count=0; while(1){if(cmpCharSeq(control_s, down_border, endc, 1)){count+=1;}
                                                                                if(cmpCharSeq(control_s, down_border, startc, 1)){count-=1;}
                                                                                if(count==0){break;}
                                                                                down_border-=1;}}
            
            control_s = getinsertChar(control_s, ")", 1, up_border); //my plus one
            control_s = getinsertChar(control_s, "(", 1, down_border+1);

            last_c += 2;

        }
    }
    return control_s;
}

String* setCompControl(String* s)
{
    char* controls[2] = {"(", ")"};
    char* startc = "(";
    char* endc = ")";

    int is_control = getIndexBorderofCharList(s, controls, 2, 0);

    if (is_control == -1)
    {
        dprint("just simple controlapply")
        printString(s);PRINTNEWLINE
        String* ss = setControl(s);
        printString(ss);PRINTNEWLINE
        return setControl(s);
    }

    String* replaceString = fastInitString("dVar");

    String* new_string = fastInitStringfs(s);

    String* inst = getExecPeace(new_string, 1);
    
    new_string = getreplaceString(new_string, inst, replaceString);

    inst = getCharSeqFromString(inst, 1, inst->len-2);
    String* res = setControl(inst);

    new_string = setCompControl(new_string);

    new_string = getreplaceStringlast(new_string, replaceString, res);

    return new_string;
}


//maht definition
typedef struct Mathdef{
    String* patern;
    int priority;
    String* (*exe_func)(String*);
} Mathdef;

Mathdef* initMathdef(char* patern, int p, String* (*func)(String*)){
    Mathdef* def = malloc(sizeof(Mathdef));
    String* s_pattern = initString();
    addChar(s_pattern, patern, lenChar(patern));
    def->patern = s_pattern;
    def->priority = p;
    def->exe_func = func;
    return def;
}

String* num_mult_func(String* s){
    char* mult = "*";
    int i = getIndexOfCharstart(s, mult);
    String** split = splitStringcut(s, i);
    decString(split[1], 1);

    char* res;
    double v1 = strtod(&split[0]->s[1], &res);
    if (res == &split[0]->s[1]){
        printf("\nerror failded to converte char to number\n");
    }

    char* res2;
    double v2 = strtod(split[1]->s, &res2);
    if (res2 == split[1]->s){
        printf("\nerror failded to converte char to number\n");
    }
    
    double result = v1*v2;
    char res_c[10];
    sprintf(res_c, "%f", result);
    String* res_s = initString();
    addChar(res_s, res_c, lenChar(res_c));
    return res_s;
}

String* num_div_func(String* s){
    char* mult = "/";
    int i = getIndexOfCharstart(s, mult);
    String** split = splitStringcut(s, i);
    decString(split[1], 1);

    char* res;
    double v1 = strtod(&split[0]->s[1], &res);
    if (res == &split[0]->s[1]){
        printf("\nerror failded to converte char to number\n");
    }

    char* res2;
    double v2 = strtod(split[1]->s, &res2);
    if (res2 == split[1]->s){
        printf("\nerror failded to converte char to number\n");
    }
    
    double result = v1/v2;
    char res_c[10];
    sprintf(res_c, "%f", result);
    String* res_s = initString();
    addChar(res_s, res_c, lenChar(res_c));
    return res_s;
}

String* num_add_func(String* s){
    char* mult = "+";
    int i = getIndexOfCharstart(s, mult);
    String** split = splitStringcut(s, i);
    decString(split[1], 1);

    char* res;
    double v1 = strtod(&split[0]->s[1], &res);
    if (res == &split[0]->s[1]){
        printf("\nerror failded to converte char to number\n");
    }

    char* res2;
    double v2 = strtod(split[1]->s, &res2);
    if (res2 == split[1]->s){
        printf("\nerror failded to converte char to number\n");
    }
    
    double result = v1+v2;
    char res_c[10];
    sprintf(res_c, "%f", result);
    String* res_s = initString();
    addChar(res_s, res_c, lenChar(res_c));
    return res_s;
}

String* num_sub_func(String* s){
    char* mult = "-";
    int i = getIndexOfCharstart(s, mult);
    String** split = splitStringcut(s, i);
    decString(split[1], 1);

    char* res;
    double v1 = strtod(&split[0]->s[1], &res);
    if (res == &split[0]->s[1]){
        printf("\nerror failded to converte char to number\n");
    }

    char* res2;
    double v2 = strtod(split[1]->s, &res2);
    if (res2 == split[1]->s){
        printf("\nerror failded to converte char to number\n");
    }
    
    double result = v1-v2;
    char res_c[10];
    sprintf(res_c, "%f", result);
    String* res_s = initString();
    addChar(res_s, res_c, lenChar(res_c));
    return res_s;
}

// all Mathdefs
Mathdef* num_mult;
Mathdef* num_div;
Mathdef* num_add;
Mathdef* num_sub;
//Mathdef brack_mult;
Mathdef* var_calc;

Mathdef* mathdefs_list[4];
int len_mathdefs;

int mult_var_equ(); //dec
int add_var_equ(); //dec

Mathdef* find_abs_syn(String* abs_s){
    for (int i = 0; i < len_mathdefs; i++){
        if (stringcmp(abs_s, mathdefs_list[i]->patern)){
            return mathdefs_list[i];
        }
    }
    return 0;
}

//control exe

String* exe_mathdef(String* inst_s, Mathdef* mathdef){
    String* res = (*mathdef->exe_func)(inst_s);
    return res;
}

String* exe_run_prio_one(String* s){
    if (testIfInst(s) == 0){
        return s;
    }
    
    String* inst_s = getExecPeace(s, 1);
    String* abs_s = translateToabstractSyntax(inst_s);
    printString(abs_s);PRINTNEWLINE
    Mathdef* mathdef = find_abs_syn(abs_s);
    if (mathdef == 0){
        return s;
    }
    String* res = exe_mathdef(inst_s, mathdef);
    String* res2 = getreplaceString(s, inst_s, res);
    //attention s not modified but res2 new string
    return res2;
}

String* run_all_pro_one(String* s){
    String* old_res = exe_run_prio_one(s);
    String* res;
    while (1){
        res = exe_run_prio_one(old_res);
        if (stringcmp(res, old_res) == 1){
            break;
        }

        old_res = res;
        res = 0;
    }

    return res;
}

void initMathdefs(){
    num_mult = initMathdef("(n*n)", 0, &num_mult_func);
    num_div = initMathdef("(n/n)", 0, &num_div_func);
    num_add = initMathdef("(n+n)", 0, &num_add_func);
    num_sub = initMathdef("(n-n)", 0, &num_sub_func);

    //brack_mult = initMathdef("(n*(nov))", 1, nullptr);
    //var_calc = initMathde("(n*v)o(n*v)")

    mathdefs_list[0] = num_mult;
    mathdefs_list[1] = num_div;
    mathdefs_list[2] = num_add;
    mathdefs_list[3] = num_sub;
    len_mathdefs = 4;
}

//Tests
int testgetExeString()
{
    String* input_s = fastInitString("(2.4556*(23/3.34454))");
    if (cmpChar(getExecPeace(input_s,1), "(23/3.34454)") == 1){return 1;}else{return 0;}
}

int testgetExeString2()
{
    String* input_s = fastInitString("(2.4556*(23/3.34454))");
    if (cmpChar(getExecPeace(input_s,2), "(2.4556*(23/3.34454))") == 1){return 1;}else{return 0;}
}

int testgetExeString3()
{
    String* input_s = fastInitString("((3+2.4556)*(23/3.34454))");
    if (cmpChar(getExecPeace(input_s,2), "((3+2.4556)*(23/3.34454))") == 1){return 1;}else{return 0;} 
}

int testgetabs()
{
    String* input_s = fastInitString("(2.4556*(23/3.34454))");
    String* inst_s = getExecPeace(input_s,1);
    if (cmpChar(translateToabstractSyntax(inst_s), "(n/n)") == 1){return 1;}else{return 0;} 
}

int testgetabs2()
{
    String* input_s = fastInitString("(2.4556*(23/3.34454))");
    String* inst_s = getExecPeace(input_s,2);
    if (cmpChar(translateToabstractSyntax(inst_s), "(n*(n/n))") == 1){return 1;}else{return 0;} 
}

int testgetabsmvar()
{
    String* input_s = fastInitString("(5*a)");
    String* inst_s = getExecPeace(input_s,1);
    String* abs_s = translateToabstractSyntax(inst_s);
    if (cmpChar(abs_mVar(abs_s), "mVar") == 1){return 1;}else{return 0;}
}

int testgetabsoperator()
{
    String* input_s = fastInitString("((5*a)*(4*b))");
    String* inst_s = getExecPeace(input_s,2);
    String* abs_s = translateToabstractSyntax(inst_s);
    String* mVar_s = abs_mVar(abs_s);
    if (cmpChar(abs_operator(mVar_s), "(mVaromVar)") == 1){return 1;}else{return 0;}
}

int testsetcontorol()
{
    String* s_s = fastInitString("3.556/5.67*887*4554-1574");
    s_s = setControl(s_s);
    if (cmpChar(s_s, "((3.556/((5.67*887)*4554))-1574)") == 1){return 1;}else{return 0;}
}

void runTest(){
    printf("\nTest mode");
    if (testgetExeString()){printf("\n      Test 1 passt");}else{printf("\n     Test 1 faild");}
    if (testgetExeString2()){printf("\n      Test 2 passt");}else{printf("\n     Test 2 faild");}
    if (testgetExeString3()){printf("\n      Test 2.1 passt");}else{printf("\n     Test 2.1 faild");}
    if (testgetabs()){printf("\n      Test 3 passt");}else{printf("\n     Test 3 faild");}
    if (testgetabs2()){printf("\n      Test 4 passt");}else{printf("\n     Test 4 faild");}
    if (testgetabsmvar()){printf("\n      Test 5 passt");}else{printf("\n     Test 5 faild");}
    if (testgetabsoperator()){printf("\n      Test 6 passt");}else{printf("\n     Test 6 faild");}
    if (testsetcontorol()){printf("\n      Test 7 passt");}else{printf("\n     Test 7 faild");}
    printf("\nEnd test mode\n\n");
}

void runExeTest()
{
    String* input_s = initString();
    char* c = "2.4556*23/3.34454";
    addChar(input_s, c, lenChar(c));

    printf("INPUT\n");
    printString(input_s);
    PRINTNEWLINE
    String* control_s = setControl(input_s);

    String* result = run_all_pro_one(control_s);
    printf("OUTPUT\n");
    printString(result);
    PRINTNEWLINE
}

void info()
{
    printf("exit        =   exit the programm"); PRINTNEWLINE
    printf("runexeTest  =   run a calculation example"); PRINTNEWLINE
    printf("runTests     =   run all tests"); PRINTNEWLINE
    printf("run:        =   starts a calculation"); PRINTNEWLINE
}

int main(){
    initMathdefs();

    if (TESTMDOE)
    {
        runTest();
    }
    

    printf("MAHTPROGRAM"); PRINTNEWLINE

    int run = 1;

    while (run && !TESTMDOE)
    {
        char input[50];
        scanf("%s", input);
        String* input_s = fastInitString(input);

        if (cmpChar(input_s, "exit") == 1){run = 0;}
        if (cmpChar(input_s, "runexeTest") == 1){runExeTest();}
        if (cmpChar(input_s, "runTests") == 1){runTest();}
        if (cmpChar(input_s, "help") == 1){info();}

        if (cmpChar(input_s, "run:") == 1)
        {
            char input[50];
            scanf("%s", input);
            input_s = fastInitString(input);

            String* control_s = setCompControl(input_s);

            String* result = run_all_pro_one(control_s);
            printf("RESULT:"); PRINTNEWLINE
            printString(result); PRINTNEWLINE
        }
    }

    printf("program has finished");

    return 0;
}

//todo
//replae predef var with own vars

//may comandline arguments
