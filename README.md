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
   + Chi tiết hơn xem thêm ở phần **Lý do cho mức điểm tự đánh giá** ở bên dưới
 ## Kết luận
   + Sau dự án này, em thật sự cảm ơn các thầy cô, thầy **Kiều Hải Đăng** cũng như các anh/chị mentor vì đã giúp em có được một trải nghiệm chưa từng có, cải thiện rất nhiều cũng như bù đắp những thiếu sót trong các kỹ năng của em. Em xin chân thành cảm ơn
# ***Mức điểm tự đánh giá: 10/10***
## Lý do cho mức điểm tự đánh giá ##
Game của em tuy không có được đồ họa đẹp tuy nhiên có rất nhiều những kỹ năng thuật toán (*Algorithm*) và kỹ năng cài đặt (*implementation*): 
   + Thuật toán **BFS/Greedy** : Tìm đường đi ngắn nhất. Do ta có thể mô hình con rắn là một điểm trên đồ thị, và do mỗi cạnh trên đồ thị của ta có chi phí di chuyển là như nhau, nên ta không cần dijkstra để tìm đường đi ngắn nhất từ rắn đến quả, chỉ cần bfs là đã thỏa mãn. Thêm vào đó, ta sẽ dùng thêm các thuật toán tham lam để cho con rắn AI tránh những trường hợp đâm vào thân của nó. Sau này, nếu ta có phát triển thêm chi phí của con rắn khi di chuyển trên map, nếu chỉ gồm trạng thái 0/1 tương đối chi phí của các ô, ta cũng không cần dùng đến dijkstra mà thay vào đó ta bfs bình thường, dùng deque thay cho queue và ta thay đổi thứ tự push và pop vào của các cạnh (đây là một hướng phát triển)
   + Thuật toán **DFS/Nén đồ thị** : DFS về cơ bản cũng khá giống với BFS. Tuy nhiên nếu BFS là tìm kiếm theo chiều rộng thì DFS là tìm kiếm theo chiều sâu, như vậy DFS sẽ được phổ biến hơn trong việc loang trong đồ thị, còn BFS thì dùng trong tìm kiếm đường đi ngắn nhất trong đồ thị trạng thái cạnh 1 hoặc 0/1. DFS được ứng dụng trong trò chơi này như sau : Trong chế độ chơi ***Challenge Mode*** ta không thể random các chướng ngại vật một cách bừa bãi, vì khi đó sẽ tồn tại rất nhiều những trường hợp người chơi không thể thắng được, ví dụ một trường hợp quả táo được bao quanh bởi các ô chướng ngại vật. Vì thế giải pháp tối ưu của chúng ta sẽ nén map của chúng ta thành một đồ thị gồm các thành phần liên thông được giải quyết bằng cách dùng DFS. Sau khi nén được đồ thị thành các thành phần liên thông, ta sẽ render táo vào cùng thành phần liên thông với rắn, tất nhiên ta cũng không quên kiểm tra với 4 ô kề cạnh của quả, không thể có từ 3 chướng ngại vật trở lên
   + **Kiến thức toán + Xử lý sai số** :  Khác với các nhân vật đứng, con rắn của ta là một thực thể bò, vì thế ta phải có những phương pháp để xử lý bo cong khi con rắn rẽ trái/phải. Khi đó ta phải sử dụng đến kiến thức toán, cụ thể là giá trị tương đối của hai ô thân rắn liền kề. Một điều cần lưu ý khi làm game rắn đó chính là ta không thể quản lý tọa độ rắn theo số thực, thay vì thế ta nhân đến khi tọa độ đạt và các phần tương ứng đạt số nguyên, sau đó xử lý trên hệ số nguyên rồi đưa về hệ số thực bằng cách chia lại cho số đã nhân, như vậy ta sẽ tránh được sai số của C++ khi thực hiện nhiều phép tính toán với số thực, vừa đảm bảo được chính xác tối ưu
   + Kỹ thuật **Tạo ma trận ảo/đồ thị ảo** : Đây chính là ý tưởng cho chế độ Endless của em, được hình thành khi em gặp [bài này](https://oj.vnoi.info/problem/voi21_rmat). Chế độ Endless có vẻ là chế độ ít tính năng nhưng là người trực tiếp làm nên tựa game này, cá nhân em lại thích chế độ này nhất.
   + Kỹ thuật **Quản lý các đối tượng** : Do trong game gồm rất nhiều chế độ, mỗi một chế độ lại bao gồm một đặc tính riêng, vì vậy em phải xử lý một lượng code cực lớn và phải rất khéo léo. Trong code, em đã tách các chế độ đặc trưng ra từng file một vì mỗi một chế độ có một đặc trưng riêng, vì vậy nếu gộp lại dùng các phần chung, có thể gây nên tốn bộ nhớ cho những phần không cần thiết. 
   + **Khả năng phát triển thêm những chế độ hay** : Ngoài hướng phát triển ở phần mục **BFS/Greedy**, một hướng phát triển tiềm năng nữa như sau. Ta sẽ tạo thêm cho rắn AI những điều kiện khi ăn quả. Thay vì suy nghĩ đơn giản là thêm các loại quả, ta sẽ có những điều kiện để rắn có thể đến được ô ăn quả táo. Một trong những hướng đó chính là chỉ cho phép rắn ăn quả nếu đi đúng điều kiện ta cho phép, có thể là vào ở một hướng và ra ở một hướng. Khi đó ta chỉ cần thêm một trạng thái, hay **bitmask** vào trong hàm BFS của chúng ta (vì bản chất BFS cũng chỉ là thuật toán **quy hoạch động**), đây cũng có thể là một chế độ tiềm năng.

***Sau tất cả những gì đã trình bày ở trên em hy vọng sẽ lọt vào top 10% của lớp***
