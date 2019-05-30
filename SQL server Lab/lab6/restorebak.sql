--restore HEADERONLY from disk ='D:\01DevelopToos\MSSQL\DEMO\Library.bak'	--1.
--restore filelistonly from disk ='D:\01DevelopToos\MSSQL\DEMO\Library.bak'	--2.
--/*
restore database Library from disk='D:\01DevelopToos\MSSQL\DEMO\Library.bak'
with FILE=3,
move 'Library' to 'D:\01DevelopToos\MSSQL\DEMO\Library.mdf',
move 'Library_Log' to 'D:\01DevelopToos\MSSQL\DEMO\Library.ldf',
nounload,stats=10

use Library
select name from sys.tables
--*/

