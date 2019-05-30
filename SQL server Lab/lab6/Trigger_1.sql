USE Library
GO

-- Copy Reader, Borrow into r_test and b_test to be as test data
SELECT * INTO r_test FROM Reader
SELECT * INTO b_test FROM Borrow
GO

-- Create the trigger
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE TRIGGER RDel_Reminder ON.r_test
AFTER DELETE
AS
BEGIN
	SET NOCOUNT ON;
	DELETE FROM b_test
	WHERE Rno = (
			SELECT Rno
			FROM deleted
			)
END
GO

-- test the trigger
DELETE FROM r_test WHERE Rno = 'R03'
SELECT * FROM r_test
SELECT * FROM b_test
