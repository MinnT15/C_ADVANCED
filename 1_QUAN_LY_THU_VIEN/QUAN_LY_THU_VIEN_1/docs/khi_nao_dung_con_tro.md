# Khi Nào Dùng Con Trỏ vs Giá Trị Thường

## 🎯 Quy Tắc Vàng

### **Dùng CON TRỎ khi:**
1. ✅ Cần **SỬA ĐỔI** dữ liệu của caller
2. ✅ Dữ liệu **LỚN** (mảng, struct, chuỗi)
3. ✅ Muốn **TRẢ NHIỀU GIÁ TRỊ**
4. ✅ Làm việc với **MẢNG** hoặc **CHUỖI**
5. ✅ Cần **DYNAMIC MEMORY** (malloc)

### **Dùng GIÁ TRỊ THƯỜNG khi:**
1. ✅ Chỉ **ĐỌC**, không sửa
2. ✅ Dữ liệu **NHỎ** (int, char, float, bool)
3. ✅ Chỉ cần **1 GIÁ TRỊ TRẢ VỀ** (qua return)
4. ✅ Muốn **AN TOÀN** (không sợ sửa nhầm)

---

## 📊 Bảng So Sánh Chi Tiết

| Tiêu chí | Con trỏ | Giá trị thường |
|----------|---------|----------------|
| **Kích thước** | Lớn (>8 bytes) | Nhỏ (≤8 bytes) |
| **Sửa đổi** | Có thể sửa gốc | Chỉ sửa copy |
| **Hiệu suất** | Nhanh (chỉ copy địa chỉ) | Chậm nếu data lớn |
| **An toàn** | Dễ lỗi (NULL, dangling) | An toàn hơn |
| **Mục đích** | Sửa data, trả nhiều giá trị | Đọc data, tính toán |

---

## 1️⃣ Dùng Con Trỏ

### **Trường hợp 1: Cần sửa đổi dữ liệu**

```c
// ✅ ĐÚNG - Dùng con trỏ để sửa
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5, y = 10;
    swap(&x, &y);
    printf("x=%d, y=%d", x, y);  // x=10, y=5 ✅
}
```

```c
// ❌ SAI - Dùng giá trị (không sửa được gốc)
void swap_wrong(int a, int b) {
    int temp = a;
    a = b;
    b = temp;  // Chỉ sửa copy!
}

int main() {
    int x = 5, y = 10;
    swap_wrong(x, y);
    printf("x=%d, y=%d", x, y);  // x=5, y=10 ❌ (không đổi!)
}
```

---

### **Trường hợp 2: Dữ liệu lớn (mảng, struct)**

```c
typedef struct {
    char name[50];
    int age;
    float salary;
} Employee;  // 58 bytes

// ✅ ĐÚNG - Dùng con trỏ (chỉ copy 8 bytes)
void print_employee(const Employee *emp) {
    printf("%s, %d, %.2f", emp->name, emp->age, emp->salary);
}

// ❌ SAI - Copy toàn bộ struct (58 bytes)
void print_employee_wrong(Employee emp) {
    printf("%s, %d, %.2f", emp.name, emp.age, emp.salary);
}
```

**So sánh:**
- Con trỏ: Copy 8 bytes (địa chỉ)
- Giá trị: Copy 58 bytes (toàn bộ struct)

---

### **Trường hợp 3: Trả nhiều giá trị**

```c
// ✅ ĐÚNG - Dùng con trỏ để trả 2 giá trị
void divide(int a, int b, int *quotient, int *remainder) {
    *quotient = a / b;
    *remainder = a % b;
}

int main() {
    int q, r;
    divide(10, 3, &q, &r);
    printf("Thương: %d, Dư: %d", q, r);  // 3, 1
}
```

---

### **Trường hợp 4: Làm việc với mảng/chuỗi**

```c
// ✅ ĐÚNG - Mảng luôn dùng con trỏ
void fill_array(int *arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        arr[i] = value;
    }
}

// ✅ ĐÚNG - Chuỗi luôn dùng con trỏ
void get_string(char *buffer, int max_len) {
    fgets(buffer, max_len, stdin);
}
```

---

## 2️⃣ Dùng Giá Trị Thường

### **Trường hợp 1: Chỉ đọc, không sửa**

```c
// ✅ ĐÚNG - Chỉ đọc, dùng giá trị
int square(int x) {
    return x * x;
}

int add(int a, int b) {
    return a + b;
}

bool is_even(int n) {
    return n % 2 == 0;
}
```

---

### **Trường hợp 2: Dữ liệu nhỏ**

```c
// ✅ ĐÚNG - int nhỏ (4 bytes), dùng giá trị
int max(int a, int b) {
    return (a > b) ? a : b;
}

// ✅ ĐÚNG - char nhỏ (1 byte), dùng giá trị
char to_upper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    return c;
}
```

---

### **Trường hợp 3: Chỉ cần 1 giá trị trả về**

```c
// ✅ ĐÚNG - Return 1 giá trị
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

float calculate_area(float radius) {
    return 3.14159 * radius * radius;
}
```

---

## 📋 Bảng Quyết Định Nhanh

| Kiểu dữ liệu | Kích thước | Dùng gì? | Lý do |
|--------------|------------|----------|-------|
| `int`, `char`, `float` | 1-8 bytes | **Giá trị** | Nhỏ, nhanh |
| `double`, `long long` | 8 bytes | **Giá trị** hoặc Con trỏ | Tùy mục đích |
| `int[100]` | 400 bytes | **Con trỏ** | Lớn |
| `char[50]` (chuỗi) | 50 bytes | **Con trỏ** | Lớn, thường sửa |
| `struct` nhỏ (<16 bytes) | <16 bytes | **Giá trị** | Nhỏ |
| `struct` lớn (>16 bytes) | >16 bytes | **Con trỏ** | Lớn |

---

## 💡 Ví Dụ Thực Tế

### **Ví dụ 1: Validation functions**

```c
// ✅ Giá trị - Chỉ đọc, data nhỏ
bool validate_id(int id) {
    return id > 0;
}

// ✅ Con trỏ - Đọc chuỗi lớn
bool validate_string(const char *str) {
    return str != NULL && str[0] != '\0';
}
```

---

### **Ví dụ 2: Input functions**

```c
// ✅ Giá trị cho prompt (chỉ đọc)
// ✅ Con trỏ cho buffer (cần sửa)
// ✅ Giá trị cho max_len (chỉ đọc, nhỏ)
void get_string_input(const char *prompt, char *buffer, int max_len) {
    printf("%s", prompt);
    fgets(buffer, max_len, stdin);
}
```

---

### **Ví dụ 3: Struct functions**

```c
typedef struct {
    int id;
    char title[100];
    char author[50];
} Book;  // ~160 bytes

// ✅ Con trỏ - Struct lớn, chỉ đọc
void print_book(const Book *book) {
    printf("%d: %s by %s", book->id, book->title, book->author);
}

// ✅ Con trỏ - Struct lớn, cần sửa
void edit_book(Book *book, const char *new_title) {
    strcpy(book->title, new_title);
}

// ✅ Giá trị - Return struct (OK nếu cần)
Book create_book(int id, const char *title, const char *author) {
    Book book;
    book.id = id;
    strcpy(book.title, title);
    strcpy(book.author, author);
    return book;  // Copy struct về
}
```

---

## ⚠️ Lưu Ý Quan Trọng

### **1. `const` với con trỏ**

```c
// Chỉ đọc, không sửa
void print_string(const char *str) {
    printf("%s", str);
    // str[0] = 'X';  // ❌ LỖI! (const)
}

// Có thể sửa
void modify_string(char *str) {
    str[0] = 'X';  // ✅ OK
}
```

---

### **2. Mảng tự động thành con trỏ**

```c
// Cả 2 cách này GIỐNG NHAU!
void func1(int arr[]) { }
void func2(int *arr) { }

// Gọi hàm
int numbers[5] = {1, 2, 3, 4, 5};
func1(numbers);  // numbers tự động thành &numbers[0]
func2(numbers);  // Giống nhau!
```

---

### **3. Khi nào dùng `const`?**

```c
// ✅ Dùng const khi chỉ đọc
void print(const char *str);
void display(const int *arr, int size);

// ✅ KHÔNG dùng const khi cần sửa
void get_input(char *buffer);
void sort(int *arr, int size);
```

---

## 📝 Tóm Tắt

### **Dùng CON TRỎ:**
- ✅ Mảng, chuỗi
- ✅ Struct lớn (>16 bytes)
- ✅ Cần sửa dữ liệu gốc
- ✅ Trả nhiều giá trị

### **Dùng GIÁ TRỊ:**
- ✅ int, char, float, bool
- ✅ Chỉ đọc, không sửa
- ✅ Tính toán đơn giản
- ✅ Return 1 giá trị

### **Quy tắc đơn giản:**
> **Nếu nghi ngờ → Dùng con trỏ!**
> **Nếu chắc chắn chỉ đọc và data nhỏ → Dùng giá trị!**
