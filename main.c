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
    printf("행사 관리 프로그램입니다.\n\n");
    printf("1. 신청하기\n");
    printf("2. 신청 정보 수정하기(준비중)\n");
    printf("3. 삭제하기(관리자용)\n");
    printf("4. 신청명단 보기(관리자용)\n");
    printf("5. 비밀번호 변경하기(관리자용)\n");
    printf("6. 종료\n\n");
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
    printf("학번: ");
    scanf("%s", (new -> info).std_No);
    printf("이름: ");
    scanf("%s", (new -> info).name);
    printf("전화번호: ");
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

    printf("학번: ");
    scanf("%s", info.std_No);

    while (p != NULL) {
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
    
    printf("관리자 모드에 진입했습니다.\n");
    printf("비밀번호: ");
    scanf("%s", pw);

    if (atoi(pw) == atoi(password)) {
        printf("진입 성공\n\n");
        return 1;
    }
    else {
        printf("진입 실패\n\n");
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
                *phead = (*phead) -> next;
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
                    *phead = (*phead) -> next;
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
        
        printf("신청자 명단을 출력합니다.\n");
        while (p != NULL) {
            printf("-%d-\n", n);
            printf("학번: %s\n", (p -> info).std_No);
            printf("이름: %s\n", (p -> info).name);
            printf("전화번호: %s\n", (p -> info).contact);
            printf("신청시간: %s\n\n", (p -> info).time);
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

            fputs("학번:", fp);
            fputs((p -> info).std_No, fp);
            fputs("\n", fp);

            fputs("이름:", fp);
            fputs((p -> info).name, fp);
            fputs("\n", fp);

            fputs("전화번호:", fp);
            fputs((p -> info).contact, fp);
            fputs("\n", fp);

            fputs("신청시간:", fp);
            fputs((p -> info).time, fp);
            p = p -> next;
            n++;
        }
    }
    fclose(fp);

    return;
}

/* void update(node* head) {
    
}*/

void change_pw() {
    if (admin_access() == 1) {
        char password[100];

        FILE* fp = fopen("password.txt", "wt");
        printf("변경할 비밀번호를 입력하시오: ");
        scanf("%s", password);
        fputs(password, fp);
        fclose(fp);
        printf("변경 성공\n");
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
        char a;
        a = fgetc(fp);
        if (a == ':') {
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
            else if (line % 4 == 3) {
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
        char answer[10];
        menu();

        printf("메뉴를 선택하시오: ");
        scanf("%d", &n);

        switch (n) {
        case 1:
            add(&head, add_node(update_time));
            break;
        case 2:
            printf("주의! 신청 정보 수정 시 순서가 뒤로 밀리게 됩니다.\n");
            printf("그래도 하시겠습니까? (Y/N): ");
            scanf("%s", answer);

            if (strcmp(answer, "Y") || strcmp(answer, "y")) {
                delete(&head, find(head), 1);
                add(&head, add_node(update_time));
            }
            else if (strcmp(answer, "N") || strcmp(answer, "n")) {
                printf("취소했습니다.\n");
            }
            else {
                printf("입력 오류입니다. Y 또는 N 중에 입력해주세요.\n");
            }
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