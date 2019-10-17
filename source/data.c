#include "data.h"
#include <strlib.h>

//读取球员的名字，储存到incode�?
void ReadStarName(int id,char* incode){
	FILE* file;
	long offset;
	file=fopen(PLAYERHZ,"rb");
	if(file==NULL){
		closegraph();
		printf("the player hz error\n");
		getch();
		exit(-1);
	}
	offset=(id-1)*STAR_NAME;
	fseek(file,offset,SEEK_SET);
	fread(incode,1,4,file);
	fclose(file);
	
}

//���ݵ������id������δӵ����Ա���������
void LoadMarketData(int *id,Star* star){         //ע��starһ����δӵ����Ա
	FILE* file;
	FILE* hz;
	Star* temp=star;
	int number=0,i,current;//���ڼ����ж��ٸ���Ա��current��debug�ò���
	int lim,length;//�������ݿ����ж�����Ա��ͬʱlength��ʾ�ļ��ж���ֽ�
	long int offset;//ƫ����
	star=(Star*)malloc(sizeof(Star));//创建头节�?
       //	Star* temp=star;
	file=fopen(DATABASE,"rb");
	hz=fopen(PLAYERHZ,"rb");
	if(hz==NULL){
		settextjustify(LEFT_TEXT,TOP_TEXT);    
		settextstyle(GOTHIC_FONT,HORIZ_DIR,1);	
		outtextxy(10,10,"Can't open file PLAYERHZ !Press any key to quit...");
		getch();
		exit(1);
	}
	if(file==NULL){
		settextjustify(LEFT_TEXT,TOP_TEXT);    
		settextstyle(GOTHIC_FONT,HORIZ_DIR,1);	
		outtextxy(10,10,"Can't open file DATABASE !Press any key to quit...");
		delay(3000);
		exit(1);
	}
	if(id==NULL){
		settextjustify(LEFT_TEXT,TOP_TEXT);    
		settextstyle(GOTHIC_FONT,HORIZ_DIR,1);	
		outtextxy(10,10,"ERROR:input id missing...");
		delay(3000);
		exit(1);
	}
	fseek(file,0L,SEEK_SET);
	fseek(hz,0L,SEEK_SET);
	//����ȷ�����ݿ⹲�ж�����Ա�������������
	fseek(hz,0L,SEEK_END);
	length=ftell(hz);
	lim=length/10;
	fseek(hz,0L,SEEK_SET);
	
	for(i=0;i<=lim;i++){
		if(id==NULL){
			break;
		}
		if(i==*id){
			offset=10;
			fseek(hz,offset,SEEK_CUR);
			offset=3+8+4+4+2;
			fseek(file,offset,SEEK_CUR);
			id++;
			continue;
		}
		else{
			Star* data=(Star*)malloc(sizeof(Star));
			fread(data->name,1,10,hz);
			fread(data->id,1,3,file);
			fread(data->price,1,8,file);
			fread(data->speed,1,4,file);
			fread(data->strength,1,4,file);
			fread(data->position,1,2,file);
			
			data->next=NULL;
			temp->next=data;
			temp=temp->next;
			
			id++;
		}
	}
	fclose(file);
	fclose(hz);
}

//�������ɵ������������Աid����
int LoadUserStarID(int id[MAX_STAR]){
	int i,length,count,star_num=0;//star_num������ı�������¼������Ա����
	long int offset;//�ļ���ƫ����
	char temp[3];//���ڴ�Ŷ�ȡ��id��Ϣ
	char username[USER_LENGTH];//�û���
	char search_username[USER_LENGTH];//���ҵ����û���
	FILE* fp;
	FILE* data;
	if((fp=fopen(USERFILE,"rb"))==NULL){
		settextjustify(LEFT_TEXT,TOP_TEXT);    
		settextstyle(GOTHIC_FONT,HORIZ_DIR,1);	
		outtextxy(10,10,"Can't open file USERFILE !Press any key to quit...");
		delay(3000);
		exit(1);
	}
	if((fp=fopen(USERDATA,"rb"))==NULL){
		settextjustify(LEFT_TEXT,TOP_TEXT);    
		settextstyle(GOTHIC_FONT,HORIZ_DIR,1);	
		outtextxy(10,10,"Can't open file USERDATA !Press any key to quit...");
		delay(3000);
		exit(1);
	}
	
	fseek(data,0L,SEEK_SET);
	fseek(fp,0L,SEEK_SET);
	fseek(data,0L,SEEK_END);
	length=ftell(data);//�����ܹ��ж����˻�
	count=length/(sizeof(User)+3*MAX_STAR);
	fread(username,1,USER_LENGTH,fp);
	
	for(i=0;i<count;i++){
		offset=i*(sizeof(User)+3*MAX_STAR);//Ѱ��Ŀǰ�Ե�½���˻����������id��Ϣ
		fseek(data,offset,SEEK_SET);
		fread(search_username,1,USER_LENGTH,data);
		if(strcmp(username,search_usernme)==0){
			break;
		}
	}
	
	if(i>=count){
		settextjustify(LEFT_TEXT,TOP_TEXT);    
		settextstyle(GOTHIC_FONT,HORIZ_DIR,1);	
		outtextxy(10,10,"User file no found!!!");
		delay(3000);
		exit(1);
	}
	
	offset=i*(sizeof(User)+3*MAX_STAR)+sizeof(User);
	fseek(data,offset,SEEK_SET);
	for(i=0;i<MAX_STAR;i++){
		fread(temp,1,3,data);
		if(temp=="\0"){
			break;//������������ݣ��˳�ѭ��
		}
		else {
			id[i]=atoi(temp);
			star_num++;
		}
	}
	
	if(i>=MAX_STAR){
		settextjustify(LEFT_TEXT,TOP_TEXT);    
		settextstyle(GOTHIC_FONT,HORIZ_DIR,1);	
		outtextxy(10,10,"Unknown error!!FUck!");
		delay(3000);
		exit(1);
	}
	
	fclose(fp);
	fclose(data);
	return star_num;

}

//����ӵ����Ա���ӳ�����
void LoadStarData(int *id,Star* star){
	FILE* file;
	FILE* hz;
	Star* temp=star;
	int number=0,i,current;//���ڼ����ж��ٸ���Ա��current��debug�ò���
	int lim,length;//�������ݿ����ж�����Ա��ͬʱlength��ʾ�ļ��ж���ֽ�
	long int offset;//ƫ����
	star=(Star*)malloc(sizeof(Star));//创建头节�?
       //	Star* temp=star;
	file=fopen(DATABASE,"rb");
	hz=fopen(PLAYERHZ,"rb");
	if(hz==NULL){
		settextjustify(LEFT_TEXT,TOP_TEXT);    
		settextstyle(GOTHIC_FONT,HORIZ_DIR,1);	
		outtextxy(10,10,"Can't open file PLAYERHZ !Press any key to quit...");
		getch();
		exit(1);
	}
	if(file==NULL){
		settextjustify(LEFT_TEXT,TOP_TEXT);    
		settextstyle(GOTHIC_FONT,HORIZ_DIR,1);	
		outtextxy(10,10,"Can't open file DATABASE !Press any key to quit...");
		delay(3000);
		exit(1);
	}
	if(id==NULL){
		settextjustify(LEFT_TEXT,TOP_TEXT);    
		settextstyle(GOTHIC_FONT,HORIZ_DIR,1);	
		outtextxy(10,10,"ERROR:input id missing...");
		delay(3000);
		exit(1);
	}
	fseek(file,0L,SEEK_SET);
	fseek(hz,0L,SEEK_SET);
	//����ȷ�����ݿ⹲�ж�����Ա�������������
	fseek(hz,0L,SEEK_END);
	length=ftell(hz);
	lim=length/10;
	fseek(hz,0L,SEEK_SET);
	
	for(i=0;i<=lim;i++){
		if(id==NULL){
			break;
		}
		if(i!=*id){
			offset=10;
			fseek(hz,offset,SEEK_CUR);
			offset=3+8+4+4+2;
			fseek(file,offset,SEEK_CUR);
			id++;
			continue;
		}
		else{
			Star* data=(Star*)malloc(sizeof(Star));
			fread(data->name,1,10,hz);
			fread(data->id,1,3,file);
			fread(data->price,1,8,file);
			fread(data->speed,1,4,file);
			fread(data->strength,1,4,file);
			fread(data->position,1,2,file);
			
			data->next=NULL;
			temp->next=data;
			temp=temp->next;
			
			id++;
		}
	}
	fclose(file);
	fclose(hz);
}

void InitManager(Manager manager){
	int i;
	

}