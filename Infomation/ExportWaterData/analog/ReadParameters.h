#ifndef __READPARAMETER__
#define __READPARAMETER__

#define max_line 1024

void memv(unsigned char *pdata,unsigned char *ppdata,int st1,int st2,int length);
int ReadParameter(char *name);
void Exportwater(char *name);
void DecToHex(int dec, unsigned char *hex, int length);
void inttohex(int aa);
unsigned short int ModBus_CRC16( unsigned char *pdata, int len);

extern char data[max_line];





#endif