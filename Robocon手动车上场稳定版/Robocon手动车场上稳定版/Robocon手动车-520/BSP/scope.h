#ifndef __SCOPE_H
#define __SCOPE_H	 

void Float2Byte(float *target,unsigned char *buf,unsigned char beg);
void DataScope_Get_Channel_Data(float Data,unsigned char Channel);
unsigned char DataScope_Data_Generate(unsigned char Channel_Number);
void scope(float a,float b,float c);

#endif
