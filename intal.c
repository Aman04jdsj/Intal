#include "intal.h"
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void karatsuba(char*, char*, char*);
char* power(char* str1,char* str2);
char* rem_leading_zeroes(char* );

void* intal_create(const char* str)
{
	char* p;int i,j=0,v=0;
	char* z;
	z=(char*)malloc(sizeof(char)*2);
	z[0]='0';
	z[1]='\0';
	if(!isdigit(str[0]))
		return (void*)z;
	for(i=0;i<strlen(str);i++)
	{
		if(isdigit(str[i])) // check if the input is a valid nonnegative integer
			v++;
		else 
			break;
	}
	while(str[j]=='0' && j<v)
		j++;
	int s;
	s=v-j;
	if(s==0)// if the intal is zero
		return (void*)z;
	p=malloc(sizeof(char)*(s+1));
	for(i=0;i<s;i++)
		p[i]=str[j++]; // initialise the pointer
	p[i]='\0'; 
	free(z);
	return p;
}

void intal_destroy(void* intal)
{
	if(intal!=NULL)
	{
		free(intal);
		return;
	}
}


char* intal2str(void* intal)
{
	char* str;
	if(intal==NULL) // invalid string
		return "NaN";
	str=(char*)intal;
	char* str2;
	str2=(char*)malloc(sizeof(char)*strlen(str)+1);
	strcpy(str2,str);
	return str2;
}


void* intal_increment(void* intal)
{
	if(intal==NULL) // to check for invalid intal
		return NULL;
	if(strcmp(intal2str(intal),"0")==0)
		return intal_create("1");
	int s;
	s=(int)strlen(intal);
	int i=s;
	char* str;
	str=(char*)intal;
	str=rem_leading_zeroes(str);
	int j,c=1,sum=0,count=0;
	while(c)
	{
		if(count==i) // if incremented intal exceeds length of given intal
		{
			char* str2=(char*)malloc((i+2)*sizeof(char));
			for(j=0;j<i;j++)
				str2[j+1]=str[j];
			str2[j+1]='\0';
			sum=(str2[1]-'0')+c;
			c=sum/10;
			str2[0]=(sum%10)+'0';
			intal=malloc(sizeof(str2));
			intal=str2;	
			return intal;
		}			
		sum=(str[--s]-'0')+c; // calculating sum bit
		c=sum/10; // calculating carry bit
		str[s]=(sum%10)+'0';
		count++;
		
	}
	return intal;	
}


void* intal_decrement(void* intal)
{
	if(intal==NULL) // to check for invalid intal
		return NULL;
	char* t;
	t=intal2str(intal);
	t=rem_leading_zeroes(t);
	if(t[0]=='0') // to check if given intal is zero
		return intal;
	int s;
	s=(int)strlen(intal);
	int i=s;
	char* str;
	str=(char*)intal;
	int j,b=1,dif=0,count=0;
	while(b)
	{
		if((str[s-1]-'0')<b) // to check if borrow is needed and calculate difference bitwise 
			dif=(str[--s]-'0')+10-b;
		else
		{
			dif=(str[--s]-'0')-b;
			b=0;
		}
		str[s]=dif+'0';
		count++;
		
	}	

	if(str[0]=='0' && strlen(str)!=1) // to remove leading zero
	{
		char* str2=(char*)realloc(str,(i-1)*sizeof(char));
		for(j=0;j<i;j++)
			str2[j]=str[j+1];
		str2[j]='\0';
		intal=malloc(sizeof(str2));
		intal=str2;
		return intal;
	}
	intal=malloc(sizeof(str));
	intal=intal_create(str);
	free(t);
	return intal;
}


void* intal_add(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL) // to check for invalid intals
		return NULL;
	int s,max,min,t,sum=0,c=0;
	char *str,*str2;
	str=intal2str(intal1);
	str=rem_leading_zeroes(str);
	str2=intal2str(intal2);
	str2=rem_leading_zeroes(str2);
	s=(int)strlen(str);
	t=(int)strlen(str2);
	/* to find max and min length of intals */
	max=(s>t)?s:t;
	min=(s>t)?t:s;
	
	
	char* str3;
	str3=(char*)malloc(sizeof(char)*(max+1));	
	str3[max]='\0';
	char* res;
	res=malloc(sizeof(str3));
	int i,j=max;
	if(strlen(str)>strlen(str2))
	{
		for(i=0;i<min;i++)
		{
			sum=(str[max-i-1]-'0')+(str2[min-i-1]-'0')+c; // bitwise addition from LSB end
			str3[--j]=(sum%10)+'0'; // sum bit
			c=sum/10; // carry bit
		}	
	}
	else
	{
		for(i=0;i<min;i++)
		{
			sum=(str[min-i-1]-'0')+(str2[max-i-1]-'0')+c; // bitwise addition from LSB end
			str3[--j]=(sum%10)+'0'; // sum bit
			c=sum/10; // carry bit
		}
	}
	/* to copy remaining bits after adding carry if present */
	if(max==s)
	{	
		while(j)
		{
			j--;
			sum=(str[j]-'0')+c;
			c=sum/10;
			sum=sum%10;
			str3[j]=sum+'0';
		}
	}
	else
	{
		while(j)
		{
			j--;
			sum=(str2[j]-'0')+c;
			c=sum/10;
			sum=sum%10;
			str3[j]=sum+'0';
		}
	}
	/* if sum exceeds the length of both the intals */
	if(c==1)
	{
		char* str4;
		str4=(char*)malloc(sizeof(char)*(int)(strlen(str3)+2));
		for(i=0;i<(int)strlen(str3);i++)
			str4[i+1]=str3[i];
		str4[i+1]='\0';
		str4[0]=c+'0';
		char* res2;
		res2=malloc(sizeof(str4));
		res2=(void*)str4;
		return res2;
	}
	res=(void*)str3;
	return res;
}

void* intal_diff(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL) // if intal is invalid 
		return NULL;
	int s,max,min,t,dif=0,b=0,k;
	s=(int)strlen(intal1);
	t=(int)strlen(intal2);
	char *str,*str2;
	if(intal_compare(intal1,intal2)<0) // if intal1<intal2
	{
		str=intal2str(intal2);
		str=rem_leading_zeroes(str);
		str2=intal2str(intal1);	
		str2=rem_leading_zeroes(str2);
	}
	else if(intal_compare(intal1,intal2)>0) // if intal1>intal2
	{
		str=intal2str(intal1);
		str=rem_leading_zeroes(str);
		str2=intal2str(intal2);
		str2=rem_leading_zeroes(str2);
	}
	else // if both the intals are equal
	{
		char* str3;
		str3=(char*)malloc(sizeof(char)*2);
		str3[0]='0';
		str3[1]='\0';
		char* res;
		res=malloc(sizeof(str3));
		res=(void*)str3;
		return res;
	}
	/* to find max and min length of the intals */
	max=(s>t)?s:t; 
	min=(s>t)?t:s;
	
	char* str3;
	str3=(char*)malloc(sizeof(char)*(max+1));	
	str3[max]='\0';
	char* res;
	res=malloc(sizeof(str3));
	
	int i,j=max-1;
	char* str5;
	str5=(char*)malloc(sizeof(char)*(max+1));
	str5[max]='\0';
	for(k=0;k<max;k++)
		str5[k]=str[k];
	for(i=0;i<min;i++)
	{
		j--;
		if((str5[max-i-1]-'0')<(str2[min-i-1]-'0')) // checking for borrow necessity
		{
			b=10;
			if((str5[j]-'0')>0) // to check if higher digit is capable of lending a borrow
				str5[j]=((str5[j]-'0')-1)+'0';
			else // borrow from first non-zero higher digit
			{
				int z;
				z=j;
				while((str5[z]-'0')==0 && z>=0)
				{
					str5[z]=((str5[z]-'0')+9)+'0';
					z--;
				}
				str5[z]=((str5[z]-'0')-1)+'0';
			}
		}
		else // borrow not needed
			b=0;
		dif=(str5[max-i-1]-'0')-(str2[min-i-1]-'0')+b; // bitwise subtraction from LSB end
		str3[max-i-1]=dif+'0'; // storing result into str3
	}

	while(j>=0) // copy remaining digits if present
	{
			str3[j]=str5[j];
			j--;
	}
	i=0;
	if(str3[0]=='0') // check and remove leading zeroes
	{
		while(str3[i]=='0' && i<strlen(str3)) // remove till the first non-zero entry occurs
		{
			i++;
			if(str3[i]!='0')
				break;
		}
	
		(i==strlen(str3))?i--:i; // to determine the sizeof result array
		char* str4;
		str4=(char*)malloc((strlen(str3)-i+1)*sizeof(char));
		int k;
		for(k=0;k<(int)strlen(str3)-i;k++)
			str4[k]=str3[k+i];
		str4[k]='\0';
		char* res2;
		res2=malloc(sizeof(str4));
		res2=(void*)str4;
		free(str5);
		return res2;
	}
	res=(void*)str3;
	free(str5);
	return res;
}

void* intal_multiply(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL) // to check for invalid intals
		return NULL;
	int i;
	char *str1,*str2;
    str1=(char*)intal1;
    str2=(char*)intal2;
    str1=rem_leading_zeroes(str1);
    str2=rem_leading_zeroes(str2);
	char* product;
    product=(char*)malloc(sizeof(char)*2);
    product[0]='0';
    product[1]='\0';
    if(str1[0]=='0' || str2[0]=='0') // to check if one of the intals is zero
   		return product;
	int max;
    max=(int)(strlen(str1)>strlen(str2)?strlen(str1):strlen(str2));
    product=(char*)malloc(sizeof(char)*((2*max)+1));
    product[(2*max)]='\0';
    for(i=0;i<2*max;i++)
		product[i]='0';
	karatsuba(str1,str2,product);
	return (void*)(rem_leading_zeroes(product));
}

void karatsuba(char* str1, char* str2, char* product)
{
	int i,j=0,p;
	char *z;
	z=(char*)malloc(sizeof(char)*2);
	z[1]='\0';
	z[0]='0';
	
	/* if any of the strings are zero*/
	if((intal_compare(intal_create(rem_leading_zeroes(str1)),z)==0)||(intal_compare(intal_create(rem_leading_zeroes(str2)),z)==0)) 
	{
		for(i=0;i<strlen(product);i++)
			product[i]='0';
		free(z);
		return;
	}
	
	int max;
    max=(int)(strlen(str1)>strlen(str2)?strlen(str1):strlen(str2));
    char *str3,*str4;
    str3=(char*)malloc(sizeof(char)*(max+1));
    str3[max]='\0';
    str4=(char*)malloc(sizeof(char)*(max+1));
    str4[max]='\0';
	if(strlen(str1)!=strlen(str2))// to make the length of intals equal
    {
        if(strlen(str1)>strlen(str2))
        {
            for(i=(int)(strlen(str2)-1);i>=0;i--)
                str4[max-(j++)-1]=str2[i];
            while(j<max)
                str4[max-(j++)-1]='0';
            str3=rem_leading_zeroes(str1);
        }
        else
        {
            for(i=(int)(strlen(str1)-1);i>=0;i--)
                str3[max-(j++)-1]=str1[i];
            while(j<max)
                str3[max-(j++)-1]='0';
            str4=rem_leading_zeroes(str2);
        }
    }
    else
    {
		for(i=0;i<max;i++)
		{
			str3[i]=str1[i];
			str4[i]=str2[i];
		}
    }
    /* str3 and str4 now contain the multiplicand and multipliers of equal length i.e padded with zeroes if needed*/
    
    //Base case i.e. single digit multiplication

    if(strlen(str3)==1 && strlen(str4)==1)
    {
        p=(str3[0]-'0')*(str4[0]-'0');
        int s,c;
        p+=(product[1]-'0');
        s=p%10;
        c=p/10;
        product[1]=(s+'0');
        product[0]=((product[0]-'0')+c)+'0';
        free(z);
		return;
    }
    
    int fh,sh;
    fh=max/2; // size of first half of the intals
    sh=max-fh; // size of second half of the intals
    
    char *xl,*xr,*yl,*yr;

    /*first half and second half of first string */
    xl=(char*)malloc(sizeof(char)*(fh+1));
    xl[fh]='\0';

    for(i=0;i<fh;i++)
        xl[i]=str3[i];
	xr=(char*)malloc(sizeof(char)*(sh+1));
    xl[sh]='\0';
    for(i=0;i<sh;i++)
        xr[i]=str3[fh+i];

    /*first half and second half of second string */
    yl=(char*)malloc(sizeof(char)*(fh+1));
    yl[fh]='\0';
    for(i=0;i<fh;i++)
        yl[i]=str4[i];
    yr=(char*)malloc(sizeof(char)*(sh+1));
    yr[sh]='\0';
    for(i=0;i<sh;i++)
        yr[i]=str4[fh+i];

	karatsuba(xl,yl,product);// Calculating partial product p1 and inserting into product array

	karatsuba(xr,yr,product+((2*max)-1-((2*sh)-1)));// Calculating partial product p1 and inserting into product array

	char *xlr,*ylr;
    xlr=intal_add(xl,xr);
	ylr=intal_add(yl,yr);
    int m;
    m=(int)(strlen(xlr)>strlen(ylr)?strlen(xlr):strlen(ylr));
    char* temp;
    temp=(char*)malloc(sizeof(char)*(2*m+1));
    temp[2*m]='\0';

    for(i=0;i<(2*m);i++)
        temp[i]='0';
	karatsuba(xlr,ylr,temp);//Calculating partial product p3
	int x;
    char *cpy=(char*)malloc(sizeof(char)*(2*fh+1));
    cpy[2*fh]='\0';
	for(x=0;x<(2*fh);x++)
    {
    	cpy[x]=product[x];//P1
    }
    char *cpy2=(char*)malloc(sizeof(char)*(2*max-(2*fh)+1));
    cpy2[2*max-(2*fh)]='\0';
    for(x=(2*fh);x<2*max;x++)
   	{
   		cpy2[x-(2*fh)]=product[x];//P2
   	}
	temp=intal2str(intal_diff(intal_create(rem_leading_zeroes(temp)),intal_create(rem_leading_zeroes(cpy))));// P3-P1
	temp=intal2str(intal_diff(intal_create(rem_leading_zeroes(temp)),intal_create(rem_leading_zeroes(cpy2))));//P3-P1-P2

	int s2,c2=0;
	for(i=0;i<strlen(temp);i++)// adding the (P3-P1-P2) part to product array from the required index 
	{
		s2=(temp[strlen(temp)-1-i]-'0')+(product[2*max-i-sh-1]-'0')+c2;
		c2=s2/10;
		s2=s2%10;
		product[2*max-i-sh-1]=s2+'0';
	}
	while(c2!=0)// if carry remains
	{
		s2=(product[2*max-i-sh-1]-'0')+c2;
		c2=s2/10;
		s2=s2%10;
		product[2*max-i-sh-1]=s2+'0';
		i++;
	}
	free(z);
	free(xl);
	free(xr);
	free(yl);
	free(yr);
	free(xlr);
	free(ylr);
	free(cpy);
	free(cpy2);
	return;
}


void* intal_pow(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL)
		return NULL;
	char *str1,*str2;
	str1=rem_leading_zeroes(intal1);
	str2=rem_leading_zeroes(intal2);
	char* str3,*str4;
	str3=(char*)malloc(sizeof(char)*(strlen(str1)+1));
	str3[strlen(str1)]='\0';
	int i;
	for(i=0;i<strlen(str1);i++)
		str3[i]=str1[i];
	str4=(char*)malloc(sizeof(char)*(strlen(str2)+1));
	str4[strlen(str2)]='\0';
	for(i=0;i<strlen(str2);i++)
		str4[i]=str2[i];
	char* res2;
	res2=power(str3,str4);
	free(str3);
	free(str4);
	return res2;
}

char* power(char* str1,char* str2)
{
	char *z,*o;
	int i;
	z=(char*)malloc(sizeof(char)*2);
	o=(char*)malloc(sizeof(char)*2);
	z[1]='\0';
	z[0]='0';
	o[1]='\0';
	o[0]='1';
	
	/*base conditions i.e. str2=0,1 and str1=0*/
	if(intal_compare(str1,z)==0)
		return z;
	if(intal_compare(str2,z)==0)
		return o;
	if(intal_compare(str2,o)==0)
	{
		char* res;int i;
		res=(char*)malloc(sizeof(char)*(strlen(str1)+1));
		res[strlen(str1)]='\0';
		for(i=0;i<strlen(str1);i++)
			res[i]=str1[i];
		free(z);
		free(o);
		return res;
	}
	
	
	/* to find n/2 */
	char* f;
	f=(char*)malloc(sizeof(char)*2);
	f[0]='5';
	f[1]='\0';
	char* fm;
	fm=intal2str(intal_multiply(intal_create(rem_leading_zeroes(str2)),intal_create(rem_leading_zeroes(f))));	
	char* b2;
	b2=(char*)malloc(sizeof(char)*strlen(fm));
	b2[strlen(fm)-1]='\0';
	for(i=0;i<strlen(fm)-1;i++)
		b2[i]=fm[i];
	b2=rem_leading_zeroes(b2);
		
	char* an2;
	an2=power(str1,b2); // a^n/2
	char* an22;
	an22=intal_multiply(intal_create(rem_leading_zeroes(an2)),intal_create(rem_leading_zeroes(an2)));// (a^(n/2))^2
	int r;
	r=(fm[strlen(fm)-1]-'0');
	if(r%2!=0)
	{
		char* an22a;
		an22a=intal2str(intal_multiply(intal_create(rem_leading_zeroes(an22)),intal_create(rem_leading_zeroes(str1))));
		free(fm);
		free(f);
		free(b2);
		free(an2);
		free(an22);
		return an22a;
	}
	free(f);
	free(fm);
	free(b2);
	free(an2);
	return an22;
}


int intal_compare(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL) // invalid strings
		return -2;
	char *str,*str2;
	str=(char*)intal1;
	str=rem_leading_zeroes(str);
	str2=(char*)intal2;
	str2=rem_leading_zeroes(str2);
	if(strlen(str)>strlen(str2)) // intal1 is greater
		return 1;
	else if(strlen(str2)>strlen(str)) // intal2 is greater
		return -1;
	else
	{
		int i;
		for(i=0;i<strlen(str);i++)
		{
			if((str[i]-'0')>(str2[i]-'0')) // intal1 is greater
				return 1;
			else if((str[i]-'0')<(str2[i]-'0')) // intal2 is greater
				return -1;
		}
	}
	return 0;
}

char* rem_leading_zeroes(char* str)
{
	int j=0,i;
	if(str[0]=='0' && strlen(str)!=1)
	{
		while(str[j]=='0') // to remove leading zeroes
			j++;
		char* str2;
		str2=(char*)malloc(sizeof(char)*(strlen(str)-j+1));
		str2[strlen(str)-j]='\0';
		for(i=0;i<(strlen(str)-j);i++)
			str2[i]=str[i+j];
		return str2;
	}
	else if(str[0]=='0' && strlen(str)==1) // if the string is only a single zero
	{
		char* res;
		res=(char*)malloc(sizeof(char)*2);
		res[0]='0';
		res[1]='\0';
		return res;
	}
	else 
		return str;
}

void* intal_divide(void* intal1, void* intal2)
{
	
	if(intal1==NULL || intal2==NULL) // invalid intals
		return NULL;
	if(strcmp(intal2str(intal2),"0")==0) // divide by zero
		return NULL;
		
	/* if intal1 is zero or less than intal2 */
	if(strcmp(rem_leading_zeroes(intal2str(intal1)),"0")==0 || intal_compare(intal1,intal2)==-1) 
		return intal_create("0");
		
	if(intal_compare(intal1,intal2)==0) // if both the intals are same
		return intal_create("1");
	char *str1,*str2;
	str1=intal2str(intal1);
	str2=intal2str(intal2);
	int i,j;
	char *str3,*str4;
	str3=(char*)malloc(sizeof(char)*(strlen(str1)+1));
	str3[strlen(str1)]='\0';
	str4=(char*)malloc(sizeof(char)*(strlen(str2)+1));
	str4[strlen(str2)]='\0';
	for(i=0;i<strlen(str1);i++)
		str3[i]=str1[i];
	for(j=0;j<strlen(str2);j++)
		str4[j]=str2[j];
	str3=rem_leading_zeroes(str3);
	str4=rem_leading_zeroes(str4);
	
	/* str3 and str4 contain the numbers to be divided */
	
	void* q; // quotient
	q=intal_create("0");
	while(intal_compare(intal_create(str3),intal_create(str4))>=0)
	{
		str3=intal_diff(intal_create(str3),intal_create(str4));
		q=intal_add(q,intal_create("1"));
	}
	free(str3);
	free(str4);
	return q;
}


