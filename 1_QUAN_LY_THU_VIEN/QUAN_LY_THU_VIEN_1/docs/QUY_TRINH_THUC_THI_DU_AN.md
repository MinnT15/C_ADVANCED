# 🚀 Quy Trình Thực Thi Dự Án Phần Mềm

> 📚 **Dành cho sinh viên mới ra trường** - Hướng dẫn chi tiết giúp bạn hiểu quy trình làm việc thực tế như một developer có 5 năm kinh nghiệm!

---

## 📋 Mục Lục

1. [Giới Thiệu - Tại Sao Cần Hiểu Quy Trình?](#1-giới-thiệu)
2. [Vòng Đời Phần Mềm (SDLC)](#2-vòng-đời-phần-mềm-sdlc)
3. [Phương Pháp Agile/Scrum](#3-phương-pháp-agilescrum)
4. [Chi Tiết Từng Giai Đoạn](#4-chi-tiết-từng-giai-đoạn)
5. [Git Workflow - Làm Việc Với Code](#5-git-workflow)
6. [Testing - Kiểm Thử](#6-testing-kiểm-thử)
7. [CI/CD Pipeline](#7-cicd-pipeline)
8. [Một Ngày Làm Việc Thực Tế](#8-một-ngày-làm-việc-thực-tế)
9. [Công Cụ Thường Dùng](#9-công-cụ-thường-dùng)
10. [Best Practices](#10-best-practices)
11. [Checklist Cho Người Mới](#11-checklist-cho-người-mới)

---

## 1. Giới Thiệu

### 🤔 Tại Sao Cần Hiểu Quy Trình?

**Câu chuyện thực tế:**

> Bạn là developer mới vào công ty. Ngày đầu tiên, lead nói:
> "Em tạo branch feature, code xong thì push PR, sau khi CI pass và được approve thì merge vào develop nhé!"
>
> Bạn: 😱 "Branch là gì? PR là gì? CI là gì???"

**Đọc xong tài liệu này, bạn sẽ:**
- ✅ Hiểu được toàn bộ quy trình từ A-Z
- ✅ Nói chuyện tự tin với senior developer
- ✅ Làm việc như đã có kinh nghiệm
- ✅ Không còn bỡ ngỡ ngày đầu đi làm

---

## 2. Vòng Đời Phần Mềm (SDLC)

### 🔄 SDLC = Software Development Life Cycle

**Tưởng tượng như xây nhà:**

```
🏠 XÂY NHÀ                    💻 LÀM PHẦN MỀM
─────────────────────────────────────────────────────────
Khách yêu cầu nhà 3 tầng  →   Requirements (Thu thập yêu cầu)
Kiến trúc sư vẽ bản thiết kế → Design (Thiết kế)
Thợ xây dựng nhà          →   Implementation (Viết code)
Kiểm tra điện nước        →   Testing (Kiểm thử)
Bàn giao cho khách        →   Deployment (Triển khai)
Sửa ống nước bị hỏng      →   Maintenance (Bảo trì)
```

### 📊 Sơ Đồ Các Giai Đoạn

```
┌─────────────────────────────────────────────────────────────────┐
│                                                                 │
│   1️⃣ REQUIREMENTS    "Khách hàng muốn gì?"                      │
│          ↓                                                      │
│   2️⃣ DESIGN          "Làm như thế nào?"                         │
│          ↓                                                      │
│   3️⃣ IMPLEMENTATION  "Viết code!"                               │
│          ↓                                                      │
│   4️⃣ TESTING         "Code có đúng không?"                      │
│          ↓                                                      │
│   5️⃣ DEPLOYMENT      "Đưa lên production!"                      │
│          ↓                                                      │
│   6️⃣ MAINTENANCE     "Sửa bug, thêm feature"                    │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 👥 Ai Làm Gì?

| Giai đoạn | Ai thực hiện? | Họ làm gì? | Output |
|-----------|---------------|------------|--------|
| Requirements | BA, PM | Họp với khách, viết yêu cầu | SRS Document |
| Design | Architect, Lead | Vẽ sơ đồ, thiết kế hệ thống | Design Document |
| Implementation | **Developer (BẠN!)** | Viết code | Source Code |
| Testing | QA, Developer | Test, tìm bug | Test Report |
| Deployment | DevOps | Deploy lên server | Production |
| Maintenance | Support | Sửa bug, update | Bug Fixes |

**💡 Ghi nhớ:** Là developer mới, bạn chủ yếu làm **Implementation** và **Testing**!

---

## 3. Phương Pháp Agile/Scrum

### 🏃 Agile Là Gì?

**So sánh dễ hiểu:**

```
📦 WATERFALL (Cũ)              🏃 AGILE (Mới)
────────────────────────────────────────────────────────
Làm hết rồi mới giao           Làm từng phần, giao liên tục
6 tháng mới xong sản phẩm      2 tuần có sản phẩm nhỏ
Khách đợi lâu                  Khách thấy sản phẩm sớm
Khó thay đổi yêu cầu           Dễ thay đổi theo feedback
```

### 🔄 Sprint Là Gì?

**Sprint = Một chu kỳ làm việc (thường 2 tuần)**

```
┌─────────────────── SPRINT (2 tuần) ────────────────────┐
│                                                         │
│  📋 Planning    👨‍💻 Development    🎯 Review    🔍 Retro │
│  (Thứ 2 đầu)   (Suốt sprint)     (Thứ 6 cuối) (Sau review)
│                                                         │
│      ↓              ↓               ↓           ↓       │
│  "Làm gì?"    "Code code code"  "Demo cho    "Rút kinh  │
│                                  khách xem"   nghiệm"   │
└─────────────────────────────────────────────────────────┘
```

### 👥 Các Vai Trò Trong Scrum

| Vai trò | Là ai? | Làm gì? |
|---------|--------|---------|
| 🎯 **Product Owner (PO)** | Đại diện khách hàng | Quyết định làm gì trước, gì sau |
| 🏃 **Scrum Master (SM)** | Như trọng tài | Giúp team làm việc hiệu quả, giải quyết vấn đề |
| 👨‍💻 **Development Team** | **BẠN!** | Thiết kế, code, test |

### 📢 Daily Standup - Họp Hàng Ngày

**Thời gian:** 15 phút mỗi sáng (9:00 AM)
**Mỗi người:** 2 phút

**Trả lời 3 câu hỏi:**

```
1️⃣ "Hôm qua tôi đã làm gì?"
   → "Tôi đã hoàn thành feature thêm sách, push PR"

2️⃣ "Hôm nay tôi sẽ làm gì?"
   → "Tôi sẽ implement chức năng tìm kiếm"

3️⃣ "Có vấn đề gì không?"
   → "Tôi đang chờ API doc từ team backend"
```

**💡 Mẹo cho người mới:**
- Chuẩn bị sẵn 3 câu trả lời trước
- Nói ngắn gọn, đúng trọng tâm
- Đừng ngại nói về vấn đề gặp phải

---

## 4. Chi Tiết Từng Giai Đoạn

> 🎯 **Phần này giải thích SIÊU CHI TIẾT** từng giai đoạn với nhiều ví dụ thực tế, bao gồm cả **lập trình nhúng** và **Embedded Linux**!

---

### 4.1 📋 REQUIREMENTS - Thu Thập Yêu Cầu (THỰC CHIẾN)

> 🎯 **Mục tiêu:** Sau phần này, bạn sẽ biết **CHÍNH XÁC** cách thu thập yêu cầu cho BẤT KỲ dự án nào!

---

#### 🤔 Vấn Đề Thường Gặp

**Bạn có từng gặp tình huống này không?**

```
📋 Đề bài: "Viết chương trình quản lý thư viện"

Bạn: 😱 "Ờ... bắt đầu từ đâu nhỉ?"
     "Quản lý thư viện là quản lý cái gì?"
     "Cần những tính năng gì?"
     "Dữ liệu lưu ở đâu?"
```

**💡 Giải pháp:** Đặt câu hỏi **ĐÚNG** trước khi code!

---

#### 🔑 CÔNG THỨC 5W1H - Đặt Câu Hỏi Đúng

**Với BẤT KỲ dự án nào, hãy hỏi 6 câu hỏi này:**

```
┌─────────────────────────────────────────────────────────────────┐
│                     CÔNG THỨC 5W1H                              │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  1️⃣ WHO - AI sử dụng?                                           │
│     "Ai là người dùng chính của phần mềm này?"                  │
│                                                                 │
│  2️⃣ WHAT - LÀM GÌ?                                              │
│     "Phần mềm cần làm được những gì?"                           │
│                                                                 │
│  3️⃣ WHERE - Ở ĐÂU?                                              │
│     "Chạy trên nền tảng nào? PC? MCU? Linux?"                   │
│                                                                 │
│  4️⃣ WHEN - KHI NÀO?                                             │
│     "Deadline? Có ràng buộc thời gian thực không?"              │
│                                                                 │
│  5️⃣ WHY - TẠI SAO?                                              │
│     "Mục đích cuối cùng là gì?"                                 │
│                                                                 │
│  6️⃣ HOW - NHƯ THẾ NÀO?                                          │
│     "Có ràng buộc kỹ thuật gì không?"                           │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

#### 📝 VÍ DỤ THỰC HÀNH: Dự Án Quản Lý Thư Viện

**Đề bài:** "Viết chương trình quản lý thư viện bằng C"

**Áp dụng 5W1H:**

```
1️⃣ WHO - AI sử dụng?
   → Thủ thư (librarian)
   → Độc giả (reader) - có thể có hoặc không
   
2️⃣ WHAT - LÀM GÌ?
   Hỏi chi tiết:
   - "Quản lý sách" = Thêm, sửa, xóa, tìm kiếm sách?
   - "Quản lý người dùng" = Có cần không?
   - "Mượn/trả sách" = Có cần không?
   - "Lưu dữ liệu" = Lưu file hay database?
   
   → Kết quả: Cần 4 nhóm tính năng
      ✅ Quản lý sách (CRUD)
      ✅ Quản lý người dùng (CRUD)
      ✅ Mượn/trả sách
      ✅ Lưu file

3️⃣ WHERE - Ở ĐÂU?
   → Chạy trên PC (terminal/console)
   → Không cần GUI
   
4️⃣ WHEN - KHI NÀO?
   → 2 tuần hoàn thành
   → Không có yêu cầu real-time
   
5️⃣ WHY - TẠI SAO?
   → Bài tập học lập trình C
   → Học cách tổ chức code module
   
6️⃣ HOW - NHƯ THẾ NÀO?
   → Ngôn ngữ: C
   → Không dùng thư viện bên ngoài
   → Tối đa 1000 sách, 500 người dùng
```

---

#### 📋 TEMPLATE: Liệt Kê Requirements

**Copy template này cho mọi dự án:**

```
=============================================================
             TAI LIEU YEU CAU DU AN
=============================================================
Ten du an: ___________________________
Ngay tao : ___/___/____

-------------------------------------------------------------
1. TONG QUAN
-------------------------------------------------------------
Muc dich   : 
Nguoi dung : 
Nen tang   : [ ] PC   [ ] MCU   [ ] Linux

-------------------------------------------------------------
2. TINH NANG (Functional Requirements)
-------------------------------------------------------------
ID       | Ten              | Input          | Output
---------|------------------|----------------|---------------
FR-001   |                  |                |
FR-002   |                  |                |
FR-003   |                  |                |

-------------------------------------------------------------
3. YEU CAU PHI CHUC NANG
-------------------------------------------------------------
Response time : < _____ ms
Max records   : _____
Memory limit  : < _____ KB

-------------------------------------------------------------
4. YEU CAU KY THUAT
-------------------------------------------------------------
Ngon ngu  : [ ] C   [ ] C++   [ ] Python
Compiler  : [ ] GCC   [ ] ARM-GCC
Thu vien  : 
Hardware  : 

-------------------------------------------------------------
5. RANG BUOC
-------------------------------------------------------------
Deadline  : ___/___/____
Ngan sach : 
Khac      : 

=============================================================
```

---

#### ✅ CHECKLIST Thu Thập Requirements

**Trước khi bắt đầu code, hãy check:**

```
□ Đã biết AI là người dùng?
□ Đã liệt kê TẤT CẢ tính năng cần làm?
□ Đã biết chạy trên nền tảng nào?
□ Đã biết deadline?
□ Đã biết ràng buộc kỹ thuật?
□ Đã xác định dữ liệu cần lưu trữ?
□ Đã xác định các trường hợp lỗi?
```

---

### 4.2 🎨 DESIGN - Thiết Kế (THỰC CHIẾN)

> 🎯 **Mục tiêu:** Sau phần này, bạn sẽ biết **BẮT ĐẦU TỪ ĐÂU** khi thiết kế BẤT KỲ dự án nào!

---

#### 🤔 Vấn Đề Thường Gặp

```
Bạn: "OK, tôi đã hiểu requirements rồi..."
     "Nhưng mà... bắt đầu từ đâu?"
     "Viết file nào trước?"
     "Struct như thế nào?"
     "Chia module ra sao?"
     😵 "Quá nhiều thứ, không biết bắt đầu từ đâu!"
```

**💡 Giải pháp:** Làm theo **7 BƯỚC** dưới đây!

---

#### 🚀 QUY TRÌNH 7 BƯỚC THIẾT KẾ

```
┌─────────────────────────────────────────────────────────────────┐
│              🎯 7 BƯỚC THIẾT KẾ DỰ ÁN                           │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  BƯỚC 1: Xác định DỮ LIỆU cần quản lý                          │
│          → Những "thứ" nào cần lưu trữ?                        │
│          → Mỗi "thứ" có những thông tin gì?                    │
│                                                                 │
│  BƯỚC 2: Thiết kế DATA STRUCTURES (struct)                     │
│          → Chuyển dữ liệu thành struct                         │
│                                                                 │
│  BƯỚC 3: Xác định OPERATIONS (thao tác)                        │
│          → Với mỗi dữ liệu, cần làm gì?                        │
│          → CRUD: Create, Read, Update, Delete                  │
│                                                                 │
│  BƯỚC 4: Thiết kế FUNCTION SIGNATURES                          │
│          → Function tên gì, nhận gì, trả về gì?                │
│                                                                 │
│  BƯỚC 5: Phân chia MODULES (files)                             │
│          → Nhóm các function liên quan                         │
│                                                                 │
│  BƯỚC 6: Thiết kế PROJECT STRUCTURE                            │
│          → Tổ chức thư mục, files                              │
│                                                                 │
│  BƯỚC 7: Vẽ SYSTEM DIAGRAM                                     │
│          → Sơ đồ tổng quan                                     │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

#### 🧠 TƯ DUY THIẾT KẾ: Áp Dụng Cho MỌI Dự Án

> 💡 **Bí quyết:** 7 bước trên áp dụng được cho **MỌI** dự án - từ ứng dụng desktop
> đến embedded MCU đến Embedded Linux. Chỉ khác nhau ở **CONTEXT** và **CONSTRAINTS**!

---

##### 🎯 NGUYÊN TẮC VÀNG: Đặt Câu Hỏi Đúng

```
┌─────────────────────────────────────────────────────────────────┐
│           CÂU HỎI THEN CHỐT CHO MỌI DỰ ÁN                       │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  📊 VỀ DỮ LIỆU:                                                 │
│  ├── "Hệ thống cần QUẢN LÝ những gì?"                           │
│  ├── "Mỗi thực thể có THUỘC TÍNH gì?"                           │
│  ├── "Các thực thể LIÊN QUAN đến nhau như thế nào?"             │
│  └── "Dữ liệu cần LƯU TRỮ ở đâu?" (RAM/Flash/File/Database)     │
│                                                                 │
│  ⚙️ VỀ HÀNH VI:                                                 │
│  ├── "Với mỗi dữ liệu, cần làm NHỮNG GÌ?"                       │
│  ├── "Có những TRẠNG THÁI nào?" (State Machine)                 │
│  ├── "Khi nào chuyển TRẠNG THÁI?"                               │
│  └── "Có những SỰ KIỆN nào cần xử lý?" (Events/Interrupts)      │
│                                                                 │
│  🔌 VỀ GIAO TIẾP:                                               │
│  ├── "Hệ thống GIAO TIẾP với bên ngoài qua gì?"                 │
│  ├── "Dùng GIAO THỨC gì?" (UART/SPI/I2C/MQTT/HTTP)              │
│  └── "AI gọi AI?" (Caller/Callee, Client/Server)                │
│                                                                 │
│  🛡️ VỀ LỖI VÀ GIỚI HẠN:                                        │
│  ├── "Có thể xảy ra LỖI gì?"                                    │
│  ├── "Xử lý lỗi NHƯ THẾ NÀO?"                                   │
│  └── "Có những RÀNG BUỘC gì?" (Memory/Speed/Power)              │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

##### 🔧 SO SÁNH: Desktop vs Embedded MCU vs Embedded Linux

```
┌──────────────────┬─────────────────┬─────────────────┬─────────────────┐
│    KHÍA CẠNH     │    DESKTOP      │  EMBEDDED MCU   │ EMBEDDED LINUX  │
│                  │   (Thư viện)    │    (STM32)      │  (Raspberry Pi) │
├──────────────────┼─────────────────┼─────────────────┼─────────────────┤
│ Bộ nhớ           │ Gần như vô hạn  │ KB - vài MB     │ MB - GB         │
│                  │ malloc thoải mái│ Static buffers  │ malloc OK       │
├──────────────────┼─────────────────┼─────────────────┼─────────────────┤
│ Lưu trữ          │ File system     │ Flash nội bộ    │ File system     │
│                  │ fopen/fclose    │ HAL_FLASH_xxx   │ fopen + sqlite  │
├──────────────────┼─────────────────┼─────────────────┼─────────────────┤
│ Giao tiếp        │ stdin/stdout    │ GPIO, UART,     │ sysfs, socket,  │
│                  │ socket          │ SPI, I2C        │ MQTT, HTTP      │
├──────────────────┼─────────────────┼─────────────────┼─────────────────┤
│ Xử lý sự kiện    │ Event loop      │ Interrupts (ISR)│ poll/epoll,     │
│                  │                 │ Timer, DMA      │ signal handlers │
├──────────────────┼─────────────────┼─────────────────┼─────────────────┤
│ Đa nhiệm         │ Threads         │ RTOS tasks hoặc │ Threads,        │
│                  │                 │ Super loop      │ Processes       │
├──────────────────┼─────────────────┼─────────────────┼─────────────────┤
│ Quản lý lỗi      │ Exception,      │ Error codes,    │ errno, signals, │
│                  │ errno           │ watchdog        │ exception       │
├──────────────────┼─────────────────┼─────────────────┼─────────────────┤
│ Năng lượng       │ Không quan tâm  │ RẤT QUAN TRỌNG  │ Quan trọng      │
│                  │                 │ Sleep modes     │ Power management│
└──────────────────┴─────────────────┴─────────────────┴─────────────────┘
```

---

##### 📋 CHECKLIST TƯ DUY THIẾT KẾ

**Khi bắt đầu BẤT KỲ dự án nào, hãy đi qua checklist này:**

```
┌─────────────────────────────────────────────────────────────────┐
│              ✅ CHECKLIST TƯ DUY THIẾT KẾ                       │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  📝 PHASE 1: HIỂU VẤN ĐỀ                                        │
│  □ Đã đọc kỹ requirements?                                      │
│  □ Đã xác định INPUT của hệ thống?                              │
│  □ Đã xác định OUTPUT mong muốn?                                │
│  □ Đã biết các constraints (bộ nhớ, tốc độ, năng lượng)?        │
│                                                                 │
│  📊 PHASE 2: MÔ HÌNH HÓA DỮ LIỆU                                │
│  □ Đã liệt kê tất cả entities (thực thể)?                       │
│  □ Mỗi entity đã có đầy đủ attributes (thuộc tính)?             │
│  □ Đã xác định relationships (quan hệ) giữa các entities?       │
│  □ Đã chọn cách lưu trữ phù hợp với platform?                   │
│                                                                 │
│  ⚙️ PHASE 3: THIẾT KẾ HÀNH VI                                   │
│  □ Đã liệt kê operations cho mỗi entity?                        │
│  □ Đã xác định states và transitions (nếu có)?                  │
│  □ Đã xác định events/interrupts cần xử lý?                     │
│  □ Đã thiết kế error handling?                                  │
│                                                                 │
│  🏗️ PHASE 4: CẤU TRÚC CODE                                      │
│  □ Đã thiết kế function signatures?                             │
│  □ Đã phân chia modules hợp lý?                                 │
│  □ Đã xác định dependencies giữa modules?                       │
│  □ Đã tạo project structure?                                    │
│                                                                 │
│  📐 PHASE 5: KIỂM TRA THIẾT KẾ                                  │
│  □ Thiết kế có đáp ứng TẤT CẢ requirements?                     │
│  □ Thiết kế có phù hợp với constraints của platform?            │
│  □ Có thể mở rộng (extensible) trong tương lai?                 │
│  □ Đã vẽ diagram tổng quan?                                     │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

##### 💡 MẸO TƯ DUY CHO TỪNG NỀN TẢNG

**🖥️ Desktop Application:**

```
Tư duy chính: "Thoải mái với tài nguyên, tập trung vào UX và maintainability"

✓ Dùng dynamic memory (malloc) tự do
✓ Dùng thư viện tiêu chuẩn (stdio, stdlib)
✓ File I/O với fopen/fread/fwrite
✓ Tập trung vào: Clean code, error handling, user experience
```

**🔧 Embedded MCU (STM32, AVR, ESP32...):**

```
Tư duy chính: "Tối ưu tài nguyên, nghĩ về timing và interrupts"

✓ Ưu tiên static allocation, tránh malloc
✓ Dùng HAL/driver của MCU
✓ Nghĩ về: "Cái này có cần interrupt không?"
✓ Nghĩ về: "Cái này mất bao lâu? Có block không?"
✓ Luôn có Error Codes + Watchdog
✓ Xem xét Power Management (sleep modes)

Câu hỏi then chốt:
├── "Cần bao nhiêu RAM/Flash?"
├── "Có real-time requirement không?"
├── "Dùng RTOS hay Super Loop?"
└── "Có cần tiết kiệm pin không?"
```

**🐧 Embedded Linux (Raspberry Pi, BeagleBone...):**

```
Tư duy chính: "Tận dụng Linux ecosystem, nghĩ về processes và IPC"

✓ Dùng được thư viện Linux (pthread, sqlite3, libcurl...)
✓ Truy cập hardware qua sysfs (/sys/class/gpio/...)
✓ Dùng file descriptors cho mọi thứ
✓ Nghĩ về: "Đây là daemon hay command-line tool?"
✓ Nghĩ về: "Các process giao tiếp với nhau như thế nào?"

Câu hỏi then chốt:
├── "Chạy như daemon hay foreground?"
├── "Cần IPC gì?" (socket/pipe/shared memory/MQTT)
├── "Log như thế nào?" (syslog/file)
└── "Cần systemd service không?"
```

---

##### 🔄 SƠ ĐỒ TƯ DUY: Từ Requirements Đến Code

```
┌─────────────────────────────────────────────────────────────────┐
│                  QUY TRÌNH TƯ DUY THIẾT KẾ                      │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│   ┌───────────────┐                                             │
│   │ REQUIREMENTS  │                                             │
│   │  "Cần làm gì" │                                             │
│   └───────┬───────┘                                             │
│           │                                                     │
│           ▼ Hỏi: "Quản lý những gì?"                            │
│   ┌───────────────┐                                             │
│   │   ENTITIES    │ (Book, User, LED, Sensor, Device...)        │
│   │   "Thực thể"  │                                             │
│   └───────┬───────┘                                             │
│           │                                                     │
│           ▼ Hỏi: "Mỗi thực thể có thuộc tính gì?"               │
│   ┌───────────────┐                                             │
│   │    STRUCTS    │ typedef struct { ... } Book;                │
│   │   "Cấu trúc"  │                                             │
│   └───────┬───────┘                                             │
│           │                                                     │
│           ▼ Hỏi: "Với mỗi thực thể, làm gì?"                    │
│   ┌───────────────┐                                             │
│   │  OPERATIONS   │ Add, Remove, Update, Find, Display...       │
│   │   "Thao tác"  │                                             │
│   └───────┬───────┘                                             │
│           │                                                     │
│           ▼ Hỏi: "Function signature như thế nào?"              │
│   ┌───────────────┐                                             │
│   │  FUNCTIONS    │ ErrorCode add_book(Library*, Book);         │
│   │   "Hàm"       │                                             │
│   └───────┬───────┘                                             │
│           │                                                     │
│           ▼ Hỏi: "Nhóm vào modules nào?"                        │
│   ┌───────────────┐                                             │
│   │   MODULES     │ book.c, user.c, led.c, gpio.c...            │
│   │   "File"      │                                             │
│   └───────┬───────┘                                             │
│           │                                                     │
│           ▼ Hỏi: "Tổ chức thư mục như thế nào?"                 │
│   ┌───────────────┐                                             │
│   │  STRUCTURE    │ src/, include/, Makefile                    │
│   │  "Cấu trúc"   │                                             │
│   └───────┬───────┘                                             │
│           │                                                     │
│           ▼                                                     │
│   ┌───────────────┐                                             │
│   │     CODE!     │ 🚀 Bắt đầu implement!                       │
│   └───────────────┘                                             │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

##### 🎓 BÀI TẬP RÈN LUYỆN TƯ DUY

Trước khi đến các ví dụ chi tiết, hãy thử tự thiết kế với các đề bài sau:

```
┌─────────────────────────────────────────────────────────────────┐
│              📝 BÀI TẬP TỰ THỰC HÀNH                            │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  🔰 CẤP ĐỘ 1 - Desktop:                                         │
│  ├── Todo List Manager                                          │
│  ├── Student Grade Calculator                                   │
│  └── Simple Bank Account System                                 │
│                                                                 │
│  🔧 CẤP ĐỘ 2 - Embedded MCU:                                    │
│  ├── Digital Clock with Alarm (7-segment + buttons)             │
│  ├── DC Motor Speed Controller (PWM + encoder)                  │
│  └── Simple Keypad Lock System (4x4 keypad + relay)             │
│                                                                 │
│  🐧 CẤP ĐỘ 3 - Embedded Linux:                                  │
│  ├── Weather Station Logger (sensors + web dashboard)           │
│  ├── Home Security Camera (motion detect + notification)        │
│  └── Plant Watering System (sensors + pump + scheduler)         │
│                                                                 │
│  💡 Với mỗi bài, hãy:                                           │
│     1. Liệt kê ENTITIES                                         │
│     2. Vẽ ra STRUCTS                                            │
│     3. Liệt kê OPERATIONS                                       │
│     4. Viết FUNCTION SIGNATURES                                 │
│     5. Phân chia MODULES                                        │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

**Yêu cầu:**
- Quản lý sách (thêm, sửa, xóa, tìm)
- Quản lý người dùng (thêm, sửa, xóa, tìm)
- Mượn/trả sách
- Lưu file

---

##### ✏️ BƯỚC 1: Xác Định DỮ LIỆU

**Hỏi:** "Hệ thống cần quản lý những GÌ?"

```
Liệt kê các "thực thể" (entities):
─────────────────────────────────────────

1️⃣ SÁCH (Book)
   - ID sách
   - Tên sách
   - Tác giả
   - Năm xuất bản
   - Đang được mượn? (có/không)
   - Ai đang mượn? (ID người mượn)

2️⃣ NGƯỜI DÙNG (User)
   - ID người dùng
   - Tên
   - Số sách đang mượn
   - Danh sách ID sách đang mượn

3️⃣ THƯ VIỆN (Library) - Container chứa tất cả
   - Danh sách sách
   - Số lượng sách
   - Danh sách người dùng
   - Số lượng người dùng
```

**💡 Mẹo:** Hãy nghĩ như đang thiết kế database!

---

##### ✏️ BƯỚC 2: Thiết Kế DATA STRUCTURES

**Chuyển từ danh sách ở Bước 1 thành struct:**

```c
// ===== Bước 2: Định nghĩa structs =====

// Constants - Giới hạn
#define MAX_BOOKS 1000
#define MAX_USERS 500
#define MAX_TITLE 100
#define MAX_NAME 50
#define MAX_BORROWED 5

// Error codes - Để xử lý lỗi
typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER = -1,
    ERROR_INVALID_INPUT = -2,
    ERROR_NOT_FOUND = -3,
    ERROR_DUPLICATE_ID = -4,
    ERROR_FULL = -5,
    ERROR_ALREADY_BORROWED = -6
} ErrorCode;

// Book structure
typedef struct {
    int id;                    // ID sách (unique)
    char title[MAX_TITLE];     // Tên sách
    char author[MAX_NAME];     // Tác giả
    int year;                  // Năm xuất bản
    bool is_borrowed;          // Đang được mượn?
    int borrowed_by;           // ID người mượn (-1 nếu chưa mượn)
} Book;

// User structure
typedef struct {
    int id;                         // ID người dùng (unique)
    char name[MAX_NAME];            // Tên
    int borrowed_count;             // Số sách đang mượn
    int borrowed_books[MAX_BORROWED]; // ID các sách đang mượn
} User;

// Library - Container chứa tất cả
typedef struct {
    Book books[MAX_BOOKS];     // Mảng sách
    int book_count;            // Số sách hiện có
    User users[MAX_USERS];     // Mảng người dùng
    int user_count;            // Số người dùng
} Library;
```

---

##### ✏️ BƯỚC 3: Xác Định OPERATIONS

**Hỏi:** "Với mỗi dữ liệu, cần làm gì?"

```
┌─────────────────────────────────────────────────────────────────┐
│                    OPERATIONS CHO TỪNG DỮ LIỆU                  │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  📚 BOOK OPERATIONS:                                            │
│  ├── CREATE: Thêm sách mới                                      │
│  ├── READ:   Tìm sách theo ID                                   │
│  │           Tìm sách theo tên                                  │
│  │           Tìm sách theo tác giả                              │
│  │           Hiển thị tất cả sách                               │
│  ├── UPDATE: Cập nhật thông tin sách                            │
│  └── DELETE: Xóa sách                                           │
│                                                                 │
│  👤 USER OPERATIONS:                                            │
│  ├── CREATE: Thêm người dùng mới                                │
│  ├── READ:   Tìm người dùng theo ID                             │
│  │           Hiển thị tất cả người dùng                         │
│  ├── UPDATE: Cập nhật thông tin người dùng                      │
│  └── DELETE: Xóa người dùng                                     │
│                                                                 │
│  📖 BORROW/RETURN OPERATIONS:                                   │
│  ├── Mượn sách                                                  │
│  └── Trả sách                                                   │
│                                                                 │
│  🛠️ UTILITY OPERATIONS:                                         │
│  ├── Validate ID                                                │
│  ├── Validate string                                            │
│  ├── Clear input buffer                                         │
│  └── Trim whitespace                                            │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

##### ✏️ BƯỚC 4: Thiết Kế FUNCTION SIGNATURES

**Viết "hợp đồng" cho mỗi function:**

```c
// ===== BOOK FUNCTIONS =====

// Helpers
int get_book_count(Library *lib);
int find_book_index_by_id(Library *lib, int id);

// CRUD
ErrorCode add_book(Library *lib, Book book);
Book* find_book_by_id(Library *lib, int id);
ErrorCode update_book(Library *lib, int id, Book new_data);
ErrorCode delete_book(Library *lib, int id);

// Search
void search_books_by_title(Library *lib, const char *title);
void search_books_by_author(Library *lib, const char *author);

// Display
void display_book(const Book *book);
void display_all_books(Library *lib);


// ===== USER FUNCTIONS =====

// Helpers
int get_user_count(Library *lib);
int find_user_index_by_id(Library *lib, int id);

// CRUD
ErrorCode add_user(Library *lib, User user);
User* find_user_by_id(Library *lib, int id);
ErrorCode update_user(Library *lib, int id, User new_data);
ErrorCode delete_user(Library *lib, int id);

// Display
void display_user(const User *user);
void display_all_users(Library *lib);


// ===== MANAGEMENT FUNCTIONS =====

ErrorCode borrow_book(Library *lib, int user_id, int book_id);
ErrorCode return_book(Library *lib, int user_id, int book_id);
void display_borrowed_books(Library *lib, int user_id);


// ===== UTILITY FUNCTIONS =====

bool validate_id(int id);
bool validate_string(const char *str);
void clear_input_buffer(void);
void trim_whitespace(char *str);
void safe_strcpy(char *dest, const char *src, size_t size);
```

**💡 Mẹo viết function signature:**
```
1. Tên function: động_từ + danh_từ (add_book, find_user)
2. Tham số đầu tiên: thường là pointer đến container (Library *lib)
3. Return type: 
   - ErrorCode nếu có thể fail
   - Pointer nếu tìm kiếm
   - void nếu chỉ hiển thị
```

---

##### ✏️ BƯỚC 5: Phân Chia MODULES

**Nhóm các function liên quan vào cùng 1 file:**

```
┌─────────────────────────────────────────────────────────────────┐
│                    PHÂN CHIA MODULES                            │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  📁 common.h                                                    │
│  └── Constants, enums, structs                                  │
│      (Không có .c vì chỉ định nghĩa, không có implementation)   │
│                                                                 │
│  📁 utils.h / utils.c                                           │
│  └── Utility functions (validate, clear buffer, trim...)        │
│                                                                 │
│  📁 book.h / book.c                                             │
│  └── All book-related functions                                 │
│                                                                 │
│  📁 user.h / user.c                                             │
│  └── All user-related functions                                 │
│                                                                 │
│  📁 management.h / management.c                                 │
│  └── Borrow/return functions                                    │
│                                                                 │
│  📁 main.c                                                      │
│  └── Entry point, menu, user interaction                        │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

##### ✏️ BƯỚC 6: Thiết Kế PROJECT STRUCTURE

```
📁 LIBRARY_MANAGEMENT/
├── 📁 include/          # Header files (.h)
│   ├── common.h         # Structs, enums, constants
│   ├── utils.h          # Utility function declarations
│   ├── book.h           # Book function declarations
│   ├── user.h           # User function declarations
│   └── management.h     # Borrow/return declarations
│
├── 📁 src/              # Source files (.c)
│   ├── main.c           # Entry point
│   ├── utils.c          # Utility implementations
│   ├── book.c           # Book implementations
│   ├── user.c           # User implementations
│   └── management.c     # Borrow/return implementations
│
├── 📁 obj/              # Object files (.o) - tạo khi compile
│
├── 📁 data/             # Data files (lưu trữ)
│   └── library.dat
│
├── 📁 docs/             # Documentation
│   └── README.md
│
├── 📁 tests/            # Unit tests
│   ├── test_book.c
│   └── test_user.c
│
├── Makefile             # Build script
└── README.md            # Project description
```

---

##### ✏️ BƯỚC 7: Vẽ SYSTEM DIAGRAM

```
┌─────────────────────────────────────────────────────────────────┐
│                    LIBRARY MANAGEMENT SYSTEM                    │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│                         ┌─────────┐                             │
│                         │ main.c  │                             │
│                         │ (Menu)  │                             │
│                         └────┬────┘                             │
│                              │                                  │
│              ┌───────────────┼───────────────┐                  │
│              │               │               │                  │
│              ▼               ▼               ▼                  │
│       ┌─────────┐     ┌─────────┐    ┌────────────┐             │
│       │ book.c  │     │ user.c  │    │management.c│             │
│       └────┬────┘     └────┬────┘    └─────┬──────┘             │
│            │               │               │                    │
│            └───────────────┼───────────────┘                    │
│                            │                                    │
│                            ▼                                    │
│                      ┌─────────┐                                │
│                      │ utils.c │                                │
│                      └────┬────┘                                │
│                           │                                     │
│                           ▼                                     │
│                      ┌─────────┐                                │
│                      │common.h │                                │
│                      │(structs)│                                │
│                      └─────────┘                                │
│                                                                 │
│  DEPENDENCY RULE:                                               │
│  common.h ← utils ← book, user ← management ← main              │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

#### 🎯 TỔNG KẾT: CÔNG THỨC THIẾT KẾ

**Khi gặp BẤT KỲ dự án nào, làm theo thứ tự:**

```
1️⃣ DỮ LIỆU    → "Cần quản lý cái gì?"
                 → Liệt kê entities và attributes

2️⃣ STRUCT     → "Chuyển thành code như nào?"
                 → Viết typedef struct

3️⃣ OPERATIONS → "Với mỗi dữ liệu, cần làm gì?"
                 → Liệt kê CRUD + các thao tác khác

4️⃣ FUNCTIONS  → "Signature như thế nào?"
                 → Viết khai báo function

5️⃣ MODULES    → "Chia file như nào?"
                 → Nhóm functions liên quan

6️⃣ STRUCTURE  → "Tổ chức thư mục ra sao?"
                 → Vẽ cây thư mục

7️⃣ DIAGRAM    → "Tổng quan như thế nào?"
                 → Vẽ sơ đồ quan hệ
```

---

#### ✅ CHECKLIST Trước Khi Code

```
□ Đã liệt kê TẤT CẢ entities (dữ liệu)?
□ Đã viết struct cho mỗi entity?
□ Đã liệt kê operations cho mỗi entity?
□ Đã viết function signatures?
□ Đã phân chia modules?
□ Đã tạo cấu trúc thư mục?
□ Đã vẽ sơ đồ tổng quan?

→ Nếu tất cả ✅, BẮT ĐẦU CODE! 🚀
```

---

#### 📝 THỰC HÀNH: Thiết Kế LED Controller (STM32)

> 🔧 **Nền tảng:** Embedded (STM32 MCU)
> 
> Đây là ví dụ cơ bản nhất để hiểu quy trình thiết kế embedded

**Yêu cầu:**
- Điều khiển 4 LED bằng 4 nút nhấn
- LED có 2 chế độ: Manual (nhấn nút) và Auto (chớp tắt tự động)
- Có xử lý debounce cho nút nhấn

---

##### ✏️ BƯỚC 1: Xác Định DỮ LIỆU

**Hỏi:** "Hệ thống cần quản lý những GÌ?"

```
Liệt kê các "thực thể" (entities):
─────────────────────────────────────────

1️⃣ LED (4 cái)
   - Số hiệu LED (0-3)
   - Port và Pin GPIO
   - Trạng thái (ON/OFF)
   - Chế độ (MANUAL/AUTO)
   - Chu kỳ chớp (ms)

2️⃣ BUTTON (4 cái)
   - Số hiệu nút (0-3)
   - Port và Pin GPIO
   - Trạng thái (PRESSED/RELEASED)
   - Thời điểm nhấn cuối (debounce)

3️⃣ SYSTEM (Controller chứa tất cả)
   - Mảng LED
   - Mảng Button
   - Trạng thái hoạt động
```

**💡 Mẹo:** Trong embedded, luôn nghĩ về hardware pins!

---

##### ✏️ BƯỚC 2: Thiết Kế DATA STRUCTURES

**Chuyển từ danh sách ở Bước 1 thành struct:**

```c
// ===== config.h - Hardware pins =====
#define NUM_LEDS    4
#define NUM_BUTTONS 4

// Pin definitions
#define LED0_PORT   GPIOA
#define LED0_PIN    GPIO_PIN_0
// ... more pins

// ===== led_types.h - Data structures =====

// Error codes
typedef enum {
    LED_OK = 0,
    LED_ERROR_INVALID_ID = -1,
    LED_ERROR_NULL_PTR = -2
} LedError;

// Trạng thái LED
typedef enum {
    LED_OFF = 0,
    LED_ON  = 1
} LedState;

// Chế độ LED
typedef enum {
    MODE_MANUAL,     // Điều khiển bằng nút
    MODE_AUTO_BLINK  // Tự động chớp tắt
} LedMode;

// Cấu trúc LED
typedef struct {
    uint8_t id;            // ID: 0-3
    GPIO_TypeDef *port;    // GPIOA, GPIOB...
    uint16_t pin;          // GPIO_PIN_0, GPIO_PIN_1...
    LedState state;        // ON/OFF
    LedMode mode;          // MANUAL/AUTO
    uint32_t blink_period; // Chu kỳ chớp (ms)
    uint32_t last_toggle;  // Thời điểm toggle cuối
} Led;

// Cấu trúc Button
typedef struct {
    uint8_t id;            // ID: 0-3
    GPIO_TypeDef *port;
    uint16_t pin;
    bool is_pressed;
    bool was_pressed;      // Trạng thái trước đó (edge detection)
    uint32_t last_press;   // Thời điểm nhấn cuối (debounce)
} Button;

// Container chứa tất cả
typedef struct {
    Led leds[NUM_LEDS];
    Button buttons[NUM_BUTTONS];
    bool system_running;
    uint32_t tick_count;   // System tick counter
} LedController;
```

**💡 Mẹo:** Trong embedded, thêm `last_xxx` để tracking thời gian!

---

##### ✏️ BƯỚC 3: Xác Định OPERATIONS

**Hỏi:** "Với mỗi dữ liệu, cần làm gì?"

```
┌─────────────────────────────────────────────────────────────────┐
│                    OPERATIONS CHO TỪNG DỮ LIỆU                  │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  💡 LED OPERATIONS:                                             │
│  ├── INIT:    Khởi tạo GPIO output                              │
│  ├── ON:      Bật LED (set pin HIGH)                            │
│  ├── OFF:     Tắt LED (set pin LOW)                             │
│  ├── TOGGLE:  Đổi trạng thái                                    │
│  ├── SET_MODE: Đặt chế độ Manual/Auto                           │
│  └── BLINK:   Xử lý chớp tắt (gọi periodic)                     │
│                                                                 │
│  🔘 BUTTON OPERATIONS:                                          │
│  ├── INIT:    Khởi tạo GPIO input                               │
│  ├── READ:    Đọc trạng thái vật lý                             │
│  ├── UPDATE:  Cập nhật với debounce                             │
│  └── IS_PRESSED: Kiểm tra edge (vừa nhấn)                       │
│                                                                 │
│  🎮 CONTROLLER OPERATIONS:                                      │
│  ├── INIT:    Khởi tạo tất cả                                   │
│  ├── RUN:     Main loop                                         │
│  ├── TICK:    Gọi mỗi 1ms (từ SysTick)                          │
│  └── HANDLE:  Xử lý sự kiện button                              │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

##### ✏️ BƯỚC 4: Thiết Kế FUNCTION SIGNATURES

**Viết "hợp đồng" cho mỗi function:**

```c
// ===== led.h =====

// Khởi tạo và điều khiển
void Led_Init(Led *led, GPIO_TypeDef *port, uint16_t pin, uint8_t id);
void Led_On(Led *led);
void Led_Off(Led *led);
void Led_Toggle(Led *led);

// Cấu hình
void Led_SetMode(Led *led, LedMode mode);
void Led_SetBlinkPeriod(Led *led, uint32_t period_ms);

// Task (gọi periodic)
void Led_BlinkTask(Led *led, uint32_t current_tick);


// ===== button.h =====

void Button_Init(Button *btn, GPIO_TypeDef *port, uint16_t pin, uint8_t id);
void Button_Update(Button *btn, uint32_t current_tick);  // Gọi mỗi 1ms
bool Button_IsPressed(Button *btn);   // Edge detection
bool Button_IsHeld(Button *btn);      // Level detection


// ===== led_controller.h =====

LedError LedController_Init(LedController *ctrl);
void LedController_Run(LedController *ctrl);           // Main loop
void LedController_Tick(LedController *ctrl);          // Gọi từ SysTick
void LedController_HandleButton(LedController *ctrl, uint8_t btn_id);
```

**💡 Mẹo:** Trong embedded, tách riêng `Init`, `Task` periodic, và `Handler`!

---

##### ✏️ BƯỚC 5: Phân Chia MODULES

**Nhóm các function liên quan vào cùng 1 file:**

```
┌─────────────────────────────────────────────────────────────────┐
│                    PHÂN CHIA MODULES                            │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  📁 config.h                                                    │
│  └── Pin definitions, constants                                 │
│      (Hardware-specific, thay đổi theo board)                   │
│                                                                 │
│  📁 led_types.h                                                 │
│  └── Enums, structs definitions                                 │
│                                                                 │
│  📁 led.h / led.c                                               │
│  └── LED control functions                                      │
│                                                                 │
│  📁 button.h / button.c                                         │
│  └── Button read + debounce                                     │
│                                                                 │
│  📁 led_controller.h / led_controller.c                         │
│  └── Main controller logic                                      │
│                                                                 │
│  📁 main.c                                                      │
│  └── Entry point, interrupt handlers                            │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

##### ✏️ BƯỚC 6: Thiết Kế PROJECT STRUCTURE

```
📁 LED_CONTROLLER/
├── 📁 Core/
│   ├── 📁 Inc/                  # Header files
│   │   ├── main.h
│   │   ├── config.h             # Pin definitions
│   │   ├── led_types.h          # Structs, enums
│   │   ├── led.h                # LED functions
│   │   ├── button.h             # Button functions
│   │   └── led_controller.h     # Main controller
│   │
│   └── 📁 Src/                  # Source files
│       ├── main.c               # Entry point
│       ├── led.c
│       ├── button.c
│       ├── led_controller.c
│       └── stm32f1xx_it.c       # Interrupt handlers
│
├── 📁 Drivers/                  # STM32 HAL (generated)
│   ├── STM32F1xx_HAL_Driver/
│   └── CMSIS/
│
├── Makefile                     # Build script
├── STM32F103.ld                 # Linker script
└── README.md
```

---

##### ✏️ BƯỚC 7: Vẽ SYSTEM DIAGRAM

```
┌─────────────────────────────────────────────────────────────────┐
│                    LED CONTROLLER SYSTEM                        │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│                         ┌─────────────┐                         │
│                         │   main.c    │                         │
│                         │  (Startup)  │                         │
│                         └──────┬──────┘                         │
│                                │                                │
│              ┌─────────────────┼─────────────────┐              │
│              │                 │                 │              │
│              ▼                 ▼                 ▼              │
│       ┌──────────┐     ┌──────────┐     ┌──────────────┐       │
│       │  led.c   │     │ button.c │     │led_controller│       │
│       └────┬─────┘     └────┬─────┘     └──────┬───────┘       │
│            │                │                  │                │
│            └────────────────┼──────────────────┘                │
│                             │                                   │
│                             ▼                                   │
│                      ┌────────────┐                             │
│                      │  STM32 HAL │                             │
│                      │   (GPIO)   │                             │
│                      └─────┬──────┘                             │
│                            │                                    │
│  ════════════════════════════════════════════════════════════  │
│                    HARDWARE LAYER                               │
│  ════════════════════════════════════════════════════════════  │
│                            │                                    │
│            ┌───────────────┼───────────────┐                   │
│            ▼               ▼               ▼                   │
│       ┌────────┐     ┌────────┐     ┌────────┐                 │
│       │  LED0  │     │  LED1  │     │  BTN0  │ ...             │
│       │ PA0    │     │ PA1    │     │ PB0    │                 │
│       └────────┘     └────────┘     └────────┘                 │
│                                                                 │
│  DEPENDENCY: config.h ← led_types ← led,button ← controller    │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

#### 📝 THỰC HÀNH: Thiết Kế UART Data Logger (STM32)

> 🔧 **Nền tảng:** Embedded (STM32 MCU)
> 
> Dự án trung bình - Làm việc với UART, Flash, State Machine

**Yêu cầu:**
- Nhận dữ liệu sensor (nhiệt độ, độ ẩm) qua UART
- Lưu dữ liệu vào Flash nội (tối đa 1000 bản ghi)
- Gửi dữ liệu lên PC qua UART khi có lệnh

---

##### ✏️ BƯỚC 1: Xác Định DỮ LIỆU

**Hỏi:** "Hệ thống cần quản lý những GÌ?"

```
Liệt kê các "thực thể" (entities):
─────────────────────────────────────────

1️⃣ SENSOR DATA (Dữ liệu sensor)
   - Nhiệt độ (float, °C)
   - Độ ẩm (float, %)
   - Timestamp (giây từ boot)
   - CRC/Checksum

2️⃣ UART (Giao tiếp serial)
   - Handle UART peripheral
   - Buffer nhận (RX)
   - Buffer gửi (TX)
   - Trạng thái (ready/busy)

3️⃣ FLASH STORAGE (Lưu trữ)
   - Địa chỉ bắt đầu vùng lưu
   - Số bản ghi tối đa
   - Số bản ghi hiện tại
   - Con trỏ ghi hiện tại

4️⃣ SYSTEM (State Machine)
   - Trạng thái: IDLE → RECEIVING → LOGGING → SENDING
   - Mã lỗi (nếu có)
   - Cờ yêu cầu (request flags)
```

**💡 Mẹo:** Vẽ State Machine diagram trước khi code!

---

##### ✏️ BƯỚC 2: Thiết Kế DATA STRUCTURES

**Chuyển từ danh sách ở Bước 1 thành struct:**

```c
// ===== logger_types.h =====

#define MAX_RECORDS     1000
#define RX_BUFFER_SIZE  64
#define TX_BUFFER_SIZE  128
#define FLASH_BASE_ADDR 0x0800F000

// Error codes
typedef enum {
    LOGGER_OK = 0,
    LOGGER_ERROR_FLASH_FULL = -1,
    LOGGER_ERROR_UART = -2,
    LOGGER_ERROR_CRC = -3,
    LOGGER_ERROR_INVALID_DATA = -4
} LoggerError;

// Trạng thái hệ thống (State Machine)
typedef enum {
    STATE_IDLE,       // Chờ lệnh hoặc dữ liệu
    STATE_RECEIVING,  // Đang nhận dữ liệu từ sensor
    STATE_LOGGING,    // Đang ghi vào Flash
    STATE_SENDING,    // Đang gửi dữ liệu lên PC
    STATE_ERROR       // Có lỗi xảy ra
} SystemState;

// Dữ liệu sensor (1 bản ghi)
typedef struct {
    float temperature;      // Nhiệt độ (°C)
    float humidity;         // Độ ẩm (%)
    uint32_t timestamp;     // Seconds since boot
    uint16_t crc;           // CRC16 checksum
} SensorData;

// Cấu hình UART
typedef struct {
    UART_HandleTypeDef *huart;
    uint8_t rx_buffer[RX_BUFFER_SIZE];
    uint8_t tx_buffer[TX_BUFFER_SIZE];
    volatile uint16_t rx_index;
    volatile bool rx_complete;
    volatile bool tx_busy;
} UartDriver;

// Cấu hình Flash Storage
typedef struct {
    uint32_t base_address;      // Địa chỉ bắt đầu
    uint32_t current_address;   // Địa chỉ ghi tiếp theo
    uint16_t record_count;      // Số bản ghi đã lưu
    uint16_t max_records;       // Giới hạn bản ghi
} FlashStorage;

// Container chứa tất cả
typedef struct {
    UartDriver uart;
    FlashStorage flash;
    SensorData current_data;
    SystemState state;
    LoggerError last_error;
    uint32_t tick_count;
} DataLogger;
```

**💡 Mẹo:** Thêm `volatile` cho các biến thay đổi trong interrupt!

---

##### ✏️ BƯỚC 3: Xác Định OPERATIONS

**Hỏi:** "Với mỗi dữ liệu, cần làm gì?"

```
┌─────────────────────────────────────────────────────────────────┐
│                    OPERATIONS CHO TỪNG DỮ LIỆU                  │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  📡 UART OPERATIONS:                                            │
│  ├── INIT:     Khởi tạo UART với baudrate                       │
│  ├── SEND:     Gửi string/binary data                           │
│  ├── CALLBACK: Xử lý khi nhận byte (interrupt)                  │
│  └── PARSE:    Phân tích protocol từ buffer                     │
│                                                                 │
│  💾 FLASH OPERATIONS:                                           │
│  ├── INIT:     Khởi tạo, đọc số bản ghi hiện có                 │
│  ├── WRITE:    Ghi 1 bản ghi (SensorData)                       │
│  ├── READ:     Đọc bản ghi theo index                           │
│  ├── ERASE:    Xóa toàn bộ vùng lưu trữ                         │
│  └── GET_COUNT: Lấy số bản ghi                                  │
│                                                                 │
│  📊 LOGGER OPERATIONS:                                          │
│  ├── INIT:     Khởi tạo toàn bộ hệ thống                        │
│  ├── RUN:      Main loop (xử lý state machine)                  │
│  ├── SAVE:     Lưu current_data vào Flash                       │
│  ├── SEND_ALL: Gửi tất cả bản ghi lên PC                        │
│  └── HANDLE_CMD: Xử lý lệnh từ PC                               │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

##### ✏️ BƯỚC 4: Thiết Kế FUNCTION SIGNATURES

**Viết "hợp đồng" cho mỗi function:**

```c
// ===== uart_driver.h =====

LoggerError UART_Init(UartDriver *uart, UART_HandleTypeDef *huart);
void UART_SendString(UartDriver *uart, const char *str);
void UART_SendData(UartDriver *uart, const uint8_t *data, uint16_t len);
void UART_RxCallback(UartDriver *uart, uint8_t byte);  // Gọi từ IRQ
bool UART_IsDataReady(UartDriver *uart);
bool UART_ParseSensorData(UartDriver *uart, SensorData *data);
void UART_ClearBuffer(UartDriver *uart);


// ===== flash_storage.h =====

LoggerError Flash_Init(FlashStorage *flash);
LoggerError Flash_WriteRecord(FlashStorage *flash, const SensorData *data);
LoggerError Flash_ReadRecord(FlashStorage *flash, uint16_t index, 
                              SensorData *data);
LoggerError Flash_EraseAll(FlashStorage *flash);
uint16_t Flash_GetRecordCount(FlashStorage *flash);
bool Flash_IsFull(FlashStorage *flash);


// ===== data_logger.h =====

LoggerError Logger_Init(DataLogger *logger, UART_HandleTypeDef *huart);
void Logger_Run(DataLogger *logger);              // Main loop
void Logger_Tick(DataLogger *logger);             // Gọi mỗi 1ms
LoggerError Logger_SaveCurrentData(DataLogger *logger);
LoggerError Logger_SendAllToPC(DataLogger *logger);
void Logger_HandleCommand(DataLogger *logger, uint8_t cmd);
SystemState Logger_GetState(DataLogger *logger);
```

**💡 Mẹo:** Return `ErrorCode` để caller có thể xử lý lỗi!

---

##### ✏️ BƯỚC 5: Phân Chia MODULES

**Nhóm các function liên quan vào cùng 1 file:**

```
┌─────────────────────────────────────────────────────────────────┐
│                    PHÂN CHIA MODULES                            │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  📁 logger_types.h                                              │
│  └── Enums, structs, constants                                  │
│                                                                 │
│  📁 uart_driver.h / uart_driver.c                               │
│  └── UART init, send, receive, parse                            │
│                                                                 │
│  📁 flash_storage.h / flash_storage.c                           │
│  └── Flash read, write, erase                                   │
│                                                                 │
│  📁 sensor_protocol.h / sensor_protocol.c                       │
│  └── Protocol parsing, CRC calculation                          │
│                                                                 │
│  📁 data_logger.h / data_logger.c                               │
│  └── Main state machine, coordination                           │
│                                                                 │
│  📁 main.c                                                      │
│  └── Entry point, interrupt handlers                            │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

##### ✏️ BƯỚC 6: Thiết Kế PROJECT STRUCTURE

```
📁 DATA_LOGGER/
├── 📁 Core/
│   ├── 📁 Inc/
│   │   ├── main.h
│   │   ├── logger_types.h       # Structs, enums
│   │   ├── uart_driver.h
│   │   ├── flash_storage.h
│   │   ├── sensor_protocol.h
│   │   └── data_logger.h
│   │
│   └── 📁 Src/
│       ├── main.c
│       ├── uart_driver.c
│       ├── flash_storage.c
│       ├── sensor_protocol.c
│       ├── data_logger.c
│       └── stm32f1xx_it.c       # UART IRQ handler
│
├── 📁 Drivers/
├── Makefile
└── README.md
```

---

##### ✏️ BƯỚC 7: Vẽ SYSTEM DIAGRAM

```
┌─────────────────────────────────────────────────────────────────┐
│                    DATA LOGGER STATE MACHINE                    │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│            ┌──────────────────────────────────┐                 │
│            │                                  │                 │
│            ▼                                  │                 │
│       ┌─────────┐    Rx Complete         ┌─────────┐           │
│   ───▶│  IDLE   │───────────────────────▶│RECEIVING│           │
│       └────┬────┘                        └────┬────┘           │
│            │                                  │                 │
│            │ Send Command                     │ Parse OK        │
│            │                                  ▼                 │
│       ┌────┴────┐                        ┌─────────┐           │
│       │ SENDING │◀───── Send Done ───────│ LOGGING │           │
│       └─────────┘                        └─────────┘           │
│                                                                 │
│  ═══════════════════════════════════════════════════════════   │
│                     MODULE DEPENDENCIES                         │
│  ═══════════════════════════════════════════════════════════   │
│                                                                 │
│                      ┌─────────────┐                           │
│                      │ data_logger │                           │
│                      └──────┬──────┘                           │
│              ┌──────────────┼──────────────┐                   │
│              ▼              ▼              ▼                   │
│       ┌────────────┐ ┌────────────┐ ┌────────────┐             │
│       │uart_driver │ │flash_store │ │sensor_proto│             │
│       └─────┬──────┘ └─────┬──────┘ └────────────┘             │
│             │              │                                    │
│             ▼              ▼                                    │
│       ┌────────────────────────────┐                           │
│       │        STM32 HAL           │                           │
│       │   (UART, FLASH drivers)    │                           │
│       └────────────────────────────┘                           │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

#### 📝 THỰC HÀNH: Thiết Kế Smart Home Hub (Raspberry Pi + Linux)

> 🐧 **Nền tảng:** Embedded Linux (Raspberry Pi)
> 
> Dự án nâng cao - Làm việc với MQTT, SQLite, Web Server

**Yêu cầu:**
- Điều khiển các thiết bị smart home qua giao thức MQTT
- Lưu trữ thông tin thiết bị và lịch sử vào SQLite
- Cung cấp REST API và web interface để điều khiển

---

##### ✏️ BƯỚC 1: Xác Định DỮ LIỆU

**Hỏi:** "Hệ thống cần quản lý những GÌ?"

```
Liệt kê các "thực thể" (entities):
─────────────────────────────────────────

1️⃣ DEVICE (Thiết bị smart home)
   - ID thiết bị (unique)
   - Tên thiết bị
   - Loại (light/switch/sensor/thermostat)
   - Trạng thái online/offline
   - Giá trị (on/off hoặc số)
   - MQTT topic riêng

2️⃣ MQTT CLIENT
   - Broker address (IP hoặc hostname)
   - Port (default 1883)
   - Client ID
   - Connection status
   - Subscribed topics

3️⃣ DATABASE (SQLite)
   - Bảng devices (thông tin thiết bị)
   - Bảng event_logs (lịch sử thao tác)
   - Bảng schedules (hẹn giờ)

4️⃣ WEB SERVER
   - HTTP port (default 8080)
   - REST API endpoints
   - Static file serving
```

**💡 Mẹo:** Linux app dùng nhiều thư viện bên ngoài (mosquitto, sqlite3, mongoose)!

---

##### ✏️ BƯỚC 2: Thiết Kế DATA STRUCTURES

**Chuyển từ danh sách ở Bước 1 thành struct:**

```c
// ===== smarthome_types.h =====

#define MAX_DEVICES     50
#define MAX_NAME_LEN    32
#define MAX_TOPIC_LEN   64
#define MAX_PATH_LEN    128

// Error codes
typedef enum {
    SH_OK = 0,
    SH_ERROR_MQTT = -1,
    SH_ERROR_DATABASE = -2,
    SH_ERROR_DEVICE_NOT_FOUND = -3,
    SH_ERROR_DEVICE_LIMIT = -4
} SmartHomeError;

// Loại thiết bị
typedef enum {
    DEVICE_LIGHT,
    DEVICE_SWITCH,
    DEVICE_SENSOR,
    DEVICE_THERMOSTAT
} DeviceType;

// Trạng thái kết nối
typedef enum {
    DEVICE_OFFLINE,
    DEVICE_ONLINE,
    DEVICE_ERROR
} DeviceStatus;

// Thiết bị
typedef struct {
    int id;                        // ID unique
    char name[MAX_NAME_LEN];       // Tên hiển thị
    DeviceType type;               // Loại thiết bị
    DeviceStatus status;           // Online/Offline
    char mqtt_topic[MAX_TOPIC_LEN];// Topic MQTT
    int value;                     // Giá trị (0/1 hoặc sensor value)
    time_t last_update;            // Thời điểm cập nhật cuối
} Device;

// Cấu hình MQTT
typedef struct {
    char broker[64];               // IP hoặc hostname
    int port;                      // 1883
    char client_id[32];            // Unique client ID
    struct mosquitto *mosq;        // mosquitto library handle
    bool connected;
} MqttClient;

// Cấu hình Database
typedef struct {
    char db_path[MAX_PATH_LEN];    // Path to SQLite file
    sqlite3 *db;                   // SQLite handle
} Database;

// Container chứa tất cả
typedef struct {
    Device devices[MAX_DEVICES];
    int device_count;
    MqttClient mqtt;
    Database db;
    int web_port;
    volatile bool running;         // Cờ tắt server
} SmartHomeHub;
```

**💡 Mẹo:** Dùng thư viện libmosquitto cho MQTT, sqlite3 cho database!

---

##### ✏️ BƯỚC 3: Xác Định OPERATIONS

**Hỏi:** "Với mỗi dữ liệu, cần làm gì?"

```
┌─────────────────────────────────────────────────────────────────┐
│                    OPERATIONS CHO TỪNG DỮ LIỆU                  │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  🔌 DEVICE OPERATIONS:                                          │
│  ├── ADD:     Thêm thiết bị mới                                 │
│  ├── REMOVE:  Xóa thiết bị                                      │
│  ├── UPDATE:  Cập nhật trạng thái/giá trị                       │
│  ├── GET:     Lấy thông tin theo ID                             │
│  └── GET_ALL: Lấy danh sách tất cả                              │
│                                                                 │
│  📡 MQTT OPERATIONS:                                            │
│  ├── INIT:       Khởi tạo mosquitto client                      │
│  ├── CONNECT:    Kết nối broker                                 │
│  ├── SUBSCRIBE:  Đăng ký nhận message từ topic                  │
│  ├── PUBLISH:    Gửi message đến topic                          │
│  ├── CALLBACK:   Xử lý message nhận được                        │
│  └── DISCONNECT: Ngắt kết nối                                   │
│                                                                 │
│  💾 DATABASE OPERATIONS:                                        │
│  ├── INIT:    Mở database, tạo tables nếu chưa có               │
│  ├── SAVE:    Lưu thông tin device                              │
│  ├── LOAD:    Load tất cả devices                               │
│  ├── LOG:     Ghi event log                                     │
│  └── QUERY:   Đọc logs/schedules                                │
│                                                                 │
│  🌐 WEB API OPERATIONS:                                         │
│  ├── GET /api/devices         : Lấy tất cả devices              │
│  ├── GET /api/devices/{id}    : Lấy 1 device                    │
│  ├── POST /api/devices        : Thêm device                     │
│  ├── PUT /api/devices/{id}    : Cập nhật device                 │
│  └── DELETE /api/devices/{id} : Xóa device                      │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

##### ✏️ BƯỚC 4: Thiết Kế FUNCTION SIGNATURES

**Viết "hợp đồng" cho mỗi function:**

```c
// ===== device.h =====

SmartHomeError Device_Add(SmartHomeHub *hub, const Device *device);
SmartHomeError Device_Remove(SmartHomeHub *hub, int device_id);
SmartHomeError Device_Update(SmartHomeHub *hub, int device_id, int value);
Device* Device_GetById(SmartHomeHub *hub, int device_id);
int Device_GetAll(SmartHomeHub *hub, Device **devices);
void Device_ToJson(const Device *dev, char *json_buf, size_t buf_size);


// ===== mqtt_client.h =====

SmartHomeError MQTT_Init(MqttClient *client, const char *broker, int port);
SmartHomeError MQTT_Connect(MqttClient *client);
SmartHomeError MQTT_Subscribe(MqttClient *client, const char *topic);
SmartHomeError MQTT_Publish(MqttClient *client, const char *topic, 
                            const char *payload);
void MQTT_OnMessage(struct mosquitto *mosq, void *userdata, 
                    const struct mosquitto_message *msg);  // Callback
void MQTT_Disconnect(MqttClient *client);
void MQTT_Loop(MqttClient *client);  // Gọi trong main loop


// ===== database.h =====

SmartHomeError DB_Init(Database *db, const char *path);
SmartHomeError DB_SaveDevice(Database *db, const Device *device);
SmartHomeError DB_LoadDevices(Database *db, Device *devices, int max, 
                               int *count);
SmartHomeError DB_LogEvent(Database *db, int device_id, const char *event);
SmartHomeError DB_GetLogs(Database *db, int device_id, char *buffer, 
                           size_t buf_size);
void DB_Close(Database *db);


// ===== web_server.h =====

SmartHomeError WebServer_Init(SmartHomeHub *hub, int port);
void WebServer_Run(SmartHomeHub *hub);   // Blocking
void WebServer_Stop(SmartHomeHub *hub);
// Internal handlers
static void handle_api_devices(struct mg_connection *c, 
                                struct mg_http_message *hm,
                                SmartHomeHub *hub);
```

**💡 Mẹo:** Dùng JSON cho REST API! Thêm hàm `_ToJson()` cho mỗi struct.

---

##### ✏️ BƯỚC 5: Phân Chia MODULES

**Nhóm các function liên quan vào cùng 1 file:**

```
┌─────────────────────────────────────────────────────────────────┐
│                    PHÂN CHIA MODULES                            │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  📁 smarthome_types.h                                           │
│  └── Enums, structs, error codes                                │
│                                                                 │
│  📁 device.h / device.c                                         │
│  └── Device CRUD operations                                     │
│                                                                 │
│  📁 mqtt_client.h / mqtt_client.c                               │
│  └── MQTT connect, publish, subscribe                           │
│      (sử dụng libmosquitto)                                     │
│                                                                 │
│  📁 database.h / database.c                                     │
│  └── SQLite operations                                          │
│      (sử dụng sqlite3)                                          │
│                                                                 │
│  📁 web_server.h / web_server.c                                 │
│  └── HTTP server, REST API                                      │
│      (sử dụng mongoose)                                         │
│                                                                 │
│  📁 json_utils.h / json_utils.c                                 │
│  └── JSON parsing/generation helpers                            │
│                                                                 │
│  📁 main.c                                                      │
│  └── Entry point, signal handlers, daemon                       │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

##### ✏️ BƯỚC 6: Thiết Kế PROJECT STRUCTURE

```
📁 smart_home_hub/
├── 📁 src/
│   ├── main.c               # Entry point, daemon init
│   ├── device.c             # Device management
│   ├── mqtt_client.c        # MQTT operations
│   ├── database.c           # SQLite operations
│   ├── web_server.c         # HTTP server (mongoose)
│   └── json_utils.c         # JSON helpers
│
├── 📁 include/
│   ├── smarthome_types.h    # Structs, enums
│   ├── device.h
│   ├── mqtt_client.h
│   ├── database.h
│   ├── web_server.h
│   └── json_utils.h
│
├── 📁 web/                  # Static web files
│   ├── index.html           # Dashboard UI
│   ├── app.js               # Frontend logic
│   └── style.css
│
├── 📁 scripts/
│   ├── install.sh           # Installation script
│   └── smarthome.service    # Systemd service file
│
├── 📁 config/
│   └── config.json          # Runtime configuration
│
├── Makefile
└── README.md
```

**Thư mục cài đặt (sau khi deploy):**

```
📁 /opt/smarthome/           # Installation directory
├── 📁 bin/
│   └── smarthome_hub        # Compiled binary
│
├── 📁 etc/
│   └── config.json          # Configuration
│
├── 📁 var/
│   ├── data.db              # SQLite database
│   └── 📁 logs/             # Log files
│
└── 📁 www/                  # Web interface
    ├── index.html
    ├── app.js
    └── style.css
```

---

##### ✏️ BƯỚC 7: Vẽ SYSTEM DIAGRAM

```
┌─────────────────────────────────────────────────────────────────┐
│                    SMART HOME HUB ARCHITECTURE                  │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│                         RASPBERRY PI                            │
│  ┌───────────────────────────────────────────────────────────┐  │
│  │                      USER SPACE                           │  │
│  │                                                           │  │
│  │  ┌───────────┐  ┌───────────┐  ┌───────────┐  ┌────────┐  │  │
│  │  │   Web     │  │   MQTT    │  │ Database  │  │  Main  │  │  │
│  │  │  Server   │  │  Client   │  │ (SQLite)  │  │  Loop  │  │  │
│  │  │(mongoose) │  │(mosquitto)│  │           │  │        │  │  │
│  │  └─────┬─────┘  └─────┬─────┘  └─────┬─────┘  └───┬────┘  │  │
│  │        │              │              │            │        │  │
│  │        └──────────────┴──────────────┴────────────┘        │  │
│  │                           │                                │  │
│  │                           ▼                                │  │
│  │           ┌───────────────────────────────┐                │  │
│  │           │        SmartHomeHub           │                │  │
│  │           │    (Container struct)         │                │  │
│  │           └───────────────────────────────┘                │  │
│  │                                                           │  │
│  └───────────────────────────────────────────────────────────┘  │
│                              │                                  │
│  ════════════════════════════════════════════════════════════  │
│                     NETWORK INTERFACES                          │
│  ════════════════════════════════════════════════════════════  │
│                              │                                  │
│         ┌────────────────────┼────────────────────┐            │
│         ▼                    ▼                    ▼            │
│  ┌────────────┐      ┌────────────┐      ┌────────────┐        │
│  │ HTTP :8080 │      │ MQTT :1883 │      │ SQLite     │        │
│  │ REST API   │      │ Pub/Sub    │      │ /var/data  │        │
│  └────────────┘      └──────┬─────┘      └────────────┘        │
│                             │                                   │
└─────────────────────────────┼───────────────────────────────────┘
                              │
                         MQTT Network
                              │
┌─────────────────────────────┼───────────────────────────────────┐
│                      SMART DEVICES                              │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐        │
│  │  Light   │  │  Switch  │  │  Sensor  │  │ Thermo-  │        │
│  │  Bulb    │  │          │  │ (DHT22)  │  │  stat    │        │
│  │ ESP8266  │  │ ESP32    │  │ ESP8266  │  │ ESP32    │        │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘        │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

#### 📝 TỔNG KẾT: SO SÁNH EMBEDDED VS EMBEDDED LINUX

**Đặc điểm riêng của Embedded (MCU):**

```
┌─────────────────────────────────────────────────────────────────┐
│                    EMBEDDED (STM32, AVR...)                     │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  1. Hardware Constraints (Ràng buộc phần cứng)                  │
│     - RAM: KB đến vài MB                                        │
│     - Flash: KB đến vài MB                                      │
│     - CPU: MHz                                                  │
│     → Phải tối ưu memory!                                       │
│                                                                 │
│  2. Direct Hardware Access                                      │
│     - Truy cập trực tiếp GPIO, UART, SPI...                     │
│     - Không có OS (bare metal) hoặc RTOS                        │
│     - Xử lý ngắt (ISR) quan trọng                               │
│                                                                 │
│  3. Real-time Requirements                                      │
│     - Đáp ứng thời gian thực                                    │
│     - Deterministic timing                                      │
│                                                                 │
│  4. Power Management                                            │
│     - Sleep modes quan trọng                                    │
│     - Battery-powered applications                              │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

**Đặc điểm riêng của Embedded Linux:**

```
┌─────────────────────────────────────────────────────────────────┐
│                    EMBEDDED LINUX (RPi, BBB...)                 │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  1. User Space vs Kernel Space                                  │
│     - Application chạy trong User Space                         │
│     - Driver chạy trong Kernel Space                            │
│     - File descriptors, system calls                            │
│                                                                 │
│  2. Rich Libraries                                              │
│     - Dùng được thư viện Linux (pthread, sqlite3...)            │
│     - Network stack sẵn có                                      │
│     - File system đầy đủ                                        │
│                                                                 │
│  3. Inter-Process Communication (IPC)                           │
│     - Pipes, Sockets, Shared Memory                             │
│     - D-Bus, MQTT cho messaging                                 │
│                                                                 │
│  4. Daemon Services                                             │
│     - Background processes                                      │
│     - Quản lý bằng Systemd                                      │
│     - Logging với syslog                                        │
│                                                                 │
│  5. File System Access                                          │
│     - /dev/ (device files)                                      │
│     - /sys/ (sysfs - GPIO, LEDs...)                             │
│     - /proc/ (process info)                                     │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

### 4.3 💻 IMPLEMENTATION - Viết Code

#### 🤔 Implementation Là Gì?

**= Chuyển design thành code thực sự**

Đây là giai đoạn **developer làm nhiều nhất**. Xem chi tiết ở phần **Git Workflow** bên dưới.

---

#### 📋 Quy Trình Implementation

```
1️⃣ Đọc design document
      ↓
2️⃣ Tạo Git branch
      ↓
3️⃣ Viết unit test trước (TDD)
      ↓
4️⃣ Viết code để pass test
      ↓
5️⃣ Compile và test locally
      ↓
6️⃣ Commit thường xuyên
      ↓
7️⃣ Push và tạo Pull Request
```

---

#### 🖥️ VÍ DỤ 1: Implementation Thư Viện

```c
// ===== src/book.c - Implementation =====

#include "book.h"

/**
 * @brief Add a new book to the library
 * @param lib Pointer to library (must not be NULL)
 * @param book Book to add
 * @return SUCCESS on success, error code otherwise
 */
ErrorCode add_book(Library *lib, Book book) {
    // Step 1: Validate NULL pointer
    if (lib == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    // Step 2: Validate book data
    if (!validate_id(book.id)) {
        return ERROR_INVALID_INPUT;
    }
    if (!validate_string(book.title)) {
        return ERROR_INVALID_INPUT;
    }
    
    // Step 3: Check capacity
    if (lib->book_count >= MAX_BOOKS) {
        return ERROR_LIBRARY_FULL;
    }
    
    // Step 4: Check duplicate ID
    if (find_book_by_id(lib, book.id) != NULL) {
        return ERROR_DUPLICATE_ID;
    }
    
    // Step 5: Add book
    lib->books[lib->book_count++] = book;
    
    return SUCCESS;
}
```

---

#### 🔧 VÍ DỤ 2: Implementation Embedded (STM32)

```c
// ===== src/temperature.c - Embedded Implementation =====

#include "temperature.h"
#include "stm32f4xx_hal.h"

static float current_temp = 0.0f;
static float target_temp = 25.0f;

/**
 * @brief Initialize temperature sensor (DS18B20 on OneWire)
 */
void Temperature_Init(void) {
    // Configure GPIO for OneWire
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    GPIO_InitStruct.Pin = TEMP_SENSOR_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    
    HAL_GPIO_Init(TEMP_SENSOR_PORT, &GPIO_InitStruct);
}

/**
 * @brief Read temperature from DS18B20 sensor
 * @return Temperature in Celsius, or -999 on error
 */
float Temperature_Read(void) {
    uint8_t data[9];
    
    // OneWire reset
    if (OneWire_Reset() != HAL_OK) {
        return -999.0f;  // Sensor not connected
    }
    
    // Send commands
    OneWire_WriteByte(0xCC);  // Skip ROM
    OneWire_WriteByte(0x44);  // Convert temperature
    
    // Wait for conversion (750ms for 12-bit)
    HAL_Delay(750);
    
    // Read scratchpad
    OneWire_Reset();
    OneWire_WriteByte(0xCC);  // Skip ROM
    OneWire_WriteByte(0xBE);  // Read Scratchpad
    
    for (int i = 0; i < 9; i++) {
        data[i] = OneWire_ReadByte();
    }
    
    // Calculate temperature
    int16_t raw = (data[1] << 8) | data[0];
    current_temp = (float)raw / 16.0f;
    
    return current_temp;
}

/**
 * @brief Control heater based on temperature
 * @note Called from timer interrupt every 1 second
 */
void Temperature_ControlLoop(void) {
    float temp = Temperature_Read();
    
    if (temp < target_temp - 0.5f) {
        // Too cold → Turn ON heater
        HAL_GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_SET);
    }
    else if (temp > target_temp + 0.5f) {
        // Too hot → Turn OFF heater
        HAL_GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_RESET);
    }
    // Else: Keep current state (hysteresis)
}
```

---

#### 🐧 VÍ DỤ 3: Implementation Embedded Linux

```c
// ===== src/sensor_daemon.c - Linux Daemon =====

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>
#include "sensor.h"
#include "mqtt.h"

static volatile int running = 1;

// Signal handler for graceful shutdown
void signal_handler(int sig) {
    syslog(LOG_INFO, "Received signal %d, shutting down...", sig);
    running = 0;
}

/**
 * @brief Initialize daemon process
 */
int Daemon_Init(void) {
    // Fork and exit parent
    pid_t pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);  // Parent exits
    }
    
    // Create new session
    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }
    
    // Set up signal handlers
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    
    // Open syslog
    openlog("sensor_daemon", LOG_PID, LOG_DAEMON);
    syslog(LOG_INFO, "Sensor daemon started");
    
    return 0;
}

/**
 * @brief Main daemon loop
 */
void Daemon_Run(void) {
    // Initialize hardware
    if (Sensor_Init() != 0) {
        syslog(LOG_ERR, "Failed to init sensor");
        return;
    }
    
    // Connect to MQTT broker
    if (MQTT_Connect("mqtt.example.com", 1883) != 0) {
        syslog(LOG_ERR, "Failed to connect MQTT");
        return;
    }
    
    // Main loop
    while (running) {
        // Read sensor
        SensorReading reading;
        reading.temperature = Sensor_ReadTemperature();
        reading.humidity = Sensor_ReadHumidity();
        reading.timestamp = time(NULL);
        
        // Format JSON
        char json[256];
        snprintf(json, sizeof(json),
            "{\"temp\":%.2f,\"humidity\":%.2f,\"time\":%ld}",
            reading.temperature,
            reading.humidity,
            reading.timestamp
        );
        
        // Publish to MQTT
        MQTT_Publish("sensors/living_room", json);
        
        syslog(LOG_INFO, "Published: %s", json);
        
        // Wait 60 seconds
        sleep(60);
    }
    
    // Cleanup
    MQTT_Disconnect();
    Sensor_Deinit();
    syslog(LOG_INFO, "Daemon stopped");
    closelog();
}

int main(void) {
    Daemon_Init();
    Daemon_Run();
    return 0;
}
```

---

### 4.4 🧪 TESTING - Kiểm Thử

Xem chi tiết ở **Phần 6: Testing**.

---

### 4.5 🚀 DEPLOYMENT - Triển Khai

#### 🤔 Deployment Là Gì?

**= Đưa code lên môi trường thật để user sử dụng**

---

#### 🖥️ Deployment Web/Server

```bash
# Quy trình deploy thông thường
1. Build production  →  make release
2. Upload lên server →  scp app user@server:/opt/
3. Restart service   →  systemctl restart app
4. Verify            →  curl http://server/health
```

---

#### 🔧 Deployment Embedded

```bash
# Flash firmware lên MCU
1. Build          →  make all
2. Flash          →  st-flash write build/app.bin 0x08000000
3. Reset          →  st-flash reset
4. Debug (nếu cần) → openocd + gdb

# Hoặc dùng IDE
STM32CubeIDE → Run → Debug
```

---

#### 🐧 Deployment Embedded Linux

```bash
# 1. Build Yocto image
bitbake core-image-minimal

# 2. Flash vào SD card
sudo dd if=core-image-minimal.wic of=/dev/sdX bs=4M status=progress

# 3. Boot device từ SD card

# 4. OTA Update (Over-The-Air)
# Dùng SWUpdate, Mender, hoặc custom solution
swupdate -i update.swu
```

---

### 4.6 🔧 MAINTENANCE - Bảo Trì

#### 🤔 Maintenance Là Gì?

**= Sửa bug, thêm feature, cập nhật sau khi release**

---

#### 📋 Các Loại Maintenance

| Loại | Mô tả | Ví dụ |
|------|-------|-------|
| **Corrective** | Sửa bug | Fix crash khi NULL pointer |
| **Adaptive** | Thích ứng môi trường mới | Support thêm OS mới |
| **Perfective** | Cải tiến hiệu năng | Giảm memory usage |
| **Preventive** | Phòng ngừa vấn đề | Refactor code cũ |

---

#### 🐛 Bug Tracking Workflow

```
1️⃣ User báo bug → Tạo ticket trên Jira
      ↓
2️⃣ Triage → Đánh giá mức độ nghiêm trọng
      ↓
3️⃣ Assign → Giao cho developer
      ↓
4️⃣ Debug → Tìm nguyên nhân
      ↓
5️⃣ Fix → Sửa code + viết test
      ↓
6️⃣ Review → Code review
      ↓
7️⃣ Deploy → Release hotfix
      ↓
8️⃣ Close ticket → Thông báo user
```

---

## 5. Git Workflow

### 🌿 Branching Strategy - Chiến Lược Nhánh

**Tưởng tượng như cây:**

```
main (production - sản phẩm thật)
  │
  │   ← Chỉ merge vào đây khi release
  │
  ├── develop (development - đang phát triển)
  │     │
  │     │   ← Developer merge feature vào đây
  │     │
  │     ├── feature/add-book      (Bạn đang làm tính năng thêm sách)
  │     │
  │     ├── feature/search        (Đồng nghiệp làm tính năng tìm kiếm)
  │     │
  │     └── feature/user-login    (Người khác làm đăng nhập)
  │
  ├── release/v1.0                (Chuẩn bị release)
  │
  └── hotfix/critical-bug         (Sửa bug gấp trên production)
```

### 🔄 Quy Trình Làm Việc Với Git

**BƯỚC 1: Nhận task mới**

```bash
# Lấy code mới nhất
git checkout develop
git pull origin develop

# Tạo branch mới cho task
git checkout -b feature/add-book
```

**💡 Tên branch:** `feature/tên-tính-năng` hoặc `fix/mô-tả-bug`

**BƯỚC 2: Viết code và commit thường xuyên**

```bash
# Sau mỗi đoạn code nhỏ hoàn thành
git add .
git commit -m "feat(book): add validation for book title"

# Tiếp tục code...
git commit -m "feat(book): implement add_book function"

# Tiếp tục...
git commit -m "test(book): add unit tests for add_book"
```

**BƯỚC 3: Push lên remote và tạo Pull Request**

```bash
# Push branch lên GitHub/GitLab
git push origin feature/add-book

# → Vào GitHub/GitLab tạo Pull Request
```

**BƯỚC 4: Code Review**

```
┌─────────────────────────────────────────────────────────┐
│                    CODE REVIEW FLOW                     │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  Bạn tạo PR → Reviewer xem code → Có comment?          │
│                                        │                │
│                                   Yes ↙   ↘ No          │
│                                      │      │           │
│                              Bạn sửa   Approve!         │
│                              code        ↓              │
│                                 │      Merge            │
│                                 ↓        ↓              │
│                              Push    Code vào           │
│                              lại     develop!           │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

### ✍️ Commit Message Convention

**Format chuẩn:**

```
<type>(<scope>): <mô tả ngắn>

Types (loại commit):
──────────────────────────────────────
📦 feat     = Tính năng mới
🐛 fix      = Sửa bug
📝 docs     = Thêm/sửa tài liệu
💅 style    = Format code (không đổi logic)
♻️ refactor = Cải tiến code (không thêm feature, không sửa bug)
🧪 test     = Thêm test
🔧 chore    = Cập nhật build, config
```

**Ví dụ tốt:**

```bash
git commit -m "feat(book): add search by title function"
git commit -m "fix(user): resolve null pointer in login"
git commit -m "docs(readme): add installation guide"
git commit -m "test(book): add unit tests for delete_book"
```

**Ví dụ XẤU (đừng làm!):**

```bash
git commit -m "fix"           # ❌ Quá ngắn
git commit -m "update"        # ❌ Không rõ ràng
git commit -m "asdfasdf"      # ❌ Vô nghĩa
git commit -m "done"          # ❌ Không mô tả gì
```

---

## 6. Testing - Kiểm Thử

### 🧪 Tại Sao Phải Test?

**Câu chuyện thật:**

> Developer: "Em đã code xong, chạy thử OK rồi!"
> 1 tuần sau trên production...
> User: "Ứng dụng của các anh crash mất dữ liệu của em!" 😭
>
> Nguyên nhân: Không test trường hợp đặc biệt (NULL, empty string, số âm...)

### 📊 Testing Pyramid

```
                    /\
                   /  \   🎭 E2E Tests (10%)
                  /    \  Test toàn bộ hệ thống
                 /──────\
                /        \  🔗 Integration Tests (20%)
               /          \ Test nhiều module cùng nhau
              /────────────\
             /              \  🧱 Unit Tests (70%)
            /                \ Test từng function riêng lẻ
           /──────────────────\
```

**💡 Ghi nhớ:** Viết Unit Test nhiều nhất! (70%)

### 🧱 Unit Test Là Gì?

**= Test từng function riêng lẻ**

```c
// ===== File: tests/test_book.c =====

#include "unity.h"   // Framework test
#include "book.h"    // Module cần test

// Test case 1: Thêm sách thành công
void test_add_book_success(void) {
    // 🎯 ARRANGE - Chuẩn bị
    Library lib = {0};
    Book book = {.id = 1, .title = "C Programming"};
    
    // 🎬 ACT - Thực hiện
    ErrorCode result = add_book(&lib, book);
    
    // ✅ ASSERT - Kiểm tra kết quả
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(1, lib.book_count);
}

// Test case 2: Thêm sách với NULL pointer
void test_add_book_null_library(void) {
    Book book = {.id = 1};
    
    ErrorCode result = add_book(NULL, book);  // Truyền NULL!
    
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
}

// Test case 3: Thêm sách trùng ID
void test_add_book_duplicate_id(void) {
    Library lib = {0};
    Book book1 = {.id = 1, .title = "Book 1"};
    Book book2 = {.id = 1, .title = "Book 2"};  // Trùng ID!
    
    add_book(&lib, book1);
    ErrorCode result = add_book(&lib, book2);
    
    TEST_ASSERT_EQUAL(ERROR_DUPLICATE_ID, result);
}
```

### ⚡ TDD - Test-Driven Development

**= Viết test TRƯỚC, viết code SAU**

```
┌───────────────────────────────────────────────────────┐
│                   TDD CYCLE                           │
│                                                       │
│   1️⃣ RED     Viết test → Test FAIL (vì chưa có code) │
│      ↓                                                │
│   2️⃣ GREEN   Viết code → Test PASS                   │
│      ↓                                                │
│   3️⃣ REFACTOR Cải tiến code → Test vẫn PASS          │
│      ↓                                                │
│   🔄 Lặp lại cho function tiếp theo                   │
│                                                       │
└───────────────────────────────────────────────────────┘
```

**Ví dụ thực tế:**

```bash
# Bước 1: Viết test trước
vim tests/test_book.c
# → Viết test cho add_book()

# Bước 2: Chạy test → FAIL (chưa có code)
$ make test
test_add_book: FAIL ❌

# Bước 3: Viết code
vim src/book.c
# → Implement add_book()

# Bước 4: Chạy test → PASS
$ make test
test_add_book: PASS ✅

# Bước 5: Refactor nếu cần, test vẫn pass
```

---

## 7. CI/CD Pipeline

### 🤖 CI/CD Là Gì?

**CI = Continuous Integration (Tích hợp liên tục)**
**CD = Continuous Deployment (Deploy liên tục)**

**Tưởng tượng như dây chuyền nhà máy:**

```
┌─────────────────────────────────────────────────────────────────┐
│                    🏭 DÂY CHUYỀN CI/CD                          │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  📤 Push code → 🔨 Build → 🧪 Test → 📦 Package → 🚀 Deploy    │
│       │           │          │          │           │           │
│       │           │          │          │           ↓           │
│       │           │          │          │      Production       │
│       │           │          │          │        Server         │
│       │           │          ↓          │                       │
│       │           │     ❌ Fail?        │                       │
│       │           │         ↓           │                       │
│       │           │    📧 Email        │                       │
│       │           │    thông báo       │                       │
│       │           ↓                     │                       │
│       │      ❌ Fail?                   │                       │
│       ↓          ↓                      │                       │
│   Trigger     ⛔ STOP!                  │                       │
│   pipeline    Không merge được          │                       │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 📝 Ví dụ GitHub Actions

```yaml
# File: .github/workflows/ci.yml

name: CI Pipeline

# Khi nào chạy?
on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main]

# Các bước thực hiện
jobs:
  build-and-test:
    runs-on: ubuntu-latest
    
    steps:
      # 1. Lấy code
      - uses: actions/checkout@v3
      
      # 2. Build
      - name: Build
        run: make all
      
      # 3. Chạy Unit Tests
      - name: Run Unit Tests
        run: make test_unit
      
      # 4. Chạy Integration Tests
      - name: Run Integration Tests
        run: make test_integration
      
      # 5. Deploy (chỉ khi push vào main)
      - name: Deploy to Production
        if: github.ref == 'refs/heads/main'
        run: ./deploy.sh production
```

**🎯 Lợi ích:**
- ✅ Tự động test mỗi khi push
- ✅ Phát hiện bug sớm
- ✅ Không thể merge code lỗi
- ✅ Deploy tự động, không cần làm tay

---

## 8. Một Ngày Làm Việc Thực Tế

### ⏰ Lịch Trình Một Ngày

```
┌─────────────────────────────────────────────────────────────────┐
│                    📅 MỘT NGÀY LÀM VIỆC                         │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  08:30  ☕ Đến công ty, check email, Slack                      │
│         → Xem có task mới, comment nào cần reply không          │
│                                                                 │
│  09:00  📢 Daily Standup (15 phút)                              │
│         → Báo cáo 3 câu hỏi                                     │
│                                                                 │
│  09:15  💻 CODING - Focus time                                  │
│         → Không họp, không bị làm phiền                         │
│         → Viết test, viết code, debug                           │
│                                                                 │
│  12:00  🍜 Ăn trưa                                              │
│                                                                 │
│  13:00  💻 CODING / 👀 Code Review                              │
│         → Review PR của đồng nghiệp                             │
│         → Fix theo comment của reviewer                         │
│                                                                 │
│  15:00  🤝 Họp (nếu có)                                         │
│         → Sprint planning, design discussion...                 │
│                                                                 │
│  16:00  💻 Tiếp tục coding                                      │
│                                                                 │
│  17:30  📤 Cuối ngày                                            │
│         → Push code lên remote                                  │
│         → Update status trên Jira                               │
│         → Commit message cuối: "WIP: ..." nếu chưa xong         │
│                                                                 │
│  18:00  🏠 Về nhà!                                              │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 📅 Lịch Một Tuần (Sprint)

```
Thứ 2  │ Sprint Planning (nếu sprint mới) + Development
Thứ 3  │ Development + Code Review
Thứ 4  │ Development + Code Review
Thứ 5  │ Development + Testing
Thứ 6  │ Sprint Review + Retrospective (nếu cuối sprint)
```

---

## 9. Công Cụ Thường Dùng

### 🧰 Theo Mục Đích

| Mục đích | Công cụ phổ biến | Ghi chú |
|----------|------------------|---------|
| **Quản lý task** | Jira, Trello | Jira phổ biến nhất |
| **Chat** | Slack, Teams | Slack phổ biến ở startup |
| **Video call** | Zoom, Meet | Họp online |
| **Version control** | Git, GitHub, GitLab | Git là **BẮT BUỘC** phải biết! |
| **IDE** | VS Code, CLion | VS Code miễn phí, nhiều plugin |
| **CI/CD** | Jenkins, GitHub Actions | Tự động build, test, deploy |
| **Test** | Unity, Google Test | Unity cho C, GTest cho C++ |
| **Documentation** | Confluence, Notion | Viết tài liệu nội bộ |

### 💡 Mẹo Cho Người Mới

```
📚 BẮT BUỘC phải biết:
├── Git (add, commit, push, pull, merge, branch)
├── Terminal/Command line
└── IDE của team đang dùng

📱 Cài trên máy ngay:
├── Slack - để chat với team
├── Jira - để xem task
└── Git client - GitHub Desktop nếu mới học
```

---

## 10. Best Practices

### ✍️ Coding Best Practices

```c
// ✅ GOOD - Code dễ đọc, có comment
/**
 * @brief Add a new book to the library
 * @param lib Pointer to library (must not be NULL)
 * @param book Book to add
 * @return SUCCESS on success, error code otherwise
 */
ErrorCode add_book(Library *lib, Book book) {
    // Validate input
    if (lib == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    // Check capacity before adding
    if (lib->book_count >= MAX_BOOKS) {
        return ERROR_LIBRARY_FULL;
    }
    
    // Add book to library
    lib->books[lib->book_count++] = book;
    return SUCCESS;
}

// ❌ BAD - Code khó hiểu, không comment
int ab(void *l) {
    if(!l) return -1;
    ((int*)l)[0]++;
    return 0;
}
```

### 📝 Git Best Practices

```bash
# ✅ GOOD - Commit message rõ ràng
git commit -m "feat(book): add validation for empty title"
git commit -m "fix(user): handle null pointer in login"
git commit -m "test(book): add edge cases for delete_book"

# ❌ BAD - Commit message mơ hồ
git commit -m "fix"
git commit -m "update"
git commit -m "done"
```

### 💬 Communication Best Practices

```
1️⃣ Update status Jira/Trello hàng ngày
   → Lead biết bạn đang làm gì

2️⃣ Thông báo SỚM nếu có vấn đề
   → Đừng đợi deadline mới nói "em không làm kịp"

3️⃣ Hỏi khi không hiểu
   → Không có câu hỏi nào là ngớ ngẩn

4️⃣ Document mọi quyết định quan trọng
   → Viết lại để sau này còn biết tại sao làm vậy

5️⃣ Respect time
   → Đến họp đúng giờ, kết thúc đúng giờ
```

---

## 11. Checklist Cho Người Mới

### 📋 Ngày Đầu Tiên

```
□ Setup môi trường development
□ Cài IDE, Git, compiler
□ Clone repository của team
□ Build và chạy thử project
□ Đọc README.md, Wiki
□ Làm quen với team members
□ NOTE: Hỏi mentor bất cứ khi nào cần!
```

### 📋 Tuần Đầu Tiên

```
□ Hiểu architecture của project
□ Hiểu code structure
□ Complete 1 task nhỏ (good first issue)
□ Tạo PR đầu tiên
□ Học Git workflow của team
□ Tham gia đầy đủ Daily Standup
□ NOTE: Đừng ngại hỏi nhiều!
```

### 📋 Tháng Đầu Tiên

```
□ Complete 3-5 features/tasks
□ Viết unit tests cho code của mình
□ Review code của đồng nghiệp
□ Được approve ít nhất 3 PRs
□ Hiểu CI/CD pipeline
□ Đóng góp documentation
□ NOTE: Bạn đã thành junior developer thực sự!
```

---

## 12. Thuật Ngữ Thường Gặp

| Thuật ngữ | Viết tắt của | Nghĩa |
|-----------|--------------|-------|
| **PR** | Pull Request | Yêu cầu merge code |
| **MR** | Merge Request | = PR (GitLab dùng) |
| **CI/CD** | Continuous Integration/Deployment | Tích hợp & deploy liên tục |
| **Sprint** | - | Chu kỳ 2-4 tuần |
| **Backlog** | - | Danh sách việc cần làm |
| **Blocker** | - | Vấn đề chặn tiến độ |
| **Hotfix** | - | Sửa bug gấp |
| **Release** | - | Phiên bản phát hành |
| **Staging** | - | Môi trường test |
| **Production** | Prod | Môi trường thật |
| **Tech Debt** | - | Nợ kỹ thuật |
| **POC** | Proof of Concept | Demo khả thi |
| **MVP** | Minimum Viable Product | Sản phẩm tối thiểu |
| **SRS** | Software Requirements Spec | Tài liệu yêu cầu |
| **UAT** | User Acceptance Testing | User test chấp nhận |

---

## 13. Tóm Tắt - Quy Trình 12 Bước

```
┌─────────────────────────────────────────────────────────────────┐
│               🎯 QUY TRÌNH 12 BƯỚC MỖI NGÀY                     │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│   1️⃣  Nhận task từ Jira/Trello                                  │
│   2️⃣  Tạo branch mới (feature/xxx)                              │
│   3️⃣  Viết test trước (TDD)                                     │
│   4️⃣  Viết code để pass test                                    │
│   5️⃣  Chạy tests locally                                        │
│   6️⃣  Commit thường xuyên (message rõ ràng)                     │
│   7️⃣  Push code lên remote                                      │
│   8️⃣  Tạo Pull Request                                          │
│   9️⃣  Được code review                                          │
│   🔟  Fix theo feedback                                         │
│   1️⃣1️⃣  Merge vào develop                                        │
│   1️⃣2️⃣  Update status trên Jira                                  │
│                                                                 │
│              🎉 DONE! Chuyển sang task tiếp theo                │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

## 💎 Lời Khuyên Vàng

> 🗣️ **"Ask early, ask often"**
> Hỏi sớm, hỏi thường xuyên. Đừng ngại hỏi - không có câu hỏi nào là ngớ ngẩn!

> 💻 **"Code is read more often than it is written"**
> Code được đọc nhiều hơn được viết. Hãy viết code dễ đọc, dễ hiểu!

> 🐛 **"Every bug is a missing test"**
> Mỗi bug là một test case bị thiếu. Viết test đầy đủ!

> 🤝 **"We are a team"**
> Chúng ta là một team. Giúp đỡ nhau, học hỏi lẫn nhau!

---

**📝 Tác giả:** Gemini AI  
**📅 Ngày tạo:** 2026-01-30  
**🔖 Version:** 2.0

---

*🚀 Chúc bạn thành công trong sự nghiệp phát triển phần mềm!*
