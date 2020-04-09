#pragma comment(lib, "libmySQL.lib")
#pragma comment(lib, "ws2_32.lib")
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <cstring>


using namespace std;

void intToString(char* str, int num);
int log_in(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row, int id);
void f_select(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row);
void manageComp(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row);
void manageCust(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row);
void manageDev(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row);
void viewInq(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row);
void viewComp(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row);
void viewCust(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row);
void viewDev(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row);
char emp[20] = {};
int id = 0;
int main(int argc, char **argv)
{
	int order = 0;
	//std::cout << mysql_get_client_info();
	//int cno = 2;
	string querry;
	string input;

	MYSQL *conn;
	MYSQL *mysql;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row=NULL;

	const char *host = "linux.mme.dongguk.edu";
	const char *user = "s2014112569";
	const char *password = "";
	const char *database = "s2014112569";
	int port = 33060;

	conn = mysql_init(NULL);
	mysql = mysql_init(NULL);

	mysql_options(conn, MYSQL_SET_CHARSET_NAME, "euckr");
	mysql_options(conn, MYSQL_INIT_COMMAND, "SET NAMES euckr");


	if (!mysql_real_connect(conn, host, user, password, database, port, NULL, 0))
	{
		fprintf(stderr, "%s", mysql_error(conn));
		exit(1);
	}
	res = mysql_use_result(conn);

	
	while (1)
	{

		printf("멀티전자 서비스센터 입니다\n");
		printf("사원번호 : ");
		scanf("%d",&id);
		int suc = log_in(conn, res, row, id);
		if (suc == 1)
		{
			printf("로그인되었습니다.\n");
			break;
		}
		
	}
	
	while (1)
	{
		printf("\n사용자 : %s 님", emp);
		printf("\n*******************************\n");
		printf("\n****** 기타 추가 사항은 ******\n");
		printf("\n***관리자에게 문의 바랍니다***\n");
		printf("\n*******************************\n");
		printf("멀티전자 서비스센터 프로그램\n\n");
		printf("1.문의 작성\n");
		printf("2.조회 업무\n");
		printf("3.데이터 관리\n");
		printf("\n*******************************\n");
		printf("\n*******************************\n");
		printf(">");
		scanf("%d", &order);

		if (order == 1)
		{
			char show[300] = {};
			char tmp[100] = {};


			char model[20] = {};
			char text_1[200] = {};
			char text_2[200] = {};
			char cname[20] = {};
			char serial[20] = {};
			char pdate[20] = {};

			while (1)
			{
				printf("1.신규 문의\n");
				printf("2.기존 문의 작성\n");
				printf("3.이전으로\n");
				printf(">");
				scanf("%d", &order);
				if (order == 1)
				{
					while (1)
					{
						printf("고객명:");
						scanf("%s", cname);

						printf("모델명:");
						scanf("%s", model);
						sprintf(show, "select model from SS_model where model like '%s'", model);
						if (mysql_query(conn, show) != 0)
						{
							printf("query fail; err = %s \n", mysql_error(conn));
							return 0;
						}
						res = mysql_store_result(conn);

						while ((row = mysql_fetch_row(res)) != NULL)
						{
							if (strcmp(row[1], tmp) == 0)
							{
							}
							else
							{
								printf("없는 모델명입니다.\n");
								return 0;
							}
						}
						printf("시리얼넘버");
						scanf("%s", serial);
						printf("구입연월");
						scanf("%s", pdate);
						printf("문의사항:");
						gets_s(text_1);
						gets_s(text_1);						
						break;
					}
					sprintf(show,"insert into SS_customer(cname)values('%s');",cname);

					if (mysql_query(conn, show) != 0)
					{
						printf("query fail; err = %s \n", mysql_error(conn));

						system("pause");
						continue;
					}
					res = mysql_store_result(conn);
					
					mysql_free_result(res);
					
					sprintf(show, "insert into SS_have(serialnum,pdate,model)values('%s','%s','%s');", serial,pdate,model);

					if (mysql_query(conn, show) != 0)
					{
						printf("query fail; err = %s \n", mysql_error(conn));
						system("pause");
						return 0;
					}

					res = mysql_store_result(conn);

					mysql_free_result(res);

					sprintf(show, "insert into SS_inq(rtime,serialnum,id,fin,text_1)values(sysdate(),'%s','%d',' ', '%s');",serial,id,text_1);
					if (mysql_query(conn, show) != 0)
					{
						printf("query fail; err = %s \n", mysql_error(conn));
						system("pause");
						return 0;
					}

					res = mysql_store_result(conn);

					mysql_free_result(res);
				}
				if (order == 2)
				{
					int no=0;
					printf("접수번호");
					scanf("%d", &no);
					printf("진행상황:");
					gets_s(text_2);
					gets_s(text_2);
					sprintf(show, "update SS_inq set text_2 = '%s' where rno = %d;",text_2,no);
					if (mysql_query(conn, show) != 0)
					{
						printf("query fail; err = %s \n", mysql_error(conn));
						system("pause");
						return 0;
					}

					res = mysql_store_result(conn);

					mysql_free_result(res);
					//완료여부수정
					//진행상황수정

				}
				if (order == 3)
				{
					break;
				}
			}
		}
		else if (order == 2)
		{
			printf("1.문의 조회\n");
			printf("2.고객 조회\n");
			printf("3.제품 및 부품 조회\n");
			printf("4.이전으로\n");
			printf(">");
			scanf("%d", &order);
			if (order == 1)
			{
				viewInq(conn, res, row);
			}
			else if (order == 2)
			{
				viewCust(conn, res, row);
			}
			else if (order == 3)
			{
				viewDev(conn, res, row);
			}
			else if (order == 4)
			{
				break;
			}
			else
				continue;
		}
		else if (order == 3)
		{
			while (1)
			{
				printf("1.부품 관리\n");
				printf("2.제품 관리\n");
				printf("3.고객 관리\n");
				printf("4.이전으로\n");
				printf(">");
				scanf("%d", &order);
				if (order == 1)
				{
					manageComp(conn, res, row);
				}
				else if (order == 2)
				{
					manageDev(conn, res, row);
				}
				else if (order == 3)
				{
					manageCust(conn, res, row);
				}
				else if (order == 4)
				{
					break;
				}
				else
					continue;
					//부품단종여부 모델단종여부 업데이트

					//고객전화번호 주소
					//사원정보
			}
		}
	}

	//f_select(conn, res, row); 

	system("pause");
	return 0;
}

int log_in(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row, int id)
{
	char tmp[10] = {};
	sprintf(tmp, "%d", id);

	const char* prop1 = "id";
	const char* prop2 = "ename";
	const char* table = "SS_employee";
	char show[100] = "";

	sprintf(show, "select %s, %s from %s where %s = %d;", prop2,prop1, table, prop1,id);
	if (mysql_query(conn, show) != 0)
	{
		printf("query fail; err = %s \n", mysql_error(conn));
		return 0;
	}
	res = mysql_store_result(conn);

	while ((row = mysql_fetch_row(res)) != NULL)
	{
		if (strcmp(row[1], tmp) == 0)
		{
			sprintf(emp," %s ", row[0]);
		}
		else
		{
			printf("없는 사원번호입니다.\n");
			return 0;
		}
	}

	return 1;
}
void viewInq(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row)
{

	char show[100] = "";
	char tmp[100] = "";

	sprintf(show, "select * from SS_inq;");
	if (mysql_query(conn, show) != 0)
	{
		printf("query fail; err = %s \n", mysql_error(conn));
		return;
	}

	res = mysql_store_result(conn);

	while ((row = mysql_fetch_row(res)) != NULL)
	{
		printf("\n%s %s %s %s %s %s %s \n", row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
	}
	mysql_free_result(res);
}
void viewCust(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row) 
{
	//select * from SS_customer
	//select * from SS_have

	char show[100] = "";
	char tmp[100] = "";

	sprintf(show, "select * from SS_customer;");
	if (mysql_query(conn, show) != 0)
	{
		printf("query fail; err = %s \n", mysql_error(conn));
		return;
	}

	res = mysql_store_result(conn);

	while ((row = mysql_fetch_row(res)) != NULL)
	{
		printf("\n\n%s %s %s %s \n", row[0], row[1], row[2], row[3]);
	}
	mysql_free_result(res);
}
void viewDev(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row)
{
	char show[200] = "";
	char model[20] = {};
	while (1)
	{
		int order = 0;
		printf("--------------\n");
		printf("1.모델부품조회\n");
		printf("2.전체부품조회\n");
		printf("3.재고조회\n");
		printf("4.이전으로\n");
		printf("--------------\n");
		printf(">");
		scanf("%d", &order);

		if (order == 1)
		{
			while (1)
			{
				while (1)
				{
					scanf("%s", model);
					sprintf(show, "select model,comp from SS_devinf where model LIKE '%s';", model);
					if (mysql_query(conn, show) != 0)
					{
						printf("query fail; err = %s \n", mysql_error(conn));
						return;
					}
					res = mysql_store_result(conn);
					while ((row = mysql_fetch_row(res)) != NULL)
					{
						if (strcmp(row[0], model) == 0)
						{

						}
						else
						{
							printf("없는 모델명입니다.\n");
							return;
						}
					}
					break;
				}
				sprintf(show, "select * from SS_devinf where model LIKE '%s' ;", model);;
				if (mysql_query(conn, show) != 0)
				{
					printf("query fail; err=%s\n", mysql_error(conn));
				}

				res = mysql_store_result(conn);
				while ((row = mysql_fetch_row(res)) != NULL)
				{
					printf("%s %s\n", row[0], row[1]);
				}
				mysql_free_result(res);
				break;
			}
		}

		else if (order == 2)
		{
			while (1)
			{
				printf("모델별부품\n");
				sprintf(show, "select * from SS_devinf;");
				if (mysql_query(conn, show) != 0)
				{
					printf("query fail; err=%s\n", mysql_error(conn));
				}

				res = mysql_store_result(conn);
				while ((row = mysql_fetch_row(res)) != NULL)
				{
					printf("모델:%s 부품:%s\n", row[0], row[1]);
				}
				printf("\n부품별정보\n");
				sprintf(show, "select * from SS_comp;");
				if (mysql_query(conn, show) != 0)
				{
					printf("query fail; err=%s\n", mysql_error(conn));
				}

				res = mysql_store_result(conn);
				while ((row = mysql_fetch_row(res)) != NULL)
				{
					printf("부품:%s 가격:%s 회사:%s 종류:%s\n", row[0], row[1], row[2], row[3]);
				}
				mysql_free_result(res);
				break;
			}
		}

		else if (order == 3)
		{
			printf("재고\n");
			sprintf(show, "select * from SS_mana;");
			if (mysql_query(conn, show) != 0)
			{
				printf("query fail; err=%s\n", mysql_error(conn));
			}

			res = mysql_store_result(conn);
			while ((row = mysql_fetch_row(res)) != NULL)
			{
				printf("%s %s %s\n", row[0], row[2] ,row[1]);
			}

		}
		else if (order == 4)
			break;
		else continue;
	

	}
}
void manageComp(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row)
{
	const char* prop1 = "model";
	const char* prop2 = "comp";
	const char* table3 = "SS_mana";
	const char* table2 = "SS_comp";
	const char* table1 = "SS_devinf";
	char props[10][20] = {};
	const char* part[5] = { "CPU","메인보드", "배터리","액정","하드디스크" };
	const char* mani[3] = { "A","B","C" };
	char show[200] = "";
	char tmp[100] = "";
	int order = 0;
	printf("--------부품관리--------\n");
	while (1)
	{
		printf("--------------\n");
		printf("1.부품 추가\n");
		printf("2.단종 처리\n");
		printf("3.재고 관리\n");
		printf("4.이전으로\n");
		printf("--------------\n");
		printf(">");
		scanf("%d", &order);
		if (order == 1)
		{
			//중복여부보긴해야되는데 일단 패스하고 멀쩡할때넣자

			//입력받아야할것
				//부품번호
				//부품종류
				//회사명
				//가격
			//입력할테이블 : 부품관리(부품번호,단종여부X 재고 0 ) && 부품정보 (부품번호)


			printf("부품종류:");
			while (1)
			{
				printf("\n1.CPU\n");
				printf("2.메인보드\n");
				printf("3.배터리\n");
				printf("4.액정\n");
				printf("5.하드디스크\n");
				printf(">");
				scanf("%d", &order);
				if (order > 0 && order < 6)
				{
					strcpy(props[0], part[order-1]);
					break;
				}
			}
			printf("부품번호:");
			{
				scanf("%s", props[1]);
			}
			printf("회사명:");
			{
				printf("\n1.A\n");
				printf("2.B\n");
				printf("3.C\n");
				printf(">");
				scanf("%d", &order);
				if (order > 0 && order < 6)
				{
					strcpy(props[2], mani[order-1]);
				}
				
			}
			printf("가격:");
			{
				scanf("%d", &order);
				sprintf(props[3], "%d", order);
			}

			sprintf(show, "insert into SS_comp(comp,price,coname,part)values('%s',%s,'%s','%s');",props[1], props[3], props[2],props[0]);
			if (mysql_query(conn, show) != 0)
			{
				printf("query fail; err = %s \n", mysql_error(conn));
				return;
			}
			else
			{
				sprintf(show, "insert into SS_mana(comp,discont,stock)values('%s',' ',0);", props[1]);
				if (mysql_query(conn, show) != 0)
				{
					printf("query fail; err = %s \n", mysql_error(conn));
					return;
				}
				else
				{
					printf("입력되었습니다.\n");
					props[3][0] = '\0';
				}
			}
			res = mysql_store_result(conn);
		
			mysql_free_result(res);
		
		}
		else if (order == 2)
		{
			printf("\n단종된부품번호:");
			scanf("%s", props[1]);
			sprintf(show, "update SS_mana SET discont = '단종' where comp LIKE '%s';", props[1]);
			if (mysql_query(conn, show) != 0)
			{
				printf("query fail; err = %s \n", mysql_error(conn));
				return;
			}
			else
			{
				printf("단종처리되었습니다.\n");
				
			}
			res = mysql_store_result(conn);

			mysql_free_result(res);
			
		}
		else if (order == 3)
		{
			int stock_num = 0;
			printf("\n입력할부품번호:");
			scanf("%s", props[1]);
			printf("\n재고 수를 입력해주세요:");
			scanf("%d", &stock_num);
			sprintf(show, "update SS_mana SET stock = %d where comp LIKE '%s';", stock_num,props[1]);
			if (mysql_query(conn, show) != 0)
			{
				printf("query fail; err = %s \n", mysql_error(conn));
				return;
			}
			else
			{
				printf("재고입력되었습니다.\n");
			}
			res = mysql_store_result(conn);

			mysql_free_result(res);

		}
		else if (order == 4)
		{
			return;
		}
		else continue;
	}
}
void manageCust(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row)
{
	while (1)
	{
		char cname[20] = {};
		char cno[20] = {};
		char show[200] = "";
		int order = 0;
		printf("--------고객관리--------\n");
		while (1)
		{

			printf("--------------\n");
			printf("1.고객정보변경\n");
			printf("2.이전으로\n");
			printf("--------------\n");
			printf(">");
			scanf("%d", &order);
			if (order == 1)
			{
				while (1)
				{
					printf("고객이름:");
					printf(">");
					scanf("%s", cname);
					printf("고객번호:");
					printf(">");
					scanf("%s", cno);
					sprintf(show, "select cname from SS_customer where cno LIKE '%s';", cno);
					if (mysql_query(conn, show) != 0)
					{
						printf("query fail; err = %s \n", mysql_error(conn));
						return;
					}
					res = mysql_store_result(conn);
					while ((row = mysql_fetch_row(res)) != NULL)
					{
						if (strcmp(row[0], cname) == 0)
						{
						}
						else
						{
							printf("없는 이름입니다.\n");
							return ;
						}
					}
					break;
				}
				while (1)
				{
					printf("1.주소변경\n");
					printf("2.번호변경\n");
					printf("3.이전으로\n");
					printf(">");
					scanf("%d", &order);
					if (order == 1)
					{
						char address[30] = {};
						printf("변경할 주소 :");
						scanf("%s", address);
						sprintf(show, "update SS_customer SET address = '%s' where cno LIKE '%s';", address, cno);
						if (mysql_query(conn, show) != 0)
						{
							printf("query fail; err = %s \n", mysql_error(conn));
							return;
						}
						else
						{
							printf("변경되었습니다.\n");
						}
						res = mysql_store_result(conn);

						mysql_free_result(res);
						order = 0;

					}
					else if (order == 2)
					{
						char phone[30] = {};
						printf("변경할 번호 :");
						scanf("%s", phone);
						sprintf(show, "update SS_customer SET phone = '%s' where cname LIKE '%s';", phone, cname);
						if (mysql_query(conn, show) != 0)
						{
							printf("query fail; err = %s \n", mysql_error(conn));
							return;
						}
						else
						{
							printf("변경되었습니다.\n");
						}
						res = mysql_store_result(conn);

						mysql_free_result(res);

					}
					else if (order == 3)
					{
						break;
					}
				}
			}
			else if (order == 2)
			{
				return;

			}
			else continue;
		}
	}
}

void manageDev(MYSQL* conn, MYSQL_RES* res, MYSQL_ROW row) 
{
	char props[10][20] = {};
	const char* product[3] = { "핸드폰","태블릿", "노트북" };
	const char* mani[3] = { "A","B","C" };
	char comp[5][20] = {};
	char show[200] = "";
	int order = 0;
	printf("--------기기관리--------\n");
	while (1)
	{
		printf("--------------\n");
		printf("1.모델 추가\n");
		printf("2.단종 처리\n");
		printf("3.이전으로\n");
		printf("--------------\n");
		printf(">");
		scanf("%d", &order);
		if (order == 1)
		{

			printf("제품종류:");
			while (1)
			{
				printf("\n1.핸드폰\n");
				printf("2.태블릿\n");
				printf("3.노트북\n");
				printf(">");
				scanf("%d", &order);
				if (order > 0 && order < 4)
				{
					strcpy(props[0], product[order - 1]);
					break;
				}
			}
			printf("모델명:");
			{
				scanf("%s", props[1]);
			}
			int stop = 0;
			int cnt = 0;
			printf("모델구성부품을 입력하세요 (그만:stop입력)\n");
			while (cnt<5)
			{
				scanf("%s", comp[cnt]);
				if (strcmp(comp[cnt], "stop") == 0)
				{
					sprintf(comp[cnt], " ");
					break;
				}
				cnt++;
				
			}

			sprintf(show, "insert into SS_model(model,discont,product)values('%s',' ','%s');", props[1], props[0]);
			if (mysql_query(conn, show) != 0)
			{
				printf("query fail; err = %s \n", mysql_error(conn));
				return;
			}
			else
			{
				for (int i = 0;i < cnt;i++)
				{
					sprintf(show, "insert into SS_devinf(model,comp)values('%s','%s');", props[1],comp[i]);
					if (mysql_query(conn, show) != 0)
					{
						printf("query fail; err = %s \n", mysql_error(conn));
						return;
					}
					else
					{
						if (i == cnt - 1)
						{
							printf("입력되었습니다.\n");
							cnt = 0;
						}
					}
				}
			}
			res = mysql_store_result(conn);
			
			mysql_free_result(res);
			
		}
		else if (order == 2)
		{
			printf("\n단종된모델번호:");
			scanf("%s", props[1]);
			sprintf(show, "update SS_model SET discont = '단종' where model LIKE '%s';", props[1]);
			if (mysql_query(conn, show) != 0)
			{
				printf("query fail; err = %s \n", mysql_error(conn));
				return;
			}
			else
			{
				printf("단종처리되었습니다.\n");

			}
			res = mysql_store_result(conn);

			mysql_free_result(res);

		}
		else if (order == 3)
		{
			return;

		}
		else continue;
	}
}