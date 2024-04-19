# Snake_Game

# Introduction
+ Họ và tên : Nguyễn Lê Minh - K68CD - UET
+ Mã sinh viên : 23020114
+ Bài tập lớn : Snake_Game(2324II_INT2215_51 - Lập trình nâng cao)

# Description
***Game description and instruction***

+ Đây là trò chơi rắn săn mồi hay nhất từ trước đến nay với nhiều tính năng hay, vượt trội. Game tổng cộng có 8 chế độ chơi, người chơi chọn Play Game ở màn hình chính: 
   + Chế độ lớn 1 : ***1 PLAYER*** đây là chế độ một người chơi, sau khi ấn, người chơi có quyền lựa chọn tiếp 5 chế độ chính : 
      + Chế độ con 1 :  *Obstacle Mode* là chế độ người chơi điều khiển con rắn của mình ăn quả, sau khi ăn một khối block tương ứng với phần thân con rắn được tạo ra trong một khoảng thời gian nhất định, người chơi cần tránh những vật cản này
      + Chế độ con 2 : *Mirror Mode* là chế độ người chơi điều khiển con rắn của mình ăn quả, song song với bóng của con rắn của người chơi tạo ra, 2 con rắn có chức năng tương tự nhau
      + Chế độ con 3 : *Reverse Mode* là chế độ người chơi điều khiển con rắn của mình ăn quả, mỗi khi ăn con rắn tự động đổi ngược hướng di chuyển của mình theo hướng đuôi của nó
      + Chế độ con 4 : *Classic* đơn giản chỉ là một chế độ rắn săn mồi cơ bản, tuy nhiên map đã được làm mới
      + Chế độ con 5 : *Challenge Mode* là chế độ mà người chơi sẽ phải vượt qua từng ải một, mỗi ải sẽ được tăng dần độ khó theo mức level của người chơi hiện tại
   + Chế độ lớn 2 : ***VS AI*** đây là chế độ đưa người so tài trực tiếp với AI, người chơi điều khiển con rắn ở một map, rắn AI ở một map khác, trong thời gian 1 phút cả hai sẽ so điểm với nhau
   + Chế độ lớn 3 : ***Endless Map*** đây là chế độ đưa con rắn vào thế giới ảo, nơi nó sẽ bò trong một map vô tận
   + Chế độ lớn 4 : ***Competitive Mode*** rắn AI và rắn người chơi điều khiển sẽ cùng nhau chơi trong một map, so tài trực tiếp điểm số với nhau
+ Game có hỗ trợ mọi tính năng cần thiết :
   + Âm nhạc : Trong màn hình chính, người chơi click chuột vào màn biểu tượng âm nhạc để chọn cho mình âm thanh phù hợp
   + Dừng game khi chơi : Người chơi nhấn phím "Esc", khi đó game sẽ dừng và mở ra một tool bar để người chơi có thể chọn những tác vụ mình cần
   + Các tác vụ cần thiết khác game cũng đã được tích hợp
### Control
   + Up Arrow : Di chuyển lên
   + Down Arrow : Di chuyển xuống
   + Left Arrow : Di chuyển sang trái
   + Right Arrow : Di chuyển sang phải
### Preview
   ![Anh1.png](https://up-anh.vi-vn.vn/img/1713502418_450dec0e5e456c40ad79488f5c84b687.png)


   ![Anh2.png](https://up-anh.vi-vn.vn/img/1713502521_b417112a367024ac7e30f0ee8b35a83c.png)


   ![Anh3.png](https://up-anh.vi-vn.vn/img/1713503311_f9770c475bc8e8d17b7a06b73513da9b.png)

   
   ![Anh4.png](https://up-anh.vi-vn.vn/img/1713503337_5f0aca45b039e7eb5db45d62edd97d8f.png)
# Demo
   [Link Demo](https://www.youtube.com/watch?v=eeIcKHB4uzw)
# Các kỹ thuật sử dụng
   + Thư viện SDL2.0
   + Có thể lưu lại điểm số cao nhất nhờ đọc ghi file
   + Dùng kiến thức toán học để thực hiện phép bo cong thân rắn
   + Khả năng tổ chức code, nạp chồng toán tử, lập trình hướng đối tượng như : tạo các đối tượng : rắn, quả, vật cản,..., inherited code,.... 
   + Các kiến thức ngoài chương trình : Toán rời rạc, Advance Algorithm như: BFS, DFS, Nén đồ thị tạo thành phần liên thông, Greedy, tạo ma trận ảo, đồ thị ảo, xử lý sai số trong hệ tọa độ, dùng các stl như set, map, deque...
   + Xử lý thao tác người dùng với trò chơi như thao tác với chuột và bàn phím
   + Tạo menu và các phím thao tác trong game
   + Dùng Paint để edit hầu hết các ảnh
### Nguồn tham khảo
   + ***Về Syntax của SDL và cách hoạt động của chúng :*** Em học trên thư viện của SDL.
   + ***Về đồ họa Game :*** Một vài hình ảnh trong game em có lấy từ Google
   + ***Về âm thanh :*** Em tìm kiếm trên Google
# Conclusion
  ## Điều tâm đắc
   + Dự án này là tự tay em làm mọi phần, không tham khảo, sao chép từ bất cứ ai hay bất cứ nguồn nào hoặc hỏi ý kiến tham khảo từ bất kì ai
   + Em đã học được rất nhiều điều sau dự án này, đặc biệt là khả năng code của bản thân. Nhờ phải quản lý một khối công việc lớn cũng như tổ chức code sao cho hợp lý em đã nâng cao khả năng lập trình rất nhiều.
   + Dự án này cũng đã giúp em cải thiện khả năng đọc hiểu Tiếng Anh cũng như tăng khả năng làm việc đường dài của bản thân.
 ## Điểm hạn chế
   + Điểm hạn chế duy nhất của game theo em là đồ họa vẫn chưa được tốt nhất so với khả năng của chính em
 ## Hướng phát triển 
   + Tạo thêm nhiều loại quả, thêm nhiều màn chơi hơn
   + Tạo thêm cho AI suy nghĩ cũng như tạo thêm độ khó của AI Mode
 ## Kết luận
   + Sau dự án này, em thật sự cảm ơn các thầy cô, thầy **Kiều Hải Đăng** cũng như các anh/chị mentor vì đã giúp em có được một trải nghiệm chưa từng có, cải thiện rất nhiều cũng như bù đắp những thiếu sót trong các kỹ năng của em. Em xin chân thành cảm ơn
# ***Mức điểm tự đánh giá: 10/10***
