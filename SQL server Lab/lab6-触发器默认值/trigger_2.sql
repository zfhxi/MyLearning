USE Library

-- create table Borrow_Count
SELECT Bno AS Bno, count(*) AS BorrowTimes INTO Borrow_Count
FROM Borrow GROUP BY Bno

SELECT * FROM Borrow_Count
GO

-- create Trigger
CREATE TRIGGER updateCt ON.Borrow
AFTER INSERT
AS
BEGIN
	UPDATE Borrow_Count
	SET BorrowTimes = BorrowTimes + 1
	WHERE Bno = (
			SELECT Bno
			FROM inserted
			)
END
GO

PRINT 'A trigger has been created! '

INSERT INTO Borrow ( Borrnum, Rno, Bno)
VALUES ( 13, 'R05', 'B06')

PRINT 'After insert new column into Borrow……'
SELECT * FROM Borrow_Count
