#include <stdio.h>
#include <string.h>

/*
Hints :
There are some secret codes in this program : You have to find out by taking a look in the codes to find out the secret codes. Only author of the program can explain the meaning of the codes
cp=check point : checkpoints are put so if user inputs out of range then the program will take him/her back to the checkpoint so s/he can input again until the input is valid acording to this program.
curSForm=Currency in short form e.g. USA dollar = USD
multiplierK=Multiplier constant : The value is going to be multiplied with constant value of money and be used to convert currency
k4sal=constant for salary : The final double that will be multiplied with the salary and decide the salary amount



 */


char currency[3]="TK",sCode[10]="",jobDes[50],userInpOrDef[10],convOrNot[10],convertToIndex[10],kValUserDef[10];
int lastInt=0;//Last integer input : In any of the input the last typed input will be the value "lastInt" variable will hold. Since the lastInp is always the last value we input as integer so we can use this lastInst variable in every case of input
const int k=100000;//Constant root value for salary. The salaries will be relative to it. For example if job1 is a high level of job and its salay is 5 and job2 is lower level of job and it's salary is 2 when k is 100000. Then if you use default constant and use the constant value as 200000 then you will get result of job1 salary as 10 and job2 salary as 4. That's why I call the program dynamic
double k4sal=1;//
int kUnited;//Constant united : If you choose to use default constant, the value of k variable will be assigned in it. Else if you choose to use user defined constant then the filtered integer value of kValUserDef will be assigned in it. Both ways the values are getting united in kUnited so we don't need to know if user choose to use default constant or user defined constant

//Note : The conversion multiplier from Taka to other currency may be incorrect according to time. According to current time (29 July, 2022) they are the accurate currency multipliers below.
const double TKtoUSD=0.011,TKtoEUR=0.010,TKtoJPY=1.42,TKtoAUD=0.015,TKtoCAD=0.014,TKtoSAR=0.040,TKtoINR=0.84;
void exitf()
{
    //Exit function : Will exit the program with a message
    println("\n\n||   Program finished   ||\n");
    exit(0);
}
int mwSCode(char scodeParam[])
{
    //matching with Secret Code?
    int False=strcmpi(sCode,scodeParam);
    if(False==0)
    {
        return 1;
    }
    return 0;
}


int isNumber(char inp[])
{
    //Since isdigit() function is limited to check character only so I had to make a user defined isNumber function so it can check if a string is pure number or not. If the string is a pure number then it will be stored in lastInt variable else it will warn and will ask for input again.
    int len=strlen(inp);
    //We need to get the length of that string so we can limit the iteration process to the last value of that string.

    //Loop for checking if it contains any other type of data except integer.
    for(int i=0; i<len; i++)
    {
        if(isdigit(inp[i])==0)
        {
            //If it finds that any of the character at position i in the string is not a digit then it will return 0 means inNumber is false
            //When it finds a character is not a number, it will return 0 and stop the function, so the conversion process below will not process, so there is not risk of error.
            println("\n   Invalid input...You must input number values that should not contain any symbol or alphabets.....\n");
            return 0;
        }
    }
    //Else : when the input is pure integer,not char or string
    //Converting the string into integer
    int temp=0;
    int n;
    for (int i=0; i<len; i++)
    {
        n=inp[i]-'0';
        //Converted and saved the character as integer digit
        //I tried but could not find any to convert string into integer directly in c. But I was able to convert a character into digit/integer. So I decided to iterate the same process over every character in a string and make it the actual number we input, by addition and multiplication
        temp+=n;//Added the digit to temp variable
        if(i<len-1)
        {
            //Then multiplied by 10 so we can get the actual value
            //If we multiply the resulted value by 10 after getting last digit of that string, then it will not give us the actual value. For example in 5412 the last value is 2. If we multiply it by 10 after we got the digit 2 then it will result 54120. So we need to avoid the multiplication when we got the last value. So there is is the condition len-1 means the multiplication will stop just before we get the last digit value.
            temp*=10;
        }
    }
    //The final result we get will be saved to lastInt( Last integer input) as integer. And also return 1 means isNumber is 1(true) means the input is pure integer type. That't what we needed
    lastInt=temp;
    return 1;
}

void sp()
{
    //Secret portal. Some special codes are preserved for special outputs
    //If the input matches with any of 3 the following values then it will let you enter to the secret portal
    if(lastInt==9874 || lastInt==3152 || lastInt==22103152)
    {
        //If the input matches with any of the values
        println("\n\n    ~~ Welcome to secret portal ~~\n");
cpScanSCode:
        scanf("%s",sCode);
        //Here are some secret codes for some specific output
        if(mwSCode("RESTART"))
        {
            println("\n\n...Restart successful...\n");
            process();
        }
        else if(mwSCode("YUSUF") || mwSCode("AUTHOR"))
        {
            println("\n\nAuthor : \nMd. Yusuf Hossen\nID : 22103152\nEmail official: 22103152@iubat.edu\nEmail personal : hereimyusuf@gmail.com\nContact no : 01623108200\n");
            goto cpScanSCode;
        }
        else if(mwSCode("EXIT")||mwSCode("LEAVE"))
        {
            exitf();
        }
        else if(mwSCode("RESET"))
        {
            println("\n\n....Reset Successful....\n\n");
            main();
        }
        else
        {
            println("\n   ....Wrong secret code. Try again....");
            goto cpScanSCode;
        }
    }

}

void selNotif(char option[])
{
    //selNotif=Selected notify : Will print the option you have selected in an attractive way
    printf("\n|          ");

    printf("    You have selected : %s\n               ------------------\n\n",option);
}
void println(char str[])
{
    //I loved the built in function "println" in JAVA that prints something with new line. So I am creating it manually to use in c so that I don't have to put \n every time.
    printf("%s\n",str);

}
void notFoundWarn(char mTitle[])
{
    //A fixed warning text with just changed index number and main title; mTitle= Main Title
    printf("    \n\n....There is no %s at index no %d. Select %s again....\n\n",mTitle,lastInt,mTitle);
}
int validSelection(char whatToSelect[],char option1[],char option2[])
{
    //The function will check the value put in compareWith parameter and check it if it's either 1 or 2. If it finds that the compareWith is equals to 1 or 2 then the function will return 1 means validSelection is true, else it will return 0 means the user selection is invalid which is not equals to 1 or 2. If validSelection is false then it will print warning to type 1 or 2 and suggestion of what to select.
    if (lastInt==1 || lastInt==2)
    {
        return 1;
    }
    //Else it will return false with a message and options
    printf("\n    ....You are supposed to type either 1 or 2....\n\nSelect %s again : \n1.%s\n2.%s\n",whatToSelect,option1,option2);
    return 0;
}
void setupCurrency(char curSForm[3],double cMult)
{
    //cMult : Convert Multiplier
    //The function will take currency format (e.g. USD) and convert multiplier (e.g. 1 taka = 0.011 dollar, it will take 0.011 in it's parameter in case of Taka to USD conversion) and update the necessary variables after conversion
    strcpy(currency,curSForm);
    kUnited*=cMult;//Earlier we have discussed about the kUnited variable. You might have already learned about it. The conversion multiplier is getting multiplied with kUnited and now the value of kUnited is the converted value of currency type user have selected
    printf("\n    Converted value is %d %s\n\n",kUnited,currency);


}

void jobSelection()
{
    println("Select job : ");
    char job[20],dept[20],degree[20],design[20],guardPos[20],stuff[20],ctnStuff[20];//Some string variables to scan the job type or sections
cpSelectJob:
    println("    Available jobs\n1.Faculty\n2.Guard\n3.Stuff\n4.Cleaner\n5.Lab assistant\n6.Librarian\n7.Account manager\n8.Admission manager\n9.Gardener\n10.Driver");

    scanf("%s",&job);
    if(isNumber(job)==1)
    {
        sp();
        switch(lastInt)
        {
        case 1:
            selNotif("Faculty");
cpSelectDept:
            println("    Select department : \n1.Business Administration\n2.Computer Science\n3.Civil Engineering\n4.Mechanical Engineering\n5.Electrical and Electronics Engineering\n6.Nursing\n7.Tourism and Hospitality Management\n8.Agriculture\n9.Economics\n10.English");
            scanf("%s",&dept);
            if(isNumber(dept)==1)
            {
                sp();
                switch (lastInt)
                {
                case 1:
                    selNotif("BA");
                    println("    Select degree : \n1.Bachelor\n2.Masters");
cpSelectDegree:
                    scanf("%s",&degree);
                    if(isNumber(degree)==1)
                    {
                        sp();
                        if(validSelection("degree","Bachelor","Masters")==1)
                        {
                            if(lastInt==1)
                            {
                                k4sal=0.6;
                                selNotif("BBA");
                                strcpy(jobDes,"Faculty of BBA department");
                            }
                            else
                            {
                                k4sal=0.8;
                                selNotif("MBA");
                                strcpy(jobDes,"Faculty of MBA department");
                            }
                        }
                        else
                        {
                            goto cpSelectDegree;
                        }

                    }
                    else
                    {
                                            println("    Select degree : \n1.Bachelor\n2.Masters");

                        goto cpSelectDegree;
                    }

                    break;
                case 2:
                    selNotif("BCSE");
                    strcpy(jobDes,"Faculty of BCSE department");
                    k4sal=1;
                    break;
                case 3:
                    selNotif("BSCE");
                    strcpy(jobDes,"Faculty of BSCE department");
                    k4sal=0.8;
                    break;
                case 4:
                    k4sal=0.8;
                    selNotif("BSME");
                    strcpy(jobDes,"Faculty of BSME department");
                    break;
                case 5:
                    k4sal=0.8;
                    selNotif("BEEE");
                    strcpy(jobDes,"Faculty of BEEE department");
                    break;
                case 6:
                    k4sal=0.6;
                    selNotif("BSN");
                    strcpy(jobDes,"Faculty of BSN department");
                    break;
                case 7:
                    k4sal=0.6;
                    selNotif("BATHM");
                    strcpy(jobDes,"Faculty of BATHM department");
                    break;
                case 8:
                    k4sal=0.7;
                    selNotif("BSAg");
                    strcpy(jobDes,"Faculty of BSAg department");
                    break;
                case 9:
                    k4sal=0.6;
                    selNotif("BAEcon");
                    strcpy(jobDes,"Faculty of BAEcon department");
                    break;
                case 10:
                    k4sal=1;
                    selNotif("BA in English");
                    strcpy(jobDes,"Faculty of BA in English department");
                    break;
                default:
                    notFoundWarn("department");
                    goto cpSelectDept;
                }
            }
            else
            {
                //Else means isNumber is false means the input is not a pure number. User might have entered some symbols or alphabets in the user inputs that's why the function isNumber returned false. Now it will show an alert message according to isNumber function
                goto cpSelectDept; //Whenever the program finds invalid input it will take the user back to the input section and ask for the input again and again until user enters a valid value the program is supposed to work with
            }

cpSelectDesign:
            println("Select designation : \n1.Chairman\n2.Coordinator\n3.Professor\n4.Assistant Professor\n5.Senior Lecturer\n6.Lecturer");
            scanf("%s",&design);
            if(isNumber(design)==1)
            {
                sp();
                switch(lastInt)
                {
                case 1:
                    k4sal*=2;
                    selNotif("Chairman");
                    strcat(jobDes," chairman");
                    break;
                case 2:
                    k4sal*=1.5;
                    selNotif("Co-ordinator");
                    strcat(jobDes," co-ordinator");
                    break;
                case 3:
                    k4sal*=1.2;
                    selNotif("Professor");
                    strcat(jobDes," professor");
                    break;
                case 4:
                    k4sal*=1;
                    selNotif("Assistant Professor");
                    strcat(jobDes," assistant professor");
                    break;
                case 5:
                    k4sal*=0.8;
                    selNotif("Senior Lecturer");
                    strcat(jobDes," senior lecturer");
                    break;
                case 6:
                    k4sal*=0.6;
                    selNotif("Lecturer");
                    strcat(jobDes," lecturer");
                    break;
                default:
                    notFoundWarn("designation");
                    goto cpSelectDesign;
                }

            }
            else
            {
                goto cpSelectDesign;
            }

            break;
        case 2:
            selNotif("Guard");
cpGuard:
            println("    Select guard position\n1.Main gate\n2.Building gate\n3.Account office\n4.Campus border\n");
            scanf("%s",&guardPos);
            if(isNumber(guardPos)==1)
            {
                sp();
                strcpy(jobDes,"Guard of");
                switch(lastInt)
                {
                case 1:
                    selNotif("Main gate");
                    k4sal=0.15;
                    strcat(jobDes," main gate");
                    break;
                case 2:
                    k4sal=0.13;
                    selNotif("Building gate");
                    strcat(jobDes," building gate");
                    break;
                case 3:
                    k4sal=0.12;
                    selNotif("Account office");
                    strcat(jobDes," account office");
                    break;
                case 4:
                    k4sal=0.12;
                    selNotif("Campus border");
                    strcat(jobDes," campus border");
                    break;
                default:
                    notFoundWarn("guard position");
                    goto cpGuard;
                }

            }
            else
            {
                goto cpGuard;
            }

            break;
        case 3:
            selNotif("Stuff");
cpStuff:
            println("    Select stuff : \n1.Canteen stuff\n2.Floor stuff\n3.Information stuff");
            scanf("%s",&stuff);
            if(isNumber(stuff)==1)
            {
                sp();
                strcpy(jobDes,"Stuff of");
                switch(lastInt)
                {
                case 1:
                    selNotif("Canteen stuff");
                    println("    Select canteen :\n1.Lemon Lime\n2.Didir canteen");
cpCtnStuff:
                    scanf("%s",&ctnStuff);
                    if(isNumber(ctnStuff)==1)
                    {
                        sp();
                        if(validSelection("canteen","Lemon Lime","Didir canteen")==1)
                        {
                            if(lastInt==1)
                            {
                                selNotif("Lemon Lime");
                                k4sal=0.25;
                                strcat(jobDes," Lemon Lime");
                            }
                            else
                            {
                                selNotif("Didir canteen");
                                k4sal=0.2;
                                strcat(jobDes," Didir canteen");
                            }
                        }
                        else
                        {
                            goto cpCtnStuff;
                        }

                    }
                    else
                    {
                    println("    Select canteen :\n1.Lemon Lime\n2.Didir canteen");
                        goto cpCtnStuff;
                    }
                    break;
                case 2:
                    selNotif("Floor stuff");
                    k4sal=0.15;
                    strcat(jobDes," floor");
                    break;
                case 3:
                    selNotif("Information stuff");
                    k4sal=0.18;
                    strcat(jobDes," information");
                    break;
                default:
                    notFoundWarn("stuff");
                    goto cpStuff;
                }

            }
            else
            {
                goto cpStuff;
            }

            break;
        case 4:
            selNotif("Cleaner");
            k4sal=0.1;
            strcpy(jobDes,"Cleaner");
            break;
        case 5:
            selNotif("Lab assistant");
            k4sal=0.3;
            strcpy(jobDes,"Lab assistant");
            break;
        case 6:
            selNotif("Librarian");
            k4sal=0.3;
            strcpy(jobDes,"Librarian");
            break;
        case 7:
            selNotif("Account manager");
            k4sal=0.5;
            strcpy(jobDes,"Account manager");
            break;
        case 8:
            selNotif("Admission manager");
            k4sal=0.3;
            strcpy(jobDes,"Admission manager");
            break;
        case 9:
            selNotif("Gardener");
            k4sal=0.15;
            strcpy(jobDes,"Gardener");
            break;
        case 10:
            selNotif("Driver");
            println("    Select bus type : \n1.Student bus\n2.Stuff bus");
            char busType[20];
cpBusType:
            scanf("%s",&busType);
            if(isNumber(busType)==1)
            {
                sp();
                if(validSelection("bus type","Student bus","Stuff bus")==1)
                {
                    if(lastInt==1)
                    {
                        selNotif("student bus");
                        k4sal=0.15;
                        strcpy(jobDes,"student bus");
                    }
                    else
                    {
                        selNotif("stuff bus");
                        k4sal=0.20;
                        strcpy(jobDes,"stuff bus");
                    }
                }
                else
                {
                    goto cpBusType;
                }

            }
            else
            {
            println("    Select bus type : \n1.Student bus\n2.Stuff bus");
                goto cpBusType;
            }

            break;
        default:
            notFoundWarn("job");
            goto cpSelectJob;
        }

    }
    else
    {
        goto cpSelectJob;
    }

}

void process()
{
    k4sal=1;//User can restart the program by using secret code. Since the program modifies k4sal value and k4sal is a global variable. So the restart program will not reset the value of k4sal. So it's default value is assigned at the beginning so restarting the program also resets the value of k4sal
    println("\n\n||   Program START :   ||\n");
    println("\n\n   Select if you want to use default constant value or input your own constant value\n1.Use default constant\n2.User defined\n");
cpEnterKorUseDef:
    scanf("%s",&userInpOrDef);
    if(isNumber(userInpOrDef)==1)
    {
        sp();
        if(validSelection("constant type","Use default constant","User defined")==1)
        {
            if(lastInt==1)
            {
                kUnited=k;
                selNotif("to use default constant 100000 Taka");

            }
            else
            {
                selNotif("to input value of constant k manually");
cpConst:
                println("    Enter value of constant k (in Taka) :");
                scanf("%s",&kValUserDef);
                if(isNumber(kValUserDef)==1)
                {
                    sp();
                    kUnited=lastInt;
                    if(kUnited<1000)
                    {
                        printf("%d",kUnited);
                        //Bug here
                        println("    ....You shouldn't use too less constant value for salary. Enter again :");
                        goto cpConst;
                    }
                    printf("\n\n    ....You are using constant value of salary as %d Taka\n\n",kUnited);

                }
                else
                {
                    goto cpConst;
                }

            }
        }
        else
        {
            //Else means valid selection is false means option selection by the user is invalid. User might have typed a value out of option range.
            goto cpEnterKorUseDef;//It will take the user to the input section again and again until the user enters a valid input value in options range.
        }
    }
    else
    {
    println("\n\n   Select if you want to use default constant value or input your own constant value\n1.Use default constant\n2.User defined\n");
        goto cpEnterKorUseDef;
    }


    println("Do you want to convert Taka to other currency or want to keep it in Taka unit?\n\n1.Let the unit be Taka\n2.Convert to another currency");
cpConvertOrNot:
    scanf("%s",&convOrNot);
    if(isNumber(convOrNot)==1)
    {
        sp();
        if(validSelection("if you want to convert or not","Let the unit be Taka","Convert to another currency")==1)
        {

            if(lastInt==1)
            {
                selNotif("Not to convert");
            }
            else
            {
                selNotif("Convert");
cpConvertCurrency:
                println("Convert to : \n1.US dollar(USD)\n2.Euro(EUR)\n3.Japanese yen(JPY)\n4.Australian dollar (AUD)\n5.Canadian dollar (CAD)\n6.Saudi riyal (SAR)\n7.Indian ruppee (INR)\n");
                scanf("%s",&convertToIndex);
                if(isNumber(convertToIndex)==1)
                {
                    ////Continue code heres
                    sp();
                    switch(lastInt)
                    {
                    case 1:
                        setupCurrency("USD",TKtoUSD);
                        break;
                    case 2:
                        setupCurrency("EUR",TKtoEUR);
                        break;
                    case 3:
                        setupCurrency("JPY",TKtoJPY);
                        break;
                    case 4:
                        setupCurrency("AUD",TKtoAUD);
                        break;
                    case 5:
                        setupCurrency("CAD",TKtoCAD);
                        break;
                    case 6:
                        setupCurrency("SAR",TKtoSAR);
                        break;
                    case 7:
                        setupCurrency("INR",TKtoINR);
                        break;
                    default:
                        notFoundWarn("currency option");
                        goto cpConvertCurrency;
                    }

                }
                else
                {
                    goto cpConvertCurrency;
                }
            }
        }
        else
        {
            goto cpConvertOrNot;
        }

    }
    else
    {
    println("Do you want to convert Taka to other currency or want to keep it in Taka unit?\n\n1.Let the unit be Taka\n2.Convert to another currency");
        goto cpConvertOrNot;
    }

    jobSelection();//After confirming the user choices if the user wants to use default constant or not, convert the currency format or not, now the jobSelection function will run which will offer options to select jobs and category

    println("    Is there any bonus you want to add?\n1.Add bonus\n2.No bonus");//If you want to add bonus then the added amount will be summed with the salary at the end of the calculation
    char haveBonus[20],bonusStr[20];
    int haveBonusBool=0,bonus=0;
cpBonus:
    scanf("%s",&haveBonus);
    if(isNumber(haveBonus)==1)
    {
        sp();
        if(validSelection("if there is bonus or not","Add bonus","No bonus"))
        {
            if(lastInt==1)
            {
                haveBonusBool=1;
                selNotif("to add bonus");
cpAddBonus:
                printf("Enter bonus amount (%s) : \n",currency);
                scanf("%s",&bonusStr);
                if(isNumber(bonusStr)==1)
                {
                    sp();
                    bonus=lastInt;
                    printf("\nNote : \nBonus amount of %d %s is saved. Later it will be added to final salary after all calculations are done\n\n",bonus,currency);

                }
                else
                {
                    goto cpAddBonus;

                }
            }
            else
            {
                selNotif("Not to add bonus");
            }
        }
        else
        {
            goto cpBonus;
        }

    }
    else
    {
    println("    Is there any bonus you want to add?\n1.Add bonus\n2.No bonus");//If you want to add bonus then the added amount will be summed with the salary at the end of the calculation
        goto cpBonus;
    }

cpPayDelay:
    println("    Salary payment delay type :\n1.Daily\n2.Weekly\n3.Monthly\n4.Yearly");
    char payDelay[20];
    char pDelayType[10];
    scanf("%s",&payDelay);
    if(isNumber(payDelay)==1)
    {
        sp();
        switch(lastInt)
        {
        case 1:
            selNotif("daily payment");
            kUnited/=30;
            strcpy(pDelayType,"daily");
            break;
        case 2:
            selNotif("weekly payment");
            strcpy(pDelayType,"weekly");
            kUnited/=4;
            break;
        case 3:
            selNotif("monthly payment");
            strcpy(pDelayType,"monthly");
            //There is no calculation needed because the program is by default made to output salary as monthly payment means KUnited should be multiplied by 1 (KUnited*=) which is useless step of calculation.
            break;
        case 4:
            selNotif("yearly payment");
            strcpy(pDelayType,"yearly");
            kUnited*=12;
            break;
        default:
            notFoundWarn("salary payment delay type");
            goto cpPayDelay;

        }

    }
    else
    {
        goto cpPayDelay;
    }
    char vatPercent[20];
cpVatPer:
    printf("\n    Enter VAT amount in percent (%s). The amount will be reduced from final salary: \n\n",currency);
    scanf("%s",&vatPercent);
    if(isNumber(vatPercent)==1)
    {
        sp();
        if(!(lastInt>=0 && lastInt<=100))
        {
            //It will restrict the user from entering any value less than 0 and greater than 100 since percentage can't be larger than 100 and less than 0
            println("    ....Invalid input. Percent input should be in between 0 to 100....");
            goto cpVatPer;
        }
        double vatPer=(double) lastInt/100;//last input was the percentage of VAT. so by dividing the lastInt value by 100 will give us the multiplier which we can use to subtract the amount of VAT from the total salary
        double finalSalery=(kUnited*k4sal)-(kUnited*k4sal*vatPer)+bonus;//finalSalary is the amount after overall calculation. kUnited is the value of the constant of the salary amount, multiplying it with k4Sal will give us the result according to the job user have selected. The selected job salary will be multiplied with vat percent and the outcome will be subtracted from the job salary will give the amount after reducing VAT from the salary. And finally adding bonus amount to it since bonus amount should not be effected by the VAT. At last the result will be saved in finalSalary variable
        printf("\n\n||||      Salary of a %s : %0.0lf %s %s",jobDes, finalSalery,currency,pDelayType);
        if(haveBonusBool==1 || vatPer>0)
        {
            printf(" (");

        }
        if(haveBonusBool==1)
        {
            //If user have selected to include bonus then the amount of the bonus will be shown in output
            printf("%d %s bonus included",bonus,currency);
        }
        if(vatPer>0)
        {
            if(haveBonusBool==1)
            {
                printf(" and ");
            }
            //If the user want to skip VAT or not want to add vat then the user should type 0 in VAT input. Else if the user input any value in VAT input greater than 0 then the output will calculate the VAT amount and show it in the output
            printf("%0.0lf %s VAT was consumed",(double) kUnited*k4sal*vatPer,currency);

        }
        if(haveBonusBool==1 || vatPer>0)
        {
            println(")      |||");
        }

    }
    else
    {
        goto cpVatPer;
    }
    exitf();
}

void main()
{
    println("Brief :\nHOW TO USE : Enter the index no of the option to select an option you will see at the left of the option. At the beginning of the program you will be asked if you want to use default constant which is 100000 Taka or want to input by yourself. After fixing a constant value you can choose if you want to use the currency unit as taka or want to convert it to another foreign currency. Now select the Job you want to calculate salary of. In some jobs you will find some sections you must select one of them and after finalizing job and catagory you will be asked if you want to Add bonus with the salary or not. If you choose to add bonus then you will be asked to enter bonus amount that will be added to the salary later. Then you have to select the salary payment delay type if it's weekly,monthly etc. After that you have to input the VAT amount percentage that will be reduced from the final salary, if there is no VAT then just type 0 that will make no changes to the salary amount.\nFinally you will get the output of calculated salary of that specific job category. Remember if you type index number out of option range then you will be asked to enter the index again and again until you select one of the option which is available in the option list and if you enter any symbol or alphabet it will warn you and ask for input again. It's one of the special feature of the program that you can't get out of it without finishing the program. There are another way to get out of the program through secret code (Author can explain)\n\nWhy the constant value?\nThe program is dynamic. The salary will be relative to the constant value. Using large amount in constant value will make the salary amount large relative to constant value and vice versa\n\n");
    process();//The brief will not be shown if the user restarts the program using secret code because in case of restart only the process() function will run. But if the user resets the program using secret code then the program will run the main() function which includes the Brief
}













