#include "common.h"
#include "ItemDistance.h"

// distance�� ��� �ִ� ����Ʈ�� ����� ���ڷ� �޾�, ���� ǰ�� ���� ���� �Ÿ�����
// ���Ͽ� �ּ��� ��ġ���� ��� ������Ʈ ���ִ� �Լ��̴�. 
// ������Ʈ �ϱ� ���������� weight�� ���ڷ� �޾� �ѱ��.
Item_distanceList* distance_update(Item_distanceList_Header *D, Item_distanceList *min_pos, Item_Header *I)
{
	int tempdis = min_pos->distance;
	min_pos->found = 1;
	Item *point_I = I->head;
	Item *temp_I;
	//���� ǰ�� ����� ��带 ã����
	while (point_I != NULL) {
		if (strcmp(point_I->Name, min_pos->name) == 0) {
			temp_I = point_I;
			break;
		}
		point_I = point_I->rlink;
	}
	related_ItemList *temp_R = temp_I->related->head;
	Item_distanceList *temp_id = D->head;
	while (temp_R != NULL) {
		int flog = 0;
		temp_id = D->head;
		while (temp_id != NULL) {
			//����� ���� ǰ���� �˻��Ͽ� �Ÿ��� �� ª���� ���� ������
			if (strcmp(temp_id->name, temp_R->item->Name) == 0) {
				if (temp_id->distance > temp_R->distance + tempdis) {
					temp_id->distance = temp_R->distance + tempdis;
				}
				flog = 1;
				break;
			}
			temp_id = temp_id->rlink;
		}
		// ����� ���� ǰ�� �߿� ���ο� ��ǰ�� ������ �߰�����
		if (flog == 0) {
			Item_distanceList *temp = (Item_distanceList*)malloc(sizeof(Item_distanceList));
			temp->name = temp_R->item->Name;
			temp->distance = temp_R->distance;
			temp->found = 0;
			temp->possible = 0;
			temp->rlink = temp->llink = NULL;
			D->rear->rlink = temp;
			temp->llink = D->rear;
			D->rear = temp;
			
		}
		temp_R = temp_R->rlink;
	}

	temp_id = D->head;
	Item_distanceList *tm=D->head;
	//�ּ� �Ÿ� �˻簡 ���� �����ʹ� found =1��, 
	// �˻簡 �ʿ��� ������ �߿� �ּ� �Ÿ� �����͸� ã�Ƽ� return�� 
	while (temp_id != NULL) {
		if (temp_id->found != 1 && tm->distance > temp_id->distance) {
			tm = temp_id;	
		}
		temp_id = temp_id->rlink;
	}
	return tm;
	// ���� ��Ʈ
}