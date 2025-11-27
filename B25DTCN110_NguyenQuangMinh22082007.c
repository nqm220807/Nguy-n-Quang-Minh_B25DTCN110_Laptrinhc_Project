#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define maxaccounts 100

struct account {
    char accountid[20];
    char fullname[50];
    char phone[15];
    float balance;
    int status;
};

int checkId(struct account accounts[], int n, char id[]);
int checkPhone(struct account accounts[], int n, char phone[]);
int addAccount(struct account accounts[], int n);
void updateAccount(struct account accounts[], int n);
void deleteandlock(struct account accounts[], int n);
void search(struct account accounts[], int n);
void showPagination(struct account accounts[], int n);
void sortAccounts(struct account accounts[], int n);
void toLowerCopy(char src[], char dest[], int size);

int main() {
    struct account accounts[maxaccounts];
    int n = 0;
    int chon;

    while (1) {
        printf("\n=====================================================\n");
        printf("                 QUAN LY TAI KHOAN NGAN HANG\n");
        printf("=====================================================\n");
        printf("   [1]  Them tai khoan moi\n");
        printf("   [2]  Cap nhat thong tin tai khoan\n");
        printf("   [3]  Khoa tai khoan\n");
        printf("   [4]  Tim kiem tai khoan (ID / Ten)\n");
        printf("   [5]  Hien thi danh sach tai khoan\n");
        printf("   [6]  Sap xep tai khoan\n");
        printf("-----------------------------------------------------\n");
        printf("   [0]  Thoat chuong trinh\n");
        printf("=====================================================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &chon);
        getchar();

        switch (chon) {
            case 1:
                n = addAccount(accounts, n);
                break;

            case 2:
                updateAccount(accounts, n);
                break;

            case 3:
                deleteandlock(accounts, n);
                break;

            case 4:
                search(accounts, n);
                break;

            case 5:
                showPagination(accounts, n);
                break;

            case 6:
                sortAccounts(accounts, n);
                break;

            case 0:
                printf("Thoat chuong trinh\n");
                return 0;

            default:
                printf("Lua chon khong hop le!\n");
                break;
        }
    }
}

void toLowerCopy(char src[], char dest[], int size) {
    int i;
    for (i = 0; i < size - 1 && src[i]; i++)
        dest[i] = tolower(src[i]);
    dest[i] = '\0';
}

int checkId(struct account accounts[], int n, char id[]) {
    for (int i = 0; i < n; i++)
        if (strcmp(accounts[i].accountid, id) == 0)
            return 1;
    return 0;
}

int checkPhone(struct account accounts[], int n, char phone[]) {
    for (int i = 0; i < n; i++)
        if (strcmp(accounts[i].phone, phone) == 0)
            return 1;
    return 0;
}

int addAccount(struct account accounts[], int n) {
    if (n >= maxaccounts) {
        printf("Danh sach da day!\n");
        return n;
    }

    char id[20], phone[15];

    while (1) {
        printf("\nNhap ID tai khoan: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = 0;

        if (strlen(id) == 0) {
            printf("ID khong duoc de trong!\n");
            continue;
        }

        if (checkId(accounts, n, id)) {
            printf("ID da ton tai!\n");
            continue;
        }

        break;
    }
    strcpy(accounts[n].accountid, id);

    while (1) {
        printf("Nhap ho ten: ");
        fgets(accounts[n].fullname, sizeof(accounts[n].fullname), stdin);
        accounts[n].fullname[strcspn(accounts[n].fullname, "\n")] = 0;
        if (strlen(accounts[n].fullname) > 0) break;
        printf("Ho ten khong duoc de trong!\n");
    }

    while (1) {
        printf("Nhap so dien thoai: ");
        fgets(phone, sizeof(phone), stdin);
        phone[strcspn(phone, "\n")] = 0;

        int len = strlen(phone);
        int valid = (len == 10);
        for (int i = 0; i < len && valid; i++)
            if (phone[i] < '0' || phone[i] > '9')
                valid = 0;

        if (!valid) {
            printf("SDT phai 10 chu so!\n");
            continue;
        }
        if (checkPhone(accounts, n, phone)) {
            printf("So dien thoai da ton tai!\n");
            continue;
        }
        break;
    }

    strcpy(accounts[n].phone, phone);

    accounts[n].balance = 0;
    accounts[n].status = 1;

    printf("Them tai khoan thanh cong!\n");
    return n + 1;
}

void updateAccount(struct account accounts[], int n) {
    char id[20];
    int pos = -1;

    while (1) {
        printf("\nNhap ID tai khoan can cap nhat: ");
        scanf("%s", id);
        getchar();
        pos = -1;
        for (int i = 0; i < n; i++)
            if (strcmp(accounts[i].accountid, id) == 0)
                pos = i;
        if (pos != -1) break;
        printf("ID khong ton tai! Nhap lai.\n");
    }


    char newName[50];
    printf("Nhap ten moi (bo trong de giu nguyen): ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = 0;
    if (strlen(newName) > 0) {
        strcpy(accounts[pos].fullname, newName);
    }

    char newPhone[15];
    while (1) {
        printf("Nhap so dien thoai moi (bo trong de giu nguyen): ");
        fgets(newPhone, sizeof(newPhone), stdin);
        newPhone[strcspn(newPhone, "\n")] = 0;

        if (strlen(newPhone) == 0) break; 

        int len = strlen(newPhone);
        int valid = (len == 10);
        for (int i = 0; i < len && valid; i++)
            if (newPhone[i] < '0' || newPhone[i] > '9')
                valid = 0;

        if (!valid) {
            printf("SDT khong hop le!\n");
            continue;
        }

        int duplicate = 0;
        for (int i = 0; i < n; i++)
            if (i != pos && strcmp(accounts[i].phone, newPhone) == 0)
                duplicate = 1;

        if (duplicate) {
            printf("SDT da ton tai!\n");
            continue;
        }

        strcpy(accounts[pos].phone, newPhone); 
        break;
    }

    printf("Cap nhat thanh cong!\n");
}

void deleteandlock(struct account accounts[], int n) {
    char id[20];
    int pos = -1;
    char confirm;

    while (1) {
        printf("\nNhap ID tai khoan can khoa: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = 0;  
        if (strlen(id) == 0) {
            printf("ID khong duoc de trong! Vui long nhap lai.\n");
            continue;
        }

        pos = -1;
        for (int i = 0; i < n; i++) {
            if (strcmp(accounts[i].accountid, id) == 0) {
                pos = i;
                break;
            }
        }

        if (pos == -1) {
            printf("ID khong ton tai! Vui long nhap lai.\n");
            continue;
        }

        
        if (accounts[pos].status == 0) {
            printf("Tai khoan da bi khoa !!!\n");
            return;
        }

        break; 
    }

    printf("\n=== THONG TIN TAI KHOAN ===\n");
    printf("ID: %s\n", accounts[pos].accountid);
    printf("Ten: %s\n", accounts[pos].fullname);
    printf("SDT: %s\n", accounts[pos].phone);
    printf("So du: %.2f\n", accounts[pos].balance);
    printf("Trang thai: %s\n", accounts[pos].status == 1 ? "Hoat dong" : "Da khoa");

    while (1) {
        printf("\nBan co chac chan muon khoa tai khoan? (y/n): ");
        scanf(" %c", &confirm);
        int d;
        while ((d = getchar()) != '\n') {} 

        if (confirm == 'y' || confirm == 'Y') {
            accounts[pos].status = 0;
            printf("\nTai khoan da duoc khoa thanh cong!\n");
            return;
        } else if (confirm == 'n' || confirm == 'N') {
            printf("Huy thao tac khoa tai khoan.\n");
            return;
        } else {
            printf("Lua chon khong hop le. Nhap lai.\n");
        }
    }
}



void search(struct account accounts[], int n) {
    char key[50], lowKey[50], lowName[50], lowId[50];

    if (n == 0) {
        printf("Danh sach rong!\n");
        return;
    }

    printf("\nNhap tu khoa tim kiem: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;
    toLowerCopy(key, lowKey, sizeof(lowKey));

    int found = 0;

    printf("\n===== KET QUA TIM KIEM =====\n");
    printf("%-5s | %-15s | %-20s | %-12s | %-10s\n", "STT", "ID", "Ten", "SDT", "Trang thai");
    printf("---------------------------------------------------------------------\n");

    for (int i = 0, stt = 1; i < n; i++) {
        toLowerCopy(accounts[i].fullname, lowName, sizeof(lowName));
        toLowerCopy(accounts[i].accountid, lowId, sizeof(lowId));
        if (strstr(lowName, lowKey) || strstr(lowId, lowKey)) {
            printf("%-5d | %-15s | %-20s | %-12s | %-10s\n",
                   stt++,
                   accounts[i].accountid,
                   accounts[i].fullname,
                   accounts[i].phone,
                   accounts[i].status == 1 ? "Hoat dong" : "Da khoa");
            found = 1;
        }
    }

    if (!found) printf("Khong tim thay tai khoan!\n");
}

void showPagination(struct account accounts[], int n) {
    if (n == 0) {
        printf("Danh sach rong!\n");
        return;
    }

    printf("\n===== DANH SACH TAI KHOAN =====\n");
    printf("%-5s | %-15s | %-20s | %-12s | %-10s\n", "STT", "ID", "Ten", "SDT", "Trang thai");
    printf("---------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%-5d | %-15s | %-20s | %-12s | %-10s\n",
               i+1,
               accounts[i].accountid,
               accounts[i].fullname,
               accounts[i].phone,
               accounts[i].status == 1 ? "Hoat dong" : "Da khoa");
    }
}

void sortAccounts(struct account accounts[], int n) {
    if (n == 0) {
        printf("Danh sach rong!\n");
        return;
    }
    int choice;
    printf("\nChon kieu sap xep:\n");
    printf("1. Theo ID \n");
    printf("2. Theo Ten \n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);
    getchar();
    struct account temp;
    if (choice == 1) {
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (strcmp(accounts[i].accountid, accounts[j].accountid) > 0) {
                    temp = accounts[i];
                    accounts[i] = accounts[j];
                    accounts[j] = temp;
                }
        printf("Sap xep theo ID thanh cong!\n");
    } 
    else if (choice == 2) {
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (strcmp(accounts[i].fullname, accounts[j].fullname) > 0) {
                    temp = accounts[i];
                    accounts[i] = accounts[j];
                    accounts[j] = temp;
                }
        printf("Sap xep theo Ten thanh cong!\n");
    } 
    else {
        printf("Lua chon khong hop le!\n");
    }
}

