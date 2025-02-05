#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
float tanh_activation(float );
void File(const char*,char[][20], int[][100]);
void Words(char[],char[][20], int[][100]);
void Dict(char[][20], char[], int[][100]);
void stochastic_gradient_descent(int , float [], int[][100], int[][100]);
void gradient_descent(int , float [], int[][100], int[][100]);
int static kelimesayisi=0;
int static cumlesayisi=0;
int main(){
srand(time(NULL));
int i, j, hotA[2000][100]={0}, hotB[2000][100]={0};
char dict[2000][20];
float *w,*p;
 float sonuc=0;
File("sport.txt", dict, hotA);
cumlesayisi=0;
File("astrology.txt", dict, hotB);
w = (float *)calloc(kelimesayisi, sizeof(float));
 for(i=0;i<kelimesayisi;i++){
 w[i]=0.6; //w icin baslangic degeri atiyorum.

}
 gradient_descent( kelimesayisi, w, hotA, hotB);
 //stochastic_gradient_descent(kelimesayisi, w, hotA, hotB);
int c=0;
 printf("-----\n");
 for(j=80;j<100;j++){ //test ediyorum.
 sonuc=0;
for(i=0;i<kelimesayisi;i++){sonuc+=w[i]*hotA[i][j];
 }
 //printf("%f\n",sonuc);
 float cikis=tanh_activation(sonuc);
 printf("%f\n",cikis);
 if(cikis>0.8){
 c++;
}
 }
 printf("a sinifi icin verimlilik %d\n",5*c) ;
c=0;
for(j=80;j<100;j++){
 sonuc=0;
for(i=0;i<kelimesayisi;i++){sonuc+=w[i]*hotB[i][j];
 }
 //printf("%f\n",sonuc);
 float cikis=tanh_activation(sonuc);
 printf("%f\n",cikis);
 if(cikis<-0.8){
 c++;
}
 }
 printf("b sinifi icin verimlilik %d",5*c) ;
return 0;
}
float tanh_activation(float x) {
 return tanhf(x);
}
void upperToLower(char kelime[]){
int i;
for(i=0;kelime[i];i++){
if(kelime[i]>='A' && kelime[i]<='Z'){
kelime[i] = kelime[i]+('a'- 'A');
}
}
}
void File(const char *fileName, char dict[][20], int hot[][100]){
FILE* fptr;
char row[200];
fptr = fopen(fileName, "r");
 if (fptr == NULL) {
 printf("file can't be opened \n");
 }
 else{
 while(fgets(row, 200, fptr)){ //cumleden satir satir okuma yapilir.
 Words(row, dict, hot);//satirdaki kelimeleri tek tek parcalar.
 cumlesayisi++;}
}
}
void Dict(char dict[][20], char word[], int hot[][100]){
int i=0, j=0;
while(i<kelimesayisi){
if(strcmp(word,dict[i]) == 0){ //kelimenin sozlukteki varligi kontrrol edilir.
if(hot[i][cumlesayisi]==0)
hot[i][cumlesayisi]=1;
return;
}
else{
i++;
}
}
strcpy(dict[i], word);kelimesayisi++;
hot[i][cumlesayisi]=1;
}
void Words(char row[], char dict[][20], int hot[][100]){
int i=0, j=0, k;
char word[20];
while(row[i] != '\0'){
if(row[i] != ' '){
word[j] = row[i];
j++;
i++;
}
else{
word[j] = '\0';
upperToLower(word);
Dict(dict, word, hot);
j=0;
i++;
}
}
}
void stochastic_gradient_descent(int wordcount, float w[2000], int hot1[2000][100], int
hot2[2000][100]){
float *xhot;
xhot=(float *)calloc(wordcount,sizeof(float));
float eps=0.4;
float sonuc=0,yh,d,result=5,yj,carp,b=0,a=0,hata=3;
int i,j,l=0,k,flag,c,random,count;
while(l<20){
result=0;
count++;
 int randomValue = rand() % 2; //hangi metinin hot vektorunu kullanacagini belirler.
 if (randomValue == 0) {
flag=1;
random=rand() %81; //hangi hot vektoru kullanacagini belirler.
 c=random;
 //printf("%d\n",c);
for(i=0;i<wordcount;i++){
 a+=hot1[i][c]*w[i];
}
yj=(1-tanh(a)); //bu islemler loss fonksiyonun turevi icin yapilir.
yh=(1-tanh(a)*tanh(a));
sonuc=yh*yj*2;
for(i=0;i<wordcount;i++){
 xhot[i]=hot1[i][c]*sonuc;
}
 }
else {
flag=0;
random=rand() %81; //hangi hot vektoru kullanacagini belirler.c=random;
for(i=0;i<wordcount;i++){
 a+=hot2[i][c]*w[i];
}
yj=(-1-tanh(a)); //bu islemler loss fonksiyonun turevi icin yapilir.
yh=(-1-tanh(a)*tanh(a));
sonuc=yh*yj*2;
for(i=0;i<wordcount;i++){
 xhot[i]=hot2[i][c]*sonuc;
}
 }
 for(i=0;i<wordcount;i++){
 w[i]=w[i]-xhot[i]*eps; //w guncellenir
}
 if(flag==1){
b=0;
for(j=0;j<wordcount;j++){
b+=w[j]*hot1[j][c];
}
d=1-tanh_activation(b);//hata hesaplanir.
result=d*d;
 }
if(flag==0){
b=0;
for(j=0;j<wordcount;j++){
b+=w[j]*hot2[j][c];
}
d=-1-tanh_activation(b);//hata hesaplanir
result=d*d;
 }
printf("%f\n",result);
l++;
 }}
void gradient_descent(int wordcount, float w[2000], int hot1[2000][100], int hot2[2000][100]){
float *xhot;
xhot=(float *)calloc(wordcount,sizeof(float));
float eps=0.04;
float sonuc=0,yh,d,result=5,yj,carp,b=0,a=0,hata=3;
int i,j,k,count;
while(result>1){
result=0;
count++;
 for(j=0;j<80;j++){ //tum egitim verileri kullanilir.
a=0;
for(i=0;i<wordcount;i++){
 a+=hot1[i][j]*w[i];
}
yj=(1-tanh(a));
yh=(1-tanh(a)*tanh(a));sonuc=yh*yj*2;
for(i=0;i<wordcount;i++){
 xhot[i]=hot1[i][j]*sonuc;
}
for(i=0;i<wordcount;i++){
 w[i]=w[i]-xhot[i]*eps;
}
 }
 for(j=0;j<80;j++){//tum egitim verileri kullanilir.
a=0;
for(i=0;i<wordcount;i++){
 a+=hot2[i][j]*w[i];
}
yj=(-1-tanh(a));
yh=(-1-tanh(a)*tanh(a));
sonuc=yh*yj*2;
for(i=0;i<wordcount;i++){
 xhot[i]=hot2[i][j]*sonuc;
}
for(i=0;i<wordcount;i++){
 w[i]=w[i]-xhot[i]*eps;
}
 }
 result/=160; //toplam hata veri sayisina bolunur.
//printf("%f\n",result);
 }
