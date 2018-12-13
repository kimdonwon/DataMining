#include "common.h"
#include "Searcher.h"

// ������ � �������� ������ ����Ʈ�� �����ϴ��� Ȯ���Ͽ� ��ġ�� ��ȯ.
// ���ٸ�, �ش� �������� ������ ����Ʈ�� �߰��ϰ� �߰����� ��ġ�� ��ȯ ���ִ� �Լ�
// ������ ����Ʈ�� �߰����ֱ� ���ؼ��� related_Item_Update�Լ� ����ؾ� �ϱ� ������
// Bucket Header�� �ʿ��ϴ�
Item* search_ItemLocation(Item_Header *I, Item *certain_Item, Item_bucket_Header *B)
{
	Item *point_I = I->head;
	Item *point_B = B->head;
	//I�� ó�� ���������
	if (is_empty_Item(I))
	{
		Item *temp = (Item*)malloc(sizeof(Item));
		temp->Name = point_B->Name;
		temp->Hit = point_B->Hit;
		temp->distance_fromEntrance = 10;
		temp->related = temp->llink = temp->rlink = NULL;

		I->head = temp;
		I->rear = temp;
		return temp;
	}
	// I���� �ߺ��� �����Ͱ� ���� ��
	while (point_I != NULL) {
		if (strcmp(certain_Item->Name, point_I->Name) == 0) {
			return point_I;
		}
		point_I = point_I->rlink;
	}
	// I�� �ߺ��� �����Ͱ� ���� �� ���� �߰�����
	Item *temp = (Item*)malloc(sizeof(Item));
	temp->Name = certain_Item->Name;
	temp->Hit = certain_Item->Hit;
	temp->distance_fromEntrance = 10;
	temp->related = temp->llink = temp->rlink = NULL;

	I->rear->rlink = temp;
	temp->llink = I->rear;
	I->rear = temp;
	return temp;
	// ���� ��Ʈ
}

// ������ � ���� �������� ���� ������ ����Ʈ�� �����ϴ��� Ȯ���Ͽ� ��ġ�� ��ȯ.
// ���ٸ�, �ش� ���� �������� ���� ������ ����Ʈ�� �߰��ϰ� �߰����� ��ġ�� ��ȯ ���ִ� �Լ�
// ���� ������ ����Ʈ�� �߰����ֱ� ���ؼ��� ������ ����Ʈ ������ �߰��ؾ� �ϴ� �������� ��ġ�� ã�ƾ� �ϱ�
// ������ search_ItemLocation�Լ��� �ʿ��Ͽ�, Item Header, Item Bucket Header�� �ʿ�
related_ItemList* search_relatedItemLocation(related_ItemList_Header *R, Item *point_I, Item_Header *I, Item_bucket_Header *B)
{
	Item *point_B = B->head;
	
	while (point_B != NULL) {
		int flog = 0;
		related_ItemList *temp = point_I->related->head;
		while (temp != NULL) {
			if (strcmp(point_B->Name, temp->item->Name) == 0) {
				flog = 1;
			}

			temp = temp->rlink;
		}
		if (strcmp(point_B->Name, point_I->Name) == 0)flog = 1;
		if (flog == 0) {
			related_ItemList *ri = (related_ItemList*)malloc(sizeof(related_ItemList));
			Item *Itemp = I->head;
			while (Itemp != NULL) {
				if (strcmp(Itemp->Name, point_B->Name) == 0)break;
				Itemp = Itemp->rlink;
			}
			ri->item = Itemp;
			ri->distance = 100;
			ri->weight = 1;
			ri->rlink = NULL;

			point_I->related->rear->rlink = ri;
			ri->llink = point_I->related->rear;
			point_I->related->rear = ri;

		}
		point_B = point_B->rlink;
	}
	// ���� ��Ʈ
}

// target_Item�� ��������� �Ͽ�, ��� ǰ���� �Ÿ��� �ľ��Ͽ�
// ������ ǰ������� �ִ� ��θ� ���ϰ� ������ִ� �Լ�(Djkstra �˰��� ����)
// �������� �������� �� ǰ������ �� �� �ִ� �Ÿ��� Ȯ���ϰ�,
// �ּڰ��� ����, �� �� ������ġ������ weight�� �հ� ������������ �Ÿ��� ���Ͽ�
// �� ���� ������ �ִܰ�� ����.

// distance�� ��� �ִ� ����Ʈ�� �����Ͽ�, �ش� ����Ʈ�� �ڱ��ڽ��� ������
// ������ �Ҵ��ϰ� �̸� ��� ������Ʈ ���־�, ��� ���������� �ִܰ�θ� �����Ѵ�.
void shortest_path(Item *target_Item, Item_Header *I)
{
	//���ͽ�Ʈ�� �˰��� ���� ����Ʈ ����
	Item_distanceList_Header *idh = (Item_distanceList_Header*)malloc(sizeof(Item_distanceList_Header));
	idh->all_checked = 0;
	idh->head = idh->rear = NULL;
	Item *i = I->head;
	int count = 0;
	while (i != NULL) {
		count++;
		i = i->rlink;
	}
	related_ItemList *rl = target_Item->related->head;
	Item_distanceList *temp = (Item_distanceList*)malloc(sizeof(Item_distanceList));
	temp->name = target_Item->Name;
	temp->distance = 0;
	temp->found = 1;
	temp->possible = 0;
	temp->rlink = temp->llink = NULL;
	idh->head = idh->rear = temp;
	
	// ���ͽ�Ʈ�� �˰��� ���� ����Ʈ�� �ʱ� �����͸� �־���
	while (rl != NULL) {
		Item_distanceList *temp = (Item_distanceList*)malloc(sizeof(Item_distanceList));
		temp->name = rl->item->Name;
		temp->distance = rl->distance;
		temp->found = 0;
		temp->possible = 0;
		temp->rlink = temp->llink = NULL;
		idh->rear->rlink = temp;
		temp->llink = idh->rear;
		idh->rear = temp;
		rl = rl->rlink;
	}

	// ���� ó�� �ּ� �Ÿ��� ã����
	Item_distanceList *point_rl = idh->head->rlink;
	Item_distanceList *temp_rl = idh->head->rlink;
	while (point_rl != NULL) {
		if (temp_rl->distance > point_rl->distance)temp_rl = point_rl;
		point_rl = point_rl->rlink;
	}
	point_rl = idh->head->rlink;
	// �ּ� �Ÿ��� �ִ� ��带 �������� �ּ� �Ÿ��� ã����
	while (point_rl != NULL) {
		temp_rl = distance_update(idh, temp_rl, I);
		if (temp_rl == idh->head)break;
		point_rl = point_rl->rlink;
	}

	point_rl = idh->head->rlink;
	while (point_rl != NULL) {
		printf("%s�κ��� %sǰ������� �ִܰŸ��� %d�Դϴ�.\n", target_Item->Name, point_rl->name, point_rl->distance);
		point_rl = point_rl->rlink;
	}
	
	// ���� ��Ʈ
}