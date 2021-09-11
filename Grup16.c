#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Range {
    char symbol[10];
    int start1;
    int end1;
    int start2;
    int end2;
};
struct ParseTable {
    int operation;
    int cond;
    int IF;
    char operand1[10];
    char operand2[10];
    struct Range dest;
    struct Range src1;
    struct Range src2;
    //ERDEM
    int INITIALIZE;
    int SUM;
    int eq;
};
struct ParseTable PT[1];


struct SymbolTable{
	char symbol[10];
	int dim;
	int size1;
	int size2;
	int *base;	
};
struct SymbolTable ST[20];
void displayPT()
{
    printf("Operation\t%d\n\n",PT[0].operation);
    printf("IF\tCondition\tOperand1\tOperand2\n");		   	printf("%d\t%d\t\t%s\t\t%s\n",PT[0].IF,PT[0].cond,PT[0].operand1,PT[0].operand2);
    printf("\n\tDestination\tSource1\t\tSource2\n");
    printf("Symbol\t");	printf("%s\t\t\t%s\t\t%s\n",PT[0].dest.symbol,PT[0].src1.symbol,PT[0].src2.symbol);
    printf("Start1\t");	printf("%d\t\t\t%d\t\t%d\n",PT[0].dest.start1,PT[0].src1.start1,PT[0].src2.start1);
    printf("End1\t");	printf("%d\t\t\t%d\t\t%d\n",PT[0].dest.end1,PT[0].src1.end1,PT[0].src2.end1);
    printf("Start2\t");	printf("%d\t\t\t%d\t\t%d\n",PT[0].dest.start2,PT[0].src1.start2,PT[0].src2.start2);
    printf("End2\t");	printf("%d\t\t\t%d\t\t%d\n",PT[0].dest.end2,PT[0].src1.end2,PT[0].src2.end2);
}
void Print()
{
	int i,j,index;
	for(i=0;i<20;i++)
	{
		if(strcmp(ST[i].symbol,PT[0].src1.symbol)==0)
		{
			index = i;
			i = 20;
		}
	}
	//printf("--%d--", index);
	if(ST[index].dim==1)
	{
		ST[index].base += PT[0].src1.start1-1;
		for(i=PT[0].src1.start1-1; i<PT[0].src1.end1;i++)
		{
			printf("%d ",*ST[index].base);
			ST[index].base++;
		}
		//printf("--%d--", *ST[index].base);
	}
	else if(ST[index].dim==2)
	{
		ST[index].base += PT[0].src1.start1-1;
		ST[index].base += PT[0].src1.start2-1;
		for(i=PT[0].src1.start1-1; i<PT[0].src1.end1;i++){
			for(j=PT[0].src1.start2-1; j<PT[0].src1.end2;j++){
				printf("%d ",*ST[index].base);
				ST[index].base++;
			}		
		}
	}
	
}
	
void sum()
{
	if(PT[0].src1.start1 >= PT[0].src1.start2)
    {
        PT[0].src1.start1 = PT[0].src1.start2;
        PT[0].src1.start2 = 0;
        if(PT[0].src1.end1 < PT[0].src1.end2)
        {
            PT[0].dest.end1 = PT[0].src1.end2;
            
        }
        else if(PT[0].src1.end1 >= PT[0].src1.end2)
        {
            PT[0].dest.end1 = PT[0].src1.end1;
            
        }
    }
    else if(PT[0].src1.start1 < PT[0].src1.start2)
    {
        PT[0].src1.start1 = PT[0].src1.start1;
        PT[0].src1.start2 = 0;
        if(PT[0].src1.end1 < PT[0].src1.end2)
        {
            PT[0].dest.end1 = PT[0].src1.end2;
            
        }
        else if(PT[0].src1.end1 >= PT[0].src1.end2)
        {
            PT[0].dest.end1 = PT[0].src1.end1;        
        }
    }
	
}	

void init()
{
	int i, index,j;
	int flag = 0;

	
	for(i=0; i < 20;i++)
	{
		if(strcmp(PT[0].dest.symbol, ST[i].symbol) == 0)
		{
			flag = 1;
			index = i;
			i=20;
		}
	}
	if(flag == 0)
	{
		for(i=0; ST[i].symbol[0] = '\0';i++);
		strcpy(ST[i].symbol, PT[0].dest.symbol);
		if(PT[0].dest.start1==0)
		{
			
			//printf("---%d---", *ST[i].base);
			ST[i].dim=0;
			ST[i].size1=0;
			ST[i].size2=0;
		}
		else if(PT[0].dest.start2 == 0 && PT[0].dest.end2 == 0)
		{
			ST[i].base= (int *) malloc(PT[0].dest.end1);
			ST[i].dim=1;
			ST[i].size1=PT[0].dest.end1;
			ST[i].size2=0;
		}
		else 
		{
			if(PT[0].dest.end1 == 0)
			{
				PT[0].dest.end1 = PT[0].dest.start1;
			}
			if(PT[0].dest.end2 == 0)
			{
				PT[0].dest.end2 = PT[0].dest.start2;
			}
			ST[i].base= (int *) malloc(PT[0].dest.end1*PT[0].dest.end2);
			ST[i].dim=2;
			ST[i].size1=PT[0].dest.end1;
			ST[i].size2=PT[0].dest.end2;
		}
		index = i;
	}
	if(ST[index].dim==0)
	{
		ST[index].base = &PT[0].eq;
	}
	if(ST[index].dim==1)
	{
		for(i=PT[0].dest.start1-1; i<PT[0].dest.end1;i++)
		{
			ST[index].base = &PT[0].eq;
			printf("---%d---", *ST[index].base);
			ST[index].base++;
		}
		
	}
	if(ST[index].dim==2)
	{
		for(i=PT[0].dest.start1-1; i<PT[0].dest.end1;i++){
			for(j=PT[0].dest.start2-1; j<PT[0].dest.end2;j++){
				ST[index].base = &PT[0].eq;
				printf("---%d---", *ST[index].base);
				ST[index].base++;
			}		
		}
	}
	
}
void main()
{
    int flag = 0;
    char command[100];
    char word[20];
    char word2[20];
    char word3[20];
    int c,i;
    while(strcmp("-1",command)) {
    	flag = 0;
        printf("> ");
        fgets(command,100,stdin);
        for (c = 0; command[c] != ' '; c++) {
            word[c] = command[c];
        }
        if (strcmp(word, "print") == 0)    //PRINT
        {

            PT[0].operation = 6;
            PT[0].IF = 0;
            strcpy(PT[0].operand1, "0");
            strcpy(PT[0].operand2, "0");
            strcpy(PT[0].dest.symbol, "0");
            PT[0].dest.start1 = 0;
            PT[0].dest.start2 = 0;
            PT[0].dest.end1 = 0;
            PT[0].dest.end2 = 0;
            strcpy(PT[0].src2.symbol, "0");
            PT[0].src2.start1 = 0;
            PT[0].src2.start2 = 0;
            PT[0].src2.end1 = 0;
            PT[0].src2.end2 = 0;
            memset(word, 0, 20);
            c++;
            for (i = 0; command[c] != '['; c++) {
                word[i] = command[c];
                i++;
            }
            strcpy(PT[0].src1.symbol, word);
            memset(word, 0, 20);
            c++;
            for (i = 0; command[c] != ':' && command[c] != ','; c++) {
                word[i] = command[c];
                i++;
            }
            PT[0].src1.start1 = atoi(word);
            memset(word, 0, 20);
            if (command[c] == ':') {
                c++;
                for (i = 0; command[c] != ']' && command[c] != ','; c++) {
                    word[i] = command[c];
                    i++;
                }
                PT[0].src1.end1 = atoi(word);
                if (command[c] == ']') {
                    PT[0].src1.start2 = 0;
                    PT[0].src1.end2 = 0;
                } else {
                    c++;
                    memset(word, 0, 20);
                    for (i = 0; command[c] != ']' && command[c] != ':'; c++) {
                        word[i] = command[c];
                        i++;
                    }
                    PT[0].src1.end2 = 0;
                    PT[0].src1.start2 = atoi(word);
                    if (command[c] == ':') {
                        c++;
                        memset(word, 0, 20);
                        for (i = 0; command[c] != ']'; c++) {
                            word[i] = command[c];
                            i++;
                        }
                        PT[0].src1.end2 = atoi(word);
                    }
                }
            } else {
            	PT[0].src1.end1 = 0;
                c++;
                for (i = 0; command[c] != ':'; c++) {
                    word[i] = command[c];
                    i++;
                }
                PT[0].src1.start2 = atoi(word);
                c++;
                memset(word, 0, 20);
                for (i = 0; command[c] != ']'; c++) {
                    word[i] = command[c];
                    i++;
                }
                PT[0].src1.end2 = atoi(word);
            }
        } else if (strcmp(word, "if") == 0)    //IF
        {
            PT[0].IF = 1;
            memset(word, 0, 20);
            c += 2;
            for (i = 0; command[c] != '=' && command[c] != '!' && command[c] != '>' && command[c] != '<'; c++) {
                word[i] = command[c];
                i++;
            }
            strcpy(PT[0].operand1, word);
            memset(word, 0, 20);
            if (command[c] == '=') {
                PT[0].cond = 1;
                c++;
            } else if (command[c] == '!' && command[c + 1] == '=') {
                PT[0].cond = 2;
                c += 2;
            } else if (command[c] == '>') {
                if (command[c + 1] == '=') {
                    PT[0].cond = 4;
                    c += 2;
                } else {
                    PT[0].cond = 3;
                    c++;
                }
            } else if (command[c] == '<') {
                if (command[c + 1] == '=') {
                    PT[0].cond = 6;
                    c += 2;
                } else {
                    PT[0].cond = 5;
                    c++;
                }
            }
            for (i = 0; command[c] != ')'; c++) {
                word[i] = command[c];
                i++;
            }
            strcpy(PT[0].operand2, word);
            c++;
            memset(word, 0, 20);
            for (i = 0; command[c] != '['; c++) {
                word[i] = command[c];
                i++;
            }
            strcpy(PT[0].dest.symbol, word);
            memset(word, 0, 20);
            c++;
            for (i = 0; command[c] != ':' && command[c] != ','; c++) {
                word[i] = command[c];
                i++;
            }
            PT[0].dest.start1 = atoi(word);
            memset(word, 0, 20);
            if (command[c] == ':') {
                c++;
                for (i = 0; command[c] != ']' && command[c] != ','; c++) {
                    word[i] = command[c];
                    i++;
                }
                PT[0].dest.end1 = atoi(word);
                if (command[c] == ']') {
                    PT[0].dest.start2 = 0;
                    PT[0].dest.end2 = 0;
                } else {
                    c++;
                    memset(word, 0, 20);
                    for (i = 0; command[c] != ']' && command[c] != ':'; c++) {
                        word[i] = command[c];
                        i++;
                    }
                    PT[0].dest.start2 = atoi(word);
                    if (command[c] == ':') {
                        c++;
                        memset(word, 0, 20);
                        for (i = 0; command[c] != ']'; c++) {
                            word[i] = command[c];
                            i++;
                        }
                        PT[0].dest.end2 = atoi(word);
                    }
                }
            } else {
                c++;
                for (i = 0; command[c] != ':'; c++) {
                    word[i] = command[c];
                    i++;
                }
                PT[0].dest.start2 = atoi(word);
                c++;
                memset(word, 0, 20);
                for (i = 0; command[c] != ']'; c++) {
                    word[i] = command[c];
                }
                PT[0].dest.end2 = atoi(word);
            }
            c += 4;
            memset(word, 0, 20);
            for (i = 0; command[c] != '['; c++) {
                word[i] = command[c];
                i++;
            }
            strcpy(PT[0].src1.symbol, word);
            c++;
            for (i = 0; command[c] != ':' && command[c] != ','; c++) {
                word[i] = command[c];
                i++;
            }
            PT[0].src1.start1 = atoi(word);
            memset(word, 0, 20);
            if (command[c] == ':') {
                c++;
                for (i = 0; command[c] != ']' && command[c] != ','; c++) {
                    word[i] = command[c];
                    i++;
                }
                PT[0].src1.end1 = atoi(word);
                if (command[c] == ']') {
                    PT[0].src1.start2 = 0;
                    PT[0].src1.end2 = 0;
                } else {
                    c++;
                    memset(word, 0, 20);
                    for (i = 0; command[c] != ']' && command[c] != ':'; c++) {
                        word[i] = command[c];
                        i++;
                    }
                    PT[0].src1.start2 = atoi(word);
                    if (command[c] == ':') {
                        c++;
                        memset(word, 0, 20);
                        for (i = 0; command[c] != ']'; c++) {
                            word[i] = command[c];
                            i++;
                        }
                        PT[0].src1.end2 = atoi(word);
                    }
                }
            } else {
                c++;
                for (i = 0; command[c] != ':'; c++) {
                    word[i] = command[c];
                    i++;
                }
                PT[0].src1.start2 = atoi(word);
                c++;
                memset(word, 0, 20);
                for (i = 0; command[c] != ']'; c++) {
                    word[i] = command[c];
                }
                PT[0].src1.end2 = atoi(word);
            }


            if (command[c + 2] == '+') {
                PT[0].operation = 1;
            } else if (command[c + 2] == '-') {
                PT[0].operation = 2;
            } else if (command[c + 2] == '*') {
                PT[0].operation = 3;
            } else if (command[c + 2] == '/') {
                PT[0].operation = 4;
            } else {
                PT[0].operation = 8;
                i = -1;
                PT[0].src2.start1 = 0;
                PT[0].src2.start2 = 0;
                PT[0].src2.end1 = 0;
                PT[0].src2.end2 = 0;
                strcpy(PT[0].src2.symbol, "0");
            }
            if (i != -1) {
                c += 4;
                memset(word, 0, 20);
                for (i = 0; command[c] != '['; c++) {
                    word[i] = command[c];
                    i++;
                }
                strcpy(PT[0].src2.symbol, word);
                c++;
                for (i = 0; command[c] != ':' && command[c] != ','; c++) {
                    word[i] = command[c];
                    i++;
                }
                PT[0].src2.start1 = atoi(word);
                memset(word, 0, 20);
                if (command[c] == ':') {
                    c++;
                    for (i = 0; command[c] != ']' && command[c] != ','; c++) {
                        word[i] = command[c];
                        i++;
                    }
                    PT[0].src2.end1 = atoi(word);
                    if (command[c] == ']') {
                        PT[0].src2.start2 = 0;
                        PT[0].src2.end2 = 0;
                    } else {
                        c++;
                        memset(word, 0, 20);
                        for (i = 0; command[c] != ']' && command[c] != ':'; c++) {
                            word[i] = command[c];
                            i++;
                        }
                        PT[0].src2.start2 = atoi(word);
                        if (command[c] == ':') {
                            c++;
                            memset(word, 0, 20);
                            for (i = 0; command[c] != ']'; c++) {
                                word[i] = command[c];
                                i++;
                            }
                            PT[0].src2.end2 = atoi(word);
                        }
                    }
                } else {
                    c++;
                    for (i = 0; command[c] != ':'; c++) {
                        word[i] = command[c];
                        i++;
                    }
                    PT[0].src2.start2 = atoi(word);
                    c++;
                    memset(word, 0, 20);
                    for (i = 0; command[c] != ']'; c++) {
                        word[i] = command[c];
                    }
                    PT[0].src2.end2 = atoi(word);
                }

            }
        }
        else if (strcmp(word, "read") == 0) //READ
        {
            printf("read");
        }

        else if (strcmp(word, "read") == 0) //INITIALIZE
        {
            printf("read");
        }

        else //SUM AND AVER IS INSIDE THIS ELSE BECAUSE OF THEIR UNIQUE SYNTAX
        {
            
            c++;
            //printf("%d",c);
            for(i=0;command[c] !=' ';c++)
            {
                word2[i]=command[c];
                i++;
            }
            c++;
            
            for(i=0;command[c] !=' ';c++)
            {
                word3[i]=command[c];
                i++;
            }
            c++;
            //printf("---%s----",word3);

            if (strcmp(word3, "sum") == 0) //SUM
            {
                PT[0].IF = 0;
                PT[0].operation = 1;
                strcpy(PT[0].operand1, "0");
                strcpy(PT[0].operand2, "0");
                strcpy(PT[0].dest.symbol, word);
                PT[0].dest.start1 = 0;
                PT[0].dest.start2 = 0;
                PT[0].dest.end1 = 0;
                PT[0].dest.end2 = 0;
                strcpy(PT[0].src2.symbol, "0");
                PT[0].src2.start1 = 0;
                PT[0].src2.start2 = 0;
                PT[0].src2.end1 = 0;
                PT[0].src2.end2 = 0;

                memset(word2, 0, 20);
                for(i = 0; command[c] != '['; c++) {
                    word2[i] = command[c];
                    i++;
                }
                strcpy(PT[0].src1.symbol, word2);
                c++;
                for (i = 0; command[c] != ':' && command[c] != ','; c++) {
                    word2[i] = command[c];
                    i++;
                }
                PT[0].src1.start1 = atoi(word2);
                memset(word2, 0, 20);

                if (command[c] == ':') {
                    c++;
                    for (i = 0; command[c] != ']' && command[c] != ','; c++) {
                        word2[i] = command[c];
                        i++;
                    }
                    PT[0].src1.end1 = atoi(word2);
                    if (command[c] == ']') {
                        PT[0].src1.start2 = 0;
                        PT[0].src1.end2 = 0;
                    } else {
                        c++;
                        memset(word2, 0, 20);
                        for (i = 0; command[c] != ']' && command[c] != ':'; c++) {
                            word2[i] = command[c];
                            i++;
                        }
                        PT[0].src1.end2 = 0;
                        PT[0].src1.start2 = atoi(word2);
                        if (command[c] == ':') {
                            c++;
                            memset(word2, 0, 20);
                            for (i = 0; command[c] != ']'; c++) {
                                word2[i] = command[c];
                                i++;
                            }
                            PT[0].src1.end2 = atoi(word2);
                        }
                    }
                } else {
                    PT[0].src1.end1 = 0;
                    c++;
                    for (i = 0; command[c] != ':'; c++) {
                        word2[i] = command[c];
                        i++;
                    }
                    PT[0].src1.start2 = atoi(word2);
                    c++;
                    memset(word2, 0, 20);
                    for (i = 0; command[c] != ']'; c++) {
                        word2[i] = command[c];
                        i++;
                    }
                    PT[0].src1.end2 = atoi(word2);
                }
            }

            //////////////code declarations for elif's part starts here//////////////

			/*int c1 = c;

			for(i=0;command[c1]!='\0';c1++)
            {
                word4[i] = command[c1];
                i++;
            }
			c1++;*/


			//////////////code declarations for elif's part ends here////////////////

			//*******************AVER*******************/// starts here
			
			/*if(strcmp(word3, "aver") == 0) {

				char passInt1[20] = "-1", passInt2[20] = "-1";
				int check, count=0, p1=0, p2, p3, p4, p5;
				int toInt1 =0, toInt2 = 0;

				memset(passInt1, 0, 20);
				memset(passInt2, 0, 20);

				PT[0].IF = 0;
                PT[0].operation = 10;
                strcpy(PT[0].operand1, "0");
                strcpy(PT[0].operand2, "0");
                strcpy(PT[0].dest.symbol, word);
				PT[0].dest.start1 = -1;
                PT[0].dest.start2 = -1;
                PT[0].dest.end1 = -1;
                PT[0].dest.end2 = -1;
				
				while(word4[p1]!='['){p1++;}

				strncpy(PT[0].src1.symbol, word4, p1); // ex:A[1, 1:3] -----> takes 'A'
				p1++;

				for(check=0; word4[check]!='\0';check++) { // to count how many ':' chars

					if(word4[check] == ':')
						count++;
				
				}

				if(count == 1) { //ex: A[1, 1:2]
					
					for(p2=0;word4[p1]!=',';p2++) { //ex: A[**1**, 1:3]

						passInt1[p2] = word4[p1];
						p1++;

					}
					p1++;
					toInt1 = atoi(passInt1);
					PT[0].src1.start1 = toInt1;
					PT[0].src1.end1 = -1;

					for(p3=0;word4[p1]!=':';p3++) { // ex: A[1, **1**:3]
						
						passInt1[p3] = word4[p1];
						p1++;
					}
					p1++;
					toInt1 = atoi(passInt1);
					PT[0].src1.start2 = toInt1;
					
					for(p4=0;word4[p1]!='\0';p4++) { // ex: A[1, 1:**3**]
						
						passInt2[p4] = word4[p1];
						p1++;
					}
					toInt2 = atoi(passInt2);
					PT[0].src1.end2 = toInt2;
					
				}

				if(count == 2) { //ex: A[1:2, 1:2]
			
					for(p2=0;word4[p1]!=':';p2++) { //ex: A[**1**, 1:3]

						passInt1[p2] = word4[p1];
						p1++;

					}
					p1++;
					toInt1 = atoi(passInt1);
					PT[0].src1.start1 = toInt1;

					for(p3=0;word4[p1]!=',';p3++) { // ex: A[1:**3**, 1:3]
						
						passInt2[p3] = word4[p1];
						p1++;
					}
					p1++;
					toInt2 = atoi(passInt2);
					PT[0].src1.end1 = toInt2;
					while(word4[p1] == ' ') {p1++;}
					
					for(p4=0;word4[p1]!=':';p4++) { // ex: A[1:3, **1**:3]
						
						passInt1[p4] = word4[p1];
						p1++;
					}
					p1++;
					toInt1 = atoi(passInt1);
					PT[0].src1.start2 = toInt1;

					for(p4=0;word4[p1]!='\0';p4++) { // ex: A[1:3, 1:**3**]
						
						passInt2[p4] = word4[p1];
						p1++;
					}
					p1++;
					toInt2 = atoi(passInt2);
					PT[0].src1.end2 = toInt2;
				}
								
				strcpy(PT[0].src2.symbol, "-1");
                PT[0].src2.start1 = -1;
                PT[0].src2.start2 = -1;
                PT[0].src2.end1 = -1;
                PT[0].src2.end2 = -1;
				
			}*/


            //printf("---%s----",word);
           //printf("---%s----",word2);
            //printf("---%s----",word3);
            else //INITIALIZE CALCULATE COPY
            {
		for(i=0; word3[i] != '\0' ;i++)
		{
			if(word3[i] == '[')
			{
				flag = 1;
			}			
		}
		if(flag == 1)//Calculate Copy
		{
		
		}
		else//Initialize
		{
			PT[0].eq=atoi(word3);
			PT[0].operation=8;
			PT[0].IF=0;
			strcpy(PT[0].operand1, "0");
               	strcpy(PT[0].operand2, "0");
               	strcpy(PT[0].src1.symbol, "0");
                	PT[0].src1.start1 = 0;
                	PT[0].src1.start2 = 0;
                	PT[0].src1.end1 = 0;
                	PT[0].src1.end2 = 0;
                	strcpy(PT[0].src2.symbol, "0");
                	PT[0].src2.start1 = 0;
                	PT[0].src2.start2 = 0;
                	PT[0].src2.end1 = 0;
                	PT[0].src2.end2 = 0;
                	//strcpy(PT[0].dest.symbol, " ");
                	flag = 0;
			for(i=0; word[i] != '\0';i++)
			{
				word2[i] = word[i];
				if(word[i] == ']')
				{
					flag = 1;
				}
			
			}
			//printf("---%d---",flag);
			if (flag == 0)
			{
				strcpy(PT[0].dest.symbol, word2);
			
			}
			else{	
				memset(word2, 0, 20);
				for (i = 0; word[i] != '['; i++)
				{
					word2[i] = word[i];
				}
				strcpy(PT[0].dest.symbol, word2);	
			}
			//printf("---%s----", command);
			//strcpy(PT[0].dest.symbol, word2);
			//printf("---%s----", word2);
			if(flag == 1)//Array init
			{
				//printf("---%s----", word);
				c=strlen(word2)+1;
				memset(word2, 0, 20);
				for (i = 0; word[c] != ':' && word[c] != ','; c++) {
                			word2[i] = word[c];
                			i++;
            			}
            			//printf("---%s----", word2);
            			PT[0].dest.start1 = atoi(word2);
            			memset(word2, 0, 20);
            			//printf("---%c----", word[c]);
            			if (word[c] == ':') 
            			{	
            				
                			c++;
                			for (i = 0; word[c] != ']' && word[c] != ','; c++) 
                			{
                    				word2[i] = word[c];
                    				i++;
                			}
                			PT[0].dest.end1 = atoi(word2);
                			if (word[c] == ']') 
                			{
                    				PT[0].dest.start2 = 0;
                    				PT[0].dest.end2 = 0;
                    			} 
                			else 
                			{
                    				c++;
                    				memset(word2, 0, 20);
                    				for (i = 0; word[c] != ']' && word[c] != ':'; c++) 
                    				{
                        				word2[i] = word[c];
                        				i++;
                    				}		
                    				PT[0].dest.end2 = 0;
                    				PT[0].dest.start2 = atoi(word2);
                    				if (word[c] == ':') 
                    				{
                       				c++;
                        				memset(word2, 0, 20);
                        				for (i = 0; word[c] != ']'; c++) 
                        				{
                            					word2[i] = word[c];
                            					i++;
                        				}
                        			PT[0].dest.end2 = atoi(word2);
                    				}
                			}
            			}	 
            			else 
            			{
            				PT[0].dest.end1 = 0;
					c++;
					for (i = 0; word[c] != ':'; c++) 
					{
                    				word2[i] = word[c];
                    				i++;
                			}
                			PT[0].dest.start2 = atoi(word2);
                			c++;
                			memset(word2, 0, 20);
                			for (i = 0; word[c] != ']'; c++) 
                			{
                    				word2[i] = word[c];
                    				i++;
                    			}
                				PT[0].dest.end2 = atoi(word2);
            				
	   			}
	   		}
	   		else//Single Variable
			{
				PT[0].dest.start1 = 0;
                		PT[0].dest.start2 = 0;
                		PT[0].dest.end1 = 0;
                		PT[0].dest.end2 = 0;
			}
		
	    	}
	}
	}
        displayPT();
        if(PT[0].operation == 8)
        {
        	init();
        } 
        else if(PT[0].operation == 6)
        {
        	Print();
        }
        else if(PT[0].operation == 1)
        {
        	sum();
        }
        memset(command, 0, 20);
        memset(word, 0, 20);
        memset(word2, 0, 20);
        memset(word3, 0, 20);
    
}
}

