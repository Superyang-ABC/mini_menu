#ifndef __PAGE_H
#define __PAGE_H

typedef struct _page PAGE;

typedef struct _page_item  //条目属性
{
    char item_name[24];
    char item_type;
    char item_value[20];
    PAGE *next_page;         //下一级page

}PAGE_ITEM;

typedef int (*PAGE_SHOW)(PAGE *page);

struct _page
{
    char page_name[24];
    int item_index ;
    int items_size;

    PAGE_ITEM *items;   //所有条目，容器
    PAGE_SHOW show;    //显示处理函数;
    PAGE *parent_page; //前一个界面
};


int main_show(PAGE *page);
PAGE main_page ;

#endif
