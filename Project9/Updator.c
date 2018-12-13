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
	
		// ���� ǰ���� �߰��� �� I�� �ּҷ� �߰��� ( hit update�Լ����� I�� ���� �÷��ֱ� ����)
		while (point_I != NULL) {
			if (strcmp(point_I->Name, target_Item->Name) == 0) {
				//I�� ���� ǰ���� ó�� ������ ��
				if (point_I->related == NULL) {
					related_ItemList_Header *rih = (related_ItemList_Header*)malloc(sizeof(related_ItemList_Header));
					point_I->related = rih;
					rih->head = rih->rear = NULL;

					Item *tempb = B->head;
					if (strcmp(point_I->Name, tempb->Name) == 0) {
						tempb = tempb->rlink;
					}
					related_ItemList *ri = (related_ItemList*)malloc(sizeof(related_ItemList));
					//���� ǰ�� �����͸� ó�� �߰���
					Item *Itemp = I->head;
					while (Itemp != NULL) {
						if (strcmp(Itemp->Name, tempb->Name) == 0)break;
						Itemp = Itemp->rlink;
					}
					ri->item = Itemp;
					ri->weight = 0;
					ri->distance = 100;
					ri->rlink = ri->llink = NULL;
					rih->head = rih->rear = ri;
					tempb = tempb->rlink;
					//���� ǰ�� �����͸� �߰���
					while (tempb != NULL) {
						if (strcmp(point_I->Name, tempb->Name) != 0) {
							related_ItemList *ri = (related_ItemList*)malloc(sizeof(related_ItemList));
							Item *Itemp = I->head;
							while (Itemp != NULL) {
								if (strcmp(Itemp->Name, tempb->Name) == 0)break;
								Itemp = Itemp->rlink;
							}
							ri->item = Itemp;
							ri->weight = 0;
							ri->distance = 100;
							ri->rlink = ri->llink = NULL;
							rih->rear->rlink = ri;
							ri->llink = rih->rear;
							rih->rear = ri;
						}
						tempb = tempb->rlink;
					}
				}
				else {
					//���� ǰ���� �̹� ������� ���� �� �ߺ��� ã��, �ߺ��� �����Ͱ� ������ �߰���
					search_relatedItemLocation(I->head->related, point_I, I, B);
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