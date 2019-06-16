-- Create DB sample_2
USE master
GO

CREATE DATABASE test2 ON PRIMARY (
	name = prim_sub1,
	filename = 'd:\exercise\prim_sub1_dat.mdf',
	size = 6 mb,
	maxsize = 20 mb,
	filegrowth = 20 %
	),
	(
	name = prim_sub2,
	filename = 'd:\exercise\prim_sub2_dat.ndf',
	size = 6 mb,
	maxsize = 20 mb,
	filegrowth = 20 %
	),
	filegroup grouptest1 (
	name = group1_sub1,
	filename = 'd:\exercise\group1_sub1_dat.ndf',
	size = 6 mb,
	maxsize = 20 mb,
	filegrowth = 5 mb
	),
	filegroup grouptest2 (
	name = group2_sub1,
	filename = 'd:\exercise\group2_sub1_dat.ndf',
	size = 6 mb,
	maxsize = 20 mb,
	filegrowth = 15 %
	),
	(
	name = group2_sub2,
	filename = 'd:\exercise\group2_sub2_dat.ndf',
	size = 6 mb,
	maxsize = 20 mb,
	filegrowth = 15 %
	) log ON (
	name = test2_log,
	filename = 'd:\exercise\test2_log.ldf',
	size = 6 mb,
	maxsize = 20 mb,
	filegrowth = 5 mb
	)
