#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
typedef struct{
    int time;
    int type;
    int duration;
}OsuObj;
typedef struct TimingS{
    int time;
    int beatL;
    int uninherited;
    struct TimingS *next;
}Timing;
Timing *timings;
int getSliderMult(FILE *input){
    char a[1000];
    do{
        fgets(a,strlen("SliderMultiplier:")+1,input);
    }while(strcmp(a,"SliderMultiplier:")!=0);
    //printf("%s\n",a);
    return (fgetc(input)-'0');
}
void getTimings(FILE *input){
    timings = malloc(sizeof(Timing));
    Timing *curr=timings;
    char a[1000];
    do{
        fgets(a,strlen("[TimingPoints]")+1,input);
    }while(strcmp(a,"[TimingPoints]")!=0);
    printf("Header - OK\n");
    int tempInt=0;
    int i=0;
    int sign=1;
    fgets(a,10,input);
    fgets(a,1000,input);
    while(a[0]!='\n'&&a[0]!='\0'&&a[0]!=13){
        tempInt=0;
        i=0;
        sign=1;
        for(;a[i]!=','&&a[i]!='\n';i++){
            if(a[i]=='-')
                sign=-1;
            else{
                tempInt*=10;
                tempInt+=a[i]-'0';
            }
        }
        curr->time=tempInt*sign;
        sign=1;
        tempInt=0;
        i++;
        //printf("Catch: %c\n",a[i]);
        for(;a[i]!=','&&a[i]!='\n'&&a[i]!='.';i++){
            if(a[i]=='-')
                sign=-1;
            else{
                tempInt*=10;
                tempInt+=a[i]-'0';
            }
        }
        curr->beatL=tempInt*sign;
        for(int commas=1;commas<6;i++){
            if(a[i]==',')
                commas++;
        }
        curr->uninherited=a[i]-'0';
        //printf("%i,%i,%i: %s\n",curr->time,curr->beatL,curr->uninherited,a);
        //scanf("%i",&tempInt);
        fgets(a,1000,input);
        if(a[0]!='\n'&&a[0]!='\0'&&a[0]!=13){
            curr->next=malloc(sizeof(Timing));
            curr=curr->next;
            curr->next=NULL;
        }
    }
}
void findstart(FILE *input){
    char a[30]; 
    do{
        fgets(a,strlen("[HitObjects]")+1,input);
    }while(strcmp(a,"[HitObjects]")!=0);
}
void parse(FILE *input, FILE *output){
    int sliderMult=getSliderMult(input);
    printf("Sliders - OK\n");
    getTimings(input);
    printf("Timings - OK\n");
    findstart(input);
    printf("Start - Found\n");
    char a[1000];
    int tempInt=0;
    int commas=0;
    int lastBeatL=timings->beatL;
    OsuObj obj;
    Timing *curr=timings;
    while(!feof(input)){
        fgets(a,1000,input);
        fgets(a,1000,input);
        commas=0;
        for(int i=0;a[i]!='\0'&&a[i]!='\n'&&commas<8;i++){
            if(a[i]==','){
                commas++;
            }
            else if(commas==2){
                tempInt=0;
                for(;a[i]!=','&&a[i]!='\n';i++){
                    tempInt*=10;
                    tempInt+=a[i]-'0';
                }
                obj.time=tempInt;
                commas++;
                if(curr->next!=NULL){
                    while(curr->next->time<=obj.time){
                        curr=curr->next;
                        if(curr->next==NULL){
                            break;
                        }
                    }
                    if(curr->uninherited){
                        lastBeatL=curr->beatL;
                    }
                }
            }
            else if(commas==3){
                obj.type=a[i]-'0';
                if (obj.type&1==1){
                    commas=8;
                }
            }
            else if(commas==5&&(obj.type>>3)&1==1){
                tempInt=0;
                for(;a[i]!=','&&a[i]!='\n';i++){
                    tempInt*=10;
                    tempInt+=a[i]-'0';
                }
                obj.duration=tempInt-obj.time;
                commas=8;
            }
            else if(commas==7&&(obj.type>>1)&1==1){
                tempInt=0;
                for(;a[i]!=','&&a[i]!='\n'&&a[i]!='.';i++){
                    tempInt*=10;
                    tempInt+=a[i]-'0';
                }
                //printf("Slider Length: %i\n",tempInt);
                if(!curr->uninherited)
                    obj.duration=tempInt*lastBeatL*(double)(curr->beatL/-100)/(sliderMult*100);
                else
                    obj.duration=tempInt*lastBeatL/(sliderMult*100);
                commas=8;
            }
        }
        printf("%i,%i,%i: %s\n",obj.time,obj.type,obj.duration,a);
        //scanf("%i",&tempInt);
        fwrite(&obj,sizeof(OsuObj),1,output);
    }
}
#ifdef HASMAIN
void main(int argc, char *argv[]){

    if(argc<2){
        printf("usage: ./osuconverter <filename>\n");
        return;
    } 
    FILE *input,*output;
    input=fopen(argv[1],"rb");
    printf("opened: %s\n",argv[1]);
    if(argc>2){
        output=fopen(argv[2],"wb");
        //printf("write: %s\n",argv[2]);
    }
    else{
        output=fopen("output.sb","wb");
    }
    parse(input,output);
    printf("Parse - COMPLETE\n");
    fclose(input);
    fclose(output);
    return;
}
#endif