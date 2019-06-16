/*
restore database test2 from disk='d:\exercise\test2bak.bak'
go
*/
--覆盖式还原
--来自https://blog.csdn.net/Candy_GL/article/details/79239622
use master
go

if exists (select 1
          from sysobjects
          where  id = object_id('proc_RestoreDB')
          and type in ('P','PC'))
   drop procedure proc_RestoreDB
go


create procedure proc_RestoreDB 
    @dbName nvarchar(max),
	@bakFilePath nvarchar(max)
as
begin
    --1.1修改为单用模式  
    exec(N'ALTER DATABASE '+@dbName+' SET SINGLE_USER WITH ROLLBACK IMMEDIATE');  
    --1.2结束链接进程  
    DECLARE @kid varchar(max)    
    SET @kid=''    
    SELECT @kid=@kid+'KILL '+CAST(spid as Varchar(10))  FROM master..sysprocesses    
    WHERE dbid=DB_ID(@dbName)  ;  
    EXEC(@kid) ;  
    --2.执行还原语句  
    restore database @dbName from  disk=@bakFilePath  
    with replace  --覆盖现有的数据库  
    --3.重置数据库为多用户模式  
    exec(N'ALTER DATABASE '+@dbName+' SET MULTI_USER WITH ROLLBACK IMMEDIATE'); 
end
go

use CzmJavaWeb
go