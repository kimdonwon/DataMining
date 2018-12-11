#include "main.h"

int main(void)
{
	Item_Header *I = (Item_Header*)malloc(sizeof(Item_Header));

	Item_bucket_Header *B = (Item_bucket_Header*)malloc(sizeof(Item_bucket_Header));

	Item *point_I = I->head;
	Item *start_point = I->head;

	int choice = 1;
	int flag;
	int yes_no;
	int i = 0;

	FILE *fp = NULL;
	char *name[10];

	init_Item(I);
	init_Item_bucket(B);

	while (choice != 0)
	{
		flag = 0;
		system("cls");
		printf("===============================================================================\n");
		print_Bucket(B);
		printf("===============================================================================\n");
		print_ItemList(I);
		printf("===============================================================================\n\n\n");

		point_I = I->head;

		if (I->head != NULL)
		{
			while (point_I != NULL)
			{
				if (point_I->related != NULL) {
					related_ItemList_Header *point_R = point_I->related;
					print_relatedItemList(point_R, point_I);

					
				}
				point_I = point_I->rlink;
				
			}
		}

		printf("\n\n���ϴ� ��ȣ�� �Է����ּ���.\n\n");
		printf("1.��ٱ��Ͽ���� \n2.��ٱ��Ͽ��� ���� \n3.���(Training) \n4.������ǰ��õ���ֱ� \n5.��ǰ����(�Ÿ�����) �� �ִܰŸ� Ȯ���ϱ� \n");

		fflush(stdin);
		scanf("%d", &choice);


		switch (choice)
		{
			case 1:
				printf("Transaction File���� �Է����ּ���.\n");
				fflush(stdin);
				scanf("%s", name);

				fp = fopen(name, "r");

				while(fscanf(fp, "%s", name) != EOF)
					insert_toBucket(B, name);

				fclose(fp);
				break;
			case 2:
				printf("��ٱ��Ͽ� ������ Item���� �Է����ּ���(Item���� 10�� ����).\n");

				fflush(stdin);
				scanf("%s", name);

				delete_fromItemBucket(B, name);
				break;
			case 3:
				insert_toItemList(I, B);
				hit_update(I, B);
				empty_out_Bucket(B);
				break;
			case 4:
				printf("���Ͻô� Item���� �Է����ּ���.(Item���� 10�� ����)\n");

				fflush(stdin);
				scanf("%s", name);

				point_I = I->head;

				// �Է¹��� ǰ����� ������ ����Ʈ���� �˻��Ͽ� ������ ��ȯ
				while (point_I != NULL)
				{
					if (strcmp(point_I->Name, name) == 0)
					{
						break;
					}
					point_I = point_I->rlink;
				}

				// �Է¹��� ǰ����� ����Ʈ�� �����Ѵٸ� ǰ�� ��ŷ
				// related_Item_Ranking�Լ� ������ ȭ�� ��±��� �Ϸ�
				if (point_I != NULL) {
					related_Item_Ranking(point_I);
				}
				_getch();
				break;
			case 5:
				printf("\n\n��ǰ(Item)���� �Ÿ��� ���� �󵵼��� ���� �ٽ� �������ּ���.\n");
				printf("	: �⺻ ���� �Ÿ� = 100, �缳�� �Ÿ� = (�⺻�����Ÿ� / (�ش��ǰ��Hit+weight)) * 10\n");
				printf("	: �Ա��κ����� �⺻ ���� �Ÿ� = 10, �缳�� �Ÿ� = (�⺻�����Ÿ� / (�ش��ǰ��Hit)) * 10\n\n\n");

				// ǰ���� �°� ���ԵǾ�����, ǰ��, �Ա��κ��� �Ÿ� �缳��
				reset_Item_Distance(I);
				distanceFromEntrance_update(I);

				printf("�����Ͻð��� �ϴ� ǰ���� �Է����ּ���.(�� �ۼ��Ͽ����� �������� end�ۼ�)\n\n");
				print_ItemList(I);

				flag = 0;

				start_point = I->head;

				// ����ڷκ��� ǰ����� �Է¹޾� �Ա��κ����� �Ÿ��� ���� ��,
				// ���� ª�� �Ÿ��� ǰ���� start_point�� ���� (ǰ�� �Է��� end������ �������� ����)
				while (flag == 0)
				{
					fflush(stdin);
					scanf("%s", name);

					point_I = I->head;

					while (point_I != NULL)
					{
						if (strcmp(point_I->Name, name) == 0)
						{
							if (start_point->distance_fromEntrance > point_I->distance_fromEntrance)
							{
								start_point = point_I;
								break;
							}
							else
								break;
						}
						point_I = point_I->rlink;
					}

					if (strcmp(name, "end") == 0)
						flag = 1;
				}

				printf("\n\n�Ա����� ���� ����� ǰ���� %s�Դϴ�.\n", start_point->Name);
				printf("%s�κ��� ���忡 �ִ� ǰ�������� �ִ� �Ÿ����� �ȳ��ص帮�ڽ��ϴ�.\n\n\n", start_point->Name);

				print_ItemList(I);
				printf("===============================================================================\n\n\n");

				// ������ ����Ʈ�鿡 �����ϴ� ���� �����۵� ������ ǰ���� �Ÿ� ���

				point_I = I->head;

				if (I->head != NULL)
				{
					while (point_I != NULL)
					{
						related_ItemList_Header *point_R = point_I->related;
						print_relatedItemList(point_R, point_I);

						point_I = point_I->rlink;
					}
				}
				// �ִܰ�� Ž��(start_point�κ���)
				shortest_path(start_point, I);
				return 0;
		}
	}
	return 0;
}