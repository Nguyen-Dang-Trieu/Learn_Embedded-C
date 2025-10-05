# Embedded-C: A Guide to Embedded Systems Programming in C
Kho lưu trữ này sẽ giúp bạn điều gì:
- Lập trình C cho vi điều khiển.
- Cách để viết mã C hiệu quả, tối ưu.

> [!CAUTION]
> Điều tối quan trọng là bạn phải đọc kỹ tài liệu, từng dòng một, để đảm bảo không bỏ sót bất kỳ chi tiết nào.

## I. Blogs và Câu hỏi
Chứa các bài viết về việc dùng C trong thực tế và các câu hỏi.
### 1. Blogs
### 2. Câu hỏi
- [Tại sao cần phải ép kiểu con trỏ](https://viblo.asia/p/tai-sao-can-phai-ep-kieu-con-tro-ZoJjeNKe4Y7)
- [Segmentation faults là gì ? Nguyên nhân và giải pháp](https://medium.com/@mohamedsamer1532/understanding-segmentation-fault-in-c-causes-and-solutions-ed3d1c159d76)

## II. Design Parttern trong Embedded System
 Chưa ghi gì giới thiệu ở đây cả
- Singleton
- Observer


## III. Kiến thức về ngôn ngữ C và Embedded
Tại đây, bạn sẽ tìm thấy bộ sưu tập các liên kết và tài liệu hữu ích liên quan đến Embedded C.
Các tài nguyên này bao gồm bảng dữ liệu, hướng dẫn và các công cụ thiết yếu để giúp bạn bắt đầu và hướng dẫn bạn.

> [!TIP]  
> Các tài nguyên được trình bày chi tiết trong các phần bên dưới.
> Để truy cập bất kỳ tài nguyên nào, chỉ cần nhấp vào liên kết màu xanh tương ứng.

- [Variables and Data Type in C Programming](./Variable.md)  
  ---  
  This document provides a comprehensive explanation of defining and using variables in Embedded C, with examples and best practices.

- [Memory Classes in C](./MemoryClass.md)  
  ---  
  An overview of memory classes in C, such as `auto`, `static`, and `extern`, and their usage in embedded systems to manage variable lifespan and scope.

- [Comments and Doxygen Format in C](./Comment.md)  
  ---  
  This document provides a comprehensive guide on how to use comments in C for embedded systems programming, including the different types of comments (single-line, multi-line), Doxygen-style comments for automatic documentation generation, and best practices for effective commenting and documentation in embedded projects.

- [Arrays, Strings, and String Handling in C](./Array_String.md)  
  ---  
  A detailed guide to working with arrays and strings, including multi-dimensional arrays, string manipulation functions, and handling memory efficiently in embedded C. 

- [ASCII Codes, Escape Sequences in C](./ASCII.md)  
  ---  
  This document provides a comprehensive explanation of ASCII codes, escape sequences, and control characters in C programming for microcontrollers. It covers how to handle character manipulation, communication protocols, and text formatting efficiently in embedded systems.

- [Data Structures in C](./Data_Structures.md)  
  ---  
  This document covers essential data structures in Embedded C, including `enum`, `struct`, `union`, `bitfield`, and `typedef`. It provides detailed explanations, examples, and practical applications of these data structures in embedded systems programming, helping to manage and organize data effectively for hardware configurations and efficient memory management.

- [Operators in C](./Operators.md)  
  ---  
  This document offers a comprehensive explanation of various operators in C programming, including **Arithmetic Operators**, **Relational Operators**, **Assignment Operators**, **Pre/Post Operators**, **Unary Operators**, and **Logical Operators**. It covers their usage with examples, helping to manipulate data, control flow, and perform complex computations effectively in embedded systems programming.

- [Loops and Control Flow in C](./Loops.md)  
  ---  
  A detailed guide to different loop structures in C, such as `while`, `do-while`, and `for`, along with control flow statements like `goto`, `break`, and `continue`, with practical examples and their applications in embedded systems.

- [Conditional Statements in C](./Conditional.md)  
  ---  
  A comprehensive guide to conditional statements in C, including the use of `if`, `else if`, `else`, the ternary operator, and `switch-case`, with examples and practical applications in embedded systems.

- [Standard I/O in C](./STDIO.md)  
  ---  
  This document offers a concise guide to key C programming concepts for embedded systems, including Format Specifiers, Literals, and functions like sprintf, snprintf, and sscanf. 

- [Functions in C](./Function.md)  
  ---  
  This document provides a detailed explanation of functions in Embedded C, covering topics such as function definition, function prototypes, parameters, return types, recursion, inline functions, and best practices for organizing code effectively in embedded systems programming.

- [Pointers in C](./Pointer.md)  
  ---  
  This document provides a comprehensive guide to pointers in Embedded C, including pointer declaration, dereferencing, pointer arithmetic, dynamic memory allocation, pointers to functions, and their applications in managing memory and hardware in embedded systems.

- [Type Casting in C](./Casting.md)  
  ---  
  This document provides an in-depth explanation of type casting in C for microcontrollers, covering both **implicit** and **explicit** casting, along with examples and potential pitfalls. It helps in understanding how to manage data types efficiently, ensuring correct behavior and preventing issues like data loss and undefined behavior in embedded systems programming.

- [Preprocessor in C](./Preprocessor.md)  
  ---  
  This document provides a comprehensive guide to preprocessor  in Embedded C, including the usage of `#define`, `#include`, conditional compilation, and compiler-specific directives like `#pragma`, `#error`, and `#warning`. It includes examples and best practices for optimizing code and managing hardware configurations efficiently in embedded systems.


## IV. 🧪 Unit Test trong Embedded C với Unity & Ceedling
Khi viết chương trình, đôi khi ta cần kiểm tra xem một hàm có thực thi đúng và cho ra kết quả mong muốn hay không.   
Để làm được điều đó, ta cần test hàm với các dữ liệu đầu vào khác nhau — đây chính là mục đích của **Unit Testing**.
### ⚙️ 1. Unity
Unity là một **framework unit test** dành riêng cho ngôn ngữ C, được thiết kế siêu nhẹ cho các hệ thống embedded (vi điều khiển, môi trường tài nguyên hạn chế).

🔹 **Tính năng chính:**
- Cho phép viết các **test case** để kiểm tra từng **hàm hoặc module nhỏ**.
- Có thể chạy test trên PC hoặc trên vi điều khiển thật.
- Có assertion (kiểm tra giá trị đúng/sai) như trong các framework test hiện đại.

📚 Nhấp vào link này để học: [Unity](https://github.com/Nguyen-Dang-Trieu/Learn_Embedded-C/tree/main/UNIT%20TESTING%20FOR%20C#i-unity)

### ⚙️2. Ceedling
Ceedling là một **công cụ tự động build & test** dành cho ngôn ngữ C, được phát triển bởi nhóm **ThrowTheSwitch** (tác giả của Unity).

🔹 **Ceedling giúp tự động hóa toàn bộ quá trình test, bao gồm:**
- Tạo cấu trúc project sẵn sàng cho test.
- Tích hợp Unity và CMock (hỗ trợ mô phỏng hàm phụ thuộc).
- Hỗ trợ build, chạy test và hiển thị báo cáo kết quả chỉ bằng một lệnh.

 📚 Nhấp vào link này để học: 

# 💻 How to Use Git and GitHub
To access the repository files and save them on your computer, there are two methods available:
1. **Using Git Bash and Cloning the Repository**
   - This method is more suitable for advanced users and those familiar with command-line tools.
   - By using this method, you can easily receive updates for the repository.

2. **Downloading the Repository as a ZIP file**
   - This method is simpler and suitable for users who are not comfortable with command-line tools.
   - Note that with this method, you will not automatically receive updates for the repository and will need to manually download any new updates.

## Clone using the URL.
First, open **Git Bash** :
-  Open the folder in **File Explorer** where you want the library to be stored.
-  **Right-click** inside the folder and select the option **"Open Git Bash here"** to open **Git Bash** in that directory.

![open Git Bash](Images/Step0.png)

> [!NOTE] 
> If you do not see the "Open Git Bash here" option, it means that Git is not installed on your system.  
> You can download and install Git from [this link](https://git-scm.com/downloads).  
> For a tutorial on how to install and use Git, check out [this video](https://youtu.be/BsykgHpmUt8).
  
-  Once **Git Bash** is open, run the following command to clone the repository:

 ```bash
git clone https://github.com/aKaReZa75/Embedded-C.git
```
- You can copy the above command by either:
- Clicking on the **Copy** button on the right of the command.
- Or select the command text manually and press **Ctrl + C** to copy.
- To paste the command into your **Git Bash** terminal, use **Shift + Insert**.

![Clone the Repository](Images/Step1.png)

- Then, press Enter to start the cloning operation and wait for the success message to appear.

![Open the Library File](Images/Step2.png)

> [!IMPORTANT]
> Please keep in mind that the numbers displayed in the image might vary when you perform the same actions.  
> This is because repositories are continuously being updated and expanded. Nevertheless, the overall process remains unchanged.

> [!NOTE]
> Advantage of Cloning the Repository:  
> - **Receiving Updates:** By cloning the repository, you can easily and automatically receive new updates.  
> - **Version Control:** Using Git allows you to track changes and revert to previous versions.  
> - **Team Collaboration:** If you are working on a project with a team, you can easily sync changes from team members and collaborate more efficiently.  

## Download Zip
If you prefer not to use Git Bash or the command line, you can download the repository directly from GitHub as a ZIP file.  
Follow these steps:  
1. Navigate to the GitHub repository page and Locate the Code button:
   - On the main page of the repository, you will see a green Code button near the top right corner.

2. Download the repository:
   - Click the Code button to open a dropdown menu.
   - Select Download ZIP from the menu.

  ![Download Zip](Images/Step7.png)  

3. Save the ZIP file:
   - Choose a location on your computer to save the ZIP file and click Save.

4. Extract the ZIP file:
   - Navigate to the folder where you saved the ZIP file.
   - Right-click on the ZIP file and select Extract All... (Windows) or use your preferred extraction tool.
   - Choose a destination folder and extract the contents.

5. Access the repository:
   - Once extracted, you can access the repository files in the destination folder.

> [!IMPORTANT]
> - No Updates: Keep in mind that downloading the repository as a ZIP file does not allow you to receive updates.    
>   If the repository is updated, you will need to download it again manually.  
> - Ease of Use: This method is simpler and suitable for users who are not comfortable with Git or command-line tools.

# 📝 How to Ask Questions
If you have any questions or issues, you can raise them through the **"Issues"** section of this repository. Here's how you can do it:  

1. Navigate to the **"Issues"** tab at the top of the repository page.  

  ![Issues](Images/Step3.png)

2. Click on the **"New Issue"** button.  
   
  ![New Issue](Images/Step4.png)

3. In the **Title** field, write a short summary of your issue or question.  

4. In the "Description" field, detail your question or issue as thoroughly as possible. You can use text formatting, attach files, and assign the issue to someone if needed. You can also use text formatting (like bullet points or code snippets) for better readability.  

5. Optionally, you can add **labels**, **type**, **projects**, or **milestones** to your issue for better categorization.  

6. Click on the **"Submit new issue"** button to post your question or issue.
   
  ![Submeet New Issue](Images/Step5.png)

I will review and respond to your issue as soon as possible. Your participation helps improve the repository for everyone!  

> [!TIP]
> - Before creating a new issue, please check the **"Closed"** section to see if your question has already been answered.  
>   ![Closed section](Images/Step6.png)  
> - Write your question clearly and respectfully to ensure a faster and better response.  
> - While the examples provided above are in English, feel free to ask your questions in **Persian (فارسی)** as well.  
> - There is no difference in how they will be handled!  

> [!NOTE]
> Pages and interfaces may change over time, but the steps to create an issue generally remain the same.

