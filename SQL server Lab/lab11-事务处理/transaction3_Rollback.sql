USE Library
GO

BEGIN TRANSACTION borrow_english
DECLARE @borrowed_cnt SMALLINT

SELECT @borrowed_cnt = count(*)
FROM Borrow br,
	Book bk
WHERE br.Bno = bk.Bno
	AND bk.Btitle = '英语世界'

IF @borrowed_cnt < 2
BEGIN
	INSERT INTO Borrow
	VALUES ( 10, 'R01', 'B06', '2019-05-07', NULL)
	COMMIT
	PRINT '《英语世界》借阅成功！'
END
ELSE
BEGIN
	ROLLBACK TRANSACTION
	PRINT '《英语世界》借阅失败！'
END

GO


