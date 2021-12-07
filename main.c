#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct user_info {
    char std_No[100];
    char name[100];
    char contact[100];
    char time[100];
}user_info;

typedef struct node {
    struct user_info info;
    struct node* next;  
}node;

void menu() {
    printf("��� ���� ���α׷��Դϴ�.\n\n");
    printf("1. ��û�ϱ�\n");
    printf("2. ��û ���� �����ϱ�\n");
    printf("3. �����ϱ�(�����ڿ�)\n");
    printf("4. ��û��� ����(�����ڿ�)\n");
    printf("5. ��й�ȣ �����ϱ�(�����ڿ�)\n");
    printf("6. ����\n\n");
}

char loc_time[100];

char* update_time() {
    time_t now_t;
    struct tm *now_d;
    time(&now_t);
    now_d = localtime(&now_t);
    strcpy(loc_time, asctime(now_d));

    return loc_time;
}

node* add_node(char* (*fp) (void)) {
    node* new = (node*)malloc(sizeof(node));
    printf("�й�: ");
    scanf("%s", (new -> info).std_No);
    printf("�̸�: ");
    scanf("%s", (new -> info).name);
    printf("��ȭ��ȣ: ");
    scanf("%s", (new -> info).contact);
    char* t = update_time();
    strcpy((new -> info).time, t);
    new -> next = NULL;

    return new;
}

void add(node** phead, node* new) {
    node* p1 = *phead;
    node* p2 = NULL;

    if (*phead == NULL) {
        *phead = new;
        new -> next = NULL;
    }
    else {
        while (p1 != NULL) {
            p2 = p1;
            p1 = p1 -> next;
        }

        p1 = new;
        p2 -> next = p1;        
    }
}

node* find(node* phead) {
    node* p = phead;
    user_info info;

    printf("�й�: ");
    scanf("%s", info.std_No);

    while (p == NULL) {
        if(!strcmp(p -> info.std_No, info.std_No)) {
            return p;
        }
        p = p -> next;
    }
}

int admin_access() {
    char pw[100];
    char password[100];

    FILE* fp = fopen("password.txt", "rt");

    fgets(password, 100, fp);
    
    printf("������ ��忡 �����߽��ϴ�.\n");
    printf("��й�ȣ: ");
    scanf("%s", &pw);

    if (atoi(pw) == atoi(password)) {
        printf("���� ����\n\n");
        return 1;
    }
    else {
        printf("���� ����\n\n");
        return 0;
    }
}

void delete(node** phead, node* del, int mode) {
    if (mode == 1) {
        node* p1 = *phead;
        node* p2 = NULL;

        if(p1 == NULL) {
            return;
        }
        else {
            if (p1 == del) {
                p1 = p1 -> next;
                free(del);
            }
            else {
                while (p1 != NULL) {
                    if (p1 == del) {
                        p2 -> next = del -> next;
                        free(del);

                        return;
                    }
                    p2 = p1;
                    p1 = p1 -> next;
                }
                
            }
        }
    }
    else if (mode == 2) {
        if (admin_access() == 1) {
            node* p1 = *phead;
            node* p2 = NULL;

            if(p1 == NULL) {
                return;
            }
            else {
                if (p1 == del) {
                    p1 = p1 -> next;
                    free(del);
                }
                else {
                    while (p1 != NULL) {
                        if (p1 == del) {
                            p2 -> next = del -> next;
                            free(del);

                            return;
                        }
                        p2 = p1;
                        p1 = p1 -> next;
                    }
                    
                }
            }
        }
    }
}

void listup(node* head) {
    if (admin_access() == 1) {
        int n = 1;
        node* p = head;
        
        printf("��û�� ����� ����մϴ�.\n");
        while (p != NULL) {
            printf("-%d-\n", n);
            printf("�й�: %s\n", (p -> info).std_No);
            printf("�̸�: %s\n", (p -> info).name);
            printf("��ȭ��ȣ: %s\n", (p -> info).contact);
            printf("��û�ð�: %s\n\n", (p -> info).time);
            p = p -> next;
            n++;
        }
    }
}

void save(node* phead) {
    node* p = phead;
    int n = '1';

    FILE* fp = fopen("DB.txt", "wt");

    if (p == NULL) {
        return;
    }
    else {
        while (p != NULL) {
            fputc(n, fp);
            fputs("\n", fp);

            fputs("�й�: ", fp);
            fputs((p -> info).std_No, fp);
            fputs("\n", fp);

            fputs("�̸�: ", fp);
            fputs((p -> info).name, fp);
            fputs("\n", fp);

            fputs("��ȭ��ȣ: ", fp);
            fputs((p -> info).contact, fp);
            fputs("\n", fp);

            fputs("��û�ð�: ", fp);
            fputs((p -> info).time, fp);
            p = p -> next;
            n++;
        }
    }
    fclose(fp);

    return;
}

/* void update(node** phead, node* head) {
    char answer[10];
    node* p = *phead;

    printf("����! ��û ���� ���� �� ������ �ڷ� �и��� �˴ϴ�.\n");
    printf("�׷��� �Ͻðڽ��ϱ�? (Y/N): ");
    scanf("%s", &answer);

    if (strcmp(answer, "Y") || strcmp(answer, "y")) {
        delete(p, find(head), 1);
        add(p, add_node(update_time()));
        return;
    }
    else if (strcmp(answer, "N") || strcmp(answer, "n")) {
        printf("����߽��ϴ�.\n");
        return;
    }
    else {
        printf("�Է� �����Դϴ�. Y �Ǵ� N �߿� �Է����ּ���.\n");
        return;
    }
}*/

void change_pw() {
    if (admin_access() == 1) {
        char password[100];

        FILE* fp = fopen("password.txt", "wt");
        printf("������ ��й�ȣ�� �Է��Ͻÿ�: ");
        scanf("%s", &password);
        fputs(password, fp);
        fclose(fp);
        printf("���� ����\n");
    }

    return;
}


int main() {
    node* head = NULL;
    int n = 0;
    int i = 0;

    update_time();

    FILE* fp = fopen("DB.txt", "rt");

    if (fp == NULL) {
        printf("Failed to open file %s\n","DB.txt");
        
        return -1;
    }
    
    int line = 0;

    while (feof(fp) == 0) {
        char ch;
        ch = fgetc(fp);
        if (ch == ':') {
            char std_No[100];
            char name[100];
            char contact[100];
            char time[100];
            
            if (line % 4 == 0) {
                fgets(std_No, sizeof(std_No), fp);
            }
            else if (line % 4 == 1) {
                fgets(name, sizeof(name), fp);
            }
            else if (line % 4 == 2) {
                fgets(contact, sizeof(contact), fp);
            }
            else if (i % 4 == 3) {
                node* new = (node*)malloc(sizeof(node));
                new -> next = NULL;
                
                fgets(time, sizeof(time), fp);

                for (i = 0; i < 100; i++) {
                    if (std_No[i] == '\n') {
                        std_No[i] = 0;
                    }
                    if (name[i] == '\n') {
                        name[i] = 0;
                    }
                    if (contact[i] == '\n') {
                        contact[i] = 0;
                    }
                    if (time[i] == '\n') {
                        time[i];
                    }
                }
                strncpy((new -> info).std_No, std_No, sizeof((new -> info).std_No));
                strncpy((new -> info).name, name, sizeof((new -> info).name));
                strncpy((new -> info).contact, contact, sizeof((new -> info).contact));
                strncpy((new -> info).time, time, sizeof((new -> info).time));
                add(&head, new);
            }
            line++;
        }
    }
    fclose(fp);

    while (1) {
        menu();

        printf("�޴��� �����Ͻÿ�: ");
        scanf("%d", &n);

        switch (n) {
        case 1:
            add(&head, add_node(update_time));
            break;
        case 2:
            //update(&head, head);
            break;
        case 3:
            delete(&head, find(head), 2);
            break;
        case 4:
            listup(head);
            break;
        case 5:
            change_pw();
            break;
        case 6:
            save(head);
            break;
        }

        if (n == 6) {
            break;
        }
    }
    
    return 0;
}