#include <stdio.h>
#include <string.h>

#define maxaccounts 100  

struct account {
    char accountid[20];   
    char fullname[50];    
    char phone[15];      
    char password[20];    
    float balance;        
    int status;           
};

int checkId(struct account accounts[], int n, char id[]) {
    for (int i = 0; i < n; i++) {                     
        if (strcmp(accounts[i].accountid, id) == 0)   
            return 1;                                 
    }
    return 0;
}

int addAccount(struct account accounts[], int n) {
    if (n >= maxaccounts) {                     
        printf("Danh sach tai khoan da day\n");
        return n;                               
    }

    char id[20];                       
    while (1) {
        printf("\nNhap ID tai khoan: ");
        scanf("%s", id);                        
        getchar();                              

        if (strlen(id) == 0) {                  
            printf("ID khong duoc rong, nhap lai.\n");
            continue;
        }

        if (checkId(accounts, n, id)) {     
            printf("ID da ton tai, nhap lai.\n");
            continue;
        }

        break;                                   
    }

    strcpy(accounts[n].accountid, id);           

    printf("Nhap ho ten: ");
    fgets(accounts[n].fullname, 50, stdin);      
    accounts[n].fullname[strcspn(accounts[n].fullname, "\n")] = 0;

    printf("Nhap so dien thoai: ");
    fgets(accounts[n].phone, 15, stdin);
    accounts[n].phone[strcspn(accounts[n].phone, "\n")] = 0;

    char pass[20];
    while (1) {
        printf("Nhap mat khau: ");
        fgets(pass, sizeof(pass), stdin);
        pass[strcspn(pass, "\n")] = 0;

        if (strlen(pass) == 0) {
            printf("Mat khau khong duoc rong\n");
            continue;
        }
        break;
    }
    strcpy(accounts[n].password, pass);         

    accounts[n].balance = 0;                     
    accounts[n].status = 1;                      

    printf("Them tai khoan thanh cong!\n");
    return n + 1;                                
}

void updateAccount(struct account accounts[], int n) {
    char id[20];
    printf("\nNhap ID tai khoan can cap nhat: ");
    scanf("%s", id);
    getchar();

    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(accounts[i].accountid, id) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Khong tim thay ID tai khoan\n");
        return;
    }

    char pass[20];
    printf("Nhap mat khau de cap nhat: ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = 0;

    if (strcmp(accounts[pos].password, pass) != 0) {
        printf("Sai mat khau! Khong the cap nhat.\n");
        return;
    }

    printf("\n=== Thong tin hien tai ===\n");
    printf("Ho ten: %s\n", accounts[pos].fullname);
    printf("So dien thoai: %s\n", accounts[pos].phone);

    char newname[50], newphone[15];
    printf("Nhap ho ten moi (de trong neu giu nguyen): ");
    fgets(newname, 50, stdin);
    newname[strcspn(newname, "\n")] = 0;

    printf("Nhap so dien thoai moi (de trong neu giu nguyen): ");
    fgets(newphone, 15, stdin);
    newphone[strcspn(newphone, "\n")] = 0;

    if (strlen(newname) > 0)
        strcpy(accounts[pos].fullname, newname);

    if (strlen(newphone) > 0)
        strcpy(accounts[pos].phone, newphone);

    printf("Cap nhat thanh cong!\n");
}

void deleteandlock(struct account accounts[], int *n) {
    char id[20];
    printf("\nNhap ID tai khoan can thao tac: ");
    scanf("%s", id);
    getchar();

    int pos = -1;
    for (int i = 0; i < *n; i++) {
        if (strcmp(accounts[i].accountid, id) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Khong tim thay tai khoan\n");
        return;
    }

    printf("Chon thao tac cho tai khoan %s:\n", id);
    printf("1 = Khoa tai khoan\n");
    printf("2 = Xoa tai khoan\n");
    printf("0 = Huy\n");
    int lua_chon;
    scanf("%d", &lua_chon);
    getchar();

    if (lua_chon == 0) {
        printf("Huy thao tac\n");
        return;
    } else if (lua_chon == 1) {
        accounts[pos].status = 0;
        printf("Khoa tai khoan thanh cong!\n");
    } else if (lua_chon == 2) {
        for (int i = pos; i < *n - 1; i++) {
            accounts[i] = accounts[i + 1];
        }
        (*n)--;
        printf("Xoa tai khoan thanh cong!\n");
    } else {
        printf("Lua chon khong hop le\n");
    }
}

void search(struct account accounts[], int n) {
    char id[20];
    printf("\nNhap ID tai khoan can tim: ");
    scanf("%s", id);
    getchar();

    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(accounts[i].accountid, id) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Khong tim thay tai khoan\n");
        return;
    }

    printf("\n=== Thong tin tai khoan ===\n");
    printf("ID: %s\n", accounts[pos].accountid);
    printf("Ho ten: %s\n", accounts[pos].fullname);
    printf("So dien thoai: %s\n", accounts[pos].phone);
    printf("So du: %.2f\n", accounts[pos].balance);
    printf("Trang thai: %s\n", accounts[pos].status == 1 ? "Active" : "Inactive");
}

int main() {
    struct account accounts[maxaccounts];
    int n = 0;
    int chon;

    while (1) {
        printf("\n===== MENU =====\n");
        printf("1. Them tai khoan\n");
        printf("2. Cap nhat tai khoan\n");
        printf("3. Khoa/Xoa tai khoan\n");
        printf("4. Tim kiem tai khoan\n");
        printf("0. Thoat\n");
        printf("Chon: ");
        scanf("%d", &chon);
        getchar();

        if (chon == 1) {
            n = addAccount(accounts, n);
        } else if (chon == 2) {
            updateAccount(accounts, n);
        } else if (chon == 3) {
            deleteandlock(accounts, &n);
        } else if (chon == 4) {
            search(accounts, n);
        } else if (chon == 0) {
            printf("Thoat chuong trinh\n");
            break;
        } else {
            printf("Lua chon khong hop le\n");
        }
    }

    return 0;
}

