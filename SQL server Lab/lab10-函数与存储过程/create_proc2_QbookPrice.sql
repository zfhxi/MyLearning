USE Library
GO
--如果已存在该存储过程，drop掉
IF ( EXISTS ( SELECT * FROM sysobjects WHERE name = 'proc_Qprice' AND type = 'P'))
DROP PROC proc_Qprice
GO

--创建存储过程
CREATE PROCEDURE proc_Qprice
AS
BEGIN
	SELECT max(Bprice) as maxPrice,
	min(Bprice) as minPrice
	FROM Book
END
GO

USE Library

--测试存储过程
exec proc_Qprice
GO