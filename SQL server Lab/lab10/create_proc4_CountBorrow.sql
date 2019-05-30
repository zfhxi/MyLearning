USE Library
GO
--如果已存在该存储过程，drop掉
IF ( EXISTS ( SELECT * FROM sysobjects WHERE name = 'proc_CountBorrow' AND type = 'P'))
DROP PROC proc_CountBorrow
GO

--创建存储过程
CREATE PROCEDURE proc_CountBorrow @Btitle NVARCHAR(100),
	@BorrowCnt smallint output
AS
BEGIN
	SELECT @BorrowCnt=count(DISTINCT Rno)
	FROM Book bk,Borrow Br
	WHERE br.Bno = bk.Bno
		AND @Btitle = bk.Btitle
END
GO
USE Library

--测试存储过程
DECLARE @B_title NVARCHAR(100),
	@BorrowCnt smallint

SELECT @B_title='数据结构'
exec proc_CountBorrow  @B_title,
	@BorrowCnt output

DECLARE @str NVARCHAR(100),@str2 NVARCHAR(100)
SET @str='借阅《'+@B_title+'》人数：'+CONVERT(NVARCHAR(5),@BorrowCnt)
PRINT @str
GO