/*
backup database test2
to disk='d:\exercise\test2bak.bak'
*/

--完全备份
--来自https://bbs.csdn.net/topics/390084088
go
create procedure proc_BackupDB 
    @dbName nvarchar(max),
	@bakFilePath nvarchar(max)
as
begin
    BACKUP DATABASE @dbName TO DISK=@bakFilePath
    WITH NOFORMAT,INIT
end
go