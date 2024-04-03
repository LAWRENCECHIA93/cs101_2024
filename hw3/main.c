#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define lotmax 69
#define lotmin 1
#define lotNoPerSet 7
#define maxset 5


typedef struct 
{
    int receipt_id;
    int receipt_price;
    char receitp_time[32];
    int lotto_set[maxset][lotNoPerSet];
}  lotto_record_t;

lotto_record_t lotto;

/*if user input not between 1 to 5, return 0
else return user input number*/
int howmanyset()
{
    char a;
    int set;
    
    while ((a = getchar()) != '\n' && a != EOF)
    {
        if('1'<=a && a<='5')
        {
            set = a - '0';
            return set;
        }
        else if ('0' == a)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

/*input lotto array, if any number is the same, return 1
else return 0*/
int anySame(int *allNo)
{
    int x,y;
    for(x=0;x<lotNoPerSet;x++)
        for(y=x+1;y<lotNoPerSet;y++)
            if (allNo[x] == allNo[y])
                return 1;
    return 0;
}


void removeChar(char* s, char c)
{
 
    int j, n = strlen(s);
    for (int i = j = 0; i < n; i++)
        if (s[i] != c)
            s[j++] = s[i];
 
    s[j] = '\0';
}

bool file_exists(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    bool is_exist = false;
    if (fp != NULL)
    {
        is_exist = true;
        fclose(fp); // close the file
    }
    return is_exist;
}

int main()
{
    int set,i,j, k,x, ret, lineNo=0, rec_id=0;
    int bingoNo[3]={0};
    time_t t; 
    char filename[32],tmpStr[32],lottoDate[32], *line = NULL;
    FILE *lottofile,*record;
    size_t len = 0;
    ssize_t read;
    
    time(&t);
    strftime(lotto.receitp_time, sizeof(lotto.receitp_time), "%a %b %d %T %Y", localtime(&t));
    if (file_exists("record.bin") == true)
    {
        printf("got record.bin\n");
        record = fopen("record.bin" , "rb");
        memset((void *)&lotto,0,sizeof(lotto));
        i=0;
        while (fgets((char *)&lotto, sizeof(lotto), record) != 0)
        { 
        // Process the read data (e.g., print or manipulate) 
            i++;
            //printf("lotto sn: %d\n",lotto.receipt_id); 
            //printf("lotto price: %d\n",lotto.receipt_price); 
            fseek(record, sizeof(lotto)*i, SEEK_SET);            
            if (lotto.receipt_id!=0)
                rec_id = lotto.receipt_id;
        } 
        //fseek(record, 0, SEEK_SET); // 蝘餃瑼
        fclose(record);
    }
    rec_id++;

    printf("甇∟???瑕?璅蔗璈\n隢??刻?鞈潸眺撟曄?(1-5)璅蔗(0:??): ");
    while (1)
    {
        set = howmanyset();
        if (set != -1)
            break;
        printf("\r 隢??啗撓??1-5): ");
    }
    if (set != 0)
    {
        lotto.receipt_id = rec_id;
        lotto.receipt_price = set * 100;
        sprintf(filename, "lotto[%05d].txt",lotto.receipt_id);
        lottofile = fopen(filename, "w");
        printf(" ============= lotto649 =============\n");
        fprintf(lottofile, " ============= lotto649 =============\n");
        printf(" ===========+ No. %05d +============\n",lotto.receipt_id);
        fprintf(lottofile, " ============+ No. %d +============\n",lotto.receipt_id);
        printf(" ====  %s  ====\n", lotto.receitp_time);
        fprintf(lottofile, " ====  %s  ====\n", lotto.receitp_time);
        srand(time(NULL));
        for (i=0;i< maxset;i++)
        {
            printf("[%d] ",i+1);
            fprintf(lottofile, "[%d] ",i+1);
            //reset lotto array to save new number
            memset(lotto.lotto_set[i],0,lotNoPerSet);
    
            //rand lotto number
            for (j=0;j< lotNoPerSet;j++)
                lotto.lotto_set[i][j] = rand()%lotmax+1;
            while(1)
            {
            // if any same number, re-generate number
                if (anySame(lotto.lotto_set[i]))
                    for (j=0;j< lotNoPerSet;j++)
                        lotto.lotto_set[i][j] = rand()%lotmax+1;
                else //no same number, break
                    break;
            }
    
            //print 7 lotto number
            for(int k=0;k<lotNoPerSet;k++)
                if (i<set)
                {
                    printf("%02d ",lotto.lotto_set[i][k]);
                    fprintf(lottofile, "%02d ",lotto.lotto_set[i][k]);
                }
                else //over user request set, just print --
                {
                    printf("-- ");
                    fprintf(lottofile,"-- ");
                }
    
            printf("\n");
            fprintf(lottofile,"\n");
        } //eof for (i=0;i< maxset;i++)
        fprintf(lottofile,"========csie@CGU========");
        fclose(lottofile);
        printf("撌脩?典??刻頃鞎瑞? %d蝯????撓?箄 %s",set,filename);
        record = fopen("record.bin" , "ab");
        
        // write struct to file
        fseek(record, 0, SEEK_SET);
        fwrite(&lotto, sizeof(lotto), 1, record);
        // close file
        fclose(record);
    }
    else
    {
        printf("隢撓?乩??葉??蝣? ");
        scanf("%d %d %d", &bingoNo[0], &bingoNo[1],&bingoNo[2]);
        printf("頛詨銝剔??Ⅳ?綽? %02d %02d %02d\n", bingoNo[0],bingoNo[1],bingoNo[2]);

        if (file_exists("record.bin") == true)
        {
            record = fopen("record.bin" , "rb");
            memset((void *)&lotto,0,sizeof(lotto));
            i=0;
            ret = 0;
            x = 0; // 撌脖葉??嚗?
            while (fgets((char *)&lotto, sizeof(lotto), record) != 0)
            { 
                for (int a=0;a<maxset;a++)
                    for (int b=0;b<lotNoPerSet;b++)
                    {
                        for (j=0;j<3;j++)
                            if (lotto.lotto_set[a][b] == bingoNo[j])
                            {
                                //printf("set:%d, lotto.lotto_set[%d][%d] = %d\n",i+1,a,b,lotto.lotto_set[a][b]);
                                if (ret == 0)
                                {
                                    printf("\n隞乩??箔葉?蔗??\n");
                                    ret = 1;
                                }
                               // printf (" 敶拙摨?嚗?05d, 蝚?%d 蝯n ?桀??嚗?s\n ?Ⅳ嚗?,lotto.receipt_id, a+1,lotto.receitp_time);
                                for (k=0;k<lotNoPerSet;k++)
                                    printf("%02d ",lotto.lotto_set[a][k]);
                                printf("\n\n");
                                x = 1;
                                break;
                            }
                        if (x == 1)
                        {
                            x = 0;
                            break;
                        }
                    }
                i++;
                fseek(record, sizeof(lotto)*i, SEEK_SET);            
            } 
            fclose(record);
        }
        else
        {
            printf("???眺璅\n");
            return 0;
        }

        fclose(record);




        
       

    }
    return 0;
}
