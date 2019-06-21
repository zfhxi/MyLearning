USE Library
GO
IF ( EXISTS ( SELECT * FROM sysobjects WHERE name = 'proc_Qborrow' AND type = 'P'))
DROP PROC proc_Qborrow
GO

CREATE PROCEDURE proc_Qborrow @Rname NVARCHAR(100) = '黄河'
AS
BEGIN
	SELECT Btitle,
		BorrowDate,
		Bauthor
	FROM Book bk,
		Reader r,
		Borrow br
	WHERE r.Rno = br.Rno
		AND bk.Bno = br.Bno
		AND r.Rname = @Rname
END
GO

USE Library

--测试存储过程
DECLARE @name NVARCHAR(100)
SET @name = '黄河'
exec proc_Qborrow @name
GO