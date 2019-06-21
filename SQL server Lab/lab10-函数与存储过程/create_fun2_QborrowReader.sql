USE Library
GO
--用户自定义函数是否已存在，存在则drop
IF ( EXISTS ( SELECT * FROM sysobjects WHERE id = object_id(N'[dbo].[fun_QborrowReader]')
				AND ( type = 'FN' OR type = 'TN' OR type = 'IF')))
	DROP FUNCTION fun_QborrowReader
GO

--创建用户自定义函数
CREATE FUNCTION fun_QborrowReader (@Btitle NVARCHAR(100))
RETURNS TABLE
AS
RETURN
    SELECT TOP 100 r.Rname,
    	r.Rage,
    	r.Reducation,
    	br.BorrowDate,
    	br.ReturnDate
    FROM book bk,
    	Borrow br,
    	Reader r
    WHERE br.Bno = bk.Bno
    	AND br.Rno = r.Rno
    	AND bk.Btitle = @Btitle
    ORDER BY BorrowDate DESC
GO

--测试用户自定义函数
SELECT *
FROM fun_QborrowReader('数据结构')
