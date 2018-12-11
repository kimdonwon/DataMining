#include "common.h"
#include "Updator.h"

// ���� bucket�� �����ϴ� ǰ����� hit���� ������Ʈ ���ش�.
// �� ��, �ش� ǰ���� ���� ��ǰ���� weight ���� ������Ʈ ���ش�.
void hit_update(Item_Header *I, Item_bucket_Header *B)
{
	Item *point_I = I->head;
	Item *point_B = B->head;

	while (point_I != NULL)
	{
		while (point_B != NULL)
		{
			if (strcmp(point_I->Name, point_B->Name) == 0)
			{
				point_I->Hit++;
				if(point_I->related!=NULL)
				weight_update(point_I->related, B);
			}
			point_B = point_B->rlink;
		}
		point_B = B->head;
		point_I = point_I->rlink;
	}
}

// weight���� ������Ʈ ���ִ� �Լ�
// bucket�� �����ϴ� ��ǰ ��, ���� ������ ����Ʈ�� �����ϴ� ǰ���� 
// weight���� ������Ʈ 
void weight_update(related_ItemList_Header *R, Item_bucket_Header *B)
{
	related_ItemList *point_R = R->head;
	Item *point_B = B->head;

	while (point_R != NULL)
	{
		while (point_B != NULL)
		{
			if (strcmp(point_R->item->Name, point_B->Name) == 0)
			{
				point_R->weight++;
			}
			point_B = point_B->rlink;
		}
		point_B = B->head;
		point_R = point_R->rlink;
	}

}

// target_Item�� ���� ����Ʈ�� bucket�� �����ϴ� ���� ǰ����� �߰�/������Ʈ ���ִ� �Լ�
// �������� �ʴ°�쿡�� �߰� (hit, weight�� ������Ʈ�� hit / weight update�Լ����� ���� ����)
// �߰� �ϴ� ��쿡�� hit, weight�� �⺻ ���� ������ �߰� ���ָ�,
// ���� �������� item field�� �ش� ǰ����� Item List I���� �˻����־� 
// �ּҰ��� �־��ش�.
void related_Item_Update(Item *target_Item, Item_Header *I, Item_bucket_Header *B)
{
	
	
	Item *point_I = I->head;
	Item *point_B = B->head;
	

	if (target_Item->llink != NULL) {
		target_Item->llink->rlink = NULL;
		B->head = target_Item;
		target_Item->llink = NULL;
		B->rear->rlink = point_B;
		point_B->llink = B->rear;
		B->rear = point_B;
	}

	
	

	point_B = B->head;
	point_I = I->head;
	while (point_I != NULL)
	{
		if (strcmp(point_I->Name, point_B->Name) == 0) {
			if (point_I->related == NULL) {
				related_ItemList_Header *rih = (related_ItemList_Header*)malloc(sizeof(related_ItemList_Header));
				related_ItemList *ri = (related_ItemList*)malloc(sizeof(related_ItemList));
				related_ItemList *temp = ri;
				point_I->related = rih;
				rih->head = rih->rear = ri;

				Item *point_B2 = B->head->rlink;
				while (point_B2 != NULL) {
					Item *point_I2 = I->head;
					while (point_I2 != NULL) {
						if (strcmp(point_I2->Name, point_B2->Name) == 0) {
							break;
						}
						point_I2 = point_I2->rlink;
						
					}
					temp->item = point_I2;
					temp->weight = 1;
					temp->distance = 100;
					related_ItemList *ri2 = (related_ItemList*)malloc(sizeof(related_ItemList));
					temp->rlink = ri2;
					if (point_B2->rlink == NULL)
						temp->rlink = NULL;
					temp = ri2;
					point_B2 = point_B2->rlink;
				}
			}
			else {

				Item *point_B = B->head->rlink;

				while (point_B != NULL)
				{
					related_ItemList *point_R = point_I->related->head;
					int flog = 0;
					while (point_R!=NULL) {
						if (strcmp(point_R->item->Name, point_B->Name) == 0) {
							flog = 1;
							break;
						}
						if (point_R->rlink == NULL)break;
						point_R = point_R->rlink;
					}

					if (flog == 0) {
						related_ItemList *ri2 = (related_ItemList*)malloc(sizeof(related_ItemList));
						ri2->item = point_B;
						ri2->weight = 1;
						ri2->distance = 100;
						ri2->rlink = NULL;
						point_R->rlink = ri2;
					}
					
					point_B = point_B->rlink;
				}
			}
			break;
		}
		point_I = point_I->rlink;
	}

	// ���� ��Ʈ
}

// �����۸���Ʈ�� �����ϴ� �����۵���
// hit���� �������� �Ա��κ����� �Ÿ��� �缳�����ִ� �Լ�
void distanceFromEntrance_update(Item_Header *I)
{
	Item *point_I = I->head;

	while (point_I != NULL)
	{
		point_I->distance_fromEntrance /= point_I->Hit;
		point_I->distance_fromEntrance *= 10;

		point_I = point_I->rlink;
	}
}