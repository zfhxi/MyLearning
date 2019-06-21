USE Library
GO
--如果已存在该存储过程，drop掉
IF ( EXISTS ( SELECT * FROM sysobjects WHERE name = 'proc_QborrowReader' AND type = 'P'))
DROP PROC proc_QborrowReader
GO

--创建存储过程
CREATE PROCEDURE proc_QborrowReader @Btitle NVARCHAR(100)
AS
BEGIN
	SELECT r.Rname,r.Rage,r.Reducation,br.BorrowDate,br.ReturnDate
	FROM Book bk,Borrow Br,Reader r
	WHERE br.Bno = bk.Bno
		AND br.Rno=r.Rno
		AND @Btitle = bk.Btitle
END
GO
USE Library

--测试存储过程
DECLARE @B_title NVARCHAR(100)

SELECT @B_title='操作系统概论'
exec proc_QborrowReader  @B_title
GO