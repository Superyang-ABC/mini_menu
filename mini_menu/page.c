#include "page.h"
#include "stdio.h"

#define nsizeof(n) (sizeof(n)/sizeof(n[0]))

int tab_page_show(PAGE *page);
char screem[512] ={0};
void clear_screem(void)
{
    memset(screem,0,sizeof(screem));
}
void write_screem(char * str,int len)
{   if(strlen(screem)+ len > sizeof(screem) -1)
   {
      len =   sizeof(screem) -1 - (strlen(screem)+ len);
      len = len > 0 ? len:0;
   }
    memcpy(screem+strlen(screem),str,len);
}
void show_screem(void)
{
    printf(screem);
}

PAGE marry_page ;
PAGE tomy_page ;
PAGE kamm_page ;

PAGE_ITEM MAIN_PAGE_ITEM[] =
{
    { "tomy",0,"15",&tomy_page},
    { "marry",0,"13",&marry_page},
    { "tomy",0,"15",0},
    { "tomy",0,"15",0},
    { "kamm",0,"15",&kamm_page},
};

PAGE_ITEM TOMY_PAGE_ITEM[] =
{
    { "q",0,"15",0},
    { "w",0,"13",0},
    { "e",0,"15",0},
    { "r",0,"15",0},
    { "t",0,"15",0},
};


PAGE_ITEM MARRY_PAGE_ITEM[] =
{
    { "h",0,"15",0},
    { "j",0,"13",0},
    { "k",0,"15",0},
    { "l",0,"15",0},
    { "m",0,"15",0},
};

PAGE_ITEM KAMM_PAGE_ITEM[] =
{
    { "1",0,"15",0},
    { "2",0,"13",0},
    { "3",0,"15",0},
    { "4",0,"15",0},
    { "5",0,"15",0},
};



PAGE marry_page = { "marry_page",0,nsizeof(TOMY_PAGE_ITEM),TOMY_PAGE_ITEM,&tab_page_show,0};
PAGE tomy_page = { "tomy_page",0,nsizeof(MARRY_PAGE_ITEM),MARRY_PAGE_ITEM,&tab_page_show,0};
PAGE kamm_page = { "kamm_page",0,nsizeof(KAMM_PAGE_ITEM),KAMM_PAGE_ITEM,&tab_page_show,0};

PAGE main_page = { "main_page",0,nsizeof(MAIN_PAGE_ITEM),MAIN_PAGE_ITEM,&tab_page_show,0};

int tab_page_show(PAGE *page)
{
    if(page == NULL)
    {
        printf("page is null\r\n");
        return -1;
    }
    int cnt = 0;

    clear_screem();
    sprintf(screem+strlen(screem),"************%s*************\r\n",page->page_name);

    for(int i = 0; i < page->items_size;i++)
    {
        sprintf(screem+strlen(screem),"%s   %s     value:%s\r\n",\
                page->item_index == i ? ">>" : "  ",\
                page->items[i].item_name,page->items[i].item_value);
    }
    sprintf(screem+strlen(screem),"***************************\r\n");
    show_screem();
    char cmd = 0;
    while(1)
    {
        cmd = getc(stdin);
        printf("getc:%c \r\n",cmd);
        switch(cmd)
        {
        case '1':
            page->item_index = (page->item_index +1) % page->items_size;
            printf("index:%d \r\n",page->item_index);
            clear_screem();
            sprintf(screem+strlen(screem),"************%s*************\r\n",page->page_name);

            for(int i = 0; i < page->items_size;i++)
            {
                sprintf(screem+strlen(screem),"%s   %s     value:%s\r\n",\
                        page->item_index == i ? ">>" : "  ",\
                        page->items[i].item_name,page->items[i].item_value);
            }
            sprintf(screem+strlen(screem),"***************************\r\n");
            show_screem();
            break;
        case '2':
            page->item_index = (page->item_index +page->items_size -1 ) % page->items_size;

            clear_screem();
            sprintf(screem+strlen(screem),"************%s*************\r\n",page->page_name);

            for(int i = 0; i < page->items_size;i++)
            {
                sprintf(screem+strlen(screem),"%s   %s     value:%s\r\n",\
                        page->item_index == i ? ">>" : "  ",\
                        page->items[i].item_name,page->items[i].item_value);
            }
            sprintf(screem+strlen(screem),"***************************\r\n");
            show_screem();
            break;
        case '3':
            if(page->parent_page)
            {
                page->parent_page->show(page->parent_page);
                return 1;
            }
            break;
        case '4':
            if(page->items[page->item_index].next_page)
            {
                page->items[page->item_index].next_page->parent_page = page;
                page->items[page->item_index].next_page->show(page->items[page->item_index].next_page);
                return 1;
            }
            break;
        default:
            break;
        }
    }

    return 0;

}
int main_show(PAGE * page)
{
    printf("**********main page************\r\n");
    printf("\r\n");
    printf("       version 1.0.1\r\n");
    printf("       date:2022.4.5\r\n");
    printf("enter any key into next page\r\n");
    printf("\r\n");
    printf("*******************************\r\n");

    main_page.show(&main_page);

    return 0;
}
