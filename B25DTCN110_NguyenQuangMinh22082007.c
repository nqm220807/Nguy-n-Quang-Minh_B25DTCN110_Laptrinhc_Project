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
void deleteandlock(struct account accounts[], int *n);
void search(struct account accounts[], int n);
void showPagination(struct account accounts[], int n);
void sortAccounts(struct account accounts[], int n);
void toLowerCopy(char src[], char dest[], int size);

int main() {
    struct account accounts[maxaccounts];
    int n = 0;
    int chon;

    while (1) {
        printf("\n<====================== MENU ====================>\n");
        printf("1. Them tai khoan\n");
        printf("2. Cap nhat tai khoan\n");
        printf("3. Khoa/Xoa tai khoan\n");
        printf("4. Tim kiem tai khoan\n");
        printf("5. Hien thi danh sach tai khoan\n");
        printf("6. Sap xep danh sach\n");
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
        } else if (chon == 5) {
            showPagination(accounts, n);
        } else if (chon == 6) {
            sortAccounts(accounts, n);
        } else if (chon == 0) {
            printf("Thoat chuong trinh\n");
            break;
        } else {
            printf("Lua chon khong hop le\n");
        }
    }

    return 0;
}


void toLowerCopy(char src[], char dest[], int size) {
    int i;
    for (i = 0; i < size-1 && src[i] != '\0'; i++) {
        dest[i] = tolower((unsigned char)src[i]);
    }
    dest[i] = '\0';
}


int checkId(struct account accounts[], int n, char id[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(accounts[i].accountid, id) == 0)
            return 1;
    }
    return 0;
}


int checkPhone(struct account accounts[], int n, char phone[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(accounts[i].phone, phone) == 0)
            return 1;
    }
    return 0;
}


int addAccount(struct account accounts[], int n) {
    if (n >= maxaccounts) {
        printf("Danh sach tai khoan da day\n");
        return n;
    }

    char id[20], phone[15];
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

    while (1) {
        printf("Nhap ho ten: ");
        fgets(accounts[n].fullname, sizeof(accounts[n].fullname), stdin);
        accounts[n].fullname[strcspn(accounts[n].fullname, "\n")] = 0;
        if (strlen(accounts[n].fullname) == 0) {
            printf("Ten khong duoc de trong\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Nhap so dien thoai: ");
        fgets(phone, sizeof(phone), stdin);
        phone[strcspn(phone, "\n")] = 0;

        if (strlen(phone) == 0) {
            printf("So dien thoai khong duoc trong\n");
            continue;
        }
        int len = strlen(phone);
        int valid = 1;
        for (int i = 0; i < len; i++) {
            if (phone[i] < '0' || phone[i] > '9') {
                valid = 0;
                break;
            }
        }
        if (!valid || len != 10) {
            printf("So dien thoai phai co 10 chu so va chi duoc so\n");
            continue;
        }
        if (checkPhone(accounts, n, phone)) {
            printf("So dien thoai da ton tai, nhap lai\n");
            continue;
        }
        break;
    }
    strcpy(accounts[n].phone, phone);

    accounts[n].balance = 0.0f;
    accounts[n].status  = 1;
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

    printf("\n=== Thong tin hien tai ===\n");
    printf("Ho ten: %s\n", accounts[pos].fullname);
    printf("So dien thoai: %s\n", accounts[pos].phone);

    char newname[50], newphone[15];

    printf("Nhap ho ten moi (de trong neu giu nguyen): ");
    fgets(newname, sizeof(newname), stdin);
    newname[strcspn(newname, "\n")] = 0;

    while (1) {
        printf("Nhap so dien thoai moi (de trong neu giu nguyen): ");
        if (!fgets(newphone, sizeof(newphone), stdin)) {
            newphone[0] = '\0';
        } else {
            newphone[strcspn(newphone, "\n")] = 0;
        }

        if (strlen(newphone) == 0) {
            break;
        }

        int len = strlen(newphone);
        int valid = 1;
        for (int i = 0; i < len; i++) {
            if (newphone[i] < '0' || newphone[i] > '9') {
                valid = 0;
                break;
            }
        }
        if (!valid || len != 10) {
            printf("SDT khong hop le. SDT phai gom 10 chu so. Vui long nhap lai hoac nhan Enter de bo qua.\n");
            continue; 
        }


        if (strcmp(newphone, accounts[pos].phone) == 0) {
            break;
        }
     
        if (checkPhone(accounts, n, newphone)) {
            printf("SDT da ton tai o tai khoan khac. Vui long nhap SDT khac.\n");
            continue; 
        }       
        break;
    }

    if (strlen(newname) > 0) {
        strcpy(accounts[pos].fullname, newname);
    }
    if (strlen(newphone) > 0) {
        strcpy(accounts[pos].phone, newphone);
    }

    printf("Cap nhat thanh cong!\n");
}


void deleteandlock(struct account accounts[], int *n) {
    char id[20];
    int pos = -1;


    while (1) {
        printf("\nNhap ID tai khoan can thao tac (nhap q de huy): ");
        if (scanf("%19s", id) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (id[0] == 'q' || id[0] == 'Q') {
            printf("Huy thao tac, tro ve menu.\n");
            return;
        }

        pos = -1;
        for (int i = 0; i < *n; i++) {
            if (strcmp(accounts[i].accountid, id) == 0) {
                pos = i;
                break;
            }
        }

        if (pos == -1) {
            printf("Khong tim thay ID tai khoan. Nhap lai hoac nhap 'q' de huy.\n");
            continue; 
        }
        break;
    }

    printf("\n=== Thong tin tai khoan ===\n");
    printf("ID: %s\n", accounts[pos].accountid);
    printf("Ho ten: %s\n", accounts[pos].fullname);
    printf("SDT: %s\n", accounts[pos].phone);
    printf("So du: %.2f\n", accounts[pos].balance);
    printf("Trang thai: %s\n", accounts[pos].status == 1 ? "Active" : "Inactive");

    while (1) {
        printf("\nLua chon thao tac: 1-Khoa tai khoan, 2-Xoa tai khoan, 3-Huy: ");
        int opt;
        if (scanf("%d", &opt) != 1) {
            while (getchar() != '\n');
            printf("Nhap khong hop le. Nhap lai.\n");
            continue;
        }
        while (getchar() != '\n');

        if (opt == 1) {
            accounts[pos].status = 0;
            printf("Da khoa tai khoan!\n");
            break;
        } else if (opt == 2) {
            for (int i = pos; i < *n - 1; i++) {
                accounts[i] = accounts[i + 1];
            }
            (*n)--;
            printf("Xoa tai khoan thanh cong!\n");
            break;
        } else if (opt == 3) {
            printf("Huy thao tac!\n");
            break;
        } else {
            printf("Lua chon khong hop le. Chon lai.\n");
        }
    }
}


void search(struct account accounts[], int n) {
    if (n == 0) {
        printf("Danh sach tai khoan rong!\n");
        return;
    }

    char input[100];
    printf("\nNhap ky tu hoac chuoi can tim (tim trong ID va Ten): ");
    if (!fgets(input, sizeof(input), stdin)) return;
    input[strcspn(input, "\n")] = 0;

    if (strlen(input) == 0) {
        printf("Chuoi tim kiem rong!\n");
        return;
    }

    char pattern[100];
    toLowerCopy(input, pattern, sizeof(pattern));
    int found = 0;

    printf("\n+----------+------------------------------+----------+--------------------+----------+\n");
    printf("|%-10s|%-30s|%-10s|%-20s|%-10s|\n", "Ma ID", "Ho va Ten", "SDT", "So du tai khoan", "Trang thai");
    printf("+----------+------------------------------+----------+--------------------+----------+\n");

    for (int i = 0; i < n; i++) {
        char idlow[20], namelow[50];
        toLowerCopy(accounts[i].accountid, idlow, sizeof(idlow));
        toLowerCopy(accounts[i].fullname, namelow, sizeof(namelow));

        if (strstr(idlow, pattern) != NULL || strstr(namelow, pattern) != NULL) {
            printf("|%-10s|%-30s|%-10s|%-20.2f|%-10s|\n",
                   accounts[i].accountid, accounts[i].fullname, accounts[i].phone, accounts[i].balance,
                   accounts[i].status == 1 ? "Active" : "Inactive");
            found = 1;
        }
    }

    printf("+----------+------------------------------+----------+--------------------+----------+\n");

    if (!found) printf("Khong tim thay tai khoan phu hop.\n");
}


void showPagination(struct account accounts[], int n) {
    int page_number = 0;
    int page_size   = 10;
    int total_pages = (n + page_size - 1) / page_size;

    if (n == 0) {
        printf("Danh sach tai khoan rong!\n");
        return;
    }

    while (1) {
        printf("Nhap so trang (1 - %d): ", total_pages);
        if (scanf("%d", &page_number) != 1) {
            while (getchar() != '\n');
            printf("Nhap khong hop le. Nhap lai.\n");
            continue;
        }
        getchar();
        if (page_number < 1 || page_number > total_pages) {
            printf("Loi du lieu khong hop le !!\n");
            continue;
        }
        break;
    }

    int start = (page_number - 1) * page_size;
    int end   = start + page_size;

    printf("\n+-------------------------------------- Trang %d/%d -------------------------------------+\n", page_number, total_pages);
    printf("+----------+------------------------------+----------+--------------------+----------+\n");
    printf("|%-10s|%-30s|%-10s|%-20s|%-10s|\n", "Ma ID", "Ho va Ten", "SDT", "So du tai khoan", "Trang thai");
    printf("+----------+------------------------------+----------+--------------------+----------+\n");

    for (int i = start; i < end && i < n; i++) {
        printf("|%-10s|%-30s|%-10s|%-20.2f|%-10s|\n",
               accounts[i].accountid,
               accounts[i].fullname,
               accounts[i].phone,
               accounts[i].balance,
               accounts[i].status == 1 ? "Active" : "Inactive");
    }

    printf("+----------+------------------------------+----------+--------------------+----------+\n");
}

void sortAccounts(struct account accounts[], int n) {
    if (n == 0) {
        printf("Khong co du lieu can sap xep\n");
        return;
    }

    int choice;
    printf("\nChon cach sap xep:\n");
    printf("1. Theo so du giam dan\n");
    printf("2. Theo ten A-Z\n");
    printf("Chon: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (accounts[i].balance < accounts[j].balance) {
                    struct account temp = accounts[i];
                    accounts[i] = accounts[j];
                    accounts[j] = temp;
                }
    } else if (choice == 2) {
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (strcmp(accounts[i].fullname, accounts[j].fullname) > 0) {
                    struct account temp = accounts[i];
                    accounts[i] = accounts[j];
                    accounts[j] = temp;
                }
    } else {
        printf("Lua chon khong hop le\n");
        return;
    }

    printf("Da sap xep xong!\n");
}

