#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//cat ../264part-* > highProfile-level4.0-fp25-1920x1080-yuv420p-duration000405.264

void writeSize(int len, FILE* out){
	char t[20];
	sprintf(t,"%d\n",len);
	fwrite(&t[0],1,strlen(t),out);
}

int type1,type2,type3;

void updateType(int newType){
	type1=type2;
	type2=type3;
	type3=newType;
}

bool isSpsPpsKey(){
	if( ( (7==type1 && 8==type2) || (8==type1 && 7==type2) ) && 5==type3){
		return true;
	}
	return false;
}

int main(){
	printf("start...\n");

	FILE* out=fopen("size.txt","wb+");

	const char* file="highProfile-level4.0-fp25-1920x1080-yuv420p-duration000405.264";
	FILE* fp=fopen(file,"rb");
	if(!fp){
		printf("no file\n");
		return -1;
	}
	fseek(fp, 0, SEEK_END);
	int filesize=ftell(fp);
	fseek(fp,0, SEEK_SET);
	printf("file size is %d\n", filesize);

	unsigned char buf[5];
	unsigned char startcode[]={0x00,0x00,0x00,0x01};
	int count=0;
	int start=0;
	int len=0;
	type1=type2=type3=-1;

	for(;;){
		int ret=fread(&buf[0],1,5,fp);
		if(ret!=5){
			int cur = ftell(fp);
			if(filesize == cur){
				count++;
				len=cur - start;
				printf("%d, found frame type=%d, %d %d\n", count, type3, start, len);
				writeSize(len, out);
				printf("good, now we are at the end of file\n");
				return 0;
			}
			printf("fail to read file\n");
			return -2;
		}
		int cur = ftell(fp);

		if(memcmp(&buf[0],&startcode[0],4)==0){
			bool gotEnd=false;
			if(isSpsPpsKey()){
				count++;
				len=cur - start - 5;
				gotEnd=true;
				printf("%d, found sps pps key, %d %d\n", count, start, len);
				writeSize(len, out);
			}else if(type3>0 && (7!=type3 && 8!=type3 && 5!=type3) ){
				count++;
				len=cur - start -5;
				gotEnd=true;
				printf("%d, found frame type=%d, %d %d\n", count, type3, start, len);
				writeSize(len, out);
			}
			
			unsigned int nalType = buf[4] & 0x1f;
                        printf("nalType=%d\n", nalType);
			updateType(nalType);
			if(gotEnd){
				start=cur-5;
			}
		}else{
			fseek(fp, -4, SEEK_CUR);
		}
	}

	return 0;
}

