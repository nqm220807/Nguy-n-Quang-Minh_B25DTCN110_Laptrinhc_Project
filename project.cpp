#include <stdio.h>   // thu vien chuan nhap xuat printf scanf
#include <string.h>  // thu vien xu ly chuoi strcpy strcmp fgets strcspn

#define maxaccounts 100  // so luong tai khoan toi da

// khai bao struct account
struct account {
    char accountid[20];   // ma tai khoan
    char fullname[50];    // ho ten
    char phone[15];       // so dien thoai
    float balance;        // so du
    int status;           // 1=active 0=inactive
};

// ham kiem tra id co ton tai chua
int isidexist(struct account accounts[], int n, char id[]) {
    for (int i = 0; i < n; i++) { // duyet tat ca tai khoan
        if (strcmp(accounts[i].accountid, id) == 0) // strcmp tra ve 0 neu bang nhau
            return 1; // id da ton tai
    }
    return 0; // id chua ton tai
}

// ham them tai khoan moi
int themtaikhoan(struct account accounts[], int n) {
    if (n >= maxaccounts) { // neu da dat so luong toi da
        printf("Danh sach tai khoan da day\n");
        return n; // khong them duoc
    }

    char id[20]; // bien tam luu id nhap tu ban phim
    printf("\nNhap ID tai khoan: ");
    scanf("%s", id); // nhap id khong chua khoang trang
    getchar(); // loai bo ky tu newline con du trong bo nho dem

    if (strlen(id) == 0 || isidexist(accounts, n, id)) { // kiem tra id rong hoac da ton tai
        printf("ID khong hop le hoac da ton tai\n");
        return n; // khong them
    }

    strcpy(accounts[n].accountid, id); // sao chep id vao truong accountid cua tai khoan moi

    printf("Nhap ho ten: ");
    fgets(accounts[n].fullname, 50, stdin); // fgets doc ca dong toi da 49 ky tu
    accounts[n].fullname[strcspn(accounts[n].fullname, "\n")] = 0; // loai bo ky tu newline cuoi chuoi neu co

    printf("Nhap so dien thoai: ");
    fgets(accounts[n].phone, 15, stdin); // nhap so dien thoai
    accounts[n].phone[strcspn(accounts[n].phone, "\n")] = 0; // loai bo newline

    accounts[n].balance = 0; // khoi tao so du bang 0
    accounts[n].status = 1; // khoi tao trang thai active

    n++; // tang so luong tai khoan
    printf("Them tai khoan thanh cong\n");
    return n; // tra ve so luong tai khoan moi
}

// ham cap nhat thong tin tai khoan
void capnhattaikhoan(struct account accounts[], int n) {
    char id[20]; // bien tam luu id can cap nhat
    printf("\nNhap ID tai khoan can cap nhat: ");
    scanf("%s", id); // nhap id
    getchar(); // loai bo newline

    int found = -1; // bien luu vi tri tai khoan tim thay -1 = chua tim thay
    for (int i = 0; i < n; i++) {
        if (strcmp(accounts[i].accountid, id) == 0) { // neu id khop
            found = i; // luu vi tri
            break; // dung vong lap
        }
    }

    if (found == -1) { // neu khong tim thay id
        printf("Khong tim thay tai khoan\n");
        return; // ket thuc ham
    }

    // hien thi thong tin hien tai
    printf("Thong tin hien tai\n");
    printf("Ho ten: %s\n", accounts[found].fullname);
    printf("So dien thoai: %s\n", accounts[found].phone);

    // nhap thong tin moi
    char newname[50], newphone[15];
    printf("Nhap ho ten moi de trong de giu nguyen: ");
    fgets(newname, 50, stdin); // nhap ho ten moi
    newname[strcspn(newname, "\n")] = 0; // loai bo newline

    printf("Nhap so dien thoai moi de trong de giu nguyen: ");
    fgets(newphone, 15, stdin); // nhap so dien thoai moi
    newphone[strcspn(newphone, "\n")] = 0; // loai bo newline

    if (strlen(newname) > 0) // neu nguoi dung nhap ho ten moi
        strcpy(accounts[found].fullname, newname); // cap nhat ho ten

    if (strlen(newphone) > 0) // neu nguoi dung nhap so dien thoai moi
        strcpy(accounts[found].phone, newphone); // cap nhat so dien thoai

    printf("Cap nhat thanh cong\n"); // thong bao
}

// ham hien thi menu
void menu() {
    printf("\n===== QUAN LY TAI KHOAN =====\n");
    printf("1. Them tai khoan moi\n");
    printf("2. Cap nhat thong tin tai khoan\n");
    printf("3. Thoat\n");
    printf("Chon chuc nang: ");
}

int main() {
    struct account accounts[maxaccounts]; // mang luu tai khoan
    int n = 0; // so luong tai khoan hien co
    int choice; // lua chon menu

    do {
        menu();
        scanf("%d", &choice); // nhap lua chon
        getchar(); // loai bo newline

        switch(choice) {
            case 1:
                n = themtaikhoan(accounts, n); // goi ham them tai khoan
                break;
            case 2:
                capnhattaikhoan(accounts, n); // goi ham cap nhat tai khoan
                break;
            case 3:
                printf("Thoat chuong trinh\n"); // thoat
                break;
            default:
                printf("Lua chon khong hop le\n"); // lua chon sai
        }
    } while(choice != 3); // lap lai menu cho den khi chon 3

    return 0; // ket thuc chuong trinh
}

