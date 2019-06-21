USE Library
GO
--用户自定义函数是否已存在，存在则drop
IF(EXISTS(SELECT* FROM sysobjects where id =object_id(N'[dbo].[fun_QborrowDate]')AND (type='FN' OR type='TN')))
DROP FUNCTION fun_QborrowDate
go
--创建用户自定义函数
create FUNCTION fun_QborrowDate(@Rname nvarchar(10),@Btitle nvarchar(100))
returns date
as BEGIN
    DECLARE @br_date date
    select @br_date=br.BorrowDate from book bk,Borrow br,Reader r
    where br.Bno=bk.Bno
        and br.Rno=r.Rno
        and r.Rname=@Rname
        and bk.Btitle=@Btitle
    return @br_date
end
go

--测试用户自定义函数
declare @borrowDate date
exec @borrowDate=fun_QborrowDate '王小明','数据结构'
PRINT '王小明同学在'+CONVERT(nvarchar(20),@borrowDate)+'借了数据结构'