int printf(char const *format, ...);
int add(int a,int d);      //declaration



int main()
{

//FUNCTION CALL
printf("function call: %d\n",add(1,2));
char* a = "asdfs";

//IF
int i = 3;
int j = 4;

if(!(i==j))
{
   printf("Equal\n");
}else
{
   printf("Not Equal\n");
}

//FOR
int k;
for(k=3;k<10;k++)
{
printf("%d",k);
}
printf("\n");


//While
int k = 3;
while(k<7)
{
k++;
printf("%d",k);
}


printf("\n");




return 0;
}

int add(int a,int d)        //{} Function Definition
{
	return a+d;
}
