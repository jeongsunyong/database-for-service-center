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

		printf("��Ƽ���� ���񽺼��� �Դϴ�\n");
		printf("�����ȣ : ");
		scanf("%d",&id);
		int suc = log_in(conn, res, row, id);
		if (suc == 1)
		{
			printf("�α��εǾ����ϴ�.\n");
			break;
		}
		
	}
	
	while (1)
	{
		printf("\n����� : %s ��", emp);
		printf("\n*******************************\n");
		printf("\n****** ��Ÿ �߰� ������ ******\n");
		printf("\n***�����ڿ��� ���� �ٶ��ϴ�***\n");
		printf("\n*******************************\n");
		printf("��Ƽ���� ���񽺼��� ���α׷�\n\n");
		printf("1.���� �ۼ�\n");
		printf("2.��ȸ ����\n");
		printf("3.������ ����\n");
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
				printf("1.�ű� ����\n");
				printf("2.���� ���� �ۼ�\n");
				printf("3.��������\n");
				printf(">");
				scanf("%d", &order);
				if (order == 1)
				{
					while (1)
					{
						printf("����:");
						scanf("%s", cname);

						printf("�𵨸�:");
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
								printf("���� �𵨸��Դϴ�.\n");
								return 0;
							}
						}
						printf("�ø���ѹ�");
						scanf("%s", serial);
						printf("���Կ���");
						scanf("%s", pdate);
						printf("���ǻ���:");
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
					printf("������ȣ");
					scanf("%d", &no);
					printf("�����Ȳ:");
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
					//�ϷῩ�μ���
					//�����Ȳ����

				}
				if (order == 3)
				{
					break;
				}
			}
		}
		else if (order == 2)
		{
			printf("1.���� ��ȸ\n");
			printf("2.�� ��ȸ\n");
			printf("3.��ǰ �� ��ǰ ��ȸ\n");
			printf("4.��������\n");
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
				printf("1.��ǰ ����\n");
				printf("2.��ǰ ����\n");
				printf("3.�� ����\n");
				printf("4.��������\n");
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
					//��ǰ�������� �𵨴������� ������Ʈ

					//����ȭ��ȣ �ּ�
					//�������
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
			printf("���� �����ȣ�Դϴ�.\n");
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
		printf("1.�𵨺�ǰ��ȸ\n");
		printf("2.��ü��ǰ��ȸ\n");
		printf("3.�����ȸ\n");
		printf("4.��������\n");
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
							printf("���� �𵨸��Դϴ�.\n");
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
				printf("�𵨺���ǰ\n");
				sprintf(show, "select * from SS_devinf;");
				if (mysql_query(conn, show) != 0)
				{
					printf("query fail; err=%s\n", mysql_error(conn));
				}

				res = mysql_store_result(conn);
				while ((row = mysql_fetch_row(res)) != NULL)
				{
					printf("��:%s ��ǰ:%s\n", row[0], row[1]);
				}
				printf("\n��ǰ������\n");
				sprintf(show, "select * from SS_comp;");
				if (mysql_query(conn, show) != 0)
				{
					printf("query fail; err=%s\n", mysql_error(conn));
				}

				res = mysql_store_result(conn);
				while ((row = mysql_fetch_row(res)) != NULL)
				{
					printf("��ǰ:%s ����:%s ȸ��:%s ����:%s\n", row[0], row[1], row[2], row[3]);
				}
				mysql_free_result(res);
				break;
			}
		}

		else if (order == 3)
		{
			printf("���\n");
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
	const char* part[5] = { "CPU","���κ���", "���͸�","����","�ϵ��ũ" };
	const char* mani[3] = { "A","B","C" };
	char show[200] = "";
	char tmp[100] = "";
	int order = 0;
	printf("--------��ǰ����--------\n");
	while (1)
	{
		printf("--------------\n");
		printf("1.��ǰ �߰�\n");
		printf("2.���� ó��\n");
		printf("3.��� ����\n");
		printf("4.��������\n");
		printf("--------------\n");
		printf(">");
		scanf("%d", &order);
		if (order == 1)
		{
			//�ߺ����κ����ؾߵǴµ� �ϴ� �н��ϰ� �����Ҷ�����

			//�Է¹޾ƾ��Ұ�
				//��ǰ��ȣ
				//��ǰ����
				//ȸ���
				//����
			//�Է������̺� : ��ǰ����(��ǰ��ȣ,��������X ��� 0 ) && ��ǰ���� (��ǰ��ȣ)


			printf("��ǰ����:");
			while (1)
			{
				printf("\n1.CPU\n");
				printf("2.���κ���\n");
				printf("3.���͸�\n");
				printf("4.����\n");
				printf("5.�ϵ��ũ\n");
				printf(">");
				scanf("%d", &order);
				if (order > 0 && order < 6)
				{
					strcpy(props[0], part[order-1]);
					break;
				}
			}
			printf("��ǰ��ȣ:");
			{
				scanf("%s", props[1]);
			}
			printf("ȸ���:");
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
			printf("����:");
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
					printf("�ԷµǾ����ϴ�.\n");
					props[3][0] = '\0';
				}
			}
			res = mysql_store_result(conn);
		
			mysql_free_result(res);
		
		}
		else if (order == 2)
		{
			printf("\n�����Ⱥ�ǰ��ȣ:");
			scanf("%s", props[1]);
			sprintf(show, "update SS_mana SET discont = '����' where comp LIKE '%s';", props[1]);
			if (mysql_query(conn, show) != 0)
			{
				printf("query fail; err = %s \n", mysql_error(conn));
				return;
			}
			else
			{
				printf("����ó���Ǿ����ϴ�.\n");
				
			}
			res = mysql_store_result(conn);

			mysql_free_result(res);
			
		}
		else if (order == 3)
		{
			int stock_num = 0;
			printf("\n�Է��Һ�ǰ��ȣ:");
			scanf("%s", props[1]);
			printf("\n��� ���� �Է����ּ���:");
			scanf("%d", &stock_num);
			sprintf(show, "update SS_mana SET stock = %d where comp LIKE '%s';", stock_num,props[1]);
			if (mysql_query(conn, show) != 0)
			{
				printf("query fail; err = %s \n", mysql_error(conn));
				return;
			}
			else
			{
				printf("����ԷµǾ����ϴ�.\n");
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
		printf("--------������--------\n");
		while (1)
		{

			printf("--------------\n");
			printf("1.����������\n");
			printf("2.��������\n");
			printf("--------------\n");
			printf(">");
			scanf("%d", &order);
			if (order == 1)
			{
				while (1)
				{
					printf("���̸�:");
					printf(">");
					scanf("%s", cname);
					printf("����ȣ:");
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
							printf("���� �̸��Դϴ�.\n");
							return ;
						}
					}
					break;
				}
				while (1)
				{
					printf("1.�ּҺ���\n");
					printf("2.��ȣ����\n");
					printf("3.��������\n");
					printf(">");
					scanf("%d", &order);
					if (order == 1)
					{
						char address[30] = {};
						printf("������ �ּ� :");
						scanf("%s", address);
						sprintf(show, "update SS_customer SET address = '%s' where cno LIKE '%s';", address, cno);
						if (mysql_query(conn, show) != 0)
						{
							printf("query fail; err = %s \n", mysql_error(conn));
							return;
						}
						else
						{
							printf("����Ǿ����ϴ�.\n");
						}
						res = mysql_store_result(conn);

						mysql_free_result(res);
						order = 0;

					}
					else if (order == 2)
					{
						char phone[30] = {};
						printf("������ ��ȣ :");
						scanf("%s", phone);
						sprintf(show, "update SS_customer SET phone = '%s' where cname LIKE '%s';", phone, cname);
						if (mysql_query(conn, show) != 0)
						{
							printf("query fail; err = %s \n", mysql_error(conn));
							return;
						}
						else
						{
							printf("����Ǿ����ϴ�.\n");
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
	const char* product[3] = { "�ڵ���","�º�", "��Ʈ��" };
	const char* mani[3] = { "A","B","C" };
	char comp[5][20] = {};
	char show[200] = "";
	int order = 0;
	printf("--------������--------\n");
	while (1)
	{
		printf("--------------\n");
		printf("1.�� �߰�\n");
		printf("2.���� ó��\n");
		printf("3.��������\n");
		printf("--------------\n");
		printf(">");
		scanf("%d", &order);
		if (order == 1)
		{

			printf("��ǰ����:");
			while (1)
			{
				printf("\n1.�ڵ���\n");
				printf("2.�º�\n");
				printf("3.��Ʈ��\n");
				printf(">");
				scanf("%d", &order);
				if (order > 0 && order < 4)
				{
					strcpy(props[0], product[order - 1]);
					break;
				}
			}
			printf("�𵨸�:");
			{
				scanf("%s", props[1]);
			}
			int stop = 0;
			int cnt = 0;
			printf("�𵨱�����ǰ�� �Է��ϼ��� (�׸�:stop�Է�)\n");
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
							printf("�ԷµǾ����ϴ�.\n");
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
			printf("\n�����ȸ𵨹�ȣ:");
			scanf("%s", props[1]);
			sprintf(show, "update SS_model SET discont = '����' where model LIKE '%s';", props[1]);
			if (mysql_query(conn, show) != 0)
			{
				printf("query fail; err = %s \n", mysql_error(conn));
				return;
			}
			else
			{
				printf("����ó���Ǿ����ϴ�.\n");

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