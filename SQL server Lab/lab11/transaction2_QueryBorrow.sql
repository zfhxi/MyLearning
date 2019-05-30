USE Library
GO

BEGIN TRANSACTION query_borrow

DECLARE @borrowed_cnt SMALLINT

SELECT @borrowed_cnt = count(*)
FROM Borrow br,
	Book bk
WHERE br.Bno = bk.bno
	AND bk.Btitle = '数据结构'

IF @borrowed_cnt < 5
	PRINT '馆中存有《数据结构》可借'
ELSE
	PRINT '馆中不存有《数据结构》可借'

COMMIT TRANSACTION query_borrow
GO


