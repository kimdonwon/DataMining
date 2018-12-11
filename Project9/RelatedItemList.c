#include "common.h"
#include "RelatedItemList.h"

// ������ ����Ʈ�� �پ� �ִ� ���� ������ ����Ʈ�� ����ִ��� Ȯ��
int is_empty_related_ItemList(related_ItemList_Header *R)
{
	return (R->head == NULL);
}

// ������ � ǰ�� ����� �ּҰ� ���� ������ ����Ʈ���� item�ڸ��� �����ϴ��� Ȯ��
int is_inRelatedItemList(related_ItemList_Header *R, Item *certain_item)
{
	related_ItemList *point_R = R->head;

	int flag = 0;

	while (point_R != NULL)
	{
		if (strcmp(point_R->item->Name, certain_item->Name) == 0)
		{
			flag = 1;
			return 1;
		}

		point_R = point_R->rlink;
	}

	if (flag == 0)
		return 0;
}

// �ش� �����ۿ� �����Ǿ� �ִ� ���� �����۵���
// weight�� �������� ������������ ��ŷ���ִ� �Լ�
// ȭ�� ��±��� �� �Լ� ������ ���ش�.
void related_Item_Ranking(Item *target_Item)
{
	if (target_Item->related == NULL)return;
	related_ItemList *point_R = target_Item->related->head;
	printf("  %s 's Related Item List Contents\n\n", target_Item->Name);
	printf("|     name     Hit     Weight     Distance     |\n");
	while (point_R != NULL) {
		printf("|     %s     %d     %d     %d     |\n", point_R->item->Name, point_R->item->Hit, point_R->weight, point_R->distance);
		point_R = point_R->rlink;
	}
	// ���� ��Ʈ
}

// �ش� ǰ�� �����ϴ� ���� �����۵��� ������ִ� �Լ�
void print_relatedItemList(related_ItemList_Header *R, Item *target_Item)
{
	related_ItemList *point_R = R->head;

	printf("  %s 's Related Item List Contents\n\n", target_Item->Name);
	printf("|	name		Hit		Weight		Distance	|\n", point_R->item->Name, point_R->item->Hit, point_R->weight);

	if (R->head == NULL)
		printf("Item List is empty now\n");
	else
	{
		while (point_R != NULL)
		{
			printf("|	%s		%d		%d		%d		|\n", point_R->item->Name, point_R->item->Hit, point_R->weight, point_R->distance);

			point_R = point_R->rlink;
		}
	}

	printf("\n\n");
}