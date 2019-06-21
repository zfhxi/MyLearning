USE Library
GO
--如果已存在该存储过程，drop掉
IF ( EXISTS ( SELECT * FROM sysobjects WHERE name = 'proc_QborrowDetail' AND type = 'P'))
DROP PROC proc_QborrowDetail
GO

--创建存储过程
CREATE PROCEDURE proc_QborrowDetail
	@Rname NVARCHAR(10),
	@Btitle NVARCHAR(100),
	@Bauthor NVARCHAR(50) OUTPUT,
	@Bprice FLOAT OUTPUT,
	@BorrowDate DATE OUTPUT,
	@ReturnDate DATE OUTPUT
AS
BEGIN
	SELECT @Bauthor=Bauthor,
		@Bprice=Bprice,
		@BorrowDate=BorrowDate,
		@ReturnDate=ReturnDate
	FROM Book bk,Reader r,Borrow Br
	WHERE br.Bno = bk.Bno
		AND br.Rno = r.Rno
		AND @Rname = r.Rname
		AND @Btitle = bk.Btitle
END
GO
USE Library

--测试存储过程
DECLARE @R_name NVARCHAR(10),
	@B_title NVARCHAR(100),
	@B_author NVARCHAR(50),
	@B_price FLOAT,
	@Borrow_Date DATE,
	@Return_Date DATE

SELECT @R_name='范君',@B_title='数据结构'
exec proc_QborrowDetail @R_name,
	@B_title,
	@B_author OUTPUT,
	@B_price OUTPUT,
	@Borrow_Date OUTPUT,
	@Return_Date OUTPUT
--输出返回值
PRINT @B_author
PRINT @B_price
PRINT @Borrow_Date
PRINT @Return_Date
GO