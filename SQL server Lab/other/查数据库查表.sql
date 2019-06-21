-- show databases name
SELECT name
FROM master..sysdatabases
WHERE name NOT IN ('master', 'tempdb', 'msdb', 'pubs', 'northwind', 'model')

-- show tables
use sales
select name from sys.tables
--SELECT * from INFORMATION_SCHEMA.COLUMNS where TABLE_NAME='customers'
exec sp_help 'orders'