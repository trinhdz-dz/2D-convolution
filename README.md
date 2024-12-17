# Convolution 2D

## Mục tiêu 
Vận dụng các kiến thức, kỹ năng đã được học để thiết kế, mô phỏng và 
thực thi một mô-đun phần cứng thực hiện tính tích chập J = 2DConV(I, K) giữa hình ảnh 
lối vào I với một ma trận kernel K ([1] ). Trong đó, mỗi pixel trong hình ảnh tích phân
J đại diện cho tổng tích lũy của tích điểm-điểm giữa ma trận K với một ma trận cùng 
kích thước được trích xuất từ ma trận đầu vào I. Phép tính tích chập được mô tả bằng ví 
dụ sau.
## Yêu cầu bài toán 
- Xây dựng thuật toán thực hiện tính nhân chập 2D.
- Xây dựng bản mô tả mức cao cho thuật toán bằng ngôn ngữ C, 
- Xây dựng testbench để kiểm chứng thuật toán bằng C simulation
- Tổng hợp bản mô tả C thành bản mô tả RTL bằng VHDL/Verilog bằng Vivado HLS 
- Mô phỏng C/RTL co-simulation để kiểm chứng và phân tích hoạt động của phần 
cứng sau tổng hợp HLS
- Tối ưu mô hình C và thêm vào các dẫn hướng để cải thiện hiệu năng của thiết kế
- Thực hiện thiết kế trên ZynQ-7000 để đánh giá lượng tài nguyên sử dụng, hiệu năng.

