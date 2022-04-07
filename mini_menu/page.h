#ifndef __PAGE_H
#define __PAGE_H

typedef struct _page PAGE;

typedef struct _page_item  //��Ŀ����
{
    char item_name[24];
    char item_type;
    char item_value[20];
    PAGE *next_page;         //��һ��page

}PAGE_ITEM;

typedef int (*PAGE_SHOW)(PAGE *page);

struct _page
{
    char page_name[24];
    int item_index ;
    int items_size;

    PAGE_ITEM *items;   //������Ŀ������
    PAGE_SHOW show;    //��ʾ������;
    PAGE *parent_page; //ǰһ������
};


int main_show(PAGE *page);
PAGE main_page ;

#endif
