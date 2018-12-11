#include "common.h"
#include "Item.h"
#include "RelatedItemList.h"

// ������ ����Ʈ�� �ʱ�ȭ���ִ� �Լ�
void init_Item(Item_Header *I)
{
	I->head = I->rear = NULL;
}

// ������ ����Ʈ�� ����ִ��� Ȯ��
int is_empty_Item(Item_Header *I)
{
	return (I->head == NULL);
}

// ������ � ������(ǰ��)�� ������ ����Ʈ�� �����ϴ��� �˻����ִ� �Լ�
int is_inItemList(Item_Header *I, Item *certain_item)
{
	Item *point_I = I->head;

	int flag = 0;

	while (point_I != NULL)
	{
		if (strcmp(point_I->Name, certain_item->Name) == 0)
		{
			flag = 1;
			return 1;
		}

		point_I = point_I->rlink;
	}

	if (flag == 0)
		return 0;
}

// Item List I�� ��ٱ���(B)�� �����ϴ� ǰ����� �߰����ִ� �Լ�.
// �� ��, �ϳ��� ǰ����� �����ϸ鼭 �� ǰ���� I�� �����ϴ��� Ȯ���ؾ� �ϸ�
// �� ������ bucket�� ��� �ִ� ���� �����۵��� ������Ʈ ����� ��(related_Item_Update�Լ� ���)
// ����, bucket�� ��� �ִ� ������ �� ������ ����Ʈ I�� ���� ���� �ִٸ� �߰����־�� �Ѵ�.
void insert_toItemList(Item_Header *I, Item_bucket_Header *B)
{
	Item *point_B = B->head;
	Item *point_I = I->head;
	

	if (is_empty_Item(I))
	{
		Item *temp = (Item*)malloc(sizeof(Item));
		*temp = *point_B;
		I->head = temp;
		I->rear = temp;
		
		point_B = point_B->rlink;
		while (point_B != NULL) {
			Item *temp2 = (Item*)malloc(sizeof(Item));
			*temp2 = *point_B;
			I->rear->rlink = temp2;
			temp2->llink = I->rear;
			I->rear = temp2;

			point_B = point_B->rlink;

		}
	
		point_B = B->head;
		point_I = I->head;
		char *tm = B->rear->Name;
		while (point_B != NULL) {
			related_Item_Update(point_B, I, B);
			if (strcmp(tm, point_B->Name) == 0)break;
			point_B = point_B->rlink;
		}
		
	}
	else
	{
		char *tm = B->rear->Name;
		while (point_B != NULL)
		{
			int flog = 0;
			point_I = I->head;
			while (point_I != NULL)
			{
				if (strcmp(point_I->Name, point_B->Name) == 0) {
					related_Item_Update(point_B,I,B);
					flog = 1;
					}
				if (point_I->rlink == NULL)break;
				point_I = point_I->rlink;
			}

			if (flog == 0) {
				Item *temp = (Item*)malloc(sizeof(Item));
				*temp = *point_B;
				I->rear->rlink = temp;
				temp->llink = I->rear;
				I->rear = temp;
				related_Item_Update(point_B, I, B);
				
				
			}
			
			if (strcmp(tm, point_B->Name) == 0)break;
			point_B = point_B->rlink;
		}

		
		
		
	}
	// ���� ��Ʈ
}

// ������ ����Ʈ�鿡 �����ϴ� ���� �����۵��� ǰ����
// �Ÿ��� �������� �缳�����ִ� �Լ�
// ǰ���� �Ÿ��� �����ȴ�.(�����ۿ� �����ϴ� ���� �����۸���)
void reset_Item_Distance(Item_Header *I)
{
	// ���� ��Ʈ
}

// Item����Ʈ�� ��� �ִ� ǰ��� ���
void print_ItemList(Item_Header *I)
{
	Item *point_I = I->head;

	printf("  Purchased Item List Contents\n\n");
	printf("|	Name		Hit		Distance(Entrance)|\n");

	if (is_empty_Item(I))
		printf("Item List is empty now\n");
	else
	{
		while (point_I != NULL)
		{
			printf("|	%s		%d		%d		|\n", point_I->Name, point_I->Hit, point_I->distance_fromEntrance);

			point_I = point_I->rlink;
		}
	}

	printf("\n\n");
}