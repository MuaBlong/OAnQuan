# Ô ăn quan
Ô ăn quan là trò chơi dân gian Việt Nam, trò chơi có cách chơi đơn giản nhưng không kém phần thú vị, lôi cuốn.

## Screenshots
[Screenshots](https://imgur.com/a/OsMilVI)
![App Screenshot](https://i.imgur.com/GGGbcLH.jpeg)
![App Screenshot](https://i.imgur.com/14o6T0E.jpeg)


## Cài đặt

Chương trình có thể mở lên bằng cách biên dịch và chạy các file mã nguồn C++ trong thư mục "Source" hoặc mở file "OAnQuan.exe" (lưu ý, file "OAnQuan.exe" và file "logo.txt" phải đặt cùng trong một thư mục).

## Điều khiển

Left, Right - di chuyển và chọn chiều đi
Spacebar - Khóa lựa chọn ô dân
    
## Luật chơi

- Bàn chơi là một hình chữ nhật được chia thành mười ô vuông, mỗi bên có 5 ô đối xứng nhau. Ở hai cạnh ngắn hơn của hình chữ nhật, kẻ hai ô lớn hình bán nguyệt hoặc hình chữ nhật. Các ô hình vuông gọi là ô dân còn hai ô lớn gọi là ô quan.
- Mục tiêu cần đạt được để giành chiến thắng: người thắng cuộc trong trò chơi này là người mà khi cuộc chơi kết thúc có tổng số dân nhiều hơn. 
- Di chuyển quân: từng người chơi khi đến lượt của mình sẽ di chuyển dân theo phương án để có thể ăn được càng nhiều dân và quan hơn đối phương càng tốt. Người thực hiện lượt đi đầu tiên thường được xác định bằng cách oẳn tù tì hay thỏa thuận tuy nhiên trong chương trình này, mặc định người chơi bên dưới được quyền đi trước. Khi đến lượt, người chơi sẽ dùng tất cả số quân trong một ô có quân bất kỳ do người đó chọn trong số 5 ô vuông thuộc quyền kiểm soát của mình để lần lượt rải vào các ô, mỗi ô 1 quân, bắt đầu từ ô gần nhất và có thể rải ngược hay xuôi chiều kim đồng hồ tùy ý. Khi rải hết quân cuối cùng, tùy tình huống mà người chơi sẽ phải xử lý tiếp như sau:
	- Nếu liền sau đó là một ô vuông có chứa quân thì tiếp tục dùng tất cả số quân đó để rải tiếp theo chiều đã chọn.
	- Nếu liền sau đó là một ô trống (không phân biệt ô quan hay ô dân) rồi đến một ô có chứa quân thì người chơi sẽ được ăn tất cả số quân trong ô đó. Số quân bị ăn sẽ được loại ra khỏi bàn chơi để người chơi tính điểm khi kết thúc. Nếu liền sau ô có quân đã bị ăn lại là một ô trống rồi đến một ô có quân nữa thì người chơi có quyền ăn tiếp cả quân ở ô này... 
	- Nếu liền sau đó là ô quan có chứa quân hoặc 2 ô trống trở lên hoặc sau khi vừa ăn thì người chơi bị mất lượt và quyền đi tiếp thuộc về đối phương.
	- Trường hợp đến lượt đi nhưng cả năm ô vuông thuộc quyền kiểm soát của người chơi đều không có dân thì người đó sẽ phải dùng 5 dân đã ăn được của mình để đặt vào mỗi ô 1 dân để có thể thực hiện việc di chuyển quân. Nếu người chơi không đủ 5 dân thì phải vay của đối phương và trả lại khi tính điểm.

- Cuộc chơi sẽ kết thúc khi toàn bộ dân và quan ở hai ô quan đã bị ăn hết. Trường hợp hai ô quan đã bị ăn hết nhưng vẫn còn dân thì quân trong những hình vuông phía bên nào coi như thuộc về người chơi bên ấy; tình huống này được gọi là "hết quan, tàn dân, thu quân, kéo về" hay "hết quan, tàn dân, thu quân, bán ruộng". 