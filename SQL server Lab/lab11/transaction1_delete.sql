USE Library
GO

BEGIN TRANSACTION del_reader

DELETE FROM Borrow WHERE Rno IN (
		SELECT Rno
		FROM Reader
		WHERE Rname = '赵楠'
		)
DELETE FROM Reader WHERE Rname = '赵楠'

COMMIT TRANSACTION del_reader
GO