USE Library
GO
--用户自定义函数是否已存在，存在则drop
IF ( EXISTS ( SELECT * FROM sysobjects WHERE id = object_id(N'[dbo].[fun_QborrowAnalysis]')
				AND ( type = 'TF')))
	DROP FUNCTION fun_QborrowAnalysis
GO

--创建用户自定义函数
CREATE FUNCTION fun_QborrowAnalysis ()
RETURNS @fun_QborrowAnalysis TABLE(Btitle NVARCHAR(100),borrowedTimes SMALLINT,averAge float)
AS
Begin
	insert @fun_QborrowAnalysis
	select Btitle,count(*),averAge=convert(decimal(4,1),avg(cast(r.Rage as float)))
    FROM book bk,
    	Borrow br,
    	Reader r
    WHERE br.Bno = bk.Bno
    	AND br.Rno = r.Rno
	group by Btitle
return 
END
GO

--测试用户自定义函数
SELECT *
FROM fun_QborrowAnalysis()
