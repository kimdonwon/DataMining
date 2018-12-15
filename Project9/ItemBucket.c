#include "common.h"
#include "ItemBucket.h"
#include "Item.h"

// ������ ����Ʈ�� �پ� �ִ� ���� ������ ����Ʈ�� �ʱ�ȭ���ִ� �Լ�
void init_Item_bucket(Item_bucket_Header *B)
{
	B->head = B->rear = NULL;
}

// ��ٱ��ϰ� ����ִ��� Ȯ��
int is_empty_Item_bucket(Item_bucket_Header *B)
{
	return (B->head == NULL);
}

// ǰ����� �Է¹޾� ��ٱ��Ͽ� �߰����ִ� �Լ�
void insert_toBucket(Item_bucket_Header *B, char *name)
{
	Item *temp = (Item*)malloc(sizeof(Item));
	char* tmp_name;

	tmp_name = (char*)malloc(sizeof(char) * 10);

	if (temp == NULL) {
		fprintf(stderr, "�޸𸮸� �Ҵ��� �� �����ϴ�");
		exit(1);
	}
	else
	{
		strcpy(tmp_name, name);

		temp->Name = tmp_name;
		temp->rlink = NULL;
		temp->Hit = 0;
		temp->distance_fromEntrance = 10;
		temp->related = NULL;

		if (is_empty_Item_bucket(B)) {
			B->head = temp;
			B->rear = temp;
			temp->llink = NULL;
		}
		else {
			B->rear->rlink = temp;
			temp->llink = B->rear;
			B->rear = temp;
		}

	}
}

// ǰ����� �Է¹޾� �ش� ǰ���� ��ٱ��Ͽ��� �˻��Ͽ� �������ִ� �Լ�
void delete_fromItemBucket(Item_bucket_Header *B, char *name)
{
	Item *temp = B->head;

	int flag = 0;

	if (is_empty_Item_bucket(B)) {
		printf("��ٱ��ϰ� ����ֽ��ϴ�.\n");
	}
	else {
		while (temp != NULL)
		{
			if (strcmp(temp->Name, name) == 0)
			{

				if (temp->llink == NULL && temp->rlink != NULL)
				{
					B->head = temp->rlink;
					temp->rlink->llink = NULL;
					free(temp);
					flag = 1;
					break;
				}
				else if (temp->rlink == NULL && temp->llink != NULL)
				{
					B->rear = temp->llink;
					temp->llink->rlink = NULL;
					free(temp);
					flag = 1;
					break;
				}
				else if (temp->rlink == NULL && temp->llink == NULL)
				{
					B->head = NULL;
					B->rear = NULL;
					free(temp);
					flag = 1;
					break;
				}
				else
				{
					temp->rlink->llink = temp->llink;
					temp->llink->rlink = temp->rlink;
					free(temp);
					flag = 1;
					break;
				}
			}
			temp = temp->rlink;
		}
	}

	if (flag == 0)
		printf("��ٱ��Ͽ� �ش� ��ǰ�� ���� ������ �� �����ϴ�.\n");

}

// ��ٱ��ϸ� ����ִ� �Լ�
void empty_out_Bucket(Item_bucket_Header *B)
{
	
	Item *point_B = B->rear;

	while (point_B != NULL)
	{
		point_B = point_B->llink;
		free(B->rear);
		B->rear = point_B;
	}

	B->rear = NULL;
	B->head = NULL;

	free(point_B);

	
}

// bucket�� ��� �ִ� ǰ��� ���
void print_Bucket(Item_bucket_Header *B)
{
	Item *point_B = B->head;

	printf("  Item Bucket Contents\n\n");
	printf("|		Name		|\n");

	if (is_empty_Item_bucket(B))
		printf("Bucket is empty now\n");
	else
	{
		while (point_B != NULL)
		{
			printf("|		%s		|\n", point_B->Name);

			point_B = point_B->rlink;
		}
	}

	printf("\n\n");
}