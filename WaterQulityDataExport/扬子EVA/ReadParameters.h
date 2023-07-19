#ifndef __READPARAMETER__
#define __READPARAMETER__

#define max_line 1024

void memv(unsigned char *pdata,unsigned char *ppdata,int st1,int st2,int length);
int ReadParameter(char *name);
void Exportwater(char *name);

extern char data[max_line];









#endif