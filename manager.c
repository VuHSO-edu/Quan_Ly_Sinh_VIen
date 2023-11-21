#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

// Cấu trúc dữ liệu sinh viên
struct Student {
    char maSV[20];
    char hoTen[50];
    int namSinh;
    // Thêm thông tin khác nếu cần
};

// Hàm nhập thông tin của một sinh viên
void nhapSinhVien(struct Student *sv) {
    printf("Nhap Ma SV: ");
    scanf("%s", sv->maSV);
    printf("Nhap Ho ten: ");
    scanf("%s", sv->hoTen);
    printf("Nhap Nam sinh: ");
    scanf("%d", &sv->namSinh);
    // Nhập các thông tin khác nếu cần
}

// Hàm hiển thị thông tin của một sinh viên
void hienThiSinhVien(struct Student sv) {
    printf("Ma SV: %s\t Ho ten: %s\t Nam sinh: %d\n", sv.maSV, sv.hoTen, sv.namSinh);
    // Hiển thị các thông tin khác nếu cần
}

// Hàm xóa sinh viên theo Mã sinh viên
void xoaSinhVien(struct Student danhSach[], int *soLuong, char maSV[]) {
    int i, j;
    for (i = 0; i < *soLuong; i++) {
        if (strcmp(danhSach[i].maSV, maSV) == 0) {
            for (j = i; j < *soLuong - 1; j++) {
                danhSach[j] = danhSach[j + 1];
            }
            (*soLuong)--;
            printf("Da xoa sinh vien co Ma SV: %s\n", maSV);
            return;
        }
    }
    printf("Khong tim thay sinh vien co Ma SV: %s\n", maSV);
}

// Hàm tìm kiếm sinh viên theo Mã sinh viên hoặc Họ tên sinh viên
void timKiemSinhVien(struct Student danhSach[], int soLuong, char keyword[]) {
    int i;
    printf("Ket qua tim kiem:\n");
    for (i = 0; i < soLuong; i++) {
        if (strstr(danhSach[i].maSV, keyword) != NULL || strstr(danhSach[i].hoTen, keyword) != NULL) {
            hienThiSinhVien(danhSach[i]);
        }
    }
}

// Hàm sắp xếp danh sách sinh viên theo Năm sinh
void sapXepTheoNamSinh(struct Student danhSach[], int soLuong) {
    int i, j;
    struct Student temp;
    for (i = 0; i < soLuong - 1; i++) {
        for (j = i + 1; j < soLuong; j++) {
            if (danhSach[i].namSinh > danhSach[j].namSinh) {
                temp = danhSach[i];
                danhSach[i] = danhSach[j];
                danhSach[j] = temp;
            }
        }
    }
    printf("Da sap xep danh sach theo Nam sinh.\n");
}

// Hàm lưu danh sách sinh viên vào file văn bản
void luuFile(struct Student danhSach[], int soLuong, char tenFile[]) {
    FILE *file = fopen(tenFile, "w");
    if (file == NULL) {
        printf("Khong mo duoc file de ghi.\n");
        return;
    }

    for (int i = 0; i < soLuong; i++) {
        fprintf(file, "%s %s %d\n", danhSach[i].maSV, danhSach[i].hoTen, danhSach[i].namSinh);
    }

    fclose(file);
    printf("Da luu danh sach sinh vien vao file %s.\n", tenFile);
}

// Hàm đọc danh sách sinh viên từ file văn bản
int docFile(struct Student danhSach[]) {
    FILE *file = fopen("danhsachsinhvien.txt", "r");
    if (file == NULL) {
        printf("Khong mo duoc file de doc.\n");
        return 0;
    }

    int soLuong = 0;
    while (fscanf(file, "%s %s %d", danhSach[soLuong].maSV, danhSach[soLuong].hoTen, &danhSach[soLuong].namSinh) != EOF) {
        soLuong++;
    }

    fclose(file);
    return soLuong;
}

int main() {
    struct Student danhSach[MAX_STUDENTS];
    int soLuong = 0;
    int choice;
    char keyword[50];

    soLuong = docFile(danhSach); // Đọc danh sách từ file nếu có

    do {
        printf("\n===== MENU =====\n");
        printf("1. Nhap danh sach sinh vien\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Xoa sinh vien theo Ma SV\n");
        printf("4. Tim kiem sinh vien\n");
        printf("5. Sap xep danh sach theo Nam sinh\n");
        printf("6. Luu danh sach vao file\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap so luong sinh vien: ");
                scanf("%d", &soLuong);
                for (int i = 0; i < soLuong; i++) {
                    nhapSinhVien(&danhSach[i]);
                }
                break;
            case 2:
                printf("\nDanh sach sinh vien:\n");
                for (int i = 0; i < soLuong; i++) {
                    hienThiSinhVien(danhSach[i]);
                }
                break;
            case 3:
                printf("Nhap Ma SV can xoa: ");
                scanf("%s", keyword);
                xoaSinhVien(danhSach, &soLuong, keyword);
                break;
            case 4:
                printf("Nhap Ma SV hoac Ho ten can tim kiem: ");
                scanf("%s", keyword);
                timKiemSinhVien(danhSach, soLuong, keyword);
                break;
            case 5:
                sapXepTheoNamSinh(danhSach, soLuong);
                break;
            case 6:
                luuFile(danhSach, soLuong, "danhsachsinhvien.txt");
                break;
        }
    } while (choice != 0);

    return 0;
}
