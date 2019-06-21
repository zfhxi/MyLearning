sp_addlogin 'SQLTeacher','hello','Library';
go
use Library
go
create user SQLTeacher for login SQLTeacher
go
sp_addrolemember 'db_datareader','SQLTeacher' --给读权限
go
grant insert,delete on Book to SQLTeacher; --给插入、以及删除权限
grant update on Book(Bauthor) to SQLTeacher; --给修改权限
go