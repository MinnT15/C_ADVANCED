#ifndef FILESTAT_H
#define FILESTAT_H

/* Cần khai báo POSIX_C_SOURCE trước mọi include để dùng lstat() với -std=c99 */
#define _POSIX_C_SOURCE 200112L

#include <sys/stat.h>
#include <stddef.h>

/* ============================================================
 * ITERATION 1: lstat() + File Type Detection
 * ============================================================ */

/**
 * @brief Lấy thông tin metadata của file/thư mục qua lstat()
 *
 * Sử dụng lstat() thay vì stat() để không đi qua symbolic link,
 * cho phép phát hiện chính xác loại "Symbolic Link".
 *
 * @param path Đường dẫn tới file, thư mục hoặc symlink
 * @param out  Con trỏ struct stat để lưu kết quả
 * @return  0 nếu thành công, -1 nếu lỗi (in thông báo lỗi ra stderr)
 */
int filestat_get_info(const char *path, struct stat *out);

/**
 * @brief Xác định loại của đối tượng file system
 *
 * @param info Con trỏ struct stat đã được điền dữ liệu bởi filestat_get_info()
 * @return Chuỗi hằng: "Regular File", "Directory", "Symbolic Link", hoặc "Unknown"
 */
const char *filestat_get_type(const struct stat *info);

/**
 * @brief In File Path và File Type ra stdout
 *
 * @param path Đường dẫn người dùng nhập vào
 * @param info Con trỏ struct stat đã được điền dữ liệu
 */
void filestat_print_basic(const char *path, const struct stat *info);

/* ============================================================
 * ITERATION 2: Size + Last Modified
 * ============================================================ */

/**
 * @brief Trả về kích thước của file tính bằng bytes
 *
 * @param info Con trỏ struct stat đã được điền dữ liệu
 * @return Kích thước file (long), giá trị của st_size
 */
long filestat_get_size(const struct stat *info);

/**
 * @brief Format thời gian sửa đổi cuối thành chuỗi human-readable
 *
 * Format output: "YYYY-MM-DD HH:MM:SS"
 * Dùng localtime() và strftime() từ <time.h>
 *
 * @param info     Con trỏ struct stat đã được điền dữ liệu
 * @param buf      Buffer để lưu chuỗi kết quả (tối thiểu 64 bytes)
 * @param buf_size Kích thước của buffer
 */
void filestat_format_time(const struct stat *info, char *buf, size_t buf_size);

/**
 * @brief In đầy đủ 4 trường: File Path, File Type, Size, Last Modified
 *
 * @param path Đường dẫn người dùng nhập vào
 * @param info Con trỏ struct stat đã được điền dữ liệu
 */
void filestat_print_all(const char *path, const struct stat *info);

#endif /* FILESTAT_H */
