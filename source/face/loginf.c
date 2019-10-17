/********************************
Function:showregisterface
Description:注册界面
input:�?
return:�?
********************************/
#include "loginf.h"
#include "welcomf.h"
#include "login.h"
void register_face(void)
{
	
	cleardevice();
	setwritemode(COPY_PUT);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(0,0,X_MAX-1,Y_MAX-1);
	setfillstyle(SOLID_FILL,GREEN);
	bar(5,5,X_MAX-5,Y_MAX-5);
	setcolor(WHITE);
	setlinestyle(0,0,3);
	circle(X_MAX,Y_MAX,60);
	line(5,190,55,190);
	line(55,190,55,290);
	line(5,290,55,290);
	line(5,140,105,140);
	line(105,140,105,340);
	line(5,340,105,340);
	line(635,190,585,190);
	line(585,190,585,290);
	line(635,290,585,290);
	line(635,140,535,140);
	line(535,140,535,340);
	line(635,340,535,340);
	line(320,5,320,475);
	setfillstyle(SOLID_FILL,YELLOW);
	/*账号字体位置160�?00密码字体位置160�?80
	确认密码字体位置120�?60*/
	bar(240,75,560,125);//�˺�
	bar(240,155,560,205);//����
	bar(240,225,560,275);//ȷ������
	bar(460,325,560,375);//ע��
	showHString(160,100,"�˺�",2,BLACK);
	showHString(160,180,"����",2,BLACK);
	showHString(120,260,"ȷ������",2,BLACK);
	showHString(510,350,"ע��",2,BLACK);
	
	
}

/***********************************
Function: log in
Description:��ʾ������漰����
input:
output:
***********************************/
void log_in_face(void)
{
   
	cleardevice();
	setwritemode(COPY_PUT);
	setfillstyle(SOLID_FILL,BLACK);
	bar(0,0,X_MAX-1,Y_MAX-1);
	/*��½������������320��105
	�˺�����λ��160��200����������λ��160��280*/
	setfillstyle(SOLID_FILL,YELLOW);
	bar(240,175,560,225);//�˺�
	bar(240,255,560,305);//����
	bar(110,335,210,385);//ע��
	bar(400,335,500,385);//��¼
	showHString(320,105,"��½",2,WHITE);
	showHString(200,200,"�˺�",1,WHITE);
	showHString(200,280,"����",1,WHITE);
	showHString(160,360,"ע��",1,BLACK);
	showHString(450,360,"��¼",1,BLACK);
	
	
	
}

/***
                 
				         ***/
void log_in_face_manage(){
	int flag=0,pre_flag=0;//�����ظ�����
	int state;
	char username[USER_LENGTH]={0};
	char password[USER_PASSWORD]={0};
	char key_0=0;//���µ�¼�����״̬��1��ʾȫ�����룬2��ʾ�˺�δ���룬3��ʾ����δ����
	char key_1=0;//���µ�¼�����״̬��0��ʾ��ע�ᣬ1��ʾ��δע��
	char key_2=0;//���µ�¼�����״̬���˻�����ƥ�䣬0��ʾ����ȷ��1��ʾ��ȷ
	log_in_face();
	showMouse();
	//updateGMouse();
	while(1){
		
		if(gMouse.x>=240&&gMouse.x<=560&&gMouse.y>=175&&gMouse.y<=225){
			if(gMouse.button==1){
				text_username(240,240+16*USER_LENGTH,175+22,username);
			}
		}
		else if(gMouse.x>=240&&gMouse.x<=560&&gMouse.y>=255&&gMouse.y<=305){
			if(gMouse.button==1){
				text_password(240,240+16*USER_PASSWORD,255+22,password);
			}
		}
			
	
		else if(gMouse.x>=400&&gMouse.x<=500&&gMouse.y>=335&&gMouse.y<=380)
		{
			/*pre_flag=flag;
			flag=1;*/
		   	if(gMouse.button==1){
				
				key_0=complete_login(username[0],password[0]);
				{
					if(key_0==2)
						{
							
							showHString(X_MAX/2,Y_MAX/2,"�˻�δ����",1,WHITE);
							delay(2000);//δ���
							log_in_face();
						}
						else if(key_0==3)
						{
							
						    showHString(X_MAX/2,Y_MAX/2,"����δ����",1,WHITE);
							delay(2000);
							log_in_face();
						}
					if(key_0==1){
						key_1=judge_same_name(username);
						if(key_1==1){
							
							showHString(X_MAX/2,Y_MAX/2,"�˻�δע��",2,RED);
							delay(2000);
							log_in_face();             
						}
					}
					if(username=="admin"){
						if(password=="admin"){
							show_main_face_manage();
							break;
						}
					}
					if(key_1==0){
						key_2=right_password(username,password);
						if(key_2==0){
							
							showHString(X_MAX/2,Y_MAX/2,"���벻��ȷ",2,RED);
							delay(2000);
							log_in_face();
						}
					}
					if(key_0==1&&key_2==1){
						
						write_user(username);
						break;
					}
					
				}
			}
		}
		else if(gMouse.x>=110&&gMouse.x<=210&&gMouse.y>=335&&gMouse.y<=385){
			/*pre_flag=flag;
			flag=1;*/
			if(gMouse.button==1){
				hideMouse();
				cleardevice();
				register_face_manage();
			}
		}
	}
	hideMouse();
	cleardevice();
	show_main_face_manage();
}

/***

					***/

void register_face_manage() {
	int flag=0,pre_flag=0;//�����ظ�����
	int state;
	char key_0=1;//�ɹ�1���˺�δ����2������δ����3
	char key_1=1;//�����˺�0��������1
	char key_2=1;//0�����ʽ������1����
	char key_3=1;//0��ʾ�������벻��ͬ��1��ʾ��ͬ
	char key_4=0;//��ʱ����
	char username[USER_LENGTH]={0};
	char password[USER_PASSWORD]={0};
	char re_password[USER_PASSWORD]={0};

	register_face();
	showMouse();
	//updateGMouse();
	while(1){
		if(gMouse.x>=240&&gMouse.x<=560&&gMouse.y>=75&&gMouse.y<=125){
			if(gMouse.button==1){
				text_username(240,240+16*USER_LENGTH,75+22,username);
			}
		}

		if(gMouse.x>=240&&gMouse.x<=560&&gMouse.y>=155&&gMouse.y<=205){
			if(gMouse.button==1){
				text_password(240,240+16*USER_PASSWORD,155+22,password);
			}
		}

		if(gMouse.x>=240&&gMouse.x<=560&&gMouse.y>=225&&gMouse.y<=275){
			if(gMouse.button==1){
				text_password(240,240+16*USER_PASSWORD,225+22,re_password);
			}
		}

		if(gMouse.x>=460&&gMouse.x<=560&&gMouse.y>=325&&gMouse.y<=375){
			if(gMouse.button==1){
				/*�ж��Ƿ�������ȫ*/
				key_0=complete_register(username[0],password[0],re_password[0]);//�ɹ�1���˺�δ����2������δ����3������δȷ��4�����֤δ����5
				if(key_0==2){
					showHString(X_MAX/2,Y_MAX/2,"�˺�δ����",1,RED);
					delay(2000);
					register_face();
				}
				else if(key_0==3){
					showHString(X_MAX/2,Y_MAX/2,"����δ����",1,RED);
					delay(2000);
					register_face();
				}
				else if(key_0==4){
					showHString(X_MAX/2,Y_MAX/2,"����δȷ��",1,RED);
					delay(2000);
					register_face();
				}
				else if(key_0==0){
					showHString(X_MAX/2,Y_MAX/2,"ϵͳ������������",1,RED);
					delay(2000);
					register_face();
				}
				key_1=judge_same_name(username);
				key_2=judge_password(password);
				key_3=compare_password(password,re_password);
				if(key_0==1){
					
					if(key_1==0){
						showHString(X_MAX/2,Y_MAX/2,"�˺���ע��",1,RED);
						delay(2000);
						register_face();
					}
				}
				if(key_1==1){
					
					if(key_2==0){
						showHString(X_MAX/2,Y_MAX/2,"���볤�Ȳ�����Ҫ��",1,RED);
						delay(2000);
						register_face();
					}
				}
				if(key_2==1){
					
					if(key_3==0){
						showHString(X_MAX/2,Y_MAX/2,"���벻��ͬ",1,RED);
						delay(2000);
						register_face();
					}
				}
				if((key_0==1)&&(key_1==1)&&(key_2==1)&&(key_3==1)){
					write_user_inf(username,password);
					break;
				}
			}
		}
	}
	hideMouse();
	gMouse.button==0;
	cleardevice();
	log_in_face_manage();
}