USE Library
GO

BEGIN TRANSACTION trans1
UPDATE Book SET Bprice = 999 WHERE Bno = 'B01' 
WAITFOR DELAY '00:00:10';
ROLLBACK TRANSACTION