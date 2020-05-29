/*

        TEXT CIPHERS
Program works in three modes:
1) Test on hard coded value. To use this run the program and enter 1.
2) Test on user input.
    To use this mode , enter 2.
    It displays three options for three different function. Eter desired 1/2/3.
3) Test on input file
    Format of input file :
    Interger (1/2/3 describing function to run) 1->classical rail fence
                                                2->2-level rail fence enc
                                                3->2-level rail fence dec
    Interger : key
    Interger : key 2 (valid only for 2-level rail fence)
    Input text terminated by "~"
Ouput:
1) Mode 1 and 2 give console ouput
2) Mode 3 Writes to a file "output.txt"
*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/* Function : to clean file pointer */
void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
/*
FUNCTION : void railFence(char* message, char* cipherText, int length, int A)
Input : 1) message : to encrypt
        2) cipherText : to hold output
        3) length : length of input text
        4) A : key
OutPut: 1) Print encrypted text : Cipher text
        2) Stores in file
Flow:   Matrix is created with all elements of size [key][length] equal to "~"
        Direction is upwards intially
        Direction is reversed everytime the rail reachs row=0 or row=key-1
        Rail grid is filled in the current direction by incrementing row and col, where in each direction "key" steps are taken
*/
void railFence(char* message, char* cipherText, int length, int A)
{
    char rail[A][length]; // To store rail grid , A=rows, length=columns
    int row = 0, col = 0; //  Set to 0, to iterate through the rail gird
    int dir_flow = 0;  // Set to 0 (up) indicate change if needed in driection of flow (upwards/downwards)

    for (int i = 0; i < A; i++)  //loop intializes the rail grid with "~"
    {
        for (int j = 0; j < length; j++)
        {
           rail[i][j]='~'; //filling the rail matrix to distinguish filled spaces from blank ones
        }
    }
    for (int i = 0; i < length; i++)
    {
        if (row == 0 || row == A - 1)  // check the direction of flow & reverse the direction if filled the top or bottom rail
            dir_flow = !dir_flow;
        rail[row][col++] = message[i]; //fill the corresponding character from input
        dir_flow ? row++ : row--;      // find the next row using direction flag
    }
    int k = 0; // integer 'k' use to input characters to Output string cipherText
    for (int i = 0; i < A; i++)
    {
        for (int j = 0; j < length; j++)
        {
           if(rail[i][j] != '~')
           {
                cipherText[k]= rail[i][j];  //constructs the cipher using the rail matrix
                k++;
           }
        }
    }
    for(int k =0 ; k<length;k++)
        printf("%c",cipherText[k]); // to print cipher text
    printf("\n");
         
    FILE *fpo = fopen("output.txt","a"); // file ouput
    fprintf(fpo,"%s  ",cipherText);
    fprintf(fpo,"\n");
    fclose(fpo); //close file pointer

}
/*
FUNCTION : void railFence2(char* message, char* cipherText, int length, int A, int B, int dir)
Implements two level rail fence algorithm using two keys.
Input : 1) message : to encrypt
        2) cipherText : to hold output
        3) length : length of input text
        4) A : key
        5) B : second key
        6) dir : if 0 ->encryption
                 if 1 ->decryption
OutPut: 1) Print encrypted text : Cipher text
        2) Stores in file
Flow:   Matrix is created with all elements of size [key][length] with all elements equal to "~"
        Direction is upwards intially
        Cycle holds the current steps (key). Initial value is key 'A'
        Direction is reversed with the conditions row == 0 || row == A-1 || (row == A-B && cycle == B)
        Everytime the loop reached row key-1, other key is assigned to cycle, where in each direction "key" steps are taken
For decryption: After matrix is created, using the same direction process, in the rail grid
                Positions are marked with '*' to  figure-out the spots where texts should be placed
                (using the same way of moving diagonally up and down alternatively ).
                Then the cipher-text is filled row wise.
                After filling it, we traverse the matrix in zig-zag manner to obtain the original text.

*/
void railFence2(char* message, char* cipherText, int length, int A, int B, int dir)
{
    char rail[A][length]; // To store rail grid , A=rows, length=columns
    int row = 0, col = 0; //  Set to 0, to iterate through the rail gird
    int dir_flow =  0;  // Set to 0  (up) indicate change if needed in driection of flow (upwards/downwards)
    int cycle = A;

    for (int i = 0; i < A; i++)  //loop intializes the rail grid with "~"
    {
        for (int j = 0; j < length; j++)
        {
           rail[i][j]='~'; //filling the rail matrix to distinguish filled spaces from blank ones
        }
    }

/* ENCRYPTION CODE */
    if( dir == 0)
    {
        for (int i = 0; i<length;i++)
        {
            if( row == 0 || row == A-1 || (row == A-B && cycle == B))  // conditions for reversing the direction of cycle
                dir_flow = !dir_flow;
            if( row == A-1)   // if cycle reaches last row, change cycle from A to B/ B to A
            {
                if(cycle == A)
                    cycle =B;
                else
                    cycle = A;
            }
            rail[row][col++] = message[i]; //fill the corresponding character
            dir_flow ? row++ : row--;    // find the next row using direction flag  
        }

        int k = 0; // integer 'k' use to input characters to Output string cipherText
        for (int i = 0; i < A; i++)
        {
            for (int j = 0; j < length; j++)
            {
               if(rail[i][j] != '~')
               {
                    cipherText[k]= rail[i][j];  //constructs the cipher using the rail matrix
                    k++;
               }
            }
        }
        for(int k =0 ; k<length;k++)
            printf("%c",cipherText[k]); // to print cipher text
        printf("\n");
        FILE *fpo = fopen("output.txt","a"); // file ouput
        fprintf(fpo,"%s  ",cipherText);
        fprintf(fpo,"\n");
        fclose(fpo); //close file pointer

    }
/* DECRYPTION CODE */
    if(dir == 1)
    {
        row=0,col=0,dir_flow=0;
        for (int i = 0; i<length;i++)
        {
            if( row == 0 || row == A-1 || (row == A-B && cycle == B))  // conditions for reversing the direction of cycle
                dir_flow = !dir_flow;
            if( row == A-1)   // if cycle reaches last row, change cycle from A to B/ B to A
            {
                if(cycle == A)
                    cycle =B;
                else
                    cycle = A;
            }
            rail[row][col++] = '*';   // mark the places with '*'  
            dir_flow ? row++ : row--;    // find the next row using direction flag  
        }
        int k = 0; // integer 'k' use to input characters to Output string cipherText
        for (int i = 0; i < A; i++)
        {
            for (int j = 0; j < length; j++)
            {
               if(rail[i][j] == '*' && k<length)
               {
                    rail[i][j] = cipherText[k++]; //fill the rail matrix row wise

               }
            }
        }
        // read in zig-zag manner
        row=0,col=0,dir_flow=0; // re-initialize code variables
        cycle=A;
        for (int i=0;i<length;i++)
        {
            if( row == 0 || row == A-1 || (row == A-B && cycle == B))  // conditions for reversing the direction of cycle
                dir_flow = !dir_flow;
            if( row==A-1)   // if cycle reaches last row, change cycle from A to B/ B to A
            {
                if(cycle == A)
                    cycle=B;
                else
                    cycle=A;
            }
            message[i] = rail[row][col++];     // store in output  
            dir_flow ? row++ : row--;    // find the next row using direction flag  
        }
        for(int k =0 ;k<length;k++)
            printf("%c",message[k]); // to print plain text
        printf("\n");

        FILE *fpo = fopen("output.txt","a"); // file ouput
        fprintf(fpo,"%s  ",message);
        fprintf(fpo,"\n");
        fclose(fpo); //close file pointer
    }
}


int main()
{
    int option; // Set to selected mode to run the program (1/2/3)
    printf(" *** TEXT CIPHERS ***\n SELECT MODE TO RUN THIS PROGRAM : \n");
    printf(" OPTIONS : \n 1) DEFAULT INPUTS TO TEST ON ALL FUNCTIONS\n 2) CUSTOM INPUT AND SELECTED FUNCTIONS \n 3) PROVIDE INPUT FROM A FILE \n");
    scanf("%d",&option);
    if( option == 1)   // run on hard-coded values
    {
        char output[10000]; //to hold cipher text
        char inputstr[] = "This Program tests three Functions of text ciphers";
        int key=4;
        int key2=2; // for 2-level rail fence
        printf(" RUNNING CLASSICAL RAIL FENCE ALGORITHM \n PLAIN TEXT : %s \n KEY : %d \n",inputstr,key);
        printf(" CIPHER TEXT : ");
        railFence(inputstr,output,strlen(inputstr),key); // call classical rail fence
        printf("\n");
        printf(" RUNNING 2-level RAIL FENCE ALGORITHM \n PLAIN TEXT : %s \n KEY 'A' : %d \n KEY 'B' : %d \n",inputstr,key,key2);
        printf(" CIPHER TEXT : ");
        railFence2(inputstr,output,strlen(inputstr),4,2,0); // call 2-level rail fence
        printf("\n");
        char cText[] = "tgt nxrhorssefosetesi ra e heuci ft ihspmttrnto cp";
        printf(" RUNNING 2-level RAIL FENCE ALGORITHM (DECRYPTION)\n CIPHER TEXT : %s \n KEY 'A' : %d \n KEY 'B' : %d \n",cText,key,key2);
        printf(" PLAIN TEXT : ");
        railFence2(output,cText,strlen(cText),4,2,1); // call 2-level rail fence for decryption
        printf("\n");
    }
    if(option == 2) // run on input values from user
    {
        char output[10000]; // to hold output
        int key,key2;  // Set to key for rail fence
        int opt;
        printf("SELECT THE FUNCTION : \n 1) ENCRYPT USING CLASSICAL RAIL FENCE ALGORITHM\n 2) ENCRYPT USING 2-LEVEL RAIL FENCE ALGORITHM\n 3) DECRYPT USING 2-LEVEL RAIL FENCE ALGORITHM \n");
        scanf("%d",&opt); // Set to function  selected
        char *inputstr;  // Set to input text string
        size_t bufsize = 10000; // Max size

        inputstr = (char *)malloc(bufsize * sizeof(char)); // memory allocation
        printf("INPUT TEXT  : ");
        clean_stdin();  // cleaning stdin for input
        scanf("%[^\n]%*c", inputstr); // Input text

        //getline(&inputstr,&bufsize,stdin);
        printf("INPUT KEY : ");
        scanf("%d",&key);  // Input key
        if( opt == 1)   // if Classical rail fence
        {
            printf("CIPHER TEXT : ");
            railFence(inputstr,output,strlen(inputstr),key);
            printf("\n");
        }
        if( opt == 2)  // if 2-level rail fence , encryption
        {
            printf("INPUT KEY 2 : ");
            scanf("%d",&key2);  // input second key
            printf("CIPHER TEXT : ");
            railFence2(inputstr,output,strlen(inputstr),key,key2,0); // call rail fence function
            printf("\n");
        }
        if( opt == 3)  // if 2-level rail fence ,decryption
        {
            printf("INPUT KEY 2 : ");
            scanf("%d",&key2);  // input key
            printf("PLAIN TEXT : \n");
            railFence2(output,inputstr,strlen(inputstr),key,key2,1); // call function
            printf("\n");
        }
        printf("\n");
    }
    if(option == 3)
    {
       
        char input_file[] = "input.txt"; // Set to input file name
        printf("ENTER FILE : ");
        scanf("%s",input_file);
        FILE *fp =fopen(input_file,"r"); // Reads input file  

        if(!fp)  
        {
            fprintf(stderr,"Cannot open file");  // Error if cannot open file
        }
        fseek(fp, 0 , SEEK_END); // to end of file
        long fileSize = ftell(fp);
        fseek(fp, 0 , SEEK_SET); // required to read

        char operation[2]; // Stores key for reading from file
        int op,key,key2;  // op = function that needs to be called , key = key
        char *input = malloc(fileSize * sizeof(char)); // Stores text read from file
        char *output = malloc(fileSize * sizeof(char)); // Stores output
        char ch; // Set to character from file
        while(!feof(fp)){
            fscanf(fp, "%[^\n]%*c", operation);  // Read line untill '/n' encountered
            if(feof(fp))
                break;
            op = atoi(operation);  // Convert to integer, Set op= function to be performed
            char *input = malloc(fileSize * sizeof(char)); // Stores text read from file
            char *output = malloc(fileSize * sizeof(char)); // Stores output
            if( op ==1 )
            {
                size_t i=0;  // loop on input variable
                fscanf(fp, "%[^\n]%*c", operation);  // read second line containg key
                key = atoi(operation); // Convert to integer the key
                while( (ch=fgetc(fp)) !='~')
                {
                    input[i++] = ch; // read input plain text
                }
                input[i++]='\0';
                printf("\nRUNNING CLASSICAL RAIL FENCE ALGORITHM :\nPLAIN TEXT : %s \nKEY : %d \n",input,key);
                printf("CIPHER TEXT : ");
                railFence(input,output,strlen(input),key);
                fgetc(fp);
            }
            else // 2-level rail fence : encryption
            {
                size_t i=0; // loop on input variable
                fscanf(fp, "%[^\n]%*c", operation);  // read second line containg key
                key = atoi(operation); // Convert to integer the key
               
                fscanf(fp, "%[^\n]%*c", operation);  // read third line containg key 2
                key2 = atoi(operation); // Convert to integer the key
               
                while( (ch=fgetc(fp)) !='~')
                {
                    input[i++] = ch; // read input plain text
                }
                input[i++]='\0';
                printf("\nRUNNING 2-LEVEL RAIL FENCE ALGORITHM :\nINPUT TEXT : %s \nKEY : %d \nKEY 2 : %d\n",input,key,key2);
                printf("OUTPUT TEXT : ");
                if( op==2 )
                    railFence2(input,output,strlen(input),key,key2,0);
                if (op==3)
                    railFence2(output,input,strlen(input),key,key2,1);
                fgetc(fp);
            }
        }
        fclose(fp);

    }
    return 0;
}
