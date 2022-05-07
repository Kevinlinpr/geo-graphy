#ifndef __TRILOOP_CODE_H__
#define __TRILOOP_CODE_H__

using namespace std;
extern "C"
{
	extern void Data2CodeWrite(double*,char*,int);
	extern void Data2Code1(double*, char*, int);
	extern void Data2Code2(char*, char*, int);
	extern void Data2Code3(char*, char*, int);
	 
	extern void Code2DataWrite(char*, double*, int);
	extern void Code2Data1(char*, double*, int);
	extern void Code2Data2(char*, char*, int);
	extern void Code2Data3(char*, char*, int);
	extern int char2int(char);
};

#endif