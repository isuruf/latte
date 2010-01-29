#include "PolyRep.h"
#include "newIntegration.h"
#include <NTL/vec_ZZ.h>
#include <NTL/ZZ.h>
#include <NTL/mat_ZZ.h>
#include <iostream>

using namespace std;

NTL_CLIENT


void delSpace(string &line)
{
	for (int i=0;i<line.length();i++)
	{
		while ((i<line.length())&&(line.at(i)==32)) {line.erase(i,1);};
	};
};

void convertToSimplex(simplexZZ &mySimplex, string line)
{
	int index,i,t,j,c;
	string temp,subtemp;
	t=2;mySimplex.d=1;
	t=line.find("[",t)+1;t=line.find("[",t)+1;
	temp=line.substr(t,line.find("]",t)-t);
	for (i=0;i<temp.length();i++) mySimplex.d+=(temp.at(i)==',');
	c=0;
	for (i=0;i<line.length();i++) c+=(line.at(i)==']');
	if (c-2!=mySimplex.d) {cout<<"The d-simplex should have d+1 vertices. Please check."<<endl; exit(1);};
 	(mySimplex.s).SetLength(mySimplex.d+1);
	cout<<line<<endl;
	index=1;
	for (i=0;i<=mySimplex.d;i++)
	{
		temp=line.substr(index,line.find("]",index)-index+1);
		c=0;
		for (j=0;j<temp.length();j++) c+=(temp.at(j)==',');
		if (c!=mySimplex.d-1) {cout<<"Each vertex should have d coordinates. Please check."<<endl; exit(1);};
		(mySimplex.s[i]).SetLength(mySimplex.d);
		t=1;
		for (j=0;j<mySimplex.d-1;j++)
		{
			subtemp=temp.substr(t,temp.find(",",t)-t);
			t=temp.find(",",t)+1;
			mySimplex.s[i][j]=to_ZZ(subtemp.c_str());
		};
		subtemp=temp.substr(t,temp.find(",",t)-t+1);
		t=temp.find(",",t);
		mySimplex.s[i][mySimplex.d-1]=to_ZZ(subtemp.c_str());
		index=line.find("]",index)+2;
	};
	mat_ZZ matt;	
	matt.SetDims(mySimplex.d,mySimplex.d);
	for (i=1;i<=mySimplex.d;i++) matt[i-1]=mySimplex.s[i]-mySimplex.s[0];
	mySimplex.v=determinant(matt);if (mySimplex.v<0) mySimplex.v=-mySimplex.v;
};

void update(ZZ &a, ZZ &b, vec_ZZ l, simplexZZ mySimplex,ZZ m, ZZ coe, ZZ de)
{
	ZZ sum,lcm,total,g,tem;
	int i,j;
	vec_ZZ inner_Pro,sum_Nu,sum_De;
	inner_Pro.SetLength(mySimplex.d+1);
	sum_Nu.SetLength(mySimplex.d+1);
	sum_De.SetLength(mySimplex.d+1);
	total=0;
	lcm=1;
	for (i=0;i<=mySimplex.d;i++)
	{
		sum=0; for (j=0;j<mySimplex.d;j++) {sum=sum+l[j]*mySimplex.s[i][j];};
		inner_Pro[i]=sum;
	};//stores inner product for use
	for (i=0;i<=mySimplex.d;i++)
	{
		sum_Nu[i]=1;for (j=0;j<m+mySimplex.d;j++) sum_Nu[i]=sum_Nu[i]*inner_Pro[i];
		sum_De[i]=1;for (j=0;j<=mySimplex.d;j++) if (i!=j) sum_De[i]=sum_De[i]*(inner_Pro[i]-inner_Pro[j]);
		if (sum_De[i]==0) {cout<<"Warning!"<<l<<" is not regular! Aborted."<<endl; /*exit(1);*/ b = to_ZZ(0); return;}; //irregular
		lcm=lcm*sum_De[i]/(GCD(lcm,sum_De[i]));
	};
	for (i=0;i<=mySimplex.d;i++)
	{
		total+=sum_Nu[i]*(lcm/sum_De[i]);
	};
	lcm=lcm*de;
	total=total*mySimplex.v*coe;
	if (a==0) {a=total;b=lcm;}
	else if ((lcm!=0)&&(b!=0)) {tem=b*lcm/GCD(b,lcm);a=a*tem/b+total*tem/lcm;b=tem;};	
	g=GCD(a,b);
	if (g!=0) 
	{
	a=a/g;
	b=b/g;};
}

void integrateList(ZZ &a, ZZ &b, string line, simplexZZ mySimplex)
{
	ZZ de,counter,m,tem,coe;
	int c,t,tt,i,j,index,k;
	vec_ZZ l;
	string temp,subtemp;
	l.SetLength(mySimplex.d);
	index=2;
	a=0;
	b=0;
	while (index<line.length())
	{
		t=line.find("]]]",index);
		temp=line.substr(index,t-index);
		subtemp=temp.substr(0,temp.find(","));
		t=temp.find("[",0)+1;
		coe=to_ZZ(subtemp.c_str());
		subtemp=temp.substr(t,temp.find(",",t)-t);
		m=to_ZZ(subtemp.c_str());
		de=1;
		for (i=1;i<=mySimplex.d;i++)
		{
			de=de*(m+i);
		}; //buggy? compare to lines 166-170 in integrateFlatVector
		t=temp.find("[",t)+1;
		temp=temp.substr(t,temp.length()-t+1);
		c=0;
		for (i=0;i<temp.length();i++) c+=(temp.at(i)==',');
		if (c+1!=mySimplex.d) {cout<<"The dimensions of the linear form and simplex don't match. Please check!"<<endl;exit(1);};
		t=0;
		for (i=0;i<mySimplex.d-1;i++)
		{
			tt=temp.find(",",t);
			subtemp=temp.substr(t,tt-t);
			l[i]=to_ZZ(subtemp.c_str());
			t=tt+1;
		}
		subtemp=temp.substr(t,temp.length()-t+1);
		l[mySimplex.d-1]=to_ZZ(subtemp.c_str());
		update(a,b,l,mySimplex,m,coe,de);
		index=line.find("]]]",index)+5;
	};
	if (b<0) {b=-b;a=-a;};
};

void integrateFlatVector(ZZ& numerator, ZZ& denominator, const linFormSum &forms , simplexZZ mySimplex)
{
  ZZ v,de,counter,m,tem,coe;
	int i,j,index,k;
	vec_ZZ l;
	if (forms.varCount!=mySimplex.d) {cout<<"The dimensions of the polynomial and simplex don't match. Please check!"<<endl;exit(1);};
	l.SetLength(mySimplex.d);
	lBlock* temForm=forms.lHead;
	cBlock<ZZ>* temCoef=forms.cHead;
	k=-1;
	numerator=0;
	denominator=0;
	//cout<<"The polynomial is decomposed to "<<forms.termCount<<" terms."<<endl;
	for (counter=0;counter<forms.termCount;counter++)
	{
		k++;
		if ((k>0)&&(k % BLOCK_SIZE==0)) {temForm=temForm->next;temCoef=temCoef->next;k=0;}
		for (i=0;i<mySimplex.d;i++) l[i]=temForm->data[k][i];
		m=temForm->degree[k];
		coe=temCoef->data[k];
		de=1;
		for (i=1;i<=mySimplex.d+m;i++)
		{
			de=de*i;
		};
		update(numerator,denominator,l,mySimplex,m,coe,de);
		if (IsZero(denominator)) { return; } //irregular
	}
	if (denominator<0) {denominator *= to_ZZ(-1); numerator *= to_ZZ(-1);};
};	